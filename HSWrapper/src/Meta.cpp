#include <hs/hs.h>

#include <format>

#include "HSWrapper/Exception.h"
#include "HSWrapper/Meta.h"
#include "HSWrapper/Pattern.h"

#include "HSWrapper/Compile/PlatformInfo.h"

void HS::Meta::setAllocator(std::function<void*(size_t)> alloc, std::function<void(void*)> free) {
    hs_error_t res = hs_set_allocator(
        alloc.target<void*(size_t)>(),
        free.target<void(void*)>()
    );
    if (res != HS_SUCCESS) [[unlikely]] {
        throw HS::RuntimeException(std::format("Can't set allocator, with code {}", res));
    }
    allocFunc_ = alloc;
    freeFunc_ = free;    
}

bool HS::Meta::canBeCompiled(const HS::Pattern& pattern, HS::MODE mode, const HS::PlatformInfo& pi) {
    bool out = false;
    hs_compile_error_t* error = nullptr;
    hs_database_t* db = nullptr;

    hs_error_t res = hs_compile(
        pattern.expr_.c_str(),
        pattern.flags_,
        static_cast<unsigned int>(mode),
        static_cast<hs_platform_info_t*>(pi.ptr_),
        &db,
        &error
    );
    if (res == HS_SUCCESS) {
        out = true;
        hs_free_database(db);       
    }
    hs_free_compile_error(error);
    return out;
}



void HS::Meta::setDestructorCallback(std::function<void(void*, const std::string&)> func) {
    destructorCallback_ = func;
}
void HS::Meta::destructorCallback(void* ptr, const std::string& message) {
    destructorCallback_(ptr, message);
}