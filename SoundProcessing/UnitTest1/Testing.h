#pragma once
#include "../SoundProcessing/Operations.h"

class Testing
{
public:
	Testing();
	AudioFile<double> GetLoadedFile(std::string path);
	~Testing();
};

