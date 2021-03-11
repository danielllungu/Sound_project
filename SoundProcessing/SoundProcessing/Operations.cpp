#include "Operations.h"
#include "Commands.h"
#include <fstream>
//=============================================================
Operations::Operations(const std::string& command)
{
	this->command = command;
}

void Operations::SplitCommand(std::vector<std::string>& splittedCommand)
{
	std::string word = "";
	for (auto index : command)
	{
		if (index == ' ')
		{
			splittedCommand.push_back(word);
			word = "";
		}

		else
		{
			word = word + index;
		}
	}
	splittedCommand.push_back(word);
}

void Operations::Run(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist, std::string& FolderPath)
{

	if (command == "--help")
	{
		PrintPlaylistOperations();
	}

	else if (command == "--helpsong")
	{
		PrintSongOperations(vec);
	}

	else if (command.find("--load", 0) != std::string::npos)
	{
		Load(vec);
	}

	else if (command.find("--save", 0) != std::string::npos)
	{
		Save(modifiedPlaylist);
	}

	else if (command.find("--quickSave", 0) != std::string::npos)
	{
		QuickSave(modifiedPlaylist);
	}

	else if (command.find("--quickLoad", 0) != std::string::npos)
	{
		QuickLoad(vec, FolderPath);
	}

	else if (command.find("--setLoadPath", 0) != std::string::npos)
	{
		SetLoadPath(FolderPath);
	}

	else if (command.find("--artificialSignals", 0) != std::string::npos)
	{
		ArtificialSignals();
	}

	else if (command == "--printList")
	{
		PrintListOfAudios(command, vec);
	}

	else if (command.find("--playback", 0) != std::string::npos && command.find("--process", 0) == std::string::npos)
	{
		Playback(vec, modifiedPlaylist);
	}

	else if (command.find("--scale", 0) != std::string::npos && command.find("--process", 0) == std::string::npos)
	{
		Scale(vec, modifiedPlaylist);
	}

	else if (command == "--printModified")
	{
		PrintListOfAudios(command, modifiedPlaylist);
	}

	else if (command.find("--printSummary", 0) != std::string::npos)
	{
		PrintSummary(vec, modifiedPlaylist);
	}
	else if (CommandInModifySongMenu())
	{
		ModifySongMenu(vec);
	}

	else if (command.find("--removeAudio", 0) != std::string::npos)
	{
		RemoveSong(vec, modifiedPlaylist);
	}

	else if (command.find("--bassboost", 0) != std::string::npos)
	{
		BassBoost(vec, modifiedPlaylist);
	}

	else if (command.find("--treble", 0) != std::string::npos)
	{
		Treble(vec, modifiedPlaylist);
	}

	else if (command.find("--process", 0) != std::string::npos)
	{
		Process(command, vec, modifiedPlaylist);
	}

	else if (command.find("--fileconfig", 0) != std::string::npos)
	{
		ConfigurationFile(vec, modifiedPlaylist);
	}
	else
		std::cout << "Invalid command. Show available commands using: --help\n";
}

//=============================================================
void Operations::PrintPlaylistOperations()
{
	std::string menu = "\n--------------- HELP ---------------\n";
	menu = menu + "--load [path] \n";
	menu = menu + "--quickLoad [folderPath] [audioName/s] \n";
	menu = menu + "--setLoadPath [Path] --> saves a path to load songs from it, using only the song name, must end with '/' \n";
	menu = menu + "--save [audioName] [path] --> saves a modified song to a path.\n";
	menu = menu + "--fileconfig --> run commands from configuration file.\n";
	menu = menu + "--quickSave [audioName] --> saves a modified song to an auto path in the same directory.\n";
	menu = menu + "--printList --> this shows the Playlist you have loaded.\n";
	menu = menu + "--printModified --> this shows the Playlist you have modified.\n";
	menu = menu + "--artificialSignals [audioNameOut] [value Audio Length (in seconds)] [value Frequency (float) in Hz (ex: 340)] [value Sample Rate (float) in Hz (ex: 44100)] [path]\n";
	menu = menu + "--removeAudio [audioName]\n";
	menu = menu + "--playback [fast/slow] [value (0,9)] [audioNameIn] [audioNameOut]  --> the fast forward or slow motion effect; the audio resulted will be saved in the same directory.\n";
	menu = menu + "--scale [up/down] [value (0,9)] [audioNameIn] [audioNameOut] --> change the volume; the audio resulted will be saved in the same directory.\n";
	menu = menu + "--process [audioNameIn] [audioNameOut] --[operation/s]\n";
	menu = menu + "--bassboost [value (1,9)] [audioNameIn] [audioNameOut] \n";
	menu = menu + "--treble [value (1,9)] [audioNameIn] [audioNameOut] \n";
	menu = menu + "--printSummary [audioName]\n";
	menu = menu + "----------------------------------\n";
	std::cout << menu;
}

void Operations::PrintSongOperations(std::vector<Audio> vec)
{
	std::string menu = "\n--------------- HELP - modify song ---------------\n";
	menu = menu + "--getBitDepth [audioName]\n";
	menu = menu + "--getLengthInSeconds [audioName]\n";
	menu = menu + "--getNumChannels [audioName]\n";
	menu = menu + "--getNumSamplesPerChannel [audioName]\n";
	menu = menu + "--getSampleRate [audioName]\n";
	menu = menu + "--isMono [audioName]\n";
	menu = menu + "--isStereo [audioName]\n";
	menu = menu + "----------------------------------\n";
	std::cout << menu;
}

