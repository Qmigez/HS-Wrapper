#ifndef HS_WRAPPER_ABSTRACT_HANDLER_INCLUDED
#define HS_WRAPPER_ABSTRACT_HANDLER_INCLUDED

namespace HS {

using HandlerTypePtr = int(*)(unsigned int, unsigned long long, unsigned long long, unsigned int, void*);

class AbstractHandler {
public:
    virtual HS::HandlerTypePtr getHandler() const = 0;
    virtual void* getCtx() = 0;
    ~AbstractHandler() = default;
};

} // namespace HS


#endif // HS_WRAPPER_ABSTRACT_HANDLER_INCLUDED