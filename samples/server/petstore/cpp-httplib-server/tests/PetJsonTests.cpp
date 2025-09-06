// ...gtest unit test for Pet model...
#include <gtest/gtest.h>
#include "models/Pet.h"
#include <nlohmann/json.hpp>
#include "models/Category.h"
#include "models/Tag.h"

using namespace sample::models;

TEST(PetModelTest, ConstructorAndGettersSetters) {
    Pet pet;
    pet.setId(1);
    Category cat;
    cat.setId(2);
    cat.setName("Dog");
    pet.setCategory(cat);
    pet.setName("Doggo");
    pet.setPhotoUrls({"url1", "url2"});
    Tag tag;
    tag.setId(3);
    tag.setName("Cute");
    pet.setTags({tag});
    pet.setStatus(PetStatus::available);
    EXPECT_EQ(pet.getId(), 1);
    EXPECT_EQ(pet.getCategory().getId(), 2);
    EXPECT_EQ(pet.getCategory().getName(), "Dog");
    EXPECT_EQ(pet.getName(), "Doggo");
    EXPECT_EQ(pet.getPhotoUrls().size(), 2);
    EXPECT_EQ(pet.getTags().size(), 1);
    EXPECT_EQ(pet.getTags()[0].getId(), 3);
    EXPECT_EQ(pet.getTags()[0].getName(), "Cute");
    EXPECT_EQ(pet.getStatus(), PetStatus::available);
}

TEST(PetModelTest, JsonSerialization) {
    Pet pet;
    pet.setId(1);
    Category cat;
    cat.setId(2);
    cat.setName("Dog");
    pet.setCategory(cat);
    pet.setName("Doggo");
    pet.setPhotoUrls({"url1", "url2"});
    Tag tag;
    tag.setId(3);
    tag.setName("Cute");
    pet.setTags({tag});
    pet.setStatus(PetStatus::available);
    nlohmann::json j = Pet::toJson(pet);
    EXPECT_EQ(j["id"], 1);
    EXPECT_EQ(j["category"]["id"], 2);
    EXPECT_EQ(j["category"]["name"], "Dog");
    EXPECT_EQ(j["name"], "Doggo");
    EXPECT_EQ(j["photoUrls"].size(), 2);
    EXPECT_EQ(j["tags"].size(), 1);
    EXPECT_EQ(j["tags"][0]["id"], 3);
    EXPECT_EQ(j["tags"][0]["name"], "Cute");
    EXPECT_EQ(j["status"], "available");
    Pet pet2 = Pet::fromJson(j);
    EXPECT_EQ(pet2.getId(), 1);
    EXPECT_EQ(pet2.getCategory().getId(), 2);
    EXPECT_EQ(pet2.getCategory().getName(), "Dog");
    EXPECT_EQ(pet2.getName(), "Doggo");
    EXPECT_EQ(pet2.getPhotoUrls().size(), 2);
    EXPECT_EQ(pet2.getTags().size(), 1);
    EXPECT_EQ(pet2.getTags()[0].getId(), 3);
    EXPECT_EQ(pet2.getTags()[0].getName(), "Cute");
    EXPECT_EQ(pet2.getStatus(), PetStatus::available);
}
// ...end of test file...