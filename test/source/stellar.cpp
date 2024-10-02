#include <doctest/doctest.h>
#include <stellar/stellar.h>
#include <stellar/version.h>

#include <string>

TEST_CASE("Stellar") {
    using namespace stellar;

    Stellar stellar;
}

TEST_CASE("Stellar version") {
    static_assert(std::string_view(STELLAR_VERSION) == std::string_view("1.0"));
    CHECK(std::string(STELLAR_VERSION) == std::string("1.0"));
}
