/*
		Sean Cragg Classes.h
		
		This file contains my class declarations.
		The member function definitions are located in Classes.cpp
*/

#pragma once

#include <iostream>
#include <string>
#include <random>

/*
		I found this simple library here https://github.com/adamstark/AudioFile, I use it
		to import the audio file and read the data as it would have been too time consuming to
		figure out how to do it myself, I use the documentation on that page to help me with the implmentation
		of the library.
*/

#include <AudioFile.h>

using namespace std;

//************************************************************************
//************************* Class Declarations ***************************
//************************************************************************

/*
		The sound class is essentially wrapper of the AudioFile class which I took from https://github.com/adamstark/AudioFile
		to load the audio files. I put the functions needed from it in to my own class as I do not need all the functionality from it
		and therefore made it easier for me to read this way.
*/
class Sound
{
public:
	void SetFilePathFromInput();
	string GetFilePath();
	void LoadSound();
	void WriteSound(string filepath);
	double GetSample(int channel, int sample);
	void SetSample(int channel, int sample, double value);
	int GetNumofSamples();
	int GetNumofChannels();

private:
	AudioFile<double> audiofile;
	string filepath;

};

/*
		This class processes the audio, and contains a function to encrypt or decrypt the file
		It has a variable which is a reference to a sound object so it will alter the original version
		this is so it does not copy the object as sound files can take up a lot of memory.
*/
class AudioTransformer
{
public:
	AudioTransformer(Sound& inputsound);
	void SetKeycodeFromInput();
	unsigned int GetKeycode();
	void EncryptSound();
	void DecryptSound();

private:
	Sound& sound;
	int keycode;
	
};

