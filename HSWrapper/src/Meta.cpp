#include <hs/hs.h>

#include "HSWrapper/Meta.h"

#include "HSWrapper/Exception.h"

bool HS::Meta::canBeCompiled(HS::Pattern pattern, HS::MODE mode, HS::PlatformInfo pi) {
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



void HS::Meta::setDestructorCallback(std::function<void(void*, std::string)> func) {
    destructorCallback_ = func;
}
void HS::Meta::destructorCallback(void* ptr, std::string message) {
    destructorCallback_(ptr, message);
}