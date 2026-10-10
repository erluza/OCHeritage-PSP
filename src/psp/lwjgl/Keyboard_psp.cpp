#include "lwjgl/Keyboard.h"
#include "lwjgl/KeyNames.h"

#ifdef PSP_PLATFORM

#include <queue>
#include <string>

namespace lwjgl
{
namespace Keyboard
{

namespace detail
{

struct Event
{
    int  key;
    int  character;
    bool down;
};

static Event             s_current = {};
static std::queue<Event> s_queue;
static bool              s_keyState[256] = {};

void pushKey(int lwjglKey, bool down)
{
    if (lwjglKey >= 0 && lwjglKey < 256)
        s_keyState[lwjglKey] = down;
    s_queue.push({lwjglKey, 0, down});
}

void pushChar(int character)
{
    s_queue.push({KEY_NONE, character, true});
}

} // namespace detail

jstring getKeyName(int_t key)
{
    if (const char *name = lwjglKeyDisplayName(key))
        return name;
    return "KEY " + std::to_string(key);
}

static bool s_repeatEvents = false;

bool next()
{
    if (detail::s_queue.empty()) return false;
    detail::s_current = detail::s_queue.front();
    detail::s_queue.pop();
    return true;
}

void clearEvents()
{
    while (!detail::s_queue.empty())
        detail::s_queue.pop();
    detail::s_current = {};
}

void enableRepeatEvents(bool repeat) { s_repeatEvents = repeat; }
bool areRepeatEventsEnabled()        { return s_repeatEvents; }

char_t getEventCharacter() { return (char_t)detail::s_current.character; }
int_t  getEventKey()       { return detail::s_current.key; }
bool   getEventKeyState()  { return detail::s_current.down; }

void poll() {}

bool isKeyDown(int_t key)
{
    if (key < 0 || key >= 256) return false;
    return detail::s_keyState[key];
}

} // namespace Keyboard
} // namespace lwjgl

#endif // PSP_PLATFORM
