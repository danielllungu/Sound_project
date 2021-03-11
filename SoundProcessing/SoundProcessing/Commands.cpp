#include "Commands.h"



int Cmd::NumberOfComponents()
{

	return 0;
}



std::string Cmd::OperationType()
{
	return "";

}

int Cmd_Load::VerifyAcceptedWord(const std::string word)
{
	if (word.size() < 5)
	{
		return 0;
	}

	else
	{
		int index = word.size();
		if (word[index - 1] == 'v' && word[index - 2] == 'a' && word[index - 3] == 'w' && word[index - 4] == '.')
		{
			return 1;
		}
		else return 0;
	}
}



std::vector<std::string> Cmd_Load::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	// salvarea in op_type operatiei --load
	commandComponents.push_back("--load");
	op_type = op_type + "--load";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

const std::string Cmd_Load::GetPath()
{
	std::vector<std::string> commandComponents;
	commandComponents = ListOfComponents();
	return commandComponents[1];
}

int Cmd_Load::NumberOfComponents()
{
	return ListOfComponents().size();
}

int Cmd_Load::VerifyCommand()
{
	std::vector<std::string> commandComponents;
	commandComponents = ListOfComponents();
	if (NumberOfComponents() == 2)
	{
		if (VerifyAcceptedWord(GetPath()) == 1)
			return 1;
	}


	return 0;
}

Cmd_Load::Cmd_Load(const std::string com)
{
	this->com = com;
}

std::vector<std::string> Cmd_Save::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--save");
	op_type = op_type + "--save";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);

	return commandComponents;
}

const std::string Cmd_Save::GetPath()
{
	return ListOfComponents()[2];
}

int Cmd_Save::VerifyPath(const std::string wav)
{
	if (wav.size() < 5)
	{
		return 0;
	}

	else
	{
		int index = wav.size();
		if (wav[index - 1] == 'v' && wav[index - 2] == 'a' && wav[index - 3] == 'w' && wav[index - 4] == '.')
		{
			return 1;
		}

	}

	return 0;
}

const std::string Cmd_Save::GetAudioName()
{
	return ListOfComponents()[1];
}

int Cmd_Save::VerifyCommand()
{
	std::vector<std::string> commandComponents;
	commandComponents = ListOfComponents();
	if (NumberOfComponents() == 3)
	{
		if (VerifyAcceptedWord(GetPath()) == 1 && VerifyAcceptedWord(GetAudioName()) == 1)
			return 1;
	}

	return 0;
}

std::vector<std::string> Cmd_Playback::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--playback");
	op_type = op_type + "--playback";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}

			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}

		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);

	return commandComponents;
}

int Cmd_Playback::VerifyAcceptedWord(const std::string word)
{
	if (word == "slow" || word == "fast")
		return 1;
	else if (word.size() == 1 && int(word.at(0)) - 48 > 0 && int(word.at(0)) - 48 < 10)
		return 1;
	else
	{
		if (word.size() < 5)
		{
			return 0;
		}

		else
		{
			int index = word.size();
			if (word[index - 1] == 'v' && word[index - 2] == 'a' && word[index - 3] == 'w' && word[index - 4] == '.')
			{
				return 1;
			}

		}
	}
	return 0;

}

const std::string Cmd_Playback::GetAudioNameIn()
{
	return ListOfComponents()[3];
}

const std::string Cmd_Playback::GetAudioNameOut()
{
	return ListOfComponents()[4];
}

const std::string Cmd_Playback::Get_type()
{
	return ListOfComponents()[1];
}

const double Cmd_Playback::GetValue()
{
	if (std::isdigit(ListOfComponents()[2].at(0)))
	{
		return std::stod(ListOfComponents()[2]);
	}

	else
		return -1;

}