void Operations::PrintSummary(std::vector<Audio> vec, std::vector<Audio> modifiedPlaylist)
{
	Cmd_PrintSummary cmd(command);

	if (cmd.VerifyCommand() == 1)
	{
		if (foundSong(vec, cmd.GetAudioName()) == 1)
		{
			for (int index = 0; index < vec.size(); index++)
			{
				if (cmd.GetAudioName() == vec[index].GetName())
				{
					std::cout << "\n";
					vec[index].GetAudio().printSummary();
					std::cout << "\n";
				}
			}
		}
		else if (foundSong(modifiedPlaylist, cmd.GetAudioName()) == 1)
		{
			for (int index = 0; index < modifiedPlaylist.size(); index++)
			{
				if (cmd.GetAudioName() == modifiedPlaylist[index].GetName())
				{
					std::cout << "\n";
					modifiedPlaylist[index].GetAudio().printSummary();
					std::cout << "\n";
				}
			}
		}
		else
			std::cout << "Audio Name ot found.\n";
	}

	else
	{
		std::cout << "Invalid command. The format must be --printSummary [audioName]\n";
	}
}

void Operations::PrintListOfAudios(std::string com, std::vector<Audio> listOfAudios)
{
	if (com == "--printList")
	{
		Cmd_Printlist cmd(command);

		if (listOfAudios.empty() == true)
		{
			std::cout << "The playlist is empty.\n";

		}

		else
		{
			for (int index = 0; index < listOfAudios.size(); index++)
				std::cout << index + 1 << ". " << listOfAudios[index].GetName() << "--with path : " << listOfAudios[index].GetPath() << "\n";

		}


	}

	else if (com == "--printModified")
	{
		Cmd_PrintModified cmd(command);

		if (listOfAudios.empty() == true)
		{
			std::cout << "Modified playlist is empty.\n";

		}

		else
		{
			for (int index = 0; index < listOfAudios.size(); index++)
				std::cout << index + 1 << ". " << listOfAudios[index].GetName() << " -- Quick Save path : " << listOfAudios[index].GetPath() << "\n";
			std::cout << "\nTo save one of this songs in your computer use --save [audioName] [path] OR --quickSave [audioName]\n\n";

		}


	}
}

//=============================================================
AudioFile<double> Operations::SelectSong(std::vector<Audio> vec, int index)
{
	for (int index1 = 0; index1 < vec.size(); index1++)
		if (index1 == index)
			return vec[index1].GetAudio();
}



//=============================================================
int Operations::foundSong(std::vector<Audio> vec, std::string audioName)
{
	for (int index = 0; index < vec.size(); index++)
	{
		if (vec[index].GetName() == audioName)
			return 1;
	}
	return 0;
}

void Operations::RemoveSong(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist)
{
	Cmd_RemoveAudio cmd(command);
	if (vec.empty() == true)
	{
		std::cout << "You can't remove a song since the playlist is empty!\n";
	}

	else
	{
		if (cmd.VerifyCommand() == 1)
		{
			int ok_removed = 0;
			for (int index = 0; index < vec.size(); index++)
			{
				if (cmd.GetAudioName() == vec[index].GetName())
				{
					vec.erase(vec.begin() + index);
					ok_removed = 1;
				}
			}
			if (ok_removed == 0)
			{
				for (int index = 0; index < modifiedPlaylist.size(); index++)
				{
					if (cmd.GetAudioName() == modifiedPlaylist[index].GetName())
					{
						modifiedPlaylist.erase(modifiedPlaylist.begin() + index);
						ok_removed = 1;
					}
				}
			}
			if (ok_removed == 1)
				std::cout << "Audio Removed.\n";
			else
				std::cout << "Audio Name not found.\n";
		}

		else
		{
			std::cout << "ERROR! The format must be --removeAudio [audioName].\n";
		}
	}
}

void Operations::Load(std::vector<Audio>& vec)
{
	Cmd_Load cmd(command);
	if (cmd.VerifyCommand() == 1)
	{
		std::string path = "" + cmd.GetPath();
		std::cout << "Loading...\n";
		Audio aux(path);

		if (aux.GetAudio().getLengthInSeconds() == 0)
		{
			std::cout << "The Audio file you are trying to load has 0 seconds. Please try again.\n";
		}

		else
		{
			vec.push_back(aux);
			std::cout << "Added to list.\n";
		}
	}

	else
	{
		std::cout << "Invalid command. The command must be --load [path]\n";
	}
}

void Operations::ArtificialSignals()
{
	Cmd_ArtificialSignals cmd(command);
	if (cmd.VerifyCommand() == 1)
	{
		if (cmd.GetSignalLength() > 0)
		{
			AudioFile<double>::AudioBuffer buffer;

			AudioFile<double> audioFile;
			buffer.resize(2);

			int new_size = 46000 * cmd.GetSignalLength();
			float new_SampleRate = cmd.GetSampleRate();
			float new_Frequency = cmd.GetFrequency();
			std::string path = "" + cmd.GetPath();
			std::string audioName = "" + cmd.GetAudioNameOut();

			buffer[0].resize(new_size); // 1.000.000 lungimea bufferului inseamna 22 de secunde lungimea audio-ului
			buffer[1].resize(new_size); // 

			int numChannels = 2;
			int numSamplesPerChannel = new_size; // 1.000.000 lungimea semnalului pe durata audio-ului 22 secunde
			float sampleRate = new_SampleRate;
			float frequency = new_Frequency;
			const double PI = 3.1415926;
			for (int i = 0; i < numSamplesPerChannel; i++)
			{
				float sample = sinf(2. * PI * ((float)i / sampleRate) * frequency);

				for (int channel = 0; channel < numChannels; channel++)
					buffer[channel][i] = sample * 0.5;
			}

			bool ok = audioFile.setAudioBuffer(buffer);

			audioFile.save(path);
			std::cout << "Saved.\n";
		}

	}
	else
		std::cout << "ERROR! The format must be:\n--artificialSignals [audioNameOut] [value Audio Length (in seconds positive number)] [value Frequency (float) in Hz] [value Sample Rate (float) in Hz] [path]\n";
}

