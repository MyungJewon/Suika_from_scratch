#include "app/SuikaApp.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#else
int main(int, char**) {
#endif
    SuikaApp app(800, 600, "Suika Game");
    app.Run();
    return 0;
}
