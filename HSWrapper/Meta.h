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
    static bool canBeCompiled(const HS::Pattern&, HS::MODE,const HS::PlatformInfo&);
    static void setDestructorCallback(std::function<void(void*, const std::string&)>);
    static void destructorCallback(void*, const std::string&);
    static void setAllocator(std::function<void*(size_t)> alloc, std::function<void(void*)> free);
    static void free(void* ptr) {
        freeFunc_(ptr);
    }
private:
    static void defaultCallback(void* ptr, const std::string& message) {
        throw HS::RuntimeException(message);
    }
private:
    inline static std::function<void(void*, const std::string&)> destructorCallback_ = &defaultCallback;
    inline static std::function<void*(size_t)> allocFunc_ = &malloc;
    inline static std::function<void(void*)> freeFunc_ = &free;
};

} // namespace HS

#endif // HS_WRAPPER_META_INCLUDED