#include <gtest/gtest.h>
#include "models/ApiResponse.h"
#include <nlohmann/json.hpp>

using namespace sample::models;

TEST(ApiResponseModelTest, ConstructorAndGettersSetters) {
    ApiResponse resp;
    resp.setCode(200);
    resp.setType("info");
    resp.setMessage("ok");
    EXPECT_EQ(resp.getCode(), 200);
    EXPECT_EQ(resp.getType(), "info");
    EXPECT_EQ(resp.getMessage(), "ok");
}

TEST(ApiResponseModelTest, JsonSerialization) {
    ApiResponse resp;
    resp.setCode(200);
    resp.setType("info");
    resp.setMessage("ok");
    nlohmann::json j = ApiResponse::toJson(resp);
    EXPECT_EQ(j["code"], 200);
    EXPECT_EQ(j["type"], "info");
    EXPECT_EQ(j["message"], "ok");
    ApiResponse resp2 = ApiResponse::fromJson(j);
    EXPECT_EQ(resp2.getCode(), 200);
    EXPECT_EQ(resp2.getType(), "info");
    EXPECT_EQ(resp2.getMessage(), "ok");
}
