#include "htree/impl/htree_impl_fwds.h"
#include "htree/impl/NodeImpl.h"
#include "logger/Logger.h"

namespace htree {
namespace impl {

NodeImpl::NodeImpl(const std::string&       name,
                   boost::shared_ptr<DAG>   dag)
: name_(name),
  vertex_(boost::add_vertex(*dag)),
  dag_(dag)
{
    (*dag)[vertex_].name = name;
}

NodeImpl::~NodeImpl()
{
}

const std::string& NodeImpl::name() const
{
    return name_;
}

const std::string& NodeImpl::description() const
{
    return description_;
}

void NodeImpl::description(const std::string& desc)
{
    description_ = desc;
}

void NodeImpl::addDependency(boost::shared_ptr<const Node> other)
{
    auto otherPtr = boost::dynamic_pointer_cast<const NodeImpl>(other);

    std::pair<DAG::edge_descriptor, bool> result = boost::add_edge(vertex_,
                                                                   otherPtr->vertex_,
                                                                   *dag_);

    if(result.second) {
        LOG_DEBUG(logger_)  << "Created HealthTree dependency: "
                            << name() << " -> " << other->name();
    }
}

} /* namespace impl */
} /* namespace htree */
