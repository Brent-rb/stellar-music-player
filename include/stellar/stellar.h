#pragma once

#include <string>

namespace stellar {

    /**  Language codes to be used with the Stellar class */
    enum class LanguageCode { EN, DE, ES, FR };

    /**
     * @brief A class for saying hello in multiple languages
     */
    class Stellar {
        std::string name;

      public:
        /**
         * @brief Creates a new greeter
         * @param name the name to greet
         */
        Stellar(std::string name);

        /**
         * @brief Creates a localized string containing the greeting
         * @param lang the language to greet in
         * @return a string containing the greeting
         */
        std::string greet(LanguageCode lang = LanguageCode::EN) const;
    };

}  // namespace stellar