int Cmd_Playback::VerifyCommand()
{
	std::vector<std::string> commandComponents;
	commandComponents = ListOfComponents();
	if (NumberOfComponents() == 5)
	{
		if (VerifyAcceptedWord(GetAudioNameIn()) == 1 && VerifyAcceptedWord(GetAudioNameOut()) == 1 && GetValue() > 0 && GetValue() < 10)

			if (Get_type() == "slow" || Get_type() == "fast")

				return 1;

	}
	return 0;
}

std::vector<std::string> Cmd_Scale::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--scale");
	op_type = op_type + "--scale";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);

	return commandComponents;
}

int Cmd_Scale::VerifyAcceptedWord(const std::string word)
{
	if (word == "up" || word == "down")
		return 1;
	else if (word.size() == 1 && int(word.at(0)) - 48 > 0 && int(word.at(0)) - 48 < 10)
		return 1;
	else
	{
		if (word.size() < 5)
		{
			return 0;
		}

		else
		{
			int index = word.size();
			if (word[index - 1] == 'v' && word[index - 2] == 'a' && word[index - 3] == 'w' && word[index - 4] == '.')
			{
				return 1;
			}

		}
	}
	return 0;
}

int Cmd_Scale::VerifyCommand()
{
	std::vector<std::string> commandComponents;
	commandComponents = ListOfComponents();
	if (NumberOfComponents() == 5)
	{
		if (VerifyAcceptedWord(GetAudioNameIn()) == 1 && VerifyAcceptedWord(GetAudioNameOut()) == 1 && GetValue() > 0 && GetValue() < 10)
			if (Get_type() == "up" || Get_type() == "down")
				return 1;

	}
	return 0;
}

Cmd_Printlist::Cmd_Printlist(const std::string com)
{
	this->com = com;
}

const std::string Cmd_Printlist::ListOfComponents()
{
	std::string op_type = "--printList";
	return op_type;
}

const std::string Cmd_PrintModified::ListOfComponents()
{
	std::string op_type = "--printModified";
	return op_type;
}

std::vector<std::string> Cmd_RemoveAudio::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	commandComponents.push_back("--removeAudio");
	op_type = op_type + "--removeAudio";
	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

Cmd_PrintSummary::Cmd_PrintSummary(const std::string com)
{
	this->com = com;
}

std::vector<std::string> Cmd_PrintSummary::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	commandComponents.push_back("--printSummary");
	op_type = op_type + "--printSummary";
	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

int Cmd_PrintSummary::VerifyAcceptedWord(const std::string word)
{
	if (word.size() < 5)
	{
		return 0;
	}
	else
	{
		int index = word.size();
		if (word[index - 1] == 'v' && word[index - 2] == 'a' && word[index - 3] == 'w' && word[index - 4] == '.')
		{
			return 1;
		}
		else return 0;
	}
}

int Cmd_PrintSummary::NumberOfComponents()
{
	return ListOfComponents().size();
}

int Cmd_PrintSummary::VerifyCommand()
{
	std::vector<std::string> commandComponents;
	commandComponents = ListOfComponents();
	if (NumberOfComponents() == 2)
		if (VerifyAcceptedWord(GetAudioName()) == 1)
			return 1;
	return 0;
}

const std::string Cmd_PrintSummary::GetAudioName()
{
	return ListOfComponents()[1];
}

std::vector<std::string> Cmd_GetBitDepth::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	commandComponents.push_back("--getBitDepth");
	op_type = op_type + "--getBitDepth";
	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

std::vector<std::string> Cmd_GetLengthInSeconds::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	commandComponents.push_back("--getLengthInSeconds");
	op_type = op_type + "--getLengthInSeconds";
	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

std::vector<std::string> Cmd_GetNumChannels::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	commandComponents.push_back("--getNumChannels");
	op_type = op_type + "--getNumChannels";
	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

std::vector<std::string> Cmd_GetNumSamplesPerChannel::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	commandComponents.push_back("--getNumSamplesPerChannel");
	op_type = op_type + "--getNumSamplesPerChannel";
	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

std::vector<std::string> Cmd_GetSampleRate::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	commandComponents.push_back("--getSampleRate");
	op_type = op_type + "--getSampleRate";
	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

