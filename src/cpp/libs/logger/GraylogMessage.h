
#ifndef LOGGER_GRAYLOGMESSAGE_H_
#define LOGGER_GRAYLOGMESSAGE_H_

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <ostream>
#include <stdint.h>
#include <string>

namespace Poco { namespace JSON { class Object; }}

namespace logger {

class Field {
public:
    virtual const std::string  getAsSting()  const = 0;
    virtual int8_t             getAsInt8()   const = 0;
    virtual int16_t            getAsInt16()  const = 0;
    virtual int32_t            getAsInt32()  const = 0;
    virtual int64_t            getAsInt64()  const = 0;
    virtual uint8_t            getAsUInt8()  const = 0;
    virtual uint16_t           getAsUInt16() const = 0;
    virtual uint32_t           getAsUInt32() const = 0;
    virtual uint64_t           getAsUInt64() const = 0;
    virtual float              getAsFloat()  const = 0;
    virtual double             getAsDouble() const = 0;

    virtual ~Field() {}
};

class GraylogMessage {
public:
	GraylogMessage(const uint8_t       level,
	               const std::string&  shortMessage,
	               const std::string&  fullMessage = "");
	virtual ~GraylogMessage();

	void addField(const std::string& fieldName,
	              const std::string& fieldValue);

    void addField(const std::string& fieldName,
                  const uint8_t      fieldValue);

    void addField(const std::string& fieldName,
                  const uint16_t     fieldValue);

    void addField(const std::string& fieldName,
                  const uint32_t     fieldValue);

    void addField(const std::string& fieldName,
                  const uint64_t     fieldValue);

    void addField(const std::string& fieldName,
                  const int8_t       fieldValue);

    void addField(const std::string& fieldName,
                  const int16_t      fieldValue);

    void addField(const std::string& fieldName,
                  const int32_t      fieldValue);

    void addField(const std::string& fieldName,
                  const int64_t      fieldValue);

    void addField(const std::string& fieldName,
                  const float        fieldValue);

    void addField(const std::string& fieldName,
                  const double       fieldValue);

    boost::shared_ptr<const Field> getField(const std::string& fieldName) const;

    friend std::ostream& operator<<(std::ostream&, const GraylogMessage&);

private:

	boost::shared_ptr<Poco::JSON::Object> impl_;
};

} // namespace logger

#endif /* LOGGER_GRAYLOGMESSAGE_H_ */
