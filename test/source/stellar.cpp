#include <doctest/doctest.h>
#include <stellar/stellar.h>
#include <stellar/version.h>

#include <string>

TEST_CASE("Stellar") {
  using namespace stellar;

  Stellar stellar("Tests");

  CHECK(stellar.greet(LanguageCode::EN) == "Hello, Tests!");
  CHECK(stellar.greet(LanguageCode::DE) == "Hallo Tests!");
  CHECK(stellar.greet(LanguageCode::ES) == "¡Hola Tests!");
  CHECK(stellar.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("Stellar version") {
  static_assert(std::string_view(STELLAR_VERSION) == std::string_view("1.0"));
  CHECK(std::string(STELLAR_VERSION) == std::string("1.0"));
}
