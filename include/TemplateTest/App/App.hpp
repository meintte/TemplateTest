#pragma once
#include <TemplateTest/App/UserParameters.hpp>

class App {
public:
    int run(int argc, const char** argv);

private:
    UserParameters m_params{};
};
