
#ifndef UTIL_GZIP_H_
#define UTIL_GZIP_H_

#include <string>

namespace util {

class GZip
{
public:

    static std::string compress(const std::string& in);

    static std::string uncompress(const std::string& in);

private:
    GZip();
};

} // namespace util

#endif /* UTIL_GZIP_H_ */
