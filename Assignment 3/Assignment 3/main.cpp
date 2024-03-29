/*
		Assignment3: Sean Cragg

		Audio Encryptor/Decryptor

		This programme currently only handles WAV files.
		I have only tested it with files exported from the freeware Audacity using WAV 16bit signed PCM format
		Therefore it may not be compatible with other formats.

*/

/*
		Include classes.h file which includes my class declarations, my #include libraries are located here also.
*/
#include "Classes.h"

using namespace std;

//************************************************************************
//************************* Function Declarations ************************
//************************************************************************
/*
		Displays program instructions to user
*/
void displayinstructions()
{
	cout << "This program allows you to take in a .WAV audio file and encrypt the audio to obscure the contents" << endl <<
		"The encrypted audio can be decrypted with this program by providing the keycode which was specified when the audio was originally encrypted." << 
		endl << "Encrypted audio will be saved as 'originalfilename_encrypted_keycode.wav'." << endl <<
		"Decrypted audio will be saved as 'originalfilename_decrypted.wav'." <<
		endl << endl;
}
/*
		allows user to input a char to a variable. cin.clear() and cin.ignore() was called to prevent an
		odd error I got when a huge input was entered, the next time cin was called user could not type
		an input would continuously input on its own.
*/
void inputchar(char& variable)
{
	cin.clear();
	cin >> variable;
	cin.ignore(INT_MAX, '\n');
}

//************************************************************************
//************************* Main Function ********************************
//************************************************************************

int main()
{
	/*
			Variable declarations
	*/
	string write_name;
	char another_file;

	displayinstructions();

	do
	{
		/*
				Create sound object and load file
		*/
		Sound sound;
		sound.LoadSound();

		/*
				Create audio transformer object taking reference to the sound object
		*/
		AudioTransformer audiotransformer(sound);

		/*
				Ask user if they wish to encrypt or decrypt the audio then call the appropriate function to transform the sound.
				if user inputs unrecognised input the user is prompted once again.
		*/
		char encrypt_or_decrypt;
		do
		{
			cout << "Do you wish to encrypt or decrypt this file? (input e/d): ";
			inputchar(encrypt_or_decrypt);
			switch (encrypt_or_decrypt)
			{

			/*
					If user chooses encrypt calls encrypt function and creates approproate filename for the saved audio
			*/
			case 'e':
			case 'E':
			{
				cout << endl << "Please enter the keycode you wish to encrypt this audio with (positive integer number up to 9 digits long): ";
				audiotransformer.SetKeycodeFromInput();
				audiotransformer.EncryptSound();
				write_name = (sound.GetFilePath()).erase((sound.GetFilePath()).length() - 4) + "_encrypted_" + to_string(audiotransformer.GetKeycode());
				break;
			}

			/*
					If user chooses decrypt calls decrypt function and creates approproate filename for the saved audio
			*/
			case 'd':
			case 'D':
			{
				cout << endl << "Please enter the keycode used to decrypt this audio: ";
				audiotransformer.SetKeycodeFromInput();
				audiotransformer.DecryptSound();
				write_name = (sound.GetFilePath()).erase((sound.GetFilePath()).length() - 4) + "_decrypted";
				break;
			}

			/*
					For unrecognised input
			*/
			default:
			{
				cout << endl << "Unrecognised input. Please try again.";
				break;
			}
			}
		} while (encrypt_or_decrypt != 'e' && encrypt_or_decrypt != 'E' && encrypt_or_decrypt != 'd' && encrypt_or_decrypt != 'D');

		/*
				Write the transformed sound to disk
		*/
		sound.WriteSound(write_name + ".wav");

		/*
				Ask user if they wish to process another file
		*/
		do {
			cout << "Do you wish to process another file? (y/n): ";
			inputchar(another_file);
			cout << endl;
			if (another_file != 'y' && another_file != 'Y' && another_file != 'n' && another_file != 'N')
				cout << "Unrecognised input. Please try again.";
		} while (another_file != 'y' && another_file != 'Y' && another_file != 'n' && another_file != 'N');

		/*
				If answers y/Y process another file by running whole process again, else exit program.
		*/
	} while (another_file == 'y' || another_file == 'Y');

	return 0;
}