std::vector<std::string> Cmd_IsMono::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	commandComponents.push_back("--isMono");
	op_type = op_type + "--isMono";
	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

std::vector<std::string> Cmd_IsStereo::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;
	commandComponents.push_back("--isStereo");
	op_type = op_type + "--isStereo";
	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

int Cmd_Process::VerifyAcceptedWord(const std::string word)
{
	if (word == "--playback" || word == "--scale" || word == "up" || word == "down" || word == "fast" || word == "slow")
		return 1;
	else if (word.size() == 1 && int(word.at(0)) - 48 > 0 && int(word.at(0)) - 48 < 10)
		return 1;
	else
	{
		if (word.size() < 5)
		{
			return 0;
		}

		else
		{
			int index = word.size();
			if (word[index - 1] == 'v' && word[index - 2] == 'a' && word[index - 3] == 'w' && word[index - 4] == '.')
			{
				return 1;
			}

		}
	}
	return 0;
}

std::vector<std::string> Cmd_Process::ListOfComponents()
{
	std::string word = "";

	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--process");
	op_type = op_type + "--process";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);

	return commandComponents;

}



int Cmd_Process::VerifyAcceptedType(const std::string type, const std::string operation)
{

	if (operation == "--playback")
	{
		if (type == "slow" || type == "fast")
			return 1;
	}
	else if (operation == "--scale")
	{
		if (type == "up" || type == "down")
			return 1;
	}
	return 0;
}

int Cmd_Process::VerifyAcceptedOp(const std::string operation)
{
	if (operation == "--playback" || operation == "--scale")
		return 1;
	return 0;
}

int Cmd_Process::VerifyAcceptedValue(const std::string value)
{
	if (value.size() == 1 && int(value.at(0)) - 48 > 0 && int(value.at(0)) - 48 < 10)
		return 1;
	return 0;
}

int Cmd_Process::VerifyAcceptedWav(const std::string wav)
{
	if (wav.size() < 5)
	{
		return 0;
	}

	else
	{
		int index = wav.size();
		if (wav[index - 1] == 'v' && wav[index - 2] == 'a' && wav[index - 3] == 'w' && wav[index - 4] == '.')
		{
			return 1;
		}

	}

	return 0;
}


int Cmd_Process::VerifyAcceptedSequence(int index)
{
	if (VerifyAcceptedOp(ListOfComponents()[index]) == 1)
	{
		if (VerifyAcceptedType(ListOfComponents()[index + 1], ListOfComponents()[index]) == 1)
			if (VerifyAcceptedValue(ListOfComponents()[index + 2]) == 1)
				return 1;
	}
	return 0;
}

int Cmd_Process::VerifyCommand()
{
	int ok = 1;
	if (NumberOfComponents() % 3 == 0 && NumberOfComponents() >= 6)
	{
		if (VerifyAcceptedWav(GetAudioNameIn()) == 1 && VerifyAcceptedWav(GetAudioNameOut()) == 1)
		{
			int index = 3;
			while (index < NumberOfComponents())
			{
				if (VerifyAcceptedSequence(index) == 0)
					ok = 0;
				else
				{
					std::vector<std::string> seq;
					seq.push_back(ListOfComponents()[index]);
					seq.push_back(ListOfComponents()[index + 1]);
					seq.push_back(ListOfComponents()[index + 2]);
					sequences.push_back(seq);
					seq.clear();
				}

				index = index + 3;
			}
		}
		else
			ok = 0;

	}
	else
		ok = 0;

	if (ok == 1)
		return 1;

	return 0;
}

const std::string Cmd_Process::GetAudioNameIn()
{
	return ListOfComponents()[1];
}

const std::string Cmd_Process::GetAudioNameOut()
{
	return ListOfComponents()[2];
}

const std::string Cmd_Process::GetTypeOfSequence(int index)
{
	return sequences[index][1];

}

