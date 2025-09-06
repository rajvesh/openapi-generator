// ...gtest unit test for Tag model...
#include <gtest/gtest.h>
#include "models/Tag.h"
#include <nlohmann/json.hpp>

using namespace sample::models;

TEST(TagModelTest, ConstructorAndGettersSetters) {
    Tag tag;
    tag.setId(42);
    tag.setName("Cute");
    EXPECT_EQ(tag.getId(), 42);
    EXPECT_EQ(tag.getName(), "Cute");
}

TEST(TagModelTest, JsonSerialization) {
    Tag tag;
    tag.setId(42);
    tag.setName("Cute");
    nlohmann::json j = Tag::toJson(tag);
    EXPECT_EQ(j["id"], 42);
    EXPECT_EQ(j["name"], "Cute");
    Tag tag2 = Tag::fromJson(j);
    EXPECT_EQ(tag2.getId(), 42);
    EXPECT_EQ(tag2.getName(), "Cute");
}
// ...end of test file...