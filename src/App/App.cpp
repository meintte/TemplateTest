#include <TemplateTest/App/App.hpp>

int App::run(int argc, const char** argv) {
    try {
        m_params = UserParameters::parse(argc, argv);
    } catch (const UserParameters::ExitCode& e) {
        return e.code;
    }

    return EXIT_SUCCESS;
}
