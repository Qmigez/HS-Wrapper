#ifndef HS_WRAPPER_TESTS_CORE_INCLUDED
#define HS_WRAPPER_TESTS_CORE_INCLUDED
#include <string>
#include <format>

#include "HSWrapper/AbstractHandler.h"

class SmartHandler : public HS::AbstractHandler {
public:
    void* getCtx() final {
        return &res_;
    }
    HS::HandlerTypePtr getHandler() const final {
        return &handler;
    }
    void clearResult() {
        res_.clear();
    }

    std::string getResult() const {
        return res_;
    }
private:
    static int handler(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* ctx) {
        *static_cast<std::string*>(ctx) += std::format("{}:{}:{}:{}\n", id, from, to, flags);
        return 0;
    }
private:
    std::string res_ = "";
};

#endif // HS_WRAPPER_TESTS_CORE_INCLUDED