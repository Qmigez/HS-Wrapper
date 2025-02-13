
#include "gtest/gtest.h"

#include "HSWrapper/Pattern.h"

#include "HSWrapper/Compile/Database.h"
#include "HSWrapper/Compile/PlatformInfo.h"

#include "HSWrapper/Runtime/Scratch.h"
#include "HSWrapper/Runtime/Stream.h"

#include "TestsCore.h"

TEST(Simple, Block) {
    HS::Database db1 = HS::Database::compile(
        HS::Pattern("0:/a/"),
        HS::MODE::BLOCK,
        HS::PlatformInfo()
    );
    
    HS::Scratch sc = db1.allocScratch();
    SmartHandler sh;
    std::string data = "abca";
    db1.scan(data, 0, sc, sh);

    ASSERT_EQ(sh.getResult(), "0:0:1:0\n0:0:4:0\n");
}

TEST(Simple, Stream) {
    HS::Database db1 = HS::Database::compile(
        HS::Pattern("0:/a/"),
        HS::MODE::STREAM,
        HS::PlatformInfo()
    );
    
    HS::Scratch sc = db1.allocScratch();
    
    HS::Stream stream = db1.openStream(0);
    SmartHandler sh;

    stream.scan("ab", 0, sc, sh);
    stream.scan("ca", 0, sc, sh);

    ASSERT_EQ(sh.getResult(), "0:0:1:0\n0:0:4:0\n");
}