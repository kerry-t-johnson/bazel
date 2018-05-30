
#include "logger/GraylogMessage.h"
#include "logger/GraylogUdpWriter.h"
#include "logger/GraylogSink.h"
#include "logger/Logger.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/program_options.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("hostname,h", boost::program_options::value<std::string>()->value_name("hostname")->default_value("localhost"), "Graylog host")
        ("port,p", boost::program_options::value<uint16_t>()->value_name("port")->default_value(12201), "Graylog port")
        ("additional,a", boost::program_options::value<std::vector<std::string> >(), "Additional attributes as key=value")
        ("messages,m", boost::program_options::value<std::vector<std::string> >(), "Message(s) to send")
    ;

    // Hidden options, will be allowed both on command line and
    // in config file, but will not be shown to the user.
    boost::program_options::positional_options_description positional;
    positional.add("messages", -1 );

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc)
                                                                                         .positional(positional)
                                                                                         .run(),
                                  vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    typedef logger::GraylogSink                                         sink_backend_t;
    typedef boost::log::sinks::synchronous_sink<logger::GraylogSink>    sink_frontend_t;

    boost::shared_ptr<sink_backend_t> sinkBackend(new logger::GraylogSink(vm["hostname"].as<std::string>(),
                                                                          vm["port"].as<uint16_t>()));

    boost::shared_ptr<sink_frontend_t> sink(new sink_frontend_t(sinkBackend));

    boost::log::core::get()->add_sink(sink);

    logger::Logger logger;

    LOG_EMERGENCY(logger) << "This is an emergency";

    logger::GraylogUdpWriter udpWriter(vm["hostname"].as<std::string>(),
                                       vm["port"].as<uint16_t>());

    const std::vector<std::string> messages = vm["messages"].as<std::vector<std::string> >();
    for(std::vector<std::string>::const_iterator iter = messages.begin(); iter != messages.end(); ++iter) {
        LOG_INFO(logger) << *iter;

        LOG_ERROR(logger) << *iter;
//        logger::GraylogMessage msg(1,
//                                   *iter,
//                                   std::string("Full message - sent by ") + argv[0]);
//
//        const std::vector<std::string> additional = vm["additional"].as<std::vector<std::string> >();
//        for(std::vector<std::string>::const_iterator addIter = additional.begin(); addIter != additional.end(); ++addIter) {
//            std::vector<std::string> key_value;
//            boost::split(key_value, *addIter, boost::is_any_of("="));
//
//            if(key_value.size() != 2) {
//                throw std::runtime_error("Unable to parse additional value: " + *addIter);
//            }
//
//            msg.addField(key_value[0], key_value[1]);
//        }
//
//        udpWriter.write(msg);
    }

    std::cout << "Sent " << boost::lexical_cast<std::string>(messages.size()) << " messages";
}
