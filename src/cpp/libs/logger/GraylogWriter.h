
#ifndef LOGGER_GRAYLOGWRITER_H_
#define LOGGER_GRAYLOGWRITER_H_

namespace logger { class GraylogMessage; }

namespace logger {

class GraylogWriter
{
public:

    virtual void write(const GraylogMessage& msg) const = 0;

    virtual ~GraylogWriter() {}
};

} // namespace logger

#endif /* LOGGER_GRAYLOGWRITER_H_ */
