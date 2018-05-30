
#include "GraylogUdpWriter.h"

#include "GraylogMessage.h"
#include "util/Chunker.h"
#include "util/GZip.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

namespace { // anonymous
    const char CHUNKED_GELF_MAGIC[2] = { 0x1e, 0x0f };
    const std::size_t GELF_HEADER_SIZE =   2  // GELF Magic
                                         + 8  // Message ID
                                         + 1  // Sequence Number
                                         + 1; // Sequence Count

    const std::size_t GELF_CHUNK_SIZE = 8192 / 2;

    boost::random::mt19937_64 randGen;
    boost::uniform_int<uint64_t> uInt64Dist(0, std::numeric_limits<uint64_t>::max());
    boost::variate_generator<boost::mt19937_64&, boost::uniform_int<uint64_t> > getRand(randGen, uInt64Dist);
}

namespace logger {

class GraylogUdpWriter::Impl
{
public:
    Impl(const std::string& host, uint16_t port, bool compress)
    : compress_(compress),
      dataChunker_(GELF_CHUNK_SIZE)
    {
        boost::asio::ip::udp::resolver resolver(service_);
        boost::asio::ip::udp::resolver::query query(host, std::to_string(port));
        endpoint_ = *resolver.resolve(query);
        socket_.reset(new boost::asio::ip::udp::socket(service_, endpoint_.protocol()));
    }
    virtual ~Impl() {}

    virtual void write(const GraylogMessage& msg) const
    {
        const std::string json = boost::lexical_cast<std::string>(msg);
        const std::string marshalled = (compress_ && json.length() > GELF_CHUNK_SIZE) ? util::GZip::compress(json)
                                                                                      : json;

        const std::vector<std::string> chunks = dataChunker_.chunk(marshalled);

        const uint64_t message_id = getRand();

        for(std::size_t i = 0; i < chunks.size(); ++i) {
            std::string gelfUdpMessage;
            gelfUdpMessage.reserve(GELF_HEADER_SIZE + chunks[i].length());

            gelfUdpMessage.append(CHUNKED_GELF_MAGIC, 2);
            gelfUdpMessage.append(reinterpret_cast<const char*>(&message_id), 8);
            gelfUdpMessage.push_back(static_cast<char>(i & 0x7F));
            gelfUdpMessage.push_back(static_cast<char>(chunks.size() & 0x7F));

            gelfUdpMessage.append(chunks[i].begin(), chunks[i].end());

            socket_->async_send_to(boost::asio::buffer(gelfUdpMessage),
                                   endpoint_,
                                   boost::bind(&Impl::write_handler,
                                               this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
        }
    }

private:

    void write_handler(const boost::system::error_code& ec,
                       std::size_t                      bytes_transferred) const
    {
        if(ec) {
            // TODO
        }
    }

    bool                                            compress_;
    util::Chunker                                   dataChunker_;
    boost::asio::io_service                         service_;
    boost::asio::ip::udp::endpoint                  endpoint_;
    boost::scoped_ptr<boost::asio::ip::udp::socket> socket_;
};

GraylogUdpWriter::GraylogUdpWriter(const std::string& host, uint16_t port, bool compress)
: impl_(new Impl(host, port, compress))
{
}

GraylogUdpWriter::~GraylogUdpWriter()
{
}

void GraylogUdpWriter::write(const GraylogMessage& msg) const
{
    impl_->write(msg);
}

} // namespace logger
