#include <htree/impl/YamlParser.h>

#include "htree/impl/Dependency.h"
#include "htree/HealthTree.h"
#include "htree/Node.h"
#include <boost/algorithm/string.hpp>
#include <stdexcept>
#include <yaml-cpp/yaml.h>

namespace htree {
namespace impl {

YamlParser::YamlParser(node_ptr     node,
                       HealthTree&  tree)
: node_(node),
  tree_(tree)
{
}

YamlParser::~YamlParser()
{
}

void YamlParser::load(const YAML::Node& yml)
{
    for(YAML::const_iterator iter = yml.begin(); iter != yml.end(); ++iter) {
        const std::string key = iter->first.as<std::string>();
        if(key == "description") {
            processDescription(iter->second);
        }
        else if(key == "dependencies") {
            processDependencies(iter->second);
        }
    }
}

void YamlParser::processDescription(const YAML::Node& yml)
{
    const std::string descString = boost::trim_copy(boost::replace_all_copy(yml.as<std::string>(),
                                                                            "\n",
                                                                            " "));

    node_->description(descString);
}

void YamlParser::processDependencies(const YAML::Node& yml)
{
    for(YAML::const_iterator diter = yml.begin(); diter != yml.end(); ++diter) {
        processDependency(*diter);
    }
}

void YamlParser::processDependency(const YAML::Node& yml)
{
    if(yml.IsScalar()) {
        const std::string dname = yml.as<std::string>();
        boost::shared_ptr<Node> dnode = tree_.createNode(dname);

        Dependency d(dname);
        node_->addDependency(dnode);
    }
    else if(yml.IsMap()) {
        processComplexDependency(yml);
    }
}

void YamlParser::processComplexDependency(const YAML::Node& yml)
{
    if(!yml["name"]) {
        throw std::runtime_error("ComplexDependency name not specified");
    }

    if(!yml["type"]) {
        throw std::runtime_error("ComplexDependency type not specified");
    }

    const std::string name = yml["name"].as<std::string>();
    const std::string type = boost::algorithm::to_lower_copy(yml["type"].as<std::string>());

    if(type == "composite") {
        boost::shared_ptr<Node> dnode = tree_.createNode(name);

        Dependency d(name);
        node_->addDependency(dnode);
    }
}

} /* namespace impl */
} /* namespace htree */
