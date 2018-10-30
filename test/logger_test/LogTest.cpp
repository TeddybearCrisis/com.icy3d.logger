//
// Created by sgreve on 30.10.2018.
//

#include <Log.h>
#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>
#include <cppfs/cppfs.h>
#include "gtest/gtest.h"


using namespace icy3d;
using namespace cppfs;

TEST(Log_test, dummy_test) {
    EXPECT_TRUE(true);
}

TEST(Log_test, init_default_test) {
    Log::init("TestLogger");
    // not providing arguments to Log::init should create the default "logs" directory
    FileHandle fh = fs::open("logs");
    EXPECT_TRUE(fh.exists());
}

