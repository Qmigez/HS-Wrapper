#include <hs/hs.h>

#include <format>

#include "HSWrapper/Exception.h"
#include "HSWrapper/Meta.h"

#include "HSWrapper/Runtime/Scratch.h"

HS::Scratch::Scratch(Scratch&& other) {
    if (this != &other) [[likely]] {
        this->ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
}

HS::Scratch& HS::Scratch::operator=(Scratch&& other) {
    if (this != &other) [[likely]] {
        hs_error_t res = hs_free_scratch(static_cast<hs_scratch_t*>(ptr_));
        if (res != HS_SUCCESS) [[unlikely]] {
            throw HS::RuntimeException(std::format("Can't free scratch with code {}", res));
        }
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;    
    }
    return *this;
}

HS::Scratch::~Scratch() {
    hs_error_t res = hs_free_scratch(static_cast<hs_scratch_t*>(ptr_));
    if (res != HS_SUCCESS) [[unlikely]] {
        HS::Meta::destructorCallback(this, std::format("Can't free scratch with code {}", res));
    }
}

HS::Scratch::Scratch(const HS::Scratch& other) {
    if (this != &other) [[likely]] {
        hs_error_t res = hs_clone_scratch(
            static_cast<hs_scratch_t*>(other.ptr_), 
            reinterpret_cast<hs_scratch_t**>(&this->ptr_)
        );
        
        if (res != HS_SUCCESS) [[unlikely]]{
            throw HS::RuntimeException(std::format("Can't clone scratch, with code {}", res));
        }
    }
}
HS::Scratch& HS::Scratch::operator=(const HS::Scratch& other) {
    if (this != &other) [[likely]] {
        hs_error_t res = hs_clone_scratch(
            static_cast<hs_scratch_t*>(other.ptr_), 
            reinterpret_cast<hs_scratch_t**>(&this->ptr_)
        );
        
        if (res != HS_SUCCESS) [[unlikely]]{
            throw HS::RuntimeException(std::format("Can't clone scratch, with code {}", res));
        }
    }
    return *this;
}