const std::string Cmd_Process::GetOperationOfSequence(int index)
{
	return sequences[index][0];
}

const double Cmd_Process::GetValueOfSequence(int index)
{
	return std::stod(sequences[index][2]);
}

const int Cmd_Process::GetSequencesSize()
{
	return sequences.size();
}


std::vector<std::string> Cmd_ArtificialSignals::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--artificialSignals");
	op_type = op_type + "--artificialSignals";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);

	return commandComponents;
}

int Cmd_ArtificialSignals::VerifyAcceptedWord(const std::string word)
{

	if (VerifyIntNumber(word) == 1)
		return 1;
	else if (VerifyFloatNumber(word) == 1)
		return 1;
	else
	{
		if (word.size() < 5)
		{
			return 0;
		}

		else
		{
			int index = word.size();
			if (word[index - 1] == 'v' && word[index - 2] == 'a' && word[index - 3] == 'w' && word[index - 4] == '.')
			{
				return 1;
			}

		}
	}
	return 0;
}

const std::string Cmd_ArtificialSignals::GetAudioNameOut()
{
	return ListOfComponents()[1];
}

const int Cmd_ArtificialSignals::GetSignalLength()
{
	return stoi(ListOfComponents()[2]);
}

const float Cmd_ArtificialSignals::GetFrequency()
{
	return stof(ListOfComponents()[3]);
}

const float Cmd_ArtificialSignals::GetSampleRate()
{
	return stof(ListOfComponents()[4]);
}

const std::string Cmd_ArtificialSignals::GetPath()
{
	return ListOfComponents()[5];
}

int Cmd_ArtificialSignals::VerifyIntNumber(const std::string word)
{
	int ok = 1;
	for (int index = 0; index < word.size(); index++)
	{
		if (!isdigit(word[index]))
			ok = 0;
	}
	if (ok == 1)
		return 1;
	return 0;
}

int Cmd_ArtificialSignals::VerifyFloatNumber(const std::string word)
{
	int ok = 1;
	int freq_minus = 0;
	for (int index = 0; index < word.size(); index++)
	{
		if (!isdigit(word[index]))
		{
			if (word[index] != '.' && word[index] != '-')
				ok = 0;
			if (word[index] == '-' && index != 0)
				ok = 0;

		}

	}
	if (ok == 1)
		return 1;
	return 0;
}

int Cmd_ArtificialSignals::VerifyWavFile(const std::string word)
{
	if (word.size() >= 5)
	{
		int index = word.size();
		if (word[index - 1] == 'v' && word[index - 2] == 'a' && word[index - 3] == 'w' && word[index - 4] == '.')
		{
			return 1;
		}
	}

	return 0;
}

int Cmd_ArtificialSignals::VerifyCommand()
{
	if (NumberOfComponents() == 6)
	{
		if (VerifyIntNumber(ListOfComponents()[2]) == 1 && VerifyFloatNumber(ListOfComponents()[3]) == 1 && VerifyFloatNumber(ListOfComponents()[4]) == 1 && VerifyWavFile(ListOfComponents()[1]) == 1 && VerifyWavFile(ListOfComponents()[5]))
		{
			return 1;
		}
	}
	return 0;
}

std::vector<std::string> Cmd_QuickSave::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--quickSave");
	op_type = op_type + "--quickSave";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);

	return commandComponents;
}

const std::string Cmd_QuickSave::GetAudioName()
{
	return ListOfComponents()[1];
}

int Cmd_QuickSave::VerifyCommand()
{
	std::vector<std::string> commandComponents;
	commandComponents = ListOfComponents();
	if (NumberOfComponents() == 2)
	{
		if (VerifyPath(GetAudioName()) == 1)
			return 1;
	}

	return 0;
}

void Cmd_quickLoad::SetLoadPath(const std::string& path)
{
	ListOfComponents()[1] = path;
}

const std::string Cmd_quickLoad::GetFolderPath()
{
	return ListOfComponents()[1];
}

int Cmd_quickLoad::VerifyPath(const std::string path)
{
	if (path[path.size() - 1] == '/' || path[path.size() - 1] == '\\')
		return 1;
	else
		return 0;
}

const int Cmd_quickLoad::GetPathSize()
{
	return GetFolderPath().size();
}

std::vector<std::string> Cmd_quickLoad::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--quickLoad");
	op_type = op_type + "--quickLoad";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0 && VerifyPath(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

int Cmd_quickLoad::VerifyCommand()
{
	bool ok = true;
	if (VerifyPath(GetFolderPath()) == 0)
		ok = false;
	for (int index = 2; index < ListOfComponents().size(); index++)
		if (VerifyAcceptedWord(ListOfComponents()[index]) == 0)
			ok = false;
	if (ok == true)
		return 1;
	return 0;
}

int Cmd_quickLoad::VerifyCommandForSettedPath()
{
	bool ok = true;
	if (VerifyPath(GetFolderPath()) == 1)
		ok = false;
	for (int index = 1; index < ListOfComponents().size(); index++)
		if (VerifyAcceptedWord(ListOfComponents()[index]) == 0)
			ok = false;
	if (ok == true)
		return 1;
	return 0;
}

void Cmd_quickLoad::print()
{
	for (int index = 0; index < ListOfComponents().size(); index++)
		std::cout << ListOfComponents()[index] << "\n";
}


//===============================================================


int Cmd_SetLoadPath::VerifyCommand()
{
	std::vector<std::string> commandComponents;
	commandComponents = ListOfComponents();
	if (NumberOfComponents() == 2)
	{
		if (VerifyPath(GetPath()) == 1)
			return 1;
	}

	return 0;
}

std::vector<std::string> Cmd_SetLoadPath::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--setLoadPath");
	op_type = op_type + "--setLoadPath";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyPath(word) == 0)
			{
				word = word + com[index];
			}
			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}
		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);
	return commandComponents;
}

const std::string Cmd_SetLoadPath::GetPath()
{
	return ListOfComponents()[1];
}

std::vector<std::string> Cmd_BassBoost::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--bassboost");
	op_type = op_type + "--bassboost";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}

			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}

		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);

	return commandComponents;
}

int Cmd_BassBoost::VerifyAcceptedWord(const std::string word)
{
	if (word.size() == 1 && int(word.at(0)) - 48 > 0 && int(word.at(0)) - 48 < 10)
		return 1;
	else
	{
		if (word.size() < 5)
		{
			return 0;
		}

		else
		{
			int index = word.size();
			if (word[index - 1] == 'v' && word[index - 2] == 'a' && word[index - 3] == 'w' && word[index - 4] == '.')
			{
				return 1;
			}

		}
	}
	return 0;
}

const std::string Cmd_BassBoost::GetAudioNameIn()
{
	return ListOfComponents()[2];
}

const std::string Cmd_BassBoost::GetAudioNameOut()
{
	return ListOfComponents()[3];
}

const double Cmd_BassBoost::GetValue()
{
	if (std::isdigit(ListOfComponents()[1].at(0)))
	{
		return std::stod(ListOfComponents()[1]);
	}

	else
		return -1;
}

int Cmd_BassBoost::VerifyWav(const std::string word)
{
	if (word.size() < 5)
	{
		return 0;
	}

	else
	{
		int index = word.size();
		if (word[index - 1] == 'v' && word[index - 2] == 'a' && word[index - 3] == 'w' && word[index - 4] == '.')
		{
			return 1;
		}

	}
}


int Cmd_BassBoost::VerifyCommand()
{
	if (ListOfComponents().size() == 4)
	{
		if (GetValue() != -1 && VerifyWav(GetAudioNameIn()) && VerifyWav(GetAudioNameOut()))
		{
			return 1;
		}
	}
	return 0;
}

std::vector<std::string> Cmd_Treble::ListOfComponents()
{
	std::string word = "";
	std::string op_type = "";
	std::vector<std::string> commandComponents;

	commandComponents.push_back("--treble");
	op_type = op_type + "--treble";

	for (int index = op_type.size() + 1; index < com.size(); index++)
	{
		if (com[index] == ' ')
		{
			if (VerifyAcceptedWord(word) == 0)
			{
				word = word + com[index];
			}

			else
			{
				commandComponents.push_back(word);
				word = "";
			}

		}

		else
		{
			word = word + com[index];
		}

	}
	commandComponents.push_back(word);

	return commandComponents;
}



const std::string Commands_ConfigurationFile::GetInputPath()
{
	int found = -1;
	for (int index = 0; index < com.size(); index++)
	{
		if (com[index] == "[Input]")
		{
			found = index;
			break;
		}
	}

	if (found != -1)
	{
		std::string path = "";
		int ok = 0;
		if (found + 1 < com.size())
			for (int index = 0; index < com[found + 1].size(); index++)
			{
				if (index + 4 < com[found + 1].size() && ok == 0)
					if (com[found + 1][index] == 'p' && com[found + 1][index + 1] == 'a' && com[found + 1][index + 2] == 't' && com[found + 1][index + 3] == 'h' && com[found + 1][index + 4] == '=')
					{
						ok = 1;
						index = index + 5;
					}
				if (ok == 1)
				{
					path = path + com[found + 1][index];
				}
			}
		if (ok == 1)
			return path;
	}

	return "NotFound";
}

const std::string Commands_ConfigurationFile::GetOutputPath()
{
	int found = -1;
	for (int index = 0; index < com.size(); index++)
	{
		if (com[index] == "[Output]")
		{
			found = index;
			break;
		}
	}

	if (found != -1)
	{
		std::string path = "";
		int ok = 0;
		if (found + 1 < com.size())
			for (int index = 0; index < com[found + 1].size(); index++)
			{
				if (index + 4 < com[found + 1].size() && ok == 0)
					if (com[found + 1][index] == 'p' && com[found + 1][index + 1] == 'a' && com[found + 1][index + 2] == 't' && com[found + 1][index + 3] == 'h' && com[found + 1][index + 4] == '=')
					{
						ok = 1;
						index = index + 5;
					}
				if (ok == 1)
				{
					path = path + com[found + 1][index];
				}
			}
		if (ok == 1)
			return path;
	}

	return "NotFound";
}

void Commands_ConfigurationFile::GetProcessors()
{
	int found = -1;
	for (int index = 0; index < com.size(); index++)
	{
		if (com[index] == "[Processors]")
		{
			found = index;
			break;
		}
	}
	if (found != -1)
	{
		std::string word = "";
		if (found + 1 < com.size())
		{
			for (int index = 0; index < com[found + 1].size(); index++)
			{
				if (index + 1 < com[found + 1].size())
				{
					if (com[found + 1][index] == '-' && com[found + 1][index + 1] == '>')
					{

						processes.push_back(word);
						word = "";
						index = index + 2;

					}
				}

				word = word + com[found + 1][index];


			}
			processes.push_back(word);
		}
	}


}

const int Commands_ConfigurationFile::GetFactor(const std::string process, int numberOfProcess)
{
	int numberFreq = 0;
	int found = -1;
	for (int index = 0; index < com.size(); index++)
	{
		if (com[index] == std::string("[" + process + "]") && numberFreq == numberOfProcess)
		{
			found = index;
			break;
		}
		else {
			if (com[index] == std::string("[" + process + "]") && numberFreq < numberOfProcess)
				numberFreq++;
		}

	}

	if (found != -1)
	{
		for (int index = 0; index < com[found + 1].size(); index++)
		{
			if (index + 7 < com[found + 1].size())
				if (com[found + 1][index] == 'f' && com[found + 1][index + 1] == 'a' && com[found + 1][index + 2] == 'c' && com[found + 1][index + 3] == 't' && com[found + 1][index + 4] == 'o' && com[found + 1][index + 5] == 'r' && com[found + 1][index + 6] == '=')
				{
					return (int)com[found + 1][index + 7] - 48;
					break;
				}

		}
	}

	return -1;

}

