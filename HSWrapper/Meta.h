#ifndef HS_WRAPPER_META_INCLUDED
#define HS_WRAPPER_META_INCLUDED

#include <string>

#include "HSWrapper/Pattern.h"

namespace HS {

class Meta {
public:
    static bool canBeCompiled(HS::Pattern, HS::MODE, HS::PlatformInfo=HS::PlatformInfo()); 
};

} // namespace HS

#endif // HS_WRAPPER_META_INCLUDED