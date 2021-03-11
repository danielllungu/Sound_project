#pragma once
//=============================================================
#include <string>
#include <iostream>
#include <vector>
#include "Audio.h";
//=============================================================
class Operations
{
public:
	//=============================================================
	Operations(const std::string& command);
	void SplitCommand(std::vector<std::string>& splittedCommand);
	void Run(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist, std::string& FolderPath);
	//=============================================================
	void PrintPlaylistOperations();
	void PrintSongOperations(std::vector<Audio> vec);
	void PrintListOfAudios(std::string com, std::vector<Audio>listOfAudios);
	void PrintSummary(std::vector<Audio> vec, std::vector<Audio> modifiedPlaylist);
	//=============================================================
	int foundSong(std::vector<Audio> vec, std::string audioName);
	void RemoveSong(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist);
	void Load(std::vector<Audio>& vec);
	void ArtificialSignals();
	void SetLoadPath(std::string& FolderPath);
	void QuickSave(std::vector<Audio> modifiedPlaylist);
	void QuickLoad(std::vector<Audio>& vec, std::string FolderPath);
	void Save(std::vector<Audio> modifiedPlaylist);
	void Playback(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist);
	void Scale(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist);
	void BassBoost(std::vector<Audio> vec, std::vector<Audio>& modifiedPlaylist);
	void Treble(std::vector<Audio> vec, std::vector<Audio>& modifiedPlaylist);
	void ReadFileConfig(std::vector<std::string>& fconfig);
	void ConfigurationFile(std::vector<Audio>& vec, std::vector<Audio>& modifiedPlaylist);
	//=============================================================
	AudioFile<double> SelectSong(std::vector<Audio> vec, int index);

	//=============================================================
	int CommandInModifySongMenu();
	void ModifySongMenu(std::vector<Audio> vec);
	//=============================================================
	const std::string GetNameOfPath(const std::string path);
	void CreatePathOut(std::string pathIn, std::string audioNameOut, std::string& pathOut);
	//=============================================================

	void Process(std::string command, std::vector<Audio> vec, std::vector<Audio>& modifiedPlaylist);
	void GeneralizedPlayback(std::vector<Audio> vec, std::vector<Audio>& modifiedSongs, std::string audioNameIn, std::string audioNameOut, std::string op_type, double value, int step);
	void GeneralizedScale(std::vector<Audio> vec, std::vector<Audio>& modifiedSongs, std::string audioNameIn, std::string audioNameOut, std::string op_type, double value, int step);
	//=============================================================
private:
	//=============================================================
	std::string command;
	//=============================================================
};
//=============================================================
