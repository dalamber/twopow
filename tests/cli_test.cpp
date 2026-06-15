#include <gtest/gtest.h>

#include <array>
#include <cstdio>
#include <string>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#else
#include <sys/wait.h>
#endif

namespace {

struct CommandResult {
    std::string output;
    int exit_code;
};

CommandResult run(const std::string& args) {
    const std::string command = std::string(TWOPOW_CLI_PATH) + " " + args;
    std::array<char, 256> buffer{};
    std::string output;
    FILE* pipe = popen(command.c_str(), "r");
    if (pipe == nullptr) {
        return {"", -1};
    }
    while (std::fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        output += buffer.data();
    }
    const int status = pclose(pipe);
#ifdef _WIN32
    const int code = status;
#else
    const int code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
#endif
    return {output, code};
}

}  // namespace

TEST(Cli, DefaultExponentPrintsFour) {
    const CommandResult result = run("");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.output, "4\n");
}

TEST(Cli, ExplicitExponent) {
    const CommandResult result = run("10");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.output, "1024\n");
}

TEST(Cli, OverflowExitsNonZero) {
    const CommandResult result = run("64");
    EXPECT_EQ(result.exit_code, 1);
}

TEST(Cli, InvalidInputExitsTwo) {
    const CommandResult result = run("banana");
    EXPECT_EQ(result.exit_code, 2);
}
