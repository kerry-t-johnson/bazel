#ifndef HTREE_HEALTHTREE_H_
#define HTREE_HEALTHTREE_H_

#include "htree/htree_fwds.h"
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <string>

namespace htree { class Dependency; }
namespace htree { class Node; }

namespace htree {

class HealthTree
{
public:
    static const std::string ROOT;

    virtual ~HealthTree() {}

    virtual node_ptr createNode(const std::string& name) = 0;

    virtual void addDependency(const Dependency&    dep,
                               const std::string&   node = ROOT) = 0;

    virtual void load(const std::string& path) = 0;

    virtual void print(std::ostream& ostr) = 0;
};

} /* namespace htree */

#endif /* HTREE_HEALTHTREE_H_ */
