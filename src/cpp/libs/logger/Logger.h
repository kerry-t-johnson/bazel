
#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <boost/log/expressions/keyword.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <iostream>
#include <string>
#include <sys/types.h>

#define LOG_WITH_COMMON_ATTRS(theLogger, theSeverity)                   \
    BOOST_LOG(theLogger)                                                \
        << boost::log::add_value("severity_level", theSeverity)         \
        << boost::log::add_value("line", __LINE__)                      \
        << boost::log::add_value("file", __FILE__)                      \
        << boost::log::add_value("function", BOOST_CURRENT_FUNCTION)

#define LOG_EMERGENCY(theLogger)                                        \
    LOG_WITH_COMMON_ATTRS(theLogger, logger::emergency)

#define LOG_ALERT(theLogger)                                            \
    LOG_WITH_COMMON_ATTRS(theLogger, logger::alert)

#define LOG_CRITICAL(theLogger)                                         \
    LOG_WITH_COMMON_ATTRS(theLogger, logger::critical)

#define LOG_ERROR(theLogger)                                            \
    LOG_WITH_COMMON_ATTRS(theLogger, logger::error)

#define LOG_WARNING(theLogger)                                          \
    LOG_WITH_COMMON_ATTRS(theLogger, logger::warning)

#define LOG_NOTICE(theLogger)                                           \
    LOG_WITH_COMMON_ATTRS(theLogger, logger::notice)

#define LOG_INFO(theLogger)                                             \
    LOG_WITH_COMMON_ATTRS(theLogger, logger::informational)

#define LOG_DEBUG(theLogger)                                            \
    LOG_WITH_COMMON_ATTRS(theLogger, logger::debug)

namespace logger {

enum severity {
    emergency = 0,
    alert,
    critical,
    error,
    warning,
    notice,
    informational,
    debug
};

BOOST_LOG_ATTRIBUTE_KEYWORD(severity_level, "severity_level", logger::severity)
BOOST_LOG_ATTRIBUTE_KEYWORD(line_number, "line", int)
BOOST_LOG_ATTRIBUTE_KEYWORD(file_name, "file", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(function_name, "function", std::string)

typedef boost::log::sources::severity_logger<severity> Logger;

std::ostream& operator<<(std::ostream& ostr, severity value);

} /* namespace logger */

#endif /* LOGGER_LOGGER_H_ */
