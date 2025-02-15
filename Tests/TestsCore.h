#ifndef HS_WRAPPER_TESTS_CORE_INCLUDED
#define HS_WRAPPER_TESTS_CORE_INCLUDED

#include <unordered_set>
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

    std::unordered_multiset<std::string> getResult() const {
        return res_;
    }
private:
    static int handler(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* ctx) {
        static_cast<std::unordered_multiset<std::string>*>(ctx)->insert(std::format("{}:{}:{}:{}", id, from, to, flags));
        return 0;
    }
private:
    std::unordered_multiset<std::string> res_;
};

#endif // HS_WRAPPER_TESTS_CORE_INCLUDED