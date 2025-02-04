#ifndef HS_WRAPPER_EXPRESSION_INCLUDED
#define HS_WRAPPER_EXPRESSION_INCLUDED

#include <string>
#include <vector>

#include "HSWrapper/Enums.h"

#include "HSWrapper/Compile/PlatformInfo.h"

namespace HS {

class Database;
class Meta;

class Pattern {
public:
    Pattern(std::string expression, std::vector<HS::FLAG>, unsigned int id);
    /// @brief 
    /// @param expression format <integer id>:/<regex>/<flags>
    Pattern(std::string expression);

    std::string toString();
    friend class HS::Database;
    friend class HS::Meta;
private:
    std::string expr_ = "";
    unsigned int flags_ = 0;
    unsigned int id_ = 0;
};

} // namespcase HS

#endif // HS_WRAPPER_EXPRESSION_INCLUDED