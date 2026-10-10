#include "java/JavaNetwork.h"

#ifdef PSP_PLATFORM

#include <istream>
#include <ostream>

namespace JavaNetwork
{

bool readUrl(const std::string &, std::vector<unsigned char> &)
{
    return false;
}

int getResponseCode(const std::string &)
{
    return 404;
}

bool postUrl(const std::string &, const std::string &,
             const std::string &, std::vector<unsigned char> &)
{
    return false;
}

std::unique_ptr<Socket> createSocket()
{
    return nullptr;
}

std::unique_ptr<std::istream> createInputStream(Socket &)
{
    return nullptr;
}

std::unique_ptr<std::ostream> createOutputStream(Socket &)
{
    return nullptr;
}

} // namespace JavaNetwork

#endif // PSP_PLATFORM
