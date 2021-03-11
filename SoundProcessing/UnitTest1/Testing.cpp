#include "pch.h"
#include "Testing.h"

Testing::Testing()
{
}

AudioFile<double> Testing::GetLoadedFile(std::string path)
{
	AudioFile<double> audio;
	audio.load(path);
	return audio;
}

Testing::~Testing()
{
}
