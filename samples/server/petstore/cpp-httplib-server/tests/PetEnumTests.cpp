// ...gtest unit test for Pet model enum...
#include <gtest/gtest.h>
#include "models/Pet.h"
#include <nlohmann/json.hpp>

using namespace sample::models;

TEST(PetModelTest, EnumConversion) {
    EXPECT_EQ(PetStatusEnumFromString("available"), PetStatus::available);
    EXPECT_EQ(PetStatusEnumFromString("pending"), PetStatus::pending);
    EXPECT_EQ(PetStatusEnumFromString("sold"), PetStatus::sold);
    EXPECT_EQ(PetStatusEnumFromString("unknown"), PetStatus::unknown);
    EXPECT_EQ(PetStatusEnumToString(PetStatus::available), "available");
    EXPECT_EQ(PetStatusEnumToString(PetStatus::pending), "pending");
    EXPECT_EQ(PetStatusEnumToString(PetStatus::sold), "sold");
    EXPECT_EQ(PetStatusEnumToString(PetStatus::unknown), "unknown");
}
// ...end of test file...