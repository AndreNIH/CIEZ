#include "CIEZ.h"

CIEZ::CIEZ(HANDLE &h)
{
    	VK[0] = VK_RETURN;
		VK[1] = VK_DOWN;
		VK[2] = VK_UP;
		consoleHandle = h;
		GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
		consoleID = GetForegroundWindow();
		begCoord = { 0,0 };
		position = { 0,0 };
}

CIEZ::~CIEZ() {CloseHandle(consoleHandle);}

void CIEZ::clearScreen()
{
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
	screenSize = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;
	FillConsoleOutputCharacter(consoleHandle, ' ', screenSize, begCoord, &writtenChars);
	SetConsoleCursorPosition(consoleHandle, begCoord);
}

int CIEZ::reqInput(int mindelim,int maxdelim)
{
    SetConsoleCursorPosition(consoleHandle, position);
		for(;;)
		{
		GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
		//CURSOR IS OUT OF MAXDELIM RANGE
		
		if (consoleInfo.dwCursorPosition.Y + 1 > maxdelim)
			{
				position.Y = mindelim + 1; 
				SetConsoleCursorPosition(consoleHandle, position);
			}
			//CURSOR IS OUT OF MINDELIMITATOR RANGE
			if (position.Y <= mindelim)
			{
				position.Y = maxdelim - 1;
				
				SetConsoleCursorPosition(consoleHandle, position);
			}
			for (auto &vKey : VK)
			{
				if (GetForegroundWindow() == consoleID && GetAsyncKeyState(vKey) & KEY_IS_PRESSED)
					switch (vKey)
					{
					case VK_RETURN:
						return position.Y;
						break;
					case VK_DOWN:
						position.Y += 1;
						SetConsoleCursorPosition(consoleHandle, position);
						break;
					case VK_UP:
						position.Y += -1;
						SetConsoleCursorPosition(consoleHandle, position);
						break;
					}
				Sleep(10);
			}
		}
};
