/*
		Sean Cragg Classes.h

		This file contains member class defenitions, declarations are found in Classes.h.
*/

#include "Classes.h"

//************************************************************************
//************************* Function Definitions *************************
//************************************************************************

//************************** Sound Functions *****************************

void Sound::SetFilePathFromInput()
{
	const int CHAR_ARRAY_SIZE = 100;
	char filepath_array[CHAR_ARRAY_SIZE];
	bool has_wav_suffix;

	do
	{
		cout << "Please enter the name of the audio file you wish to load including the file extension." << endl <<
			"The file must be located in the same folder as the application: ";
		/*
				using cin.getline() so i can read filenames with spaces included
		*/
		cin.clear();
		cin.getline(filepath_array, CHAR_ARRAY_SIZE);
		cout << endl;
		/*
				convert filepath_array to string so can perform checks
		*/
		string file(filepath_array);
		/*
				Ensures input is longer than 4 chars, prevents out of range error for next check 
		*/
		if (file.size() < 4)
		{
			cout << "File must end in .wav, try another file." << endl;
		}
		else
		{
			/*
					Checks if filename ends in .wav
			*/
			if ((file.substr(file.size() - 4)) != ".wav")
			{
				cout << "File must end in .wav, try another file." << endl;
				has_wav_suffix = false;
			}
			else
			{	
				/*
				if good writes file string to member variable filepath
				*/
				filepath = file;
				has_wav_suffix = true;
			}
		}
	} while (!has_wav_suffix);
}

/*
		Returns filepath variable
*/
string Sound::GetFilePath()
{
	return filepath;
}

/*
		Loads sound to the object using the AudioFile library, sound is written to an AudioFile object
*/
void Sound::LoadSound()
{
	bool soundloaded = false;

	/*
			If sound cannot successfully load, prompt the user again for a file.
	*/
	while (!soundloaded)
	{
		/*
				I want to refer to the filepath in the class so I can reference it later when setting the output file name.
		*/
		SetFilePathFromInput();
		/*
				Checking for error reading file. Output messages are dealt with by the function I have used from AudioFile.h
		*/
		if (audiofile.load(filepath))
		{	
			if (audiofile.getNumChannels() > 2)
				cout << "Error, more than two channels of audio. Try another file." << endl;
			else
			{
				soundloaded = true;
				cout << filepath << " loaded successfully." << endl;
			}
		}
	}
}

/*
		return number of samples. ie length
*/
int Sound::GetNumofSamples()
{
	return audiofile.getNumSamplesPerChannel();
}

/*
		return number of channels, ie mono or stereo
*/
int Sound::GetNumofChannels()
{
	return audiofile.getNumChannels();
}

/*
		Writes sound to disk with the filename specified in filepath
*/
void Sound::WriteSound(string filepath)
{
	if (audiofile.save(filepath))
		cout << "File successfully saved as: " << filepath << endl << endl;

}

/*
		Returns value for a single channel within chosen channel
*/
double Sound::GetSample(int channel, int sample)
{
	return audiofile.samples[channel][sample];
}

/*
		Set the value for a sample within chosen channel
*/
void Sound::SetSample(int channel, int sample, double value)
{
	audiofile.samples[channel][sample] = value;
}


//************************** Audio Transformer Functions *****************************

/*
		Constructor for Audio Transformer
*/
AudioTransformer::AudioTransformer(Sound& inputsound) : sound(inputsound)
{

}

void AudioTransformer::SetKeycodeFromInput()
{	
	do
	{
		cin.clear();
		cin >> keycode;

		/*
				Was hoping this would prevent float and negative input but does not work, however does prevent char inputs so I have left it here.
		*/
		while (!cin.good())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');

			cout << "Must be a positive integer value." << endl << "Please enter the keycode: " << endl;
			cin >> keycode;
		}

		if (keycode >= 1000000000 || keycode < 0)
			cout << "Keycode must be a positive integer up to 9 digits long, try again." << endl;

	} while (keycode >= 1000000000 || keycode < 0);
}

/*
		Returns the keycode
*/
unsigned int AudioTransformer::GetKeycode()
{
	return keycode;
}


/*
		This is the function used to encrypt the audio, uses psuedorandom numbers to add noise to the audio file
		The random number generator is seeded by the keycode, this allows the audio to later be decrypted by using the same keycode.

*/

void AudioTransformer::EncryptSound()
{
	/*
			Seed the random number generator with the keycode. I took the code of the random number generator off of lectures from my graphics module
			and adapted it to output double values.
	*/
	std::mt19937 generator(keycode);
	std::uniform_real_distribution<double> distribution(-0.95, 0.95);
	/*
			For each channel loop through each sample and add a psuedorandom number to a fraction of the original sample
	*/
	for (int i = 0; i < sound.GetNumofChannels(); i++)
	for (int j = 0; j < sound.GetNumofSamples(); j++)
	{
		sound.SetSample(i, j, (sound.GetSample(i, j) * 0.05) + distribution(generator));
	}
}

/*
		This is the function used to decrypt an encrypted audio file, uses the keycode to seed the pesudorandom number
		generator which takes the noise away from the encrypted file.

*/
void AudioTransformer::DecryptSound()
{
	/*
			Seed the random number generator with the keycode. I took the code of the random number generator from lectures from my graphics module
			and adapted it to output double values.
	*/
	std::mt19937 generator(keycode);
	std::uniform_real_distribution<double> distribution(-0.95, 0.95);
	/*
			Loop through each sample take away number generated by the psuedorandom generator and the increase the amplitude to make it audible
	*/
	for (int i = 0; i < sound.GetNumofChannels(); i++)
	for (int j = 0; j < sound.GetNumofSamples(); j++)
	{
		sound.SetSample(i, j, ((sound.GetSample(i, j)) - distribution(generator)) * 20);
	}
}
