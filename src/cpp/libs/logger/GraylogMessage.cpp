#include "GraylogMessage.h"

#include <boost/asio/ip/host_name.hpp>
#include <boost/lexical_cast.hpp>
#include <Poco/JSON/Object.h>
#include <set>
#include <stdexcept>
#include <sys/time.h>

namespace { // anonymous
const std::set<std::string> BUILTIN_FIELDS{ "version", "host", "short_message", "full_message", "timestamp", "level", "id" };


std::string convertFieldName(const std::string& fieldName, bool strict = false)
{
    const bool isBuiltIn = BUILTIN_FIELDS.find(fieldName) != BUILTIN_FIELDS.end();

    if(isBuiltIn) {
        if(strict) {
            throw std::runtime_error("Illegal field name: " + fieldName);
        }
        else {
            return fieldName;
        }
    }
    else {
        return "_" + fieldName;
    }
}

class FieldImpl : public logger::Field {
public:

    FieldImpl(const std::string&                           fieldName,
              boost::shared_ptr<const Poco::JSON::Object>  json)
    : fieldName_(convertFieldName(fieldName)),
      json_(json)
    {}

    virtual const std::string getAsSting() const
    {
        return json_->get(fieldName_).toString();
    }

    virtual int8_t getAsInt8() const
    {
        return json_->get(fieldName_).convert<int8_t>();
    }

    virtual int16_t getAsInt16() const
    {
        return json_->get(fieldName_).convert<int16_t>();
    }

    virtual int32_t getAsInt32() const
    {
        return json_->get(fieldName_).convert<int32_t>();
    }

    virtual int64_t getAsInt64() const
    {
        return json_->get(fieldName_).convert<int64_t>();
    }

    virtual uint8_t getAsUInt8() const
    {
        return json_->get(fieldName_).convert<uint8_t>();
    }

    virtual uint16_t getAsUInt16() const
    {
        return json_->get(fieldName_).convert<uint16_t>();
    }

    virtual uint32_t getAsUInt32() const
    {
        return json_->get(fieldName_).convert<uint32_t>();
    }

    virtual uint64_t getAsUInt64() const
    {
        return json_->get(fieldName_).convert<uint64_t>();
    }

    virtual float getAsFloat() const
    {
        return json_->get(fieldName_).convert<float>();
    }

    virtual double getAsDouble() const
    {
        return json_->get(fieldName_).convert<double>();
    }

    virtual ~FieldImpl() {}

private:
    const std::string                           fieldName_;
    boost::shared_ptr<const Poco::JSON::Object> json_;
};

} // anonymous

namespace logger {

GraylogMessage::GraylogMessage(const uint8_t      level,
                               const std::string& shortMessage,
                               const std::string& fullMessage)
: impl_(new Poco::JSON::Object)
{
    ::timeval curTime;
    ::gettimeofday(&curTime, NULL);

	impl_->set("version", "1.1");
	impl_->set("host", boost::asio::ip::host_name());
	impl_->set("timestamp", static_cast<double>(curTime.tv_sec) + (static_cast<double>(curTime.tv_usec) / 1000000.0));
	impl_->set("short_message", shortMessage);
	impl_->set("level", level);

	if(!fullMessage.empty()) {
	    impl_->set("full_message", fullMessage);
	}
}

GraylogMessage::~GraylogMessage()
{
}

void GraylogMessage::addField(const std::string& fieldName,
                              const std::string& fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const uint8_t      fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const uint16_t     fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const uint32_t     fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const uint64_t     fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const int8_t       fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const int16_t      fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const int32_t      fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const int64_t      fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const float        fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

void GraylogMessage::addField(const std::string& fieldName,
                              const double       fieldValue)
{
    impl_->set(convertFieldName(fieldName, true), fieldValue);
}

std::ostream& operator<<(std::ostream& ostr, const GraylogMessage& msg)
{
    msg.impl_->stringify(ostr);
    return ostr;
}

boost::shared_ptr<const Field> GraylogMessage::getField(const std::string& fieldName) const
{
    return boost::shared_ptr<const Field>(new FieldImpl(fieldName, impl_));
}

} // namespace logger
