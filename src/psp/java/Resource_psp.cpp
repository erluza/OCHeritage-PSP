#include "java/Resource.h"
#include "java/String.h"
#include "net/minecraft/src/GameResources.h"

#include <stdexcept>
#include <sstream>
#include <string>

namespace Resource
{

std::istream *getResource(const jstring &name)
{
    // GameResources::open resolves through AssetPak (assets.pak) or loose
    // files under ms0:/PSP/GAME/OptiCraft/assets/.
    //
    // This is called during static initialization (SharedConstants,
    // ChatAllowedCharacters) before main() runs, so the filesystem and
    // asset pak must already be accessible.  On PSP, newlib's IO layer
    // handles ms0: paths transparently.
    auto input = GameResources::open(static_cast<const std::string &>(name));
    if (input)
        return input.release();

    // If we cannot find the resource, return an empty stream instead of
    // throwing.  A throw during static initialization calls std::terminate
    // and the user just sees "sceKernelExitGame".  An empty stream lets the
    // callers (readAcceptableChars, getAllowedCharacters) produce an empty
    // string, which is gracefully replaced once the pak is properly mounted.
    static std::istringstream s_empty("");
    return new std::istringstream("");
}

} // namespace Resource
