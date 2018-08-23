#ifndef HTREE_IMPL_IMPL_FWDS_H_
#define HTREE_IMPL_IMPL_FWDS_H_

#include "htree/htree_fwds.h"
#include <boost/graph/adjacency_list.hpp>
#include <string>

namespace htree { namespace impl {

struct Vertex {
    std::string name;
};

struct Edge {
    int weight;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, Vertex, Edge>    DAG;

}}



#endif /* HTREE_IMPL_IMPL_FWDS_H_ */
