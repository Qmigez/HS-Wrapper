#include <unordered_set>
#include <string>
#include <tuple>
#include <vector>

#include "HSWrapper/Pattern.h"

const std::vector<
    std::tuple<
        std::vector<HS::Pattern>, // паттерны
        std::vector<
            std::pair<std::string, std::unordered_multiset<std::string>> // пара (data, result)
        >
    >
> inputData = {
    {
        // паттерны
        {
            HS::Pattern("0:/a/")
        },
        // результаты
        {
            {
                "abca", {
                    "0:0:1:0", 
                    "0:0:4:0"
                }
            },
            {
                "abcb", {
                    "0:0:1:0"
                }
            }
        }
    },
    {
        // паттерны
        {
            HS::Pattern("0:/a/"),
            HS::Pattern("1:/ab/")
        },
        // результаты
        {
            {
                "abca", {
                    "0:0:1:0", 
                    "0:0:4:0",
                    "1:0:2:0"
                }
            }, {
                "accc", {
                    "0:0:1:0"
                }
            }
        }
    }
};