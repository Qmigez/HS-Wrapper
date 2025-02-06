#include <hs/hs.h>

#include <format>

#include "HSWrapper/AbstractHandler.h"
#include "HSWrapper/Exception.h"
#include "HSWrapper/Meta.h"
#include "HSWrapper/Stream.h"

#include "HSWrapper/Runtime/Scratch.h"

HS::Stream::Stream(const Stream& other) {
    if (this != &other) [[likely]] {
        hs_error_t res = hs_copy_stream(
            reinterpret_cast<hs_stream_t**>(this->ptr_),
            static_cast<hs_stream_t*>(other.ptr_)
        );
        if (res != HS_SUCCESS) [[unlikely]] {
            throw HS::RuntimeException(std::format("Can't copy stream with code {}", res));
        }
    }
}

HS::Stream& HS::Stream::operator=(const HS::Stream& other) {
    if (this != &other) [[likely]]{
        hs_error_t res = hs_close_stream(
            static_cast<hs_stream_t*>(this->ptr_),
            nullptr,
            nullptr,
            nullptr
        );
        if (res != HS_SUCCESS) [[unlikely]] {
            throw HS::RuntimeException(std::format("Can't close stream with code {}", res));
        }
        this->ptr_ = nullptr;
        res = hs_copy_stream(
            reinterpret_cast<hs_stream_t**>(this->ptr_),
            static_cast<hs_stream_t*>(other.ptr_)
        );
        if (res != HS_SUCCESS) [[unlikely]] {
            throw HS::RuntimeException(std::format("Can't copy stream with code {}", res));
        }
    } 
    return *this;
}

HS::Stream::Stream(Stream&& other) {
    if (this != &other) [[likely]] {
        this->ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
}

HS::Stream& HS::Stream::operator=(HS::Stream&& other) {
    if (this != &other) [[likely]] {
        hs_error_t res = hs_close_stream(
            static_cast<hs_stream_t*>(this->ptr_),
            nullptr,
            nullptr,
            nullptr
        );
        if (res != HS_SUCCESS) [[unlikely]] {
            throw HS::RuntimeException(std::format("Can't close stream with code {}", res));
        }
        this->ptr_ = nullptr;
        
        res = hs_close_stream(
            static_cast<hs_stream_t*>(this->ptr_),
            nullptr,
            nullptr,
            nullptr
        );
        if (res != HS_SUCCESS) [[unlikely]] {
            throw HS::RuntimeException(std::format("Can't close stream with code {}", res));
        }
        this->ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}

HS::Stream::~Stream() {
    hs_error_t res = hs_close_stream(
        static_cast<hs_stream_t*>(ptr_),
        nullptr,
        nullptr,
        nullptr
    );
    if (res != HS_SUCCESS) [[unlikely]] {
        Meta::destructorCallback(this, "can't close stream");
    }
}

HS::RESULT HS::Stream::scan(std::string data, unsigned int flags, HS::Scratch& scratch, HS::AbstractHandler& ah) {
    hs_error_t res = hs_scan_stream(
        static_cast<hs_stream_t*>(this->ptr_),
        data.c_str(),
        data.size(),
        flags,
        static_cast<hs_scratch_t*>(scratch.ptr_),
        ah.getHandler(),
        ah.getCtx()
    );
    switch (res) {
        case HS_SUCCESS:
            return HS::RESULT::SUCCESS;
            break;
        case HS_SCAN_TERMINATED:
            return HS::RESULT::SCAN_TERMINATED;
            break;
        default:
            throw HS::RuntimeException(std::format("Can't scan stream with code {}", res));
            break;
    }
}