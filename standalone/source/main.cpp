#include <stellar/stellar.h>
#include <stellar/version.h>

#include <cstdio>
#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, const char* argv[]) -> int {
    stellar::Stellar stellar;

    if (argc == 2) {
        std::string file_path(argv[1]);
        stellar.init();
        std::cout << "[Info] Playing " << file_path << std::endl;
        stellar.playSong(file_path);

        char c = 'x';
        do {
            uint currentSeconds = static_cast<uint>(stellar.getCursorSeconds());
            uint maxSeconds = static_cast<uint>(stellar.getDurationSeconds());

            if (c != '\n')
                std::cout << "[" << currentSeconds / 60 << "m" << currentSeconds % 60 << "s - "
                          << maxSeconds / 60 << "m" << maxSeconds % 60 << "] "
                          << "Press one of the following: " << std::endl
                          << " - s: stop" << std::endl
                          << " - r: resume" << std::endl
                          << " - f: forward 10s" << std::endl
                          << " - b: backward 10s" << std::endl
                          << " - x: quit" << std::endl;
            c = getchar();

            switch (c) {
                case 's':
                    stellar.stop();
                    break;
                case 'r':
                    stellar.start();
                    break;
                case 'f':
                    stellar.seek(10);
                    break;
                case 'b':
                    stellar.seek(-10);
                    break;
            }
        } while (c != 'x');
    } else {
        std::cout << "Usage: ./stellar <song path>" << std::endl;
    }

    return 0;
}
