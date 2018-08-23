#include "htree/impl/HealthTreeImpl.h"
#include "htree/impl/NodeImpl.h"
#include "htree/impl/YamlParser.h"
#include <boost/filesystem.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/mutex.hpp>
#include <fstream>
#include <stdexcept>
#include <utility>
#include <yaml-cpp/yaml.h>

namespace htree { namespace impl {

HealthTreeImpl::HealthTreeImpl(const std::string& name)
: root_(name),
  dag_(new DAG),
  lock_(new boost::mutex)
{
    createNode(root_);
}

HealthTreeImpl::~HealthTreeImpl()
{
}

void HealthTreeImpl::addDependency(const Dependency&    dep,
                                   const std::string&   node)
{
    node_ptr parentNode = createNode((node == ROOT) ? root_ : node);
    node_ptr depNode    = createNode(dep.name());

    parentNode->addDependency(depNode);
}

void HealthTreeImpl::load(const std::string& path)
{
    boost::filesystem::path p(path);

    if(!boost::filesystem::is_regular(p)) {
        throw std::runtime_error("");
    }

    loadFile(p);
}

void HealthTreeImpl::loadFile(const boost::filesystem::path& p)
{

    YAML::Node yml = YAML::LoadFile(p.string());

    if(!yml.IsMap()) {
        throw std::runtime_error("Invalid YML configuration");
    }

    for(YAML::const_iterator outer = yml.begin(); outer != yml.end(); ++outer) {
        node_ptr n = createNode(outer->first.as<std::string>());

        if(!outer->second.IsMap()) {
            throw std::runtime_error(std::string("Expected " + n->name() + " to be a map"));
        }

        YamlParser parser(n, *this);
        parser.load(outer->second);

    }

    LOG_DEBUG(logger_)  << "Loaded file: " << p;
}

void HealthTreeImpl::print(std::ostream& ostr)
{
    boost::write_graphviz(ostr, *dag_, boost::make_label_writer(boost::get(&Vertex::name, *dag_)));
}

node_ptr HealthTreeImpl::createNode(const std::string& name)
{
    boost::mutex::scoped_lock scopedLock(*lock_);

    node_map::const_iterator iter = nodes_.find(name);
    if(iter != nodes_.end()) {
        return iter->second;
    }

    node_ptr node = boost::make_shared<NodeImpl>(name, dag_);
    nodes_[name] = node;

    LOG_DEBUG(logger_) << "Created HealthTree node: " << name;

    return node;
}

}} /* namespace htree */
