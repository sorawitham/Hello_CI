#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "orders/IPaymentGateway.hpp"
#include "orders/OrderService.hpp"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

namespace orders {

// Mock dependency
class MockPaymentGateway : public IPaymentGateway {
public:
    MOCK_METHOD(bool, charge,
                (const std::string& user, int cents, std::string& out_txn_id),
                (override));
};

TEST(OrderService, HappyPath_ReturnsTxnId) {
    MockPaymentGateway mock;
    OrderService service(mock);

    EXPECT_CALL(mock, charge("alice", 5000, _))
        .WillOnce(DoAll(SetArgReferee<2>(std::string("TXN-42")), Return(true)));

    const auto txn = service.placeOrder("alice", 5000);
    EXPECT_EQ(txn, "TXN-42");
}

TEST(OrderService, InvalidInput_Throws) {
    MockPaymentGateway mock;
    OrderService service(mock);

    EXPECT_THROW(service.placeOrder("", 100), std::invalid_argument);
    EXPECT_THROW(service.placeOrder("bob", 0), std::invalid_argument);
    EXPECT_THROW(service.placeOrder("bob", -10), std::invalid_argument);
}

TEST(OrderService, PaymentFailed_Throws) {
    MockPaymentGateway mock;
    OrderService service(mock);

    EXPECT_CALL(mock, charge("bob", 200000, _))
        .WillOnce(DoAll(SetArgReferee<2>(std::string()), Return(false)));

    EXPECT_THROW(service.placeOrder("bob", 200000), std::runtime_error);
}

} // namespace orders
