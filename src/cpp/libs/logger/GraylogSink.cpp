

#include "GraylogSink.h"
#include "GraylogMessage.h"
#include "GraylogUdpWriter.h"
#include "Logger.h"
#include <boost/log/attributes/value_extraction.hpp>
#include <boost/log/expressions/message.hpp>
#include <boost/log/trivial.hpp>

namespace logger {

GraylogSink::GraylogSink(const std::string& graylogHost, uint16_t graylogPort)
: impl_(new GraylogUdpWriter(graylogHost, graylogPort))
{

}

GraylogSink::~GraylogSink()
{
}

void GraylogSink::consume(boost::log::record_view const& rec)
{
    boost::log::value_ref<severity, tag::severity_level>    severitylevel   = rec[severity_level];
    boost::log::value_ref<int, tag::line_number>            linenumber      = rec[line_number];
    boost::log::value_ref<std::string, tag::file_name>      filename        = rec[file_name];
    boost::log::value_ref<std::string, tag::function_name>  functionName    = rec[function_name];

    GraylogMessage msg(severitylevel ? severitylevel.get() : 0,
                       rec[boost::log::expressions::smessage].get());

    if(linenumber) {
        msg.addField("line", linenumber.get());
    }

    if(filename) {
        msg.addField("file", filename.get());
    }

    if(functionName) {
        msg.addField("function", functionName.get());
    }

    impl_->write(msg);
}

} /* namespace logger */
