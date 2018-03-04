#include "CIEZ.h"
#include <iostream>
int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CIEZ consoleIO(h);

	std::cout << "What should i do this winter?\nBuild a nuke\nSend a man to mars\nNothing lol";
	switch (consoleIO.reqInput(0, 4))
	{
	case 1:
		consoleIO.clearScreen();
		std::cout << "NUKE EM!";
		break;
	case 2:
		consoleIO.clearScreen();
		std::cout << "SpaceX got nothing on me";
		break;
	case 3:
		consoleIO.clearScreen();
		std::cout << "so productive;";
		break;
	}
	std::cin.ignore(32767, '\n');
	std::cin.get();
  return 0;
}
