
#include "GZip.h"

#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

namespace util {

std::string GZip::compress(const std::string& data)
{
    std::stringstream origin(data);

    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    out.push(boost::iostreams::gzip_compressor(boost::iostreams::gzip_params(boost::iostreams::gzip::best_compression)));
    out.push(origin);

    std::stringstream compressed;
    boost::iostreams::copy(out, compressed);

    return compressed.str();
}

std::string GZip::uncompress(const std::string& data)
{
    std::stringstream compressed(data);

    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    out.push(boost::iostreams::gzip_decompressor());
    out.push(compressed);

    std::stringstream decompressed;
    boost::iostreams::copy(out, decompressed);

    return decompressed.str();
}

} // namespace util
