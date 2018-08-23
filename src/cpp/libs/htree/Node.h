#ifndef HTREE_IMPL_NODE_H_
#define HTREE_IMPL_NODE_H_

#include "htree/htree_fwds.h"
#include <boost/smart_ptr/shared_ptr.hpp>
#include <string>

namespace htree {

class Node
{
public:
    virtual ~Node() {}

    virtual const std::string& name() const = 0;

    virtual const std::string& description() const = 0;

    virtual void description(const std::string& desc) = 0;

    virtual void addDependency(const_node_ptr other) = 0;

};

} /* namespace htree */

#endif /* HTREE_IMPL_NODE_H_ */
