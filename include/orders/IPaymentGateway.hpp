#pragma once
#include <string>

namespace orders {

class IPaymentGateway {
public:
    virtual ~IPaymentGateway() = default;
    virtual bool charge(const std::string& user, int cents, std::string& out_txn_id) = 0;
};

} // namespace orders
