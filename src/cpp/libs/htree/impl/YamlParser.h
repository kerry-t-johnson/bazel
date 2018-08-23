#ifndef HTREE_IMPL_YAMLPARSER_H_
#define HTREE_IMPL_YAMLPARSER_H_

#include "htree/impl/htree_impl_fwds.h"

namespace YAML { class Node; }

namespace htree {
namespace impl {

class YamlParser
{
public:
    YamlParser(node_ptr     node,
               HealthTree&  tree);
    virtual ~YamlParser();

    void load(const YAML::Node& yml);

private:

    void processDescription(const YAML::Node& yml);
    void processDependencies(const YAML::Node& yml);
    void processDependency(const YAML::Node& yml);
    void processComplexDependency(const YAML::Node& yml);

    node_ptr        node_;
    HealthTree&     tree_;
};

} /* namespace impl */
} /* namespace htree */

#endif /* HTREE_IMPL_YAMLPARSER_H_ */
