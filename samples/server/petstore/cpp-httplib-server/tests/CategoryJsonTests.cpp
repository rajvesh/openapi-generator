// ...gtest unit test for Category model...
#include <gtest/gtest.h>
#include "models/Category.h"
#include <nlohmann/json.hpp>

using namespace sample::models;

TEST(CategoryModelTest, ConstructorAndGettersSetters) {
    Category cat;
    cat.setId(123);
    cat.setName("Cats");
    EXPECT_EQ(cat.getId(), 123);
    EXPECT_EQ(cat.getName(), "Cats");
}

TEST(CategoryModelTest, JsonSerialization) {
    Category cat;
    cat.setId(123);
    cat.setName("Cats");
    nlohmann::json j = Category::toJson(cat);
    EXPECT_EQ(j["id"], 123);
    EXPECT_EQ(j["name"], "Cats");
    Category cat2 = Category::fromJson(j);
    EXPECT_EQ(cat2.getId(), 123);
    EXPECT_EQ(cat2.getName(), "Cats");
}
// ...end of test file...