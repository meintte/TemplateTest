#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <CLI/CLI.hpp>
#include <TemplateTest/App/UserParameters.hpp>

// This file will be generated automatically when cur_you run the CMake
// configuration step. It creates a namespace called `TemplateTest`. You can
// modify the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>

UserParameters UserParameters::parse(int argc, const char** argv) {
    UserParameters params;

    CLI::App app{fmt::format("{} version {}", TemplateTest::cmake::project_name,
                             TemplateTest::cmake::project_version)};

    // general flags
    app.set_version_flag("--version",
                         std::string{TemplateTest::cmake::project_version},
                         "Show version information");
    app.set_config("--config")->check(CLI::ExistingFile);
    app.option_defaults()->always_capture_default();

    // Output directory
    app.add_option("--output", params.output_dir, "Output directory")
        ->check(CLI::ExistingDirectory);

    // Grid in x direction
    auto* gridX = app.add_option_group("GridX", "Grid in x direction");
    gridX->add_option("--nx", params.nx, "Number of grid cells in x direction")
        ->check(CLI::PositiveNumber);
    gridX->add_option("--Lx", params.Lx, "Length of grid in x direction")
        ->check(CLI::PositiveNumber);

    // Grid in y direction
    auto* gridY = app.add_option_group("GridY", "Grid in y direction");
    gridY->add_option("--ny", params.ny, "Number of grid cells in y direction")
        ->check(CLI::PositiveNumber);
    gridY->add_option("--Ly", params.Ly, "Length of grid in y direction")
        ->check(CLI::PositiveNumber);

    // Material properties
    auto* matrix = app.add_option_group("Matrix", "Matrix properties");
    matrix->add_option("--km", params.km, "Matrix permeability")
        ->check(CLI::PositiveNumber);
    matrix->add_option("--phi", params.phi, "Matrix porosity")
        ->check(CLI::Range(0.0, 1.0));

    // Monte Carlo
    auto* monteCarlo = app.add_option_group("MC", "Monte Carlo");
    monteCarlo->add_option("--seed", params.seed, "Random seed")
        ->check(CLI::PositiveNumber);
    monteCarlo
        ->add_option("iterations", params.iterations, "Number of iterations")
        ->check(CLI::PositiveNumber);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        throw ExitCode(app.exit(e));
    }

    spdlog::info("Config:\n{}", app.config_to_str(true, true));

    return params;
}