void Operations::SetLoadPath(std::string& FolderPath)
{
	Cmd_SetLoadPath cmd(command);
	if (cmd.VerifyCommand() == 1)
	{
		FolderPath = "" + cmd.GetPath();
		std::cout << "Path to quickly Load is set to: " << FolderPath << std::endl;
	}
	else
		std::cout << "ERROR! The format must be: \n --setLoadPath [Path] , and must end with a '/' or '\\'\n ";
}


void Operations::QuickSave(std::vector<Audio> modifiedPlaylist)
{
	Cmd_QuickSave cmd(command);


	if (cmd.VerifyCommand() == 1)
	{
		std::string pathOut = "";
		AudioFile<double> audiof;
		std::string audioName = cmd.GetAudioName();
		for (int index = 0; index < modifiedPlaylist.size(); index++)
		{
			if (modifiedPlaylist[index].GetName() == audioName)
			{
				pathOut = pathOut + modifiedPlaylist[index].GetPath();
				audiof = modifiedPlaylist[index].GetAudio();
				break;
			}
		}
		std::cout << "Saving...\n";
		audiof.save(pathOut);
		std::cout << "Saved at: " << pathOut << "\n";
	}
	else
		std::cout << "Incorrect command.\n";
}

void Operations::QuickLoad(std::vector<Audio>& vec, std::string FolderPath)
{
	Cmd_quickLoad cmd(command);
	if (cmd.VerifyCommand() == 1)
	{

		std::string currentAudioPath;



		for (int index = 2; index < cmd.ListOfComponents().size(); index++)
		{
			currentAudioPath = cmd.GetFolderPath() + cmd.ListOfComponents()[index];
			std::cout << "Loading...\n";
			Audio aux(currentAudioPath);
			if (aux.GetAudio().getLengthInSeconds() == 0)
			{
				std::cout << "The Audio file you are trying to load has 0 seconds. Please try again.\n";
			}
			else
			{
				vec.push_back(aux);
				std::cout << "Added to list.\n";
			}
			currentAudioPath = "";
		}
	}

	else if (cmd.VerifyCommandForSettedPath() == 1)
	{
		std::string currentAudioPath = "";


		for (int index = 1; index < cmd.ListOfComponents().size(); index++)
		{
			currentAudioPath = FolderPath + cmd.ListOfComponents()[index];
			std::cout << currentAudioPath << "\n";
			std::cout << "Loading...\n";
			Audio aux(currentAudioPath);
			if (aux.GetAudio().getLengthInSeconds() == 0)
			{
				std::cout << "The Audio file you are trying to load has 0 seconds. Please try again.\n";
			}
			else
			{
				vec.push_back(aux);
				std::cout << "Added to list.\n";
			}
			currentAudioPath = "";
		}
	}

	else
	{
		std::cout << "Invalid command. The command must be --quickLoad [folderPath] [audioName/s] OR --quickLoad [audioName/s] (with setted Path using setLoadPath)\n ---(Attention! The folder path must end with slash/backslash)---\n";
	}
}

void Operations::Save(std::vector<Audio> modifiedPlaylist)
{
	Cmd_Save cmd(command);
	if (cmd.VerifyCommand() == 1)
	{
		std::string audioName = "" + cmd.GetAudioName();
		std::string path = "" + cmd.GetPath();
		int found = 0;
		AudioFile<double> auxiliar;
		for (int index = 0; index < modifiedPlaylist.size(); index++)
		{
			if (modifiedPlaylist[index].GetName() == audioName)
			{
				auxiliar = modifiedPlaylist[index].GetAudio();
				std::cout << "Audio file: " << audioName << " -- saving to: " << path << "\nPlease wait...\n";
				found = 1;
				break;
			}
		}

		if (found == 1)
		{
			auxiliar.save(path);
			std::cout << "Saved.\n";
		}

		if (found == 0)
		{
			std::cout << "File not found.\n" << audioName;
		}
	}

	else
	{
		std::cout << "Invalid Command. The command must be --save [audioName] [path]\n";
	}
}

void Operations::Playback(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist)
{
	if (vec.empty() == true)
	{
		std::cout << "The playlist is empty! Please insert a song using '--load [path]' before you want to perform any action.\n";
	}

	else
	{
		Cmd_Playback cmd(command);
		if (cmd.VerifyCommand() == 1)
		{
			if (foundSong(vec, cmd.GetAudioNameIn()) == 1)
			{
				std::vector<Audio> modifiedSong;
				int step = 0; //pasul este 0 deoarece aceasta metoda fiind folosita si in --process, step 0 reprezinta prima prelucrare a unui audio Original nemodificat pana acum care se va salva pe prima pozitie in modifiedSong.
				std::cout << "Modifying playback...\n";
				GeneralizedPlayback(vec, modifiedSong, cmd.GetAudioNameIn(), cmd.GetAudioNameOut(), cmd.Get_type(), cmd.GetValue(), step);
				AudioFile<double> temp;
				temp = modifiedSong[0].GetAudio();
				std::string pathIn = "" + modifiedSong[0].GetPath();
				std::string pathOut = "";
				modifiedSong.clear();
				CreatePathOut(pathIn, cmd.GetAudioNameOut(), pathOut);
				std::pair<AudioFile<double>, std::string> pereche;
				pereche.first = temp;
				pereche.second = pathOut;
				Audio songtoSave(pereche);
				modifiedPlaylist.push_back(songtoSave);
				std::cout << "Audio file saved in Modified Songs Playlist.\n";
			}
			else if (foundSong(modifiedPlaylist, cmd.GetAudioNameIn()) == 1)
			{
				std::vector<Audio> modifiedSong;
				int step = 0; //pasul este 0 deoarece aceasta metoda fiind folosita si in --process, step 0 reprezinta prima prelucrare a unui audio Original nemodificat pana acum care se va salva pe prima pozitie in modifiedSong.
				std::cout << "Modifying playback...\n";
				GeneralizedPlayback(modifiedPlaylist, modifiedSong, cmd.GetAudioNameIn(), cmd.GetAudioNameOut(), cmd.Get_type(), cmd.GetValue(), step);
				AudioFile<double> temp;
				temp = modifiedSong[0].GetAudio();
				std::string pathIn = "" + modifiedSong[0].GetPath();
				std::string pathOut = "";
				modifiedSong.clear();
				CreatePathOut(pathIn, cmd.GetAudioNameOut(), pathOut);
				std::pair<AudioFile<double>, std::string> pereche;
				pereche.first = temp;
				pereche.second = pathOut;
				Audio songtoSave(pereche);
				modifiedPlaylist.push_back(songtoSave);
				std::cout << "Audio file saved in Modified Songs Playlist.\n";
			}

			else
				std::cout << "Audio Name not found.\n";
		}

		else
		{
			std::cout << "ERROR! The format must be: --playback [slow/fast] [value] [audioNameIn] [audioNameOut]\n--value must be in [1,9]--\n";
		}
	}
}

void Operations::Scale(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist)
{
	Cmd_Scale cmd(command);
	if (cmd.VerifyCommand() == 1)
	{
		if (foundSong(vec, cmd.GetAudioNameIn()) == 1)
		{
			std::vector<Audio> modifiedSong;
			int step = 0; //step=0 prima prelucrare a piesei/ generalizare/ se cauta piesa de modificat in Playlistul cu piese nemodificate.
			std::cout << "Modifying scale...\n";
			GeneralizedScale(vec, modifiedSong, cmd.GetAudioNameIn(), cmd.GetAudioNameOut(), cmd.Get_type(), cmd.GetValue(), step);
			AudioFile<double> temp;
			temp = modifiedSong[0].GetAudio();
			std::string pathIn = "" + modifiedSong[0].GetPath();
			std::string pathOut = "";
			modifiedSong.clear();
			CreatePathOut(pathIn, cmd.GetAudioNameOut(), pathOut);
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = pathOut;
			Audio songtoSave(pereche);
			modifiedPlaylist.push_back(songtoSave);
			std::cout << "Scaled audio file saved in Modified Songs Playlist.\n";
		}

		else if (foundSong(modifiedPlaylist, cmd.GetAudioNameIn()) == 1)
		{
			std::vector<Audio> modifiedSong;
			int step = 0; //step=0 prima prelucrare a piesei/ generalizare/ se cauta piesa de modificat in Playlistul cu piese nemodificate.
			std::cout << "Modifying scale...\n";
			GeneralizedScale(modifiedPlaylist, modifiedSong, cmd.GetAudioNameIn(), cmd.GetAudioNameOut(), cmd.Get_type(), cmd.GetValue(), step);
			AudioFile<double> temp;
			temp = modifiedSong[0].GetAudio();
			std::string pathIn = "" + modifiedSong[0].GetPath();
			std::string pathOut = "";
			modifiedSong.clear();
			CreatePathOut(pathIn, cmd.GetAudioNameOut(), pathOut);
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = pathOut;
			Audio songtoSave(pereche);
			modifiedPlaylist.push_back(songtoSave);
			std::cout << "Scaled audio file saved in Modified Songs Playlist.\n";
		}

		else
			std::cout << "Audio Name not found.\n";
	}

	else
	{
		std::cout << "ERROR! The format must be --scale [down/up] [value] [audioNameIn] [audioNameOut]\n--value must be in [1,9]--\n";
	}
}

void Operations::BassBoost(std::vector<Audio> vec, std::vector<Audio>& modifiedPlaylist)
{
	Cmd_BassBoost cmd(command);
	if (cmd.VerifyCommand() == 1)
	{
		AudioFile<double> temp;
		std::string path = "";
		int found = 0;
		for (int index = 0; index < vec.size(); index++)
		{
			if (vec[index].GetName() == cmd.GetAudioNameIn())
			{
				temp = vec[index].GetAudio();
				path = path + vec[index].GetPath();
				found = 1;
			}
		}
		if (found == 0)
		{
			for (int index = 0; index < modifiedPlaylist.size(); index++)
			{
				if (modifiedPlaylist[index].GetName() == cmd.GetAudioNameIn())
				{
					temp = modifiedPlaylist[index].GetAudio();
					path = path + modifiedPlaylist[index].GetPath();
					found = 1;
				}
			}
		}

		if (found == 1)
		{
			double newValue;
			for (int canal = 0; canal < temp.getNumChannels(); canal++)
			{
				for (int i = 0; i < temp.getNumSamplesPerChannel(); i++)
				{
					if (temp.samples[canal][i] < 0)
					{
						newValue = temp.samples[canal][i] - (cmd.GetValue() / 10 * temp.samples[canal][i]);
						temp.samples[canal][i] = newValue;
					}
				}
			}
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "";
			CreatePathOut(path, cmd.GetAudioNameOut(), pereche.second);

			Audio songToSave(pereche);
			modifiedPlaylist.push_back(songToSave);
			std::cout << "Song saved in Modified Playlist.\n";

		}
		else
			std::cout << "Audio Name not found.\n";
	}
	else
		std::cout << "Invalid command. The command must be: --bassboost [value (0,5)] [audioNameIn] [audioNameOut]\n";

}

void Operations::Treble(std::vector<Audio> vec, std::vector<Audio>& modifiedPlaylist)
{
	Cmd_Treble cmd(command);
	if (cmd.VerifyCommand() == 1)
	{
		AudioFile<double> temp;
		std::string path = "";
		int found = 0;
		for (int index = 0; index < vec.size(); index++)
		{
			if (vec[index].GetName() == cmd.GetAudioNameIn())
			{
				temp = vec[index].GetAudio();
				path = path + vec[index].GetPath();
				found = 1;
			}
		}
		if (found == 0)
		{
			for (int index = 0; index < modifiedPlaylist.size(); index++)
			{
				if (modifiedPlaylist[index].GetName() == cmd.GetAudioNameIn())
				{
					temp = modifiedPlaylist[index].GetAudio();
					path = path + modifiedPlaylist[index].GetPath();
					found = 1;
				}
			}
		}

		if (found == 1)
		{
			double newValue;
			for (int canal = 0; canal < temp.getNumChannels(); canal++)
			{
				for (int i = 0; i < temp.getNumSamplesPerChannel(); i++)
				{
					if (temp.samples[canal][i] > 0)
					{
						newValue = temp.samples[canal][i] + (cmd.GetValue() / 10 * temp.samples[canal][i]);
						temp.samples[canal][i] = newValue;
					}
				}
			}
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "";
			CreatePathOut(path, cmd.GetAudioNameOut(), pereche.second);

			Audio songToSave(pereche);
			modifiedPlaylist.push_back(songToSave);
			std::cout << "Song saved in Modified Playlist.\n";

		}
		else
			std::cout << "Audio Name not found.\n";
	}
	else
		std::cout << "Invalid command. The command must be: --treble [value (1,9)] [audioNameIn] [audioNameOut]\n";
}


void Operations::ReadFileConfig(std::vector<std::string>& fconfig)
{
	std::ifstream file("fileconfig.txt");
	std::string line = "";
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::getline(file >> std::ws, line);
			fconfig.push_back(line);
			line = "";
		}
	}
	file.close();

}

void Operations::ConfigurationFile(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist)
{
	std::vector<std::string> fconfig;
	ReadFileConfig(fconfig);
	Commands_ConfigurationFile cmd(fconfig);

	std::vector<std::string> processes;

	if (cmd.verifyCommand() == 1)
	{
		processes = cmd.GetAllProcesses();

		std::vector<std::pair<int, int>> index_freq_process;
		index_freq_process = cmd.IndexFreq();

		for (int index = 0; index < processes.size(); index++)
		{

			std::cout << "\nProcess : " << processes[index] << " -- ";
			for (int i = 0; i < index_freq_process.size(); i++)
			{
				if (index_freq_process[i].first == index)
				{
					std::cout << "FACTOR = " << cmd.GetFactor(processes[index], index_freq_process[i].second) << " TYPE = " << cmd.GetType(processes[index], index_freq_process[i].second);
				}
			}
		}
		std::cout << std::endl;

		std::string cmdProcess = "";
		cmdProcess = cmdProcess + "--process ";
		std::cout << "Loading...\n";
		std::string pathToLoad = "" + cmd.GetInputPath();
		Audio temp(pathToLoad);
		std::cout << "Loaded.\n";
		vec.push_back(temp);
		cmdProcess = cmdProcess + temp.GetName() + " " + GetNameOfPath(cmd.GetOutputPath());

		for (int index = 0; index < processes.size(); index++)
		{
			for (int i = 0; i < index_freq_process.size(); i++)
			{
				if (index_freq_process[i].first == index)
				{
					if (processes[index] == "playback")
					{
						cmdProcess = cmdProcess + " --playback " + cmd.GetType(processes[index], index_freq_process[i].second) + " " + std::to_string(cmd.GetFactor(processes[index], index_freq_process[i].second));
					}
					else if (processes[index] == "scale")
					{
						cmdProcess = cmdProcess + " --scale " + cmd.GetType(processes[index], index_freq_process[i].second) + " " + std::to_string(cmd.GetFactor(processes[index], index_freq_process[i].second));
					}
				}
			}
		}

		Process(cmdProcess, vec, modifiedPlaylist);

		for (int index = 0; index < modifiedPlaylist.size(); index++)
		{
			if (modifiedPlaylist[index].GetName() == GetNameOfPath(cmd.GetOutputPath()))
			{
				modifiedPlaylist[index].GetAudio().save(cmd.GetOutputPath());
				std::cout << "Audio file saved to path.\n";
				break;
			}
		}
	}

	else
		std::cout << "ATTENTION!\n\nThe format must be:\n\n[Input]\npath=[PATH to LOAD]\n[Output]\npath=[PATH to SAVE]\n[Operation/s]\nfactor=[FACTOR]\ntype=[TYPE]\n";




}

//=============================================================
int Operations::CommandInModifySongMenu()
{
	std::vector<std::string> wordsCommand;
	SplitCommand(wordsCommand);
	if (wordsCommand.size() == 2)
	{
		if (wordsCommand[0] == "--getBitDepth" || wordsCommand[0] == "--getLengthInSeconds" || wordsCommand[0] == "--getNumChannels" || wordsCommand[0] == "--getNumSamplesPerChannel" || wordsCommand[0] == "--getSampleRate" || wordsCommand[0] == "--isMono" || wordsCommand[0] == "--isStereo")
		{
			return 1;
		}
	}
	return 0;
}

void Operations::ModifySongMenu(std::vector<Audio> vec)
{
	if (command.find("--getBitDepth", 0) != std::string::npos)
	{
		Cmd_GetBitDepth cmd(command);
		if (vec.empty() == true)
		{
			std::cout << "The playlist is empty! Please insert a song before you want to perform any action.\n";
		}

		else
		{
			if (cmd.VerifyCommand() == 1)
			{
				int found = 0;
				for (int index = 0; index < vec.size(); index++)
				{
					if (vec[index].GetName() == cmd.GetAudioName())
					{
						std::cout << "Bit depth = " << vec[index].GetAudio().getBitDepth() << "\n";
						found = 1;
					}
				}
				if (found == 0)
				{
					std::cout << "Audio Name not found.\n";
				}
			}
			else
			{
				std::cout << "Invalid command. The format must be --getBitDepth [audioName]\n";
			}
		}
	}

	else if (command.find("--getLengthInSeconds", 0) != std::string::npos)
	{
		Cmd_GetLengthInSeconds cmd(command);
		if (vec.empty() == true)
		{
			std::cout << "The playlist is empty! Please insert a song before you want to perform any action.\n";
		}

		else
		{
			if (cmd.VerifyCommand() == 1)
			{
				bool found = false;
				for (int index = 0; index < vec.size(); index++)
				{
					if (vec[index].GetName() == cmd.GetAudioName())
					{
						std::cout << "Length in seconds = " << vec[index].GetAudio().getLengthInSeconds() << "\n";
						found = true;
					}
				}
				if (found == false)
				{
					std::cout << "Audio Name not found.\n";
				}
			}
			else
			{
				std::cout << "Invalid command. The format must be --getLengthInSeconds [audioName]\n";
			}
		}
	}

	else if (command.find("--getNumChannels", 0) != std::string::npos)
	{
		Cmd_GetNumChannels cmd(command);
		if (vec.empty() == true)
		{
			std::cout << "The playlist is empty! Please insert a song before you want to perform any action.\n";
		}

		else
		{
			if (cmd.VerifyCommand() == 1)
			{
				int found = false;
				for (int index = 0; index < vec.size(); index++)
				{
					if (vec[index].GetName() == cmd.ListOfComponents()[1])
					{
						std::cout << "Number of channels = " << vec[index].GetAudio().getNumChannels() << "\n";
						found = true;
					}
				}
				if (found == false)
				{
					std::cout << "Audio Name not found.\n";
				}
			}
			else
			{
				std::cout << "Invalid command. The format must be --getNumChannels [audioName]\n";
			}
		}
	}

	else if (command.find("--getNumSamplesPerChannel", 0) != std::string::npos)
	{
		Cmd_GetNumSamplesPerChannel cmd(command);
		if (vec.empty() == true)
		{
			std::cout << "The playlist is empty! Please insert a song before you want to perform any action.\n";
		}

		else
		{
			if (cmd.VerifyCommand() == 1)
			{
				bool found = false;
				for (int index = 0; index < vec.size(); index++)
				{
					if (vec[index].GetName() == cmd.GetAudioName())
					{
						std::cout << "Number of samples per channel = " << vec[index].GetAudio().getNumSamplesPerChannel() << "\n";
						found = true;
					}
				}
				if (found == false)
				{
					std::cout << "Audio Name not found.\n";
				}
			}
			else
			{
				std::cout << "Invalid command. The format must be --getNumSamplesPerChannel [audioName]\n";
			}
		}
	}

	else if (command.find("--isMono", 0) != std::string::npos)
	{
		Cmd_IsMono cmd(command);
		if (vec.empty() == true)
		{
			std::cout << "The playlist is empty! Please insert a song before you want to perform any action.\n";
		}
		else
		{
			if (cmd.VerifyCommand() == 1)
			{
				int found = false;
				for (int index = 0; index < vec.size(); index++)
				{
					if (vec[index].GetName() == cmd.ListOfComponents()[1])
					{
						std::cout << "Is Mono = " << vec[index].GetAudio().isMono() << "\n";
						found = true;
					}
				}
				if (found == false)
				{
					std::cout << "Audio Name not found.\n";
				}
			}
			else
			{
				std::cout << "Invalid command. The format must be --isMono [audioName]\n";
			}
		}
	}

	else if (command.find("--isStereo", 0) != std::string::npos)
	{
		Cmd_IsStereo cmd(command);
		if (vec.empty() == true)
		{
			std::cout << "The playlist is empty! Please insert a song before you want to perform any action.\n";
		}
		else
		{
			if (cmd.VerifyCommand() == 1)
			{
				bool found = false;
				for (int index = 0; index < vec.size(); index++)
				{
					if (vec[index].GetName() == cmd.ListOfComponents()[1]);
					{
						std::cout << "Is Stereo = " << vec[index].GetAudio().isStereo() << "\n";
						found = true;
					}
				}
				if (found == false)
				{
					std::cout << "Audio Name not found.\n";
				}
			}
			else
			{
				std::cout << "Invalid command. The format must be --isStereo [audioName]\n";
			}
		}
	}

	else if (command.find("--getSampleRate", 0) != std::string::npos)
	{
		Cmd_GetSampleRate cmd(command);
		if (vec.empty() == true)
		{
			std::cout << "The playlist is empty! Please insert a song before you want to perform any action.\n";
		}
		else
		{
			if (cmd.VerifyCommand() == 1)
			{
				bool found = false;
				for (int index = 0; index < vec.size(); index++)
				{
					if (vec[index].GetName() == cmd.ListOfComponents()[1])
					{
						std::cout << "Sample Rate = " << vec[index].GetAudio().getSampleRate() << "\n";
						found = true;
					}
				}
				if (found == false)
				{
					std::cout << "Audio Name not found.\n";
				}
			}
			else
			{
				std::cout << "Invalid command. The format must be --getSampleRate [audioName]\n";
			}
		}
	}
}
const std::string Operations::GetNameOfPath(const std::string path)
{
	std::string name = "";
	int found = -1;
	for (int index = 0; index < path.size(); index++)
	{
		if (path[index] == '/' || path[index] == '\\')
			found = index;
	}
	for (int index = found + 1; index < path.size(); index++)
	{
		name = name + path[index];
	}
	return name;
}

//=============================================================


void Operations::CreatePathOut(std::string pathIn, std::string audioNameOut, std::string& pathOut)
{
	int poz_slash = 0;
	int ok_slash = 0;
	for (int index = 0; index < pathIn.size(); index++)
	{
		if (pathIn[index] == '/')
		{
			poz_slash = index;
			ok_slash = 1;
		}
	}
	if (ok_slash == 1)
	{
		for (int index = 0; index < poz_slash; index++)
		{
			pathOut = pathOut + pathIn[index];
		}
		pathOut = pathOut + "/";
		pathOut = pathOut + audioNameOut;
	}

	else
	{
		for (int index = 0; index < pathIn.size(); index++)
		{
			if (pathIn[index] == '\\')
			{
				poz_slash = index;
			}
		}
		for (int index = 0; index < poz_slash; index++)
		{
			pathOut = pathOut + pathIn[index];
		}
		pathOut = pathOut + "\\";
		pathOut = pathOut + audioNameOut;
	}


}
//=============================================================
void Operations::Process(std::string command, std::vector<Audio> vec, std::vector<Audio>& modifiedPlaylist)
{
	Cmd_Process cmd(command);
	if (cmd.VerifyCommand() == 1)
	{
		if (foundSong(vec, cmd.GetAudioNameIn()) == 1)
		{
			std::vector<Audio> modifiedSong;
			std::string audioNameIn = "" + cmd.GetAudioNameIn();
			std::string audioNameOut = "" + cmd.GetAudioNameOut();


			int index = 0;
			while (index < cmd.GetSequencesSize())
			{
				if (cmd.GetOperationOfSequence(index) == "--playback")
				{
					std::cout << "Modifying playback...\n";
					GeneralizedPlayback(vec, modifiedSong, audioNameIn, audioNameOut, cmd.GetTypeOfSequence(index), cmd.GetValueOfSequence(index), index);
				}
				else
				{
					std::cout << "Modifying scale...\n";
					GeneralizedScale(vec, modifiedSong, audioNameIn, audioNameOut, cmd.GetTypeOfSequence(index), cmd.GetValueOfSequence(index), index);
				}

				index++;
			}
			AudioFile<double> finalSong;
			if (modifiedSong[0].GetAudio().getLengthInSeconds() != 0)
			{
				std::cout << "Done.\n";
				finalSong = modifiedSong[0].GetAudio();
				std::string pathIn;
				pathIn = "" + modifiedSong[0].GetPath();
				std::string pathOut = "";
				CreatePathOut(pathIn, audioNameOut, pathOut);
				std::pair<AudioFile<double>, std::string> pereche;
				pereche.first = finalSong;
				pereche.second = "" + pathOut;
				Audio songtoSave(pereche);
				modifiedPlaylist.push_back(songtoSave);
				std::cout << audioNameOut << " saved in Modified Songs Playlist.\n";
				modifiedSong.clear();
			}
			else
			{
				std::cout << "This process made the song 0 seconds.\n";
			}
		}
		else
			std::cout << "Audio file name not found.\n";

	}

	else
		std::cout << "Invalid command. The format must be: --process [audioNameIn] [audioNameOut] [--operation/s]\n";


}

