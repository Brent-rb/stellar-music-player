#define MINIAUDIO_IMPLEMENTATION
#include <fmt/format.h>
#include <miniaudio.h>
#include <stellar/stellar.h>

#include <iostream>

using namespace stellar;

Stellar::Stellar(std::string _name) : name(std::move(_name)) {}

std::string Stellar::greet(LanguageCode lang) const {
    switch (lang) {
        default:
        case LanguageCode::EN:
            return fmt::format("Hello, {}!", name);
        case LanguageCode::DE:
            return fmt::format("Hallo {}!", name);
        case LanguageCode::ES:
            return fmt::format("¡Hola {}!", name);
        case LanguageCode::FR:
            return fmt::format("Bonjour {}!", name);
    }
}

int Stellar::test() const {
    ma_result result;
    ma_engine engine;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return -1;
    }

    result = ma_engine_play_sound(&engine, "test.m4a", NULL);
    if (result != MA_SUCCESS) {
        std::cerr << "Can't play file" << std::endl;
        return -1;
    }

    printf("Press Enter to quit...");
    getchar();

    ma_engine_uninit(&engine);

    return 0;
}
