#ifndef HS_WRAPPER_COMPILE_PLATFORM_INFO_INCLUDED
#define HS_WRAPPER_COMPILE_PLATFORM_INFO_INCLUDED

#include <string>

namespace HS {

class Database;
class Meta;

class PlatformInfo {
public:
    PlatformInfo();

    PlatformInfo(unsigned int tune, unsigned long long cpu_features, unsigned long long reserved1, unsigned long long reserved2);
    
    ~PlatformInfo();

    PlatformInfo(const PlatformInfo&);
    PlatformInfo& operator=(const PlatformInfo&);

    PlatformInfo(PlatformInfo&&);
    PlatformInfo& operator=(PlatformInfo&&);
    
    std::string toString() const;
    
    friend class HS::Database;
    friend class HS::Meta;
private:
    void* ptr_ = nullptr;
};

} // namespace HS

#endif // HS_WRAPPER_COMPILE_PLATFORM_INFO_INCLUDED