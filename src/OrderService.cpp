#include "orders/OrderService.hpp"

namespace orders {

OrderService::OrderService(IPaymentGateway& gateway)
    : gateway_(gateway) {}

std::string OrderService::placeOrder(const std::string& user, int cents) {
    if (user.empty()) {
        throw std::invalid_argument("user must not be empty");
    }
    if (cents <= 0) {
        throw std::invalid_argument("cents must be positive");
    }

    std::string txn;
    const bool ok = gateway_.charge(user, cents, txn);
    if (!ok) {
        throw std::runtime_error("payment failed");
    }
    return txn;
}

} // namespace orders
