#pragma once

#include <filesystem>
#include <exception>

struct UserParameters {
    std::filesystem::path output_dir = "test";

    // GRID
    int32_t nx = 10;
    int32_t ny = 5;

    double Lx = 1.0;
    double Ly = 0.5;

    // MATERIAL PROPERTIES
    double km = 1.0;
    double phi = 1.0;

    // MONTE CARLO
    int32_t seed = 42;
    int32_t iterations = 1000;

    // To pass the exit code from CLI11 to the caller of the parse function
    struct ExitCode : public std::exception {
        explicit ExitCode(int code_) : code(code_) {}
        int code;
    };

    static UserParameters parse(int argc, const char **argv);
};