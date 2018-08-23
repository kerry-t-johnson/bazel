#ifndef HTREE_HEALTHTREEIMPL_H_
#define HTREE_HEALTHTREEIMPL_H_


#include "htree/HealthTree.h"
#include "htree/impl/Dependency.h"
#include "htree/impl/htree_impl_fwds.h"
#include "logger/Logger.h"
#include <boost/filesystem/path.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/thread/pthread/mutex.hpp>
#include <iostream>
#include <map>
#include <string>

namespace boost { class mutex; }
namespace boost { namespace filesystem { class path; }}

namespace htree { namespace impl {

class HealthTreeImpl : public HealthTree
{
public:
    HealthTreeImpl(const std::string& name = ROOT);
    virtual ~HealthTreeImpl();

    node_ptr createNode(const std::string& name);

    virtual void addDependency(const Dependency&    dep,
                               const std::string&   node = ROOT);

    virtual void load(const std::string& path);

    virtual void print(std::ostream& ostr);

private:

    typedef std::map<std::string, node_ptr> node_map;

    void loadFile(const boost::filesystem::path& p);

    const std::string               root_;
    node_map                        nodes_;
    boost::shared_ptr<DAG>          dag_;
    logger::Logger                  logger_;
    boost::shared_ptr<boost::mutex> lock_;
};

}} /* namespace htree */

#endif /* HTREE_HEALTHTREEIMPL_H_ */
