#ifndef HS_WRAPPER_META_INCLUDED
#define HS_WRAPPER_META_INCLUDED

#include <string>

#include "HSWrapper/Pattern.h"

namespace HS {

using DestructorCallbackPtr = void(*)(void*, std::string);

class Meta {
public:
    static bool canBeCompiled(HS::Pattern, HS::MODE, HS::PlatformInfo=HS::PlatformInfo());
    static void setDestructorCallback(DestructorCallbackPtr);
    static void destructorCallback(void*, std::string);
private:
    static DestructorCallbackPtr destructorCallback_;
};

void defaultCallback(void* ptr, std::string);

DestructorCallbackPtr HS::Meta::destructorCallback_ = &defaultCallback;

} // namespace HS

#endif // HS_WRAPPER_META_INCLUDED