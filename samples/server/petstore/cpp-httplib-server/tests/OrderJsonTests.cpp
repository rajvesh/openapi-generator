// ...gtest unit test for Order model...
#include <gtest/gtest.h>
#include "models/Order.h"
#include <nlohmann/json.hpp>

using namespace sample::models;

TEST(OrderModelTest, ConstructorAndGettersSetters) {
    Order order;
    order.setId(100);
    order.setPetId(200);
    order.setQuantity(2);
    order.setShipDate("2024-01-01");
    order.setStatus(OrderStatus::approved);
    order.setComplete(true);
    EXPECT_EQ(order.getId(), 100);
    EXPECT_EQ(order.getPetId(), 200);
    EXPECT_EQ(order.getQuantity(), 2);
    EXPECT_EQ(order.getShipDate(), "2024-01-01");
    EXPECT_EQ(order.getStatus(), OrderStatus::approved);
    EXPECT_EQ(order.isComplete(), true);
}

TEST(OrderModelTest, JsonSerialization) {
    Order order;
    order.setId(100);
    order.setPetId(200);
    order.setQuantity(2);
    order.setShipDate("2024-01-01");
    order.setStatus(OrderStatus::approved);
    order.setComplete(true);
    nlohmann::json j = Order::toJson(order);
    EXPECT_EQ(j["id"], 100);
    EXPECT_EQ(j["petId"], 200);
    EXPECT_EQ(j["quantity"], 2);
    EXPECT_EQ(j["shipDate"], "2024-01-01");
    EXPECT_EQ(j["status"], "approved");
    EXPECT_EQ(j["complete"], true);
    Order order2 = Order::fromJson(j);
    EXPECT_EQ(order2.getId(), 100);
    EXPECT_EQ(order2.getPetId(), 200);
    EXPECT_EQ(order2.getQuantity(), 2);
    EXPECT_EQ(order2.getShipDate(), "2024-01-01");
    EXPECT_EQ(order2.getStatus(), OrderStatus::approved);
    EXPECT_EQ(order2.isComplete(), true);
}
// ...end of test file...