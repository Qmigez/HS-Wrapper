#ifndef HS_WRAPPER_ENUMS_INCLUDED
#define HS_WRAPPER_ENUMS_INCLUDED

namespace HS {

// HS::FLAG::X used as HS_FLAG_X
enum class FLAG {
    CASELESS = 1,
    DOTALL = 2,
    MULTILINE = 4,
    SINGLEMATCH = 8,
    ALLOWEMPTY = 16,
    UTF8 = 32,
    UCP = 64,
    PREFILTER = 128,
    SOM_LEFTMOST = 256,
    COMBINATION = 512,
    QUIET = 1024
};
// HS::MODE::X used as HS_MODE_X
enum class MODE {
    BLOCK = 1,
    NOSTREAM = 1,
    STREAM = 2,
    VECTORED = 4,
    SOM_HORIZON_LARGE = (1U << 24),
    SOM_HORIZON_MEDIUM = (1U << 25),
    SOM_HORIZON_SMALL = (1U << 26)
};
}
#endif // HS_WRAPPER_ENUMS_INCLUDED