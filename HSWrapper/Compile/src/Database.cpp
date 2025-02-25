#include "hs/hs.h"

#include <format>

#include "HSWrapper/AbstractHandler.h"
#include "HSWrapper/Exception.h"
#include "HSWrapper/Meta.h"
#include "HSWrapper/Pattern.h"

#include "HSWrapper/Compile/Database.h"
#include "HSWrapper/Compile/PlatformInfo.h"

#include "HSWrapper/Runtime/Scratch.h"
#include "HSWrapper/Runtime/Stream.h"

/*
    info functions
*/
std::string HS::Database::info() const {
    char* info = nullptr;
    hs_error_t res = hs_database_info(
        static_cast<const hs_database_t*>(this->ptr_),
        &info
    );
    if (res != HS_SUCCESS) [[unlikely]] {
        throw HS::RuntimeException(std::format("Can't database info, with code {}", res));
    }
    std::string out(info);
    free(info);
    return out;
}

size_t HS::Database::size() const {
    size_t out;
    hs_error_t res = hs_database_size(
        static_cast<const hs_database_t*>(this->ptr_),
        &out
    );
    if (res != HS_SUCCESS) [[unlikely]] {
        throw HS::RuntimeException(std::format("Can't database size, with code {}", res));
    }
    return out;
}


/*
    HS::Scratch functions
*/
HS::Scratch HS::Database::allocScratch() const {
    HS::Scratch out;
    hs_error_t res = hs_alloc_scratch(
        static_cast<hs_database_t*>(ptr_), 
        reinterpret_cast<hs_scratch_t**>(&out.ptr_)
    );
    if (res != HS_SUCCESS) [[unlikely]] {
        throw HS::RuntimeException(std::format("Can't alloc scratch, with code {}", res));
    }
    return out;
}

/*
    Scan functions
*/
void HS::Database::scan(const std::string& data, unsigned int flags, const HS::Scratch& scratch, HS::AbstractHandler& ah) const{
    hs_error_t res = hs_scan(
        static_cast<hs_database_t*>(ptr_),
        data.c_str(),
        data.size(),
        flags,
        static_cast<hs_scratch_t*>(scratch.ptr_),
        ah.getHandler(),
        ah.getCtx()
    );
    if (res != HS_SUCCESS) [[unlikely]] {
        throw HS::RuntimeException(std::format("Can't scan with error {}", res));
    }
}

/*
    HS::Database static
*/
HS::Database HS::Database::compile(const HS::Pattern& expr, HS::MODE mode, const HS::PlatformInfo& platfrom) {
    Database db;

    hs_compile_error_t* error = nullptr;

    hs_error_t res = hs_compile(expr.expr_.c_str(), expr.flags_, static_cast<unsigned int>(mode), 
        static_cast<hs_platform_info_t*>(platfrom.ptr_), 
        reinterpret_cast<hs_database_t**>(&db.ptr_), 
        reinterpret_cast<hs_compile_error_t**>(&error)
    );
    if (res != HS_SUCCESS) [[unlikely]] {
        std::string exceptionString = std::format("Can't compile \"{}\" with compile error expression \"{}\" and message \"{}\"", 
            expr.expr_, 
            error->expression, 
            error->message
        );
        hs_free_compile_error(error);
        throw HS::CompileException(exceptionString);
    }
    return db;
}
HS::Database HS::Database::compileMulti(const std::vector<HS::Pattern>& exprs, HS::MODE mode, const HS::PlatformInfo& platform) {
    HS::Database out;
    std::vector<const char*> expressons;
    std::vector<unsigned int> flags;
    std::vector<unsigned int> ids;

    for (auto& e : exprs) {
        expressons.emplace_back(e.expr_.c_str());
        flags.emplace_back(e.flags_);
        ids.emplace_back(e.id_);
    }
    hs_compile_error_t* err = nullptr;
    hs_error_t res = hs_compile_multi(
        expressons.data(), 
        flags.data(), 
        ids.data(), 
        exprs.size(), 
        static_cast<unsigned int>(mode),
        static_cast<hs_platform_info_t*>(platform.ptr_),
        reinterpret_cast<hs_database_t**>(&out.ptr_),
        &err
    );

    if (res != HS_SUCCESS) [[unlikely]]{
        std::string errorString = std::format("Can't hs_compile_multi with compile error expression \"{}\" and message \"{}\"",
            err->expression, err->message);
        hs_free_compile_error(err);
        throw HS::CompileException(errorString);
    }
    return out;
}

/*
    HS::Database functions
*/

HS::Database::Database(HS::Database&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

HS::Database& HS::Database::operator=(HS::Database&& other) noexcept{
    if (this != &other) {
        hs_free_database(static_cast<hs_database_t*>(this->ptr_));    
        this->ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}

HS::Database::~Database() {
    hs_error_t res = hs_free_database(static_cast<hs_database_t*>(ptr_));
    if (res != HS_SUCCESS) [[unlikely]] {
        HS::Meta::destructorCallback(this, std::format("Can't free database with code {}", res));
    }
}

HS::Stream HS::Database::openStream(unsigned int flags) const {
    HS::Stream out;
    hs_error_t res = hs_open_stream(
        static_cast<hs_database_t*>(this->ptr_),
        flags,
        reinterpret_cast<hs_stream_t**>(&out.ptr_)
    );
    if (res != HS_SUCCESS) [[unlikely]] {
        throw HS::RuntimeException(std::format("Can't open stream with code {}", res));
    }
    return out;
}