#include <stellar/stellar.h>
#include <stellar/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main() -> int {
    stellar::Stellar stellar("Brent");

    return stellar.test();
}
