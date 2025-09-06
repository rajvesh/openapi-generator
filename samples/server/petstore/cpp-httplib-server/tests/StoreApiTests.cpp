// ...gtest unit test for StoreApi handler...
#include <gtest/gtest.h>
#include "api/StoreApi.h"

using namespace api;

class MockStoreApi : public Store {
public:
    void handleDeleteForStoreOrderorderId() override {}
    GetResponseForStoreInventory handleGetForStoreInventory() override {
        return 42;
    }
    GetResponseForStoreOrderorderId handleGetForStoreOrderorderId() override {
        return sample::models::Order();
    }
    PostResponseForStoreOrder handlePostForStoreOrder(const PostRequestForStoreOrder&) override {
        return sample::models::Order();
    }
};

TEST(StoreApiTest, HandlerInvocation) {
    MockStoreApi api;
    api.handleDeleteForStoreOrderorderId();
    auto resp1 = api.handleGetForStoreInventory();
    EXPECT_TRUE(std::holds_alternative<int>(resp1));
    auto resp2 = api.handleGetForStoreOrderorderId();
    EXPECT_TRUE(std::holds_alternative<sample::models::Order>(resp2));
    Store::PostRequestForStoreOrder req;
    auto resp3 = api.handlePostForStoreOrder(req);
    EXPECT_TRUE(std::holds_alternative<sample::models::Order>(resp3));
}

TEST(StoreApiTest, HandleGetResponseForStoreInventory) {
    httplib::Response res;
    Store::GetResponseForStoreInventory result = 42;
    Store::handleGetResponseForStoreInventory(result, res);
    EXPECT_EQ(res.body, "42");
}

TEST(StoreApiTest, HandleGetResponseForStoreOrderorderId) {
    httplib::Response res;
    sample::models::Order order;
    order.setId(7);
    Store::GetResponseForStoreOrderorderId result = order;
    Store::handleGetResponseForStoreOrderorderId(result, res);
    nlohmann::json j = nlohmann::json::parse(res.body);
    EXPECT_EQ(j["id"], 7);
}

TEST(StoreApiTest, ParsePostRequestForStoreOrder) {
    httplib::Request req;
    nlohmann::json j = { {"id", 8}, {"status", "placed"} };
    req.body = j.dump();
    auto params = Store::parsePostRequestForStoreOrder(req);
    ASSERT_TRUE(params.m_request.has_value());
    EXPECT_EQ(params.m_request->getId(), 8);
}

TEST(StoreApiTest, HandlePostResponseForStoreOrder) {
    httplib::Response res;
    sample::models::Order order;
    order.setId(9);
    Store::PostResponseForStoreOrder result = order;
    Store::handlePostResponseForStoreOrder(result, res);
    nlohmann::json j = nlohmann::json::parse(res.body);
    EXPECT_EQ(j["id"], 9);
}
// ...end of test file...