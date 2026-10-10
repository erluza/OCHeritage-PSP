#include "platform/Resources.h"

#ifdef PSP_PLATFORM

#include "platform/storage/AssetPak.h"
#include "platform/Storage.h"
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>

// No std::filesystem on PSP — ms0: device paths break its parser.
// Use POSIX stat() through newlib instead.
namespace
{
bool pspPathExists(const std::string& path)
{
    struct stat st;
    return ::stat(path.c_str(), &st) == 0;
}
}

std::string PlatformResources::baseDir()
{
    return "ms0:/PSP/GAME/OptiCraft";
}

std::string PlatformResources::assetsDir()
{
    return baseDir() + "/assets";
}

std::string PlatformResources::audioDir()
{
    return baseDir() + "/resources";
}

std::string PlatformResources::resolveExisting(const std::string& path)
{
    if (AssetPak::mountFrom(baseDir()) && AssetPak::exists(path))
        return AssetPak::makePath(path);

    std::string resolved;
    if (path.rfind("assets/", 0) == 0)
        resolved = assetsDir() + "/" + path.substr(7);
    else if (path.rfind("resources/", 0) == 0)
        resolved = audioDir() + "/" + path.substr(10);
    else
        resolved = baseDir() + "/" + path;

    if (pspPathExists(resolved))
        return resolved;

    return std::string();
}

std::string PlatformResources::resolveAsset(const std::string& input)
{
    std::string path = input;
    if (!path.empty() && path[0] == '/')
        path.erase(path.begin());
    return resolveExisting("assets/" + path);
}

long PlatformResources::fileSize(const std::string& path)
{
    if (AssetPak::isPakPath(path))
        return AssetPak::size(AssetPak::keyOf(path));
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    return file ? static_cast<long>(file.tellg()) : -1L;
}

unsigned char* PlatformResources::loadFile(const std::string& path, unsigned int* outSize)
{
    if (AssetPak::isPakPath(path))
        return AssetPak::load(AssetPak::keyOf(path), outSize);

    if (outSize)
        *outSize = 0;
    const long size = fileSize(path);
    if (size <= 0)
        return nullptr;

    unsigned char* data = static_cast<unsigned char*>(std::malloc(static_cast<std::size_t>(size)));
    if (!data)
        return nullptr;

    std::ifstream file(path, std::ios::binary);
    if (!file.read(reinterpret_cast<char*>(data), size))
    {
        std::free(data);
        return nullptr;
    }
    if (outSize)
        *outSize = static_cast<unsigned int>(size);
    return data;
}

#endif // PSP_PLATFORM
