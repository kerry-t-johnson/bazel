
#ifndef HTREE_DEPENDENCY_H_
#define HTREE_DEPENDENCY_H_

#include <string>

namespace htree {

class Dependency
{
public:
    Dependency(const std::string& name);
    virtual ~Dependency();

    inline const std::string& name() const { return name_; }

private:

    const std::string name_;
};

} /* namespace htree */

#endif /* HTREE_DEPENDENCY_H_ */
