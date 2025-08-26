#pragma once
#include "IPaymentGateway.hpp"

namespace orders {

class LivePaymentGateway : public IPaymentGateway {
public:
    bool charge(const std::string& user, int cents, std::string& out_txn_id) override;
};

} // namespace orders
