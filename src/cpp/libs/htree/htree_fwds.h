#ifndef HTREE_FWDS_H_
#define HTREE_FWDS_H_

#include <boost/shared_ptr.hpp>

namespace htree {

class HealthTree;
class Node;

using node_ptr          = boost::shared_ptr<Node>;
using const_node_ptr    = boost::shared_ptr<const Node>;

}



#endif /* HTREE_FWDS_H_ */
