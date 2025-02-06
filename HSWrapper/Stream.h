#ifndef HS_WRAPPER_STREAM_INCLUDED
#define HS_WRAPPER_STREAM_INCLUDED

namespace HS {

class Database;

class Stream {
public:
    Stream(const Stream&);
    Stream& operator=(const Stream&);
    Stream(Stream&&);
    Stream& operator=(Stream&&);
    ~Stream();
    
    friend class HS::Database;
private:
    Stream() = default;
private:
    void* ptr_ = nullptr;
};

} // namespace HS

#endif // HS_WRAPPER_STREAM_INCLUDED