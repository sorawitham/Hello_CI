#pragma once
#include "IPaymentGateway.hpp"
#include <stdexcept>
#include <string>

namespace orders {

class OrderService {
public:
    explicit OrderService(IPaymentGateway& gateway);
    std::string placeOrder(const std::string& user, int cents);

private:
    IPaymentGateway& gateway_;
};

} // namespace orders
