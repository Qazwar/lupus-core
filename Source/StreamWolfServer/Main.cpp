#include "Linker.h"
#include "Application.h"

using namespace std;
using namespace StreamWolf::Application;

int main(int argc, char** argv)
{
    int result = 0;
    Application app;
    
    if ((result = app.Initialize(argc, argv) != 0)) {
        return result;
    } else if ((result = app.Execute()) != 0 && result != -1) {
        return result;
    } else if ((result = app.Shutdown()) != 0) {
        return result;
    }

    return 0;
}
