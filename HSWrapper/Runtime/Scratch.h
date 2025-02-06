#ifndef HS_WRAPPER_RUNTIME_SCRATCH_INCLUDED
#define HS_WRAPPER_RUNTIME_SCRATCH_INCLUDED

namespace HS {

class Database;
class Stream;

class Scratch {
public:
    Scratch(const Scratch&);
    Scratch& operator=(const Scratch&);

    Scratch(Scratch&&);
    Scratch& operator=(Scratch&&);
    ~Scratch();
    
    friend class HS::Database;
    friend class HS::Stream;
private:
    Scratch() = default;

    void* ptr_ = nullptr;
};

} // namespace HS

#endif // HS_WRAPPER_RUNTIME_SCRATCH_INCLUDED