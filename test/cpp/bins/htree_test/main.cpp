
#include "htree/impl/Dependency.h"
#include "htree/impl/HealthTreeImpl.h"
#include "logger/Logger.h"
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("dot,d", boost::program_options::value<std::string>()->value_name("DOT/OUT/PATH"), "Dot file destination")
    ;

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc)
                                                                                         .run(),
                                  vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    logger::Logger logger;
    htree::impl::HealthTreeImpl impl;

    impl.load("test/cpp/bins/htree_test/test_data.yml");

    if(vm.count("dot")) {
        std::ofstream of(vm["dot"].as<std::string>(), std::ios_base::out | std::ios_base::trunc);
        impl.print(of);

        LOG_INFO(logger) << "Wrote DOT file: " << vm["dot"].as<std::string>();
    }

    return 0;
}
