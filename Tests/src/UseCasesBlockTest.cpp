#include "gtest/gtest.h"

#include "HSWrapper/Compile/Database.h"
#include "HSWrapper/Compile/PlatformInfo.h"

#include "HSWrapper/Runtime/Scratch.h"

#include "TestsCore.h"
#include "TestsData.h"

TEST(Block, Regular) {
    for (auto& [patterns, data] : inputData) {
        if (patterns.size() == 1) {
            HS::Database db = HS::Database::compile(patterns[0], HS::MODE::BLOCK, HS::PlatformInfo());
            HS::Scratch sc = db.allocScratch();
            SmartHandler sh;
            for (auto& [data, result] : data) {
                sh.clearResult();
                db.scan(data, 0, sc, sh);
                ASSERT_EQ(sh.getResult(), result);
            }
        } else {
            HS::Database db = HS::Database::compileMulti(patterns, HS::MODE::BLOCK, HS::PlatformInfo());
            HS::Scratch sc = db.allocScratch();
            SmartHandler sh;
            for (auto& [data, result] : data) {
                sh.clearResult();
                db.scan(data, 0, sc, sh);
                ASSERT_EQ(sh.getResult(), result);
            }
        }
    }
}

TEST(Block, Move) {
    for (auto& [patterns, data] : inputData) {
        if (patterns.size() == 1) {
            HS::Database db = HS::Database::compile(std::move(patterns[0]), std::move(HS::MODE::BLOCK), std::move(HS::PlatformInfo()));
            HS::Scratch sc = db.allocScratch();
            SmartHandler sh;
            for (auto& [data, result] : data) {
                sh.clearResult();
                db.scan(std::move(data), 0, std::move(sc), sh);
                ASSERT_EQ(sh.getResult(), result);
            }
        } else {
            HS::Database db = HS::Database::compileMulti(std::move(patterns), std::move(HS::MODE::BLOCK), std::move(HS::PlatformInfo()));
            HS::Scratch sc = db.allocScratch();
            SmartHandler sh;
            for (auto& [data, result] : data) {
                sh.clearResult();
                db.scan(std::move(data), 0, std::move(sc), sh);
                ASSERT_EQ(sh.getResult(), result);
            }
        }
    }
}