const std::string Commands_ConfigurationFile::GetType(const std::string process, int numberOfProcess)
{
	int numberFreq = 0;
	int found = -1;
	for (int index = 0; index < com.size(); index++)
	{
		if (com[index] == std::string("[" + process + "]") && numberFreq == numberOfProcess)
		{
			found = index;
			break;
		}
		else {
			if (com[index] == std::string("[" + process + "]") && numberFreq < numberOfProcess)
				numberFreq++;
		}


	}

	if (found != -1)
	{
		std::string type = "";
		int ok = 0;
		for (int index = 0; index < com[found + 2].size(); index++)
		{
			if (index + 4 < com[found + 2].size() && ok == 0)
				if (com[found + 2][index] == 't' && com[found + 2][index + 1] == 'y' && com[found + 2][index + 2] == 'p' && com[found + 2][index + 3] == 'e' && com[found + 2][index + 4] == '=')
				{
					ok = 1;
					index = index + 5;
				}
			if (ok == 1)
			{
				type = type + com[found + 2][index];
			}

		}
		return type;

	}
	return "NotFound";

}

int Commands_ConfigurationFile::verifyPath(std::string path)
{
	if (path.size() < 5)
	{
		return 0;
	}

	else
	{
		int index = path.size();
		if (path[index - 1] == 'v' && path[index - 2] == 'a' && path[index - 3] == 'w' && path[index - 4] == '.')
		{
			return 1;
		}

	}

	return 0;
}

int Commands_ConfigurationFile::verifyCommand()
{
	std::vector<std::pair<int, int>> index_freq_process;
	if (verifyPath(GetInputPath()) == 1 && verifyPath(GetOutputPath()) == 1)
	{
		GetProcessors();
		index_freq_process = IndexFreq();
		for (int index = 0; index < processes.size(); index++)
		{
			if (processes[index] == "playback")
			{
				for (int index1 = 0; index1 < index_freq_process.size(); index1++)
				{
					if (index_freq_process[index1].first == index)
					{
						if (GetType(processes[index], index_freq_process[index1].second) != "fast" && GetType(processes[index], index_freq_process[index1].second) != "slow")
							return -1;
						if (GetFactor(processes[index], index_freq_process[index1].second) < 1 && GetFactor(processes[index], index_freq_process[index1].second) > 9)
							return -2;
					}
				}

			}
			else if (processes[index] == "scale")
			{
				for (int index1 = 0; index1 < index_freq_process.size(); index1++)
				{
					if (index_freq_process[index1].first == index)
					{
						if (GetType(processes[index], index_freq_process[index1].second) != "up" && GetType(processes[index], index_freq_process[index1].second) != "down")
						{
							return -3;

						}
						if (GetFactor(processes[index], index_freq_process[index1].second) < 1 && GetFactor(processes[index], index_freq_process[index1].second) > 9)
							return -4;
					}
				}

			}
			else
				return 0;

		}
		return 1;
	}
	return 0;
}

std::vector<std::string> Commands_ConfigurationFile::GetAllProcesses()
{
	return processes;
}

std::vector<std::pair<int, int>> Commands_ConfigurationFile::IndexFreq()
{
	std::vector<std::pair<int, int>> index_freq_process;
	std::pair<int, int> index_frecventa;
	int freq_scale = 0;
	int freq_playback = 0;
	for (int index = 0; index < processes.size(); index++)
	{
		if (processes[index] == "scale")
		{
			index_frecventa.first = index;
			index_frecventa.second = freq_scale;
			index_freq_process.push_back(index_frecventa);
			freq_scale++;
		}
		else if (processes[index] == "playback")
		{
			index_frecventa.first = index;
			index_frecventa.second = freq_playback;
			index_freq_process.push_back(index_frecventa);
			freq_playback++;
		}
	}
	return index_freq_process;
}
