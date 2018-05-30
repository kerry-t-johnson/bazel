
#ifndef LOGGER_GRAYLOGUDPWRITER_H_
#define LOGGER_GRAYLOGUDPWRITER_H_

#include "GraylogWriter.h"
#include <boost/scoped_ptr.hpp>
#include <stdint.h>
#include <string>

namespace logger {

class GraylogUdpWriter: public GraylogWriter
{
public:
    GraylogUdpWriter(const std::string& host, uint16_t port, bool compress = true);
    virtual ~GraylogUdpWriter();

    virtual void write(const GraylogMessage& msg) const;

private:

    class Impl;

    boost::scoped_ptr<Impl>     impl_;
};

} // namespace logger

#endif /* LOGGER_GRAYLOGUDPWRITER_H_ */
