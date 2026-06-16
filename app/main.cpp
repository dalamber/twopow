#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>

#include "twopow/twopow.hpp"

namespace {

constexpr int kExitSuccess = 0;
constexpr int kExitUsage = 2;
constexpr int kExitOverflow = 1;

constexpr const char* kLogo =
    "   _                                          ___\n"
    "  | |___      _____  _ __   _____      __    |_  )\n"
    "  | __\\ \\ /\\ / / _ \\| '_ \\ / _ \\ \\ /\\ / /     / /\n"
    "  | |_ \\ V  V / (_) | |_) | (_) \\ V  V /     /___|\n"
    "   \\__| \\_/\\_/ \\___/| .__/ \\___/ \\_/\\_/     base-2, forever\n"
    "                    |_|\n"
    "        deterministic base-2 exponentiation  -  2^n = 1 << n\n";

void print_usage(std::ostream& os) {
    os << "Usage: twopow-cli [EXPONENT]\n"
       << "Compute 2 raised to EXPONENT (default " << twopow::kDefaultExponent
       << ").\n\n"
       << "Options:\n"
       << "  -h, --help     Show this help and exit.\n"
       << "  -v, --version  Show version information and exit.\n"
       << "      --logo     Print the project logo and exit.\n";
}

}  // namespace

int main(int argc, char** argv) {
    std::string_view arg = (argc > 1) ? argv[1] : "";

    if (arg == "-h" || arg == "--help") {
        print_usage(std::cout);
        return kExitSuccess;
    }
    if (arg == "-v" || arg == "--version") {
        std::cout << "twopow-cli " << TWOPOW_VERSION << "\n";
        return kExitSuccess;
    }
    if (arg == "--logo") {
        std::cout << kLogo;
        return kExitSuccess;
    }

    unsigned exponent = twopow::kDefaultExponent;
    if (!arg.empty()) {
        try {
            std::size_t consumed = 0;
            const std::string s(arg);
            const unsigned long parsed = std::stoul(s, &consumed);
            if (consumed != s.size()) {
                std::cerr << "twopow-cli: not a valid exponent: " << arg
                          << "\n";
                return kExitUsage;
            }
            exponent = static_cast<unsigned>(parsed);
        } catch (const std::exception&) {
            std::cerr << "twopow-cli: not a valid exponent: " << arg << "\n";
            return kExitUsage;
        }
    }

    try {
        std::cout << twopow::two_pow(exponent) << "\n";
    } catch (const twopow::overflow_error& e) {
        std::cerr << e.what() << "\n";
        return kExitOverflow;
    }
    return kExitSuccess;
}
