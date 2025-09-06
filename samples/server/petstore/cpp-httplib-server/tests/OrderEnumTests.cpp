#include <gtest/gtest.h>
#include "models/Order.h"

using namespace sample::models;

TEST(OrderModelTest, EnumConversion) {
    EXPECT_EQ(OrderStatusEnumFromString("placed"), OrderStatus::placed);
    EXPECT_EQ(OrderStatusEnumFromString("approved"), OrderStatus::approved);
    EXPECT_EQ(OrderStatusEnumFromString("delivered"), OrderStatus::delivered);
    EXPECT_EQ(OrderStatusEnumFromString("unknown"), OrderStatus::unknown);
    EXPECT_EQ(OrderStatusEnumToString(OrderStatus::placed), "placed");
    EXPECT_EQ(OrderStatusEnumToString(OrderStatus::approved), "approved");
    EXPECT_EQ(OrderStatusEnumToString(OrderStatus::delivered), "delivered");
    EXPECT_EQ(OrderStatusEnumToString(OrderStatus::unknown), "unknown");
}
