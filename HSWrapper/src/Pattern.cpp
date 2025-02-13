#include <hs/hs.h>

#include <map>
#include <format>

#include "HSWrapper/Enums.h"
#include "HSWrapper/Pattern.h"

#include "HSWrapper/Compile/PlatformInfo.h"

HS::Pattern::Pattern(const std::string& expression, const std::vector<HS::FLAG>& flags, unsigned int id) : expr_(expression), id_(id) {
    for(auto& f : flags) {
        flags_ |= static_cast<unsigned int>(f);
    }
}

const static std::map<char, HS::FLAG> conversion{
    {'i', HS::FLAG::CASELESS},
    {'s', HS::FLAG::DOTALL},
    {'m', HS::FLAG::MULTILINE},
    {'H', HS::FLAG::SINGLEMATCH},
    {'V', HS::FLAG::ALLOWEMPTY},
    {'8', HS::FLAG::UTF8},
    {'W', HS::FLAG::UCP},
    {'P', HS::FLAG::PREFILTER},
    {'L', HS::FLAG::SOM_LEFTMOST},
    {'C', HS::FLAG::COMBINATION},
    {'Q', HS::FLAG::QUIET}
};

const static std::map<HS::FLAG, char> reConversion {
    {HS::FLAG::CASELESS, 'i'},
    {HS::FLAG::DOTALL, 's'},
    {HS::FLAG::MULTILINE, 'm'},
    {HS::FLAG::SINGLEMATCH, 'H'},
    {HS::FLAG::ALLOWEMPTY, 'V'},
    {HS::FLAG::UTF8, '8'},
    {HS::FLAG::UCP, 'W'},
    {HS::FLAG::PREFILTER, 'P'},
    {HS::FLAG::SOM_LEFTMOST, 'L'},
    {HS::FLAG::COMBINATION, 'C'},
    {HS::FLAG::QUIET, 'Q'}
};

HS::Pattern::Pattern(const std::string& expression) {
    auto firstSlash = expression.find('/');
    auto lastSlash = expression.rfind('/');
    id_ = std::stoul(expression.substr(0, firstSlash));
    expr_ = expression.substr(firstSlash + 1, lastSlash - firstSlash - 1);
    std::string suffix = expression.substr(lastSlash + 1);
    for (auto& v : suffix) {
        flags_ |= static_cast<unsigned int>(conversion.at(v));
    }
}

std::string HS::Pattern::toString() {
    std::string flagsString = "";
    for (auto& [k, v] : reConversion) {
        if (flags_ & static_cast<unsigned int>(k)) {
            flagsString += v;
        }
    }
    return std::format("{}:/{}/{}", id_, expr_, flagsString);
}