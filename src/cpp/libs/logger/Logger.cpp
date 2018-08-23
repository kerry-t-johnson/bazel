
#include "Logger.h"
#include <boost/log/attributes.hpp>

namespace logger {

void init(int argc, char** argv)
{

}

std::ostream& operator<< (std::ostream& strm, severity level)
{
    switch(level) {
    case emergency:
        strm << "emergency";
        break;
    case alert:
        strm << "alert";
        break;
    case critical:
        strm << "critical";
        break;
    case error:
        strm << "error";
        break;
    case warning:
        strm << "warning";
        break;
    case notice:
        strm << "notice";
        break;
    case informational:
        strm << "informational";
        break;
    case debug:
        strm << "debug";
        break;
    default:
        strm << static_cast<int>(level);
    }

    return strm;
}

} /* namespace logger */
