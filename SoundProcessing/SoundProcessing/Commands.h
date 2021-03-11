#pragma once
#include <string>
#include <vector>
#include "Audio.h"

class Cmd
{
protected:
	std::string com = "";
public:
	virtual int NumberOfComponents();
	virtual std::string OperationType();

};

class Cmd_Load : protected Cmd
{
public:
	Cmd_Load(const std::string com);
	virtual int VerifyAcceptedWord(const std::string word);
	virtual std::vector<std::string> ListOfComponents();
	const virtual std::string GetPath();
	virtual int NumberOfComponents();
	virtual int VerifyCommand();
};

class Cmd_Save : protected Cmd_Load
{
public:
	Cmd_Save(const std::string com) :Cmd_Load(com) {
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
	const virtual std::string GetPath();
	virtual int VerifyPath(std::string wav);
	const virtual std::string GetAudioName();
	virtual int VerifyCommand();
};

class Cmd_Printlist : protected Cmd
{
public:
	Cmd_Printlist(const std::string com);
	const virtual std::string ListOfComponents();
};


class Cmd_PrintModified : public Cmd_Printlist
{
public:
	Cmd_PrintModified(const std::string com) : Cmd_Printlist(com)
	{
		this->com = com;
	}
	const virtual std::string ListOfComponents();
};

class Cmd_PrintSummary : protected Cmd
{
public:
	Cmd_PrintSummary(const std::string com);
	virtual std::vector<std::string> ListOfComponents();
	virtual int VerifyAcceptedWord(const std::string word);
	virtual int NumberOfComponents();
	virtual int VerifyCommand();
	const virtual std::string GetAudioName();
};

class Cmd_RemoveAudio : public Cmd_PrintSummary
{
public:
	Cmd_RemoveAudio(const std::string com) : Cmd_PrintSummary(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
};


class ceva
{
private:
	int a;
public:
	void show()
	{
		std::cout << "";
	}
};



class Cmd_Playback : protected Cmd_Save
{
public:
	Cmd_Playback(const std::string com) : Cmd_Save(com) {
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
	virtual int VerifyAcceptedWord(const std::string word);
	const virtual std::string GetAudioNameIn();
	const virtual std::string GetAudioNameOut();
	const virtual std::string Get_type();
	const virtual double GetValue();
	virtual int VerifyCommand();
};

class Cmd_Scale : public Cmd_Playback
{
public:
	Cmd_Scale(const std::string com) : Cmd_Playback(com) {
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
	virtual int VerifyAcceptedWord(std::string word);
	virtual int VerifyCommand();
};

class Cmd_GetBitDepth : public Cmd_RemoveAudio
{
public:
	Cmd_GetBitDepth(const std::string com) :Cmd_RemoveAudio(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
};

class Cmd_GetLengthInSeconds : public Cmd_GetBitDepth
{
public:
	Cmd_GetLengthInSeconds(const std::string com) : Cmd_GetBitDepth(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
};

class Cmd_GetNumChannels : public Cmd_GetLengthInSeconds
{
public:
	Cmd_GetNumChannels(const std::string com) : Cmd_GetLengthInSeconds(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string>ListOfComponents();
};

class Cmd_GetNumSamplesPerChannel : public Cmd_GetNumChannels
{
public:
	Cmd_GetNumSamplesPerChannel(const std::string com) : Cmd_GetNumChannels(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
};

class Cmd_GetSampleRate : public Cmd_GetNumSamplesPerChannel
{
public:
	Cmd_GetSampleRate(const std::string com) : Cmd_GetNumSamplesPerChannel(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
};

class Cmd_IsMono : public Cmd_GetSampleRate
{
public:
	Cmd_IsMono(const std::string com) : Cmd_GetSampleRate(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
};

class Cmd_IsStereo : public Cmd_IsMono
{
public:
	Cmd_IsStereo(const std::string com) : Cmd_IsMono(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
};

class Cmd_Process : protected Cmd_Playback
{
public:
	Cmd_Process(const std::string com) : Cmd_Playback(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
	virtual int VerifyAcceptedWord(const std::string word);
	virtual int VerifyAcceptedType(const std::string type, const std::string operation);
	virtual int VerifyAcceptedOp(const std::string operation);
	virtual int VerifyAcceptedValue(const std::string value);
	virtual int VerifyAcceptedWav(const std::string wav);
	virtual int VerifyAcceptedSequence(int index);
	virtual int VerifyCommand();
	const virtual std::string GetAudioNameIn();
	const virtual std::string GetAudioNameOut();
	const virtual std::string GetTypeOfSequence(int index);
	const virtual std::string GetOperationOfSequence(int index);
	const virtual double GetValueOfSequence(int index);
	const virtual int GetSequencesSize();

private:
	std::vector<std::vector<std::string>> sequences;


};

class Cmd_ArtificialSignals : protected Cmd_Playback
{
public:
	Cmd_ArtificialSignals(const std::string com) :Cmd_Playback(com)
	{
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
	virtual int VerifyAcceptedWord(std::string word);
	const virtual std::string GetAudioNameOut();
	const virtual int GetSignalLength();
	const virtual float GetFrequency();
	const virtual float GetSampleRate();
	const virtual std::string GetPath();
	virtual int VerifyIntNumber(const std::string word);
	virtual int VerifyFloatNumber(const std::string word);
	virtual int VerifyWavFile(const std::string word);
	virtual int VerifyCommand();
};



class Cmd_QuickSave : protected Cmd_Save
{
public:
	Cmd_QuickSave(const std::string com) :Cmd_Save(com) {
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
	const virtual std::string GetAudioName();
	virtual int VerifyCommand();
};

class Cmd_quickLoad : protected Cmd_Load
{
public:
	Cmd_quickLoad(const std::string com) : Cmd_Load(com)
	{
		this->com = com;
	}
	virtual void SetLoadPath(const std::string& path);
	virtual std::vector<std::string> ListOfComponents();
	const virtual std::string GetFolderPath();
	virtual int VerifyPath(const std::string path);
	const virtual int GetPathSize();
	virtual int VerifyCommand();
	virtual int VerifyCommandForSettedPath();
	virtual void print();
};


class Cmd_SetLoadPath : protected Cmd_quickLoad
{
public:
	Cmd_SetLoadPath(const std::string com) :Cmd_quickLoad(com) {
		this->com = com;
	}
	const virtual std::string GetPath();
	virtual std::vector<std::string> ListOfComponents();
	virtual int VerifyCommand();
};

class Cmd_BassBoost : protected Cmd_Playback
{
public:
	Cmd_BassBoost(const std::string com) : Cmd_Playback(com) {
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
	virtual int VerifyAcceptedWord(const std::string word);
	const virtual std::string GetAudioNameIn();
	const virtual std::string GetAudioNameOut();
	const virtual double GetValue();
	virtual int VerifyWav(const std::string word);
	virtual int VerifyCommand();
};

class Cmd_Treble : public Cmd_BassBoost {
public:
	Cmd_Treble(const std::string com) :Cmd_BassBoost(com) {
		this->com = com;
	}
	virtual std::vector<std::string> ListOfComponents();
};


class Commands_ConfigurationFile
{
public:
	Commands_ConfigurationFile(std::vector<std::string> com) {
		this->com = com;
	}

	const virtual std::string GetInputPath();
	const virtual std::string GetOutputPath();
	virtual void GetProcessors();
	const virtual int GetFactor(const std::string process, int numberOfProcess);
	const virtual std::string GetType(const std::string process, int numberOfProcess);
	virtual int verifyPath(const std::string path);
	virtual int verifyCommand();
	virtual std::vector<std::string> GetAllProcesses();
	virtual std::vector<std::pair<int, int>> IndexFreq();



private:
	std::vector<std::string> com;
	std::vector<std::string> processes;
};


