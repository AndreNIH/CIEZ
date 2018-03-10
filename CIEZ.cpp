#include "CIEZ.h"

CIEZ::CIEZ(HANDLE &h, short startingXpos,short startingYpos)
{
    	VK[0] = VK_RETURN;
		VK[1] = VK_DOWN;
		VK[2] = VK_UP;
		consoleHandle = h;
		GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
		consoleID = GetForegroundWindow();
		begCoord = { 0,0 };
		position = { startingXpos,startingXpos };
}

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

void CIEZ::setNewPosition(short x, short y) { position.X = x; position.Y = y;}
void CIEZ::updatePosition() {SetConsoleCursorPosition(consoleHandle, position);}

int CIEZ::reqInput(int mindelim,int maxdelim)
{
    SetConsoleCursorPosition(consoleHandle, position);
		for(;;)
		{
		GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
		
		if (consoleInfo.dwCursorPosition.Y + 1 > maxdelim)
			{
				position.Y = mindelim + 1; 
				SetConsoleCursorPosition(consoleHandle, position);
			}

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
			}
			Sleep(10);
		}
};
