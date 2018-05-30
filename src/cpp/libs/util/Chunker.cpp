
#include "Chunker.h"

namespace util {

Chunker::Chunker(std::size_t chunkSize)
: maxChunkSize(chunkSize)
{
}

Chunker::~Chunker()
{
}

std::vector<std::string> Chunker::chunk(const std::string& data) const
{
    std::vector<std::string> out;

    for(std::size_t i = 0; i < data.length();) {
        const std::size_t dataRemaining = data.length() - i;
        const std::size_t chunkSize = std::min(dataRemaining, maxChunkSize);

        out.push_back(std::string(data, i, chunkSize));

        i += chunkSize;
    }

    return out;
}

} // namespace util
