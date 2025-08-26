#include "orders/LivePaymentGateway.hpp"
#include <chrono>

namespace orders {

bool LivePaymentGateway::charge(const std::string& user, int cents, std::string& out_txn_id) {
    (void)user;

    if (cents <= 0 || cents > 100000) {
        return false;
    }

    using namespace std::chrono;
    const auto now = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
    out_txn_id = "SIM-" + std::to_string(now) + "-" + std::to_string(cents);
    return true;
}

} // namespace orders
