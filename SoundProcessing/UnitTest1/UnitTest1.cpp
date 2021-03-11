#include "pch.h"

#include "CppUnitTest.h"
#include "../SoundProcessing/Operations.h"
#include "../SoundProcessing/Operations.cpp"
#include "../SoundProcessing/Commands.h"
#include "../SoundProcessing/Commands.cpp"
#include "../SoundProcessing/Audio.h"
#include "../SoundProcessing/Audio.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestPlaybackMethod)
		{
			std::vector<Audio> Playlist, modifiedSong;
			AudioFile<double> audio;
			audio.load("C:/Users/Daniel/Desktop/Final/guitar.wav");
			double SampleRate = audio.getSampleRate();
			std::pair<AudioFile<double>, std::string> per;
			per.first = audio;
			per.second = "C:/Users/Daniel/Desktop/Final/guitar.wav";
			Audio toSave(per);
			Playlist.push_back(toSave);
			std::string command = "--playback fast 3 No Complaints.wav PlaybackTest.wav";
			Operations op(command);
			op.GeneralizedPlayback(Playlist, modifiedSong, "No Complaints.wav", "PlaybackTest.wav", "fast", 3, 0);


			uint32_t newValue = SampleRate + (0.1 * 3 * SampleRate);
			Assert::AreEqual(modifiedSong[0].GetAudio().getSampleRate(), newValue);
		}

		TEST_METHOD(TestScaleMethod)
		{
			std::vector<Audio> Playlist, modifiedSong;
			AudioFile<double> audio;
			audio.load("C:/Users/Daniel/Desktop/Final/guitar.wav");
			double SampleRate = audio.getSampleRate();
			std::pair<AudioFile<double>, std::string> per;
			per.first = audio;
			per.second = "C:/Users/Daniel/Desktop/Final/guitar.wav";
			Audio toSave(per);
			Playlist.push_back(toSave);
			std::string command = "--scale up 3 No Complaints.wav ScaleTest.wav";
			Operations op(command);
			op.GeneralizedScale(Playlist, modifiedSong, "No Complaints.wav", "ScaleTest.wav", "up", 3, 0);




			double newValue;
			for (int canal = 0; canal < audio.getNumChannels(); canal++)
			{
				for (int i = 0; i < audio.getNumSamplesPerChannel(); i++)
				{
					newValue = audio.samples[canal][i] + ((double)3 / 10 * audio.samples[canal][i]);
					Assert::AreEqual(newValue, modifiedSong[0].GetAudio().samples[canal][i]);
				}
			}

		}







	};
}
