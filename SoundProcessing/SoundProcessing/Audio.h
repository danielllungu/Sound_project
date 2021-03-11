#pragma once
//=============================================================
#include <vector>
#include "AudioFile.h"
#include <string>
//=============================================================
class Audio
{
public:
	//=============================================================
	Audio();
	Audio(const std::string path);
	Audio(std::pair < AudioFile<double>, std::string>temp);
	~Audio();
	//=============================================================
	std::string GetName();
	void SetName(const std::string name);
	std::string GetPath();
	AudioFile<double> GetAudio();
	//=============================================================
private:
	//=============================================================
	std::pair<AudioFile<double>, std::string > m_audioFile;
	//=============================================================
};

