#include <hs/hs.h>

#include <format>
#include <iostream>

#include "HSWrapper/Exception.h"
#include "HSWrapper/Runtime/Scratch.h"

HS::Scratch::Scratch(Scratch&& other) {
    std::cout << "HS::Scratch::Scratch(Scratch&&)\n";
    this->ptr_ = other.ptr_;
    other.ptr_ = nullptr;
}

HS::Scratch& HS::Scratch::operator=(Scratch&& other) {
    std::cout << "HS::Scratch::operator=(Scratch&&)\n";
    if (this != &other) {
        hs_free_scratch(static_cast<hs_scratch_t*>(ptr_));
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;    
    }
    return *this;
}

HS::Scratch::~Scratch() {
    hs_free_scratch(static_cast<hs_scratch_t*>(ptr_));
}

HS::Scratch::Scratch(const HS::Scratch& other) {
    std::cout << "HS::Scratch::Scratch(const HS::Scratch&)" <<std::endl;
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
    std::cout << "operator=(const HS::Scratch&)" <<std::endl;
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