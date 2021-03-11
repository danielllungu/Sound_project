#include "Audio.h"
#include "Operations.h";
#include "Commands.h"
//=============================================================
int main()
{
	std::vector<Audio> vec;
	std::vector<Audio> modifiedPlaylist;
	std::cout << "Welcome to the soundprocessing application.\n";
	std::cout << "To see all the available operations for the songs list, type --help\n";
	std::cout << "To see all the available operations for a song, type --helpsong\n";
	std::cout << "To exit the application, type --exit\n";
	std::string command, path;
	std::getline(std::cin >> std::ws, command);
	while (command != "--exit")
	{
		Operations input(command);
		std::cout << "\n";
		input.Run(vec, modifiedPlaylist, path);
		std::cout << "\n";
		std::getline(std::cin >> std::ws, command);
	}




}
//=============================================================