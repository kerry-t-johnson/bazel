#ifndef HTREE_IMPL_NODEIMPL_H_
#define HTREE_IMPL_NODEIMPL_H_

#include "htree/Node.h"
#include "htree/impl/htree_impl_fwds.h"
#include "logger/Logger.h"
#include <boost/enable_shared_from_this.hpp>
#include <string>

namespace htree {
namespace impl {

class NodeImpl: public Node,
                public boost::enable_shared_from_this<Node>
{
public:
    NodeImpl(const std::string&     name,
             boost::shared_ptr<DAG> dag);
    virtual ~NodeImpl();


    virtual const std::string& name() const;

    virtual const std::string& description() const;
    virtual void description(const std::string& desc);

    virtual void addDependency(boost::shared_ptr<const Node> other);

private:

    const std::string               name_;
    const DAG::vertex_descriptor    vertex_;
    std::string                     description_;
    boost::shared_ptr<DAG>          dag_;
    logger::Logger                  logger_;

};

} /* namespace impl */
} /* namespace htree */

#endif /* HTREE_IMPL_NODEIMPL_H_ */
