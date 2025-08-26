#include "orders/LivePaymentGateway.hpp"
#include "orders/OrderService.hpp"
#include <iostream>

int main() {
    orders::LivePaymentGateway gateway;
    orders::OrderService service(gateway);

    try {
        const auto txn = service.placeOrder("alice", 1999);
        std::cout << "Order success. TXN = " << txn << "\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Order failed: " << ex.what() << "\n";
        return 1;
    }
}
