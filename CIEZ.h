#ifndef CIEZ_H
#define CIEZ_H

#define KEY_IS_PRESSED 0x7FFF
#include <Windows.h>
class CIEZ
{
 private:
    short VK[4];
	HWND consoleID;
	COORD begCoord;
	COORD position;
	HANDLE consoleHandle;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	DWORD writtenChars;
	DWORD screenSize;
public:
CIEZ(HANDLE &h);
~CIEZ();
void clearScreen();
int reqInput(int mindelim, int maxdelim);
};
#endif