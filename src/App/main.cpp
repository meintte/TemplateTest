#include <TemplateTest/App/App.hpp>
#include <memory>

int main(int argc, const char** argv) {
    auto app = std::make_unique<App>();

    return app->run(argc, argv);
}
