#ifndef HS_WRAPPER_RUNTIME_STREAM_INCLUDED
#define HS_WRAPPER_RUNTIME_STREAM_INCLUDED
#include <string>

#include "HSWrapper/Enums.h"

namespace HS {

class AbstractHandler;
class Database;
class Scratch;

class Stream {
public:
    Stream(const Stream&);
    Stream& operator=(const Stream&);
    Stream(Stream&&);
    Stream& operator=(Stream&&);
    ~Stream();
public:
    HS::RESULT scan(const std::string& data, unsigned int flags, const HS::Scratch&, HS::AbstractHandler&);
    friend class HS::Database;
private:
    Stream() = default;
private:
    void* ptr_ = nullptr;
};

} // namespace HS

#endif // HS_WRAPPER_RUNTIME_STREAM_INCLUDED