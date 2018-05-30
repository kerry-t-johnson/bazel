#include "GraylogMessage.h"
#include "GraylogStreamWriter.h"

namespace logger {

GraylogStreamWriter::GraylogStreamWriter(std::ostream& ostr)
: ostr_(ostr)
{

}

GraylogStreamWriter::~GraylogStreamWriter()
{
}

void GraylogStreamWriter::write(const GraylogMessage& msg) const
{
    ostr_ << msg;
}

} // namespace logger