void Operations::GeneralizedPlayback(std::vector<Audio> vec, std::vector<Audio>& modifiedSongs, std::string audioNameIn, std::string audioNameOut, std::string op_type, double value, int step)
{
	if (step == 0) //prima prelucrare
	{
		AudioFile<double> temp;
		std::string path = "";
		for (int index = 0; index < vec.size(); index++)
		{
			if (audioNameIn == vec[index].GetName())
			{
				temp = vec[index].GetAudio();
				path = path + vec[index].GetPath();
				break;
			}
		}

		if (op_type == "fast")
		{
			double SampleRate = temp.getSampleRate();
			double newValue = SampleRate + (0.1 * value * SampleRate);
			temp.setSampleRate(newValue);
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "" + path; //salvez in modifiedSongs piesa modificata si path-ul original al acesteia.
			Audio songToSave(pereche);
			modifiedSongs.push_back(songToSave);
		}

		else if (op_type == "slow")
		{
			value = -value;
			double SampleRate = temp.getSampleRate();
			double newValue = SampleRate + (0.1 * value * SampleRate);
			temp.setSampleRate(newValue);
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "" + path; //salvez in modifiedSongs piesa modificata si path-ul original al acesteia.
			Audio songToSave(pereche);
			modifiedSongs.push_back(songToSave);
		}
	}

	else
	{
		AudioFile<double> temp;
		std::string path = "";
		temp = modifiedSongs[0].GetAudio();
		path = path + modifiedSongs[0].GetPath();

		if (op_type == "fast")
		{
			double SampleRate = temp.getSampleRate();
			double newValue = SampleRate + (0.1 * value * SampleRate);
			temp.setSampleRate(newValue);
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "" + path; //salvez in modifiedSongs piesa modificata si path-ul original al acesteia.
			modifiedSongs.clear(); //sterg continutul vectorului modifiedSongs; in el va ramane doar o singura piesa, cea care are toate modificarile
			Audio songToSave(pereche);
			modifiedSongs.push_back(songToSave);
		}

		else if (op_type == "slow")
		{
			value = -value;
			double SampleRate = temp.getSampleRate();
			double newValue = SampleRate + (0.1 * value * SampleRate);
			temp.setSampleRate(newValue);
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "" + path; //salvez in modifiedSongs piesa modificata si path-ul original al acesteia.
			modifiedSongs.clear();
			Audio songToSave(pereche);
			modifiedSongs.push_back(songToSave);
		}
	}
}

void Operations::GeneralizedScale(std::vector<Audio> vec, std::vector<Audio>& modifiedSongs, std::string audioNameIn, std::string audioNameOut, std::string op_type, double value, int step)
{
	if (step == 0) //prima prelucrare
	{
		AudioFile<double> temp;
		std::string path = "";
		for (int index = 0; index < vec.size(); index++)
		{
			if (audioNameIn == vec[index].GetName())
			{
				temp = vec[index].GetAudio();
				path = path + vec[index].GetPath();
				break;
			}
		}

		if (op_type == "up")
		{
			double newValue;
			for (int canal = 0; canal < temp.getNumChannels(); canal++)
			{
				for (int i = 0; i < temp.getNumSamplesPerChannel(); i++)
				{
					newValue = temp.samples[canal][i] + ((double)value / 10 * temp.samples[canal][i]);
					temp.samples[canal][i] = newValue;
				}
			}
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "" + path; //salvez in modifiedSongs piesa modificata si path-ul original al acesteia.
			Audio songToSave(pereche);
			modifiedSongs.push_back(songToSave);
		}

		else if (op_type == "down")
		{
			double newValue;
			for (int canal = 0; canal < temp.getNumChannels(); canal++)
			{
				for (int i = 0; i < temp.getNumSamplesPerChannel(); i++)
				{
					newValue = temp.samples[canal][i] - ((double)value / 10 * temp.samples[canal][i]);
					temp.samples[canal][i] = newValue;
				}
			}
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "" + path; //salvez in modifiedSongs piesa modificata si path-ul original al acesteia.
			Audio songToSave(pereche);
			modifiedSongs.push_back(songToSave);
		}
	}
	else
	{
		AudioFile<double> temp;
		std::string path = "";
		temp = modifiedSongs[0].GetAudio();
		path = path + modifiedSongs[0].GetPath();

		if (op_type == "up")
		{
			double newValue;
			for (int canal = 0; canal < temp.getNumChannels(); canal++)
			{
				for (int i = 0; i < temp.getNumSamplesPerChannel(); i++)
				{
					newValue = temp.samples[canal][i] + ((double)value / 10 * temp.samples[canal][i]);
					temp.samples[canal][i] = newValue;
				}
			}
			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "" + path; //salvez in modifiedSongs piesa modificata si path-ul original al acesteia.
			modifiedSongs.clear(); //sterg continutul vectorului modifiedSongs; in el va ramane doar o singura piesa, cea care are toate modificarile
			Audio songToSave(pereche);
			modifiedSongs.push_back(songToSave);
		}

		else if (op_type == "down")
		{
			double newValue;
			for (int canal = 0; canal < temp.getNumChannels(); canal++)
			{
				for (int i = 0; i < temp.getNumSamplesPerChannel(); i++)
				{
					newValue = temp.samples[canal][i] - ((double)value / 10 * temp.samples[canal][i]);
					temp.samples[canal][i] = newValue;
				}
			}

			std::pair<AudioFile<double>, std::string> pereche;
			pereche.first = temp;
			pereche.second = "" + path; //salvez in modifiedSongs piesa modificata si path-ul original al acesteia.
			modifiedSongs.clear();
			Audio songToSave(pereche);
			modifiedSongs.push_back(songToSave);
		}
	}
}
//=============================================================
//=============================================================