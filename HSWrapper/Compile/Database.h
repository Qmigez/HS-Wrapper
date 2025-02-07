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
    Scratch functions
*/
public:
    HS::Scratch allocScratch();
/*
    Stream functions
*/
public:
    HS::Stream openStream(unsigned int flags);
/*
    Scan functions
*/
public:
    void scan(std::string& data, unsigned int flags, HS::Scratch& scratch, HS::AbstractHandler&);
/*
    DB static functions
*/
public:
    static HS::Database compile(HS::Pattern, 
        HS::MODE, 
        HS::PlatformInfo
    );
    static HS::Database compileMulti(std::vector<HS::Pattern>, 
        HS::MODE, 
        HS::PlatformInfo
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