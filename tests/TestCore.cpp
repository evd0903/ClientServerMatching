#include <gtest/gtest.h>
#include "../src/Core.h"
#include "../src/OrderBook.h"

class CoreTest : public ::testing::Test {
protected:
    void SetUp() override {
        core = &GetCore();
        core->reset();
    }

    void TearDown() override {
        core->reset();
    }

    Core* core;
};

TEST_F(CoreTest, HandleOrderWithoutDeal) {
    Core& core = GetCore();
    Order order(10, 60, OrderType::BUY, 1, 12345);
    core.addOrder(order);

    EXPECT_EQ(core.mOrderBook.getBuyOrders().size(), 1);
    EXPECT_EQ(core.mOrderBook.getSellOrders().size(), 0);
}

TEST_F(CoreTest, PartialExecution) {
    Core& core = GetCore();
    Order buyOrder(20, 60, OrderType::BUY, 1, 12345);
    Order sellOrder(10, 60, OrderType::SELL, 2, 12346);
    core.addOrder(buyOrder);
    core.addOrder(sellOrder);

    EXPECT_EQ(core.mOrderBook.getBuyOrders().size(), 1);
    EXPECT_EQ(core.mOrderBook.getSellOrders().size(), 0);
    EXPECT_EQ(core.mUsers[1].usdBalance, 10);
    EXPECT_EQ(core.mUsers[2].usdBalance, -10);
}

TEST_F(CoreTest, ExecutionWithMultipleOrders) {
    Core& core = GetCore();
    Order buyOrder1(10, 60, OrderType::BUY, 1, 12345);
    Order buyOrder2(10, 60, OrderType::BUY, 3, 12346);
    Order sellOrder(20, 60, OrderType::SELL, 2, 12347);
    core.addOrder(buyOrder1);
    core.addOrder(buyOrder2);
    core.addOrder(sellOrder);

    EXPECT_EQ(core.mOrderBook.getBuyOrders().size(), 0);
    EXPECT_EQ(core.mOrderBook.getSellOrders().size(), 0);
    EXPECT_EQ(core.mUsers[1].usdBalance, 10);
    EXPECT_EQ(core.mUsers[2].usdBalance, -20);
    EXPECT_EQ(core.mUsers[3].usdBalance, 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
