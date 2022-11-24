#include "app.hpp"

 int main(const int argc, const char* argv[]) {
    const auto app = std::make_shared<midikeys::app>(midikeys::app_paths::make_default());

    app->run(argv);

    return 0;
};
