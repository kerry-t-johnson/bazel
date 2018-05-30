
#ifndef UTIL_CHUNKER_H_
#define UTIL_CHUNKER_H_

#include <string>
#include <vector>

namespace util {

class Chunker
{
public:
    Chunker(std::size_t chunkSize);
    virtual ~Chunker();

    std::vector<std::string> chunk(const std::string& data) const;

private:

    const std::size_t maxChunkSize;
};

} // namespache util

#endif /* UTIL_CHUNKER_H_ */
