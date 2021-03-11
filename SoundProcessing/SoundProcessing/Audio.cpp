#include "Audio.h"

//=============================================================
Audio::Audio()
{

}

Audio::Audio(const std::string path)
{
	AudioFile<double> audiof;
	audiof.load(path);
	m_audioFile.first = audiof;
	m_audioFile.second = "" + path;
}

Audio::Audio(std::pair < AudioFile<double>, std::string>temp)
{
	m_audioFile.first = temp.first;
	m_audioFile.second = "" + temp.second;
}

Audio::~Audio()
{

}
//=============================================================
std::string Audio::GetName()
{
	int poz = 0;
	std::string path = m_audioFile.second;
	std::string audioName = "";
	for (int index = 0; index < path.size(); index++)
	{
		if (path.at(index) == '/' || path.at(index) == '\\')
		{
			poz = index;
		}
	}
	for (int index = poz + 1; index < path.size(); index++)
		audioName = audioName + path[index];

	return audioName;
}

void Audio::SetName(const std::string name)
{
	m_audioFile.second = name;
}

std::string Audio::GetPath()
{
	return m_audioFile.second;
}

AudioFile<double> Audio::GetAudio()
{
	return m_audioFile.first;
}
//=============================================================

//=============================================================

