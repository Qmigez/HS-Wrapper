#include <gtest/gtest.h>

#include "HSWrapper/Meta.h"
#include "HSWrapper/Pattern.h"

#include "HSWrapper/Compile/Database.h"
#include "HSWrapper/Compile/PlatformInfo.h"

#include "HSWrapper/Runtime/Scratch.h"

#include "TestsCore.h"

const std::function<void*(size_t)> customAlloc = 
[](size_t c) -> void* { 
    void *mem = malloc(c + 2);
    if (!mem) {
        return nullptr;
    }
    return (char*)mem + 2; 
};
const std::function<void(void*)> customFree = 
[](void* mem) -> void { 
    if (!mem) {
        return;
    }
    free((char *)mem - 2);
};

TEST(CustomAlloc, simple) {
    HS::Meta::setAllocator(customAlloc, customFree);
    HS::Database db = HS::Database::compile(
        HS::Pattern("0:/a/"),
        HS::MODE::BLOCK,
        HS::PlatformInfo()
    );
    HS::Scratch sc = db.allocScratch();
    
    SmartHandler sh;
    db.scan("a", 0, sc, sh);

    ASSERT_EQ(sh.getResult(), std::unordered_multiset<std::string>{"0:0:1:0"});
};