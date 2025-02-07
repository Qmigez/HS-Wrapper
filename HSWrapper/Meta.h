#ifndef HS_WRAPPER_META_INCLUDED
#define HS_WRAPPER_META_INCLUDED

#include <functional>
#include <string>

#include "HSWrapper/Enums.h"
#include "HSWrapper/Exception.h"

namespace HS {

class Pattern;
class PlatformInfo;

class Meta {
public:
    static bool canBeCompiled(HS::Pattern, HS::MODE, HS::PlatformInfo);
    static void setDestructorCallback(std::function<void(void*, std::string)>);
    static void destructorCallback(void*, std::string);
private:
    static void defaultCallback(void* ptr, std::string message) {
        throw HS::RuntimeException(message);
    }
private:
    inline static std::function<void(void*, std::string)> destructorCallback_ = &defaultCallback;
};

} // namespace HS

#endif // HS_WRAPPER_META_INCLUDED