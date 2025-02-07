#ifndef HS_WRAPPER_EXCEPTION_INCLUDED
#define HS_WRAPPER_EXCEPTION_INCLUDED

#include <exception>
#include <string>

namespace HS {

class RuntimeException : public std::exception {
public:
    RuntimeException(std::string);
    const char* what() const noexcept final;
private: 
    std::string err_ = "";
};

class CompileException : public std::exception {
public:
    CompileException(std::string);

    const char* what() const noexcept final;
private:
    std::string err_ = "";
};

} // namespace HS


#endif // HS_WRAPPER_EXCEPTION_INCLUDED