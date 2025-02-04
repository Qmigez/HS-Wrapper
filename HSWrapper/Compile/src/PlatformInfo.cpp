#include <hs/hs.h>

#include <format>

#include "HSWrapper/Compile/PlatformInfo.h"

HS::PlatformInfo::PlatformInfo() {}

HS::PlatformInfo::PlatformInfo(unsigned int tune, unsigned long long cpu_features, unsigned long long reserved1, unsigned long long reserved2) {
    ptr_ = new hs_platform_info_t();
    static_cast<hs_platform_info_t*>(ptr_)->tune = tune;
    static_cast<hs_platform_info_t*>(ptr_)->cpu_features = cpu_features;
    static_cast<hs_platform_info_t*>(ptr_)->reserved1 = reserved1;
    static_cast<hs_platform_info_t*>(ptr_)->reserved2 = reserved2;
}

HS::PlatformInfo::PlatformInfo(const HS::PlatformInfo& other) {
    if (other.ptr_ == nullptr) {
        this->ptr_ = nullptr;
    } else {
        this->ptr_ = new hs_platform_info_t();
        static_cast<hs_platform_info_t*>(this->ptr_)->tune = static_cast<hs_platform_info_t*>(other.ptr_)->tune;
        static_cast<hs_platform_info_t*>(this->ptr_)->cpu_features = static_cast<hs_platform_info_t*>(other.ptr_)->cpu_features;
        static_cast<hs_platform_info_t*>(this->ptr_)->reserved1 = static_cast<hs_platform_info_t*>(other.ptr_)->reserved1;
        static_cast<hs_platform_info_t*>(this->ptr_)->reserved2 = static_cast<hs_platform_info_t*>(other.ptr_)->reserved2;   
    }
}

HS::PlatformInfo& HS::PlatformInfo::operator=(const HS::PlatformInfo& other) {
    if (this != &other) [[likely]] {
        delete static_cast<hs_platform_info_t*>(this->ptr_);
        if (other.ptr_ == nullptr) {
            this->ptr_ = nullptr;
        } else {
            this->ptr_ = new hs_platform_info_t();
            static_cast<hs_platform_info_t*>(this->ptr_)->tune = static_cast<hs_platform_info_t*>(other.ptr_)->tune;
            static_cast<hs_platform_info_t*>(this->ptr_)->cpu_features = static_cast<hs_platform_info_t*>(other.ptr_)->cpu_features;
            static_cast<hs_platform_info_t*>(this->ptr_)->reserved1 = static_cast<hs_platform_info_t*>(other.ptr_)->reserved1;
            static_cast<hs_platform_info_t*>(this->ptr_)->reserved2 = static_cast<hs_platform_info_t*>(other.ptr_)->reserved2;
        }
    }
    return *this;
}

HS::PlatformInfo::PlatformInfo(HS::PlatformInfo&& other) {
    this->ptr_ = other.ptr_;
    other.ptr_ = nullptr;
}

HS::PlatformInfo& HS::PlatformInfo::operator=(HS::PlatformInfo&& other) {
    if (this != &other) {
        if (this->ptr_ != nullptr) {
            delete static_cast<hs_platform_info_t*>(ptr_);
        }
        this->ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}


HS::PlatformInfo::~PlatformInfo() {
    delete static_cast<hs_platform_info_t*>(ptr_);
}

std::string HS::PlatformInfo::toString() const {
    if (ptr_ == nullptr) {
        return "not init";
    } else {
        return std::format("{}:{}:{}:{}", 
            static_cast<hs_platform_info_t*>(ptr_)->tune,
            static_cast<hs_platform_info_t*>(ptr_)->cpu_features,
            static_cast<hs_platform_info_t*>(ptr_)->reserved1,
            static_cast<hs_platform_info_t*>(ptr_)->reserved2
        );
    }
}