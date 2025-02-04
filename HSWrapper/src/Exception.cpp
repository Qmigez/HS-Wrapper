#include <hs/hs.h>

#include <format>

#include "HSWrapper/Exception.h"

HS::RuntimeException::RuntimeException(std::string message) 
    : err_(std::format("[HS::RuntimeException] {}", message)) {}

const char* HS::RuntimeException::what() const noexcept {
    return err_.c_str();
}


HS::CompileException::CompileException(std::string message) 
    : err_(std::format("[HS::CompileException] {}", message)) {}

const char* HS::CompileException::what() const noexcept {
    return err_.c_str();
}
