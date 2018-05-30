

#ifndef LOGGER_GRAYLOGSINK_H_
#define LOGGER_GRAYLOGSINK_H_

#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/scoped_ptr.hpp>

namespace logger { class GraylogUdpWriter; }

namespace logger {

class GraylogSink : public boost::log::sinks::basic_sink_backend<boost::log::sinks::concurrent_feeding>
{
public:
    GraylogSink(const std::string& graylogHost, uint16_t graylogPort);
    virtual ~GraylogSink();

    void consume(boost::log::record_view const& rec);

private:

    boost::scoped_ptr<GraylogUdpWriter> impl_;
};

} /* namespace logger */

#endif /* LOGGER_GRAYLOGSINK_H_ */
