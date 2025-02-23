#ifndef HS_WRAPPER_COMPILE_DATADASE_INCLUDED
#define HS_WRAPPER_COMPILE_DATADASE_INCLUDED

#include <string>
#include <vector>

#include "HSWrapper/Enums.h"

namespace HS {

class AbstractHandler;
class Scratch;
class Stream;
class Pattern;
class PlatformInfo;

class Database {
/*
    information functions
*/
public:
    std::string info() const;
    size_t size() const;
/*
    Scratch functions
*/
public:
    HS::Scratch allocScratch() const;
/*
    Stream functions
*/
public:
    HS::Stream openStream(unsigned int flags) const;
/*
    Scan functions
*/
public:
    void scan(const std::string& data, unsigned int flags, const HS::Scratch& scratch, HS::AbstractHandler&) const;
/*
    DB static functions
*/
public:
    static HS::Database compile(const HS::Pattern&, 
        HS::MODE, 
        const HS::PlatformInfo&
    );
    static HS::Database compileMulti(const std::vector<HS::Pattern>&, 
        HS::MODE, 
        const HS::PlatformInfo&
    );
/*
    DB functions
*/
public:
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    Database(Database&&) noexcept;
    Database& operator=(Database&&) noexcept;
    ~Database();

private:
    Database() {};
private:
    void* ptr_ = nullptr;
};

} // namespace HS


#endif // HS_WRAPPER_COMPILE_DATADASE_INCLUDED