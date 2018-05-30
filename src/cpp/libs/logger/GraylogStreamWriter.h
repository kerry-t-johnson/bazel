
#ifndef LOGGER_GRAYLOGSTREAMWRITER_H_
#define LOGGER_GRAYLOGSTREAMWRITER_H_

#include "GraylogWriter.h"
#include <ostream>

namespace logger {

class GraylogStreamWriter: public GraylogWriter
{
public:
    GraylogStreamWriter(std::ostream& ostr);
    virtual ~GraylogStreamWriter();

    virtual void write(const GraylogMessage& msg) const;

private:
    std::ostream& ostr_;
};

} // namespace logger

#endif /* LOGGER_GRAYLOGSTREAMWRITER_H_ */
