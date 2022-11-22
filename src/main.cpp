#include "app.hpp"

int main(const int argc, const char* argv[]) {
    midikeys::app app{
        midikeys::app_paths::make_default()
    };

    app.run(argv);

    return 0;
};
