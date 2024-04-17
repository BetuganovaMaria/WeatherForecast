#include <lib/application.h>
#include <string>
#include "windows.h"

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);
    std::string config_path = Parse(argc, argv);
    Application application = Application(config_path);
    application.Run();
    return 0;
}