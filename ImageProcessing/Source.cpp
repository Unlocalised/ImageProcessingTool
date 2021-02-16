#include "SDL_Wrapper.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
//Function Prototypes
void DisplaySurfaceUntilClose(SDL_Surface* Surface);
void DisplayMenu();
void DisplayImage(SDL_Surface* ImgSurface, int width, int height);
void ApplyTint(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void ChangeContrast(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void NegativeImage(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void RemoveColour(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void AddNoise(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void EdgeDetection(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void AdjustBrightness(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void DrawMargins(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void ApplyRandomEffect(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void Blur(SDL_Surface* ImageSurface, Uint8 R, Uint8 G, Uint8 B);
void BlackAndWhiteImage(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B);
void SaveImage(SDL_Surface* ImgSurface,SDL_Surface *SecondImage);
void DisplayDebugInfo(SDL_Surface* ImgSurface);
int VerifyInput(istream& Stream, int UserInput, int Val1, int Val2);
int SaveProgress();

int main(int argc, char * argv[])
{
	int  UserInput = 0, width = 0, height = 0; // Stores the users menu selection and the width and height of the window
	string Location = ""; // stores the location of the window 
	bool IsSuccessful = 0, OnExit = 0; //boolean to determine if the image has been loaded correctly
	SDL_Surface* ImageSurface = NULL, *OriginalImage = NULL, *StoredImage = NULL; //Defines an image surface pointer and sets it to NULL
	Uint8 R = 0, G = 0, B = 0; // Gets the RGB Value from a Pixel Location

	cout << "Welcome to the image processing tool! " << endl << endl;

	do
	{
		cout << "Enter your image location: " << endl;
		cin >> Location;
		// Load in the Image
		cout << "Loading Image : " << Location << endl;
		ImageSurface = LoadImage(Location.c_str());
		OriginalImage= LoadImage(Location.c_str());
		// Check if the image has been loaded correctly
		if (ImageSurface == NULL)
		{
			IsSuccessful = 0; // Loop and try again
		}
		else
		{
			IsSuccessful = 1; // Image loaded correctly

			// Get The Array of the Pixels (Access to the Raw Data Pointer)
			//
			// This is a 1D array, however represents the entire image. 

			Uint8* ImageArray = GetPixelArray(ImageSurface, &width, &height);
			Uint8 *NewArray = GetPixelArray(OriginalImage, &width, &height);
		}
	} while (IsSuccessful == 0); //Loops until the image can be loaded

	do
	{
		DisplayMenu(); //Displays choices to user

		switch (VerifyInput(cin, UserInput, 18, 0)) //Selects alteration to image based on user input
		{
		case 1:
			DisplayImage(ImageSurface, width, height); //Displays Image by calling function
			break;
		case 2:
			if (SaveProgress() == 0)
			{
				ApplyTint(OriginalImage, R, G, B); //Calls tint function
				DisplayImage(OriginalImage, width, height); //Displays changes and asks if user wishes to save
			}
			else
			{
				ApplyTint(ImageSurface, R, G, B); //Calls tint function
				DisplayImage(ImageSurface, width, height); //Displays changes and asks if user wishes to save
			}
			break;
		case 3:
			if (SaveProgress() == 0)
			{
				ChangeContrast(OriginalImage, R, G, B); //Calls contrast function
				DisplayImage(OriginalImage, width, height); //Displays changes and asks if user wishes to save
			}
			else
			{
				ChangeContrast(ImageSurface, R, G, B); //Calls contrast function
				DisplayImage(ImageSurface, width, height); //Displays changes and asks if user wishes to save
			}
			
			break;
		case 4:
			if (SaveProgress() == 0)
			{
				NegativeImage(OriginalImage, R, G, B);//Calls negative image function
				DisplayImage(OriginalImage, width, height);
			}
			else
			{
				NegativeImage(ImageSurface, R, G, B);
				DisplayImage(ImageSurface, width, height);
			}
			break;
		case 5:
			if (SaveProgress() == 0)
			{
				RemoveColour(OriginalImage, R, G, B); //Calls remove colour function
				DisplayImage(OriginalImage, width, height);
			}
			else
			{
				RemoveColour(ImageSurface, R, G, B); //Calls remove colour function
				DisplayImage(ImageSurface, width, height);
			}
			break;
		case 6:
			if (SaveProgress() == 0)
			{
				AddNoise(OriginalImage, R, G, B); //Calls add noise function
				DisplayImage(OriginalImage, width, height);
			}
			else
			{
				AddNoise(ImageSurface, R, G, B); //Calls add noise function
				DisplayImage(ImageSurface, width, height);
			}
			break;
		case 7:
			if (SaveProgress() == 0)
			{
				EdgeDetection(OriginalImage, R, G, B); //Calls Edge detection function
				DisplayImage(OriginalImage, width, height);
			}
			else
			{
				EdgeDetection(ImageSurface, R, G, B); //Calls edge detection function
				DisplayImage(ImageSurface, width, height);
			}
			break;
		case 8:
			if (SaveProgress() == 0)
			{
				AdjustBrightness(OriginalImage, R, G, B); //Calls brightness function
				DisplayImage(OriginalImage, width, height);
			}
			else
			{
				AdjustBrightness(ImageSurface, R, G, B); //Calls brightness function
				DisplayImage(ImageSurface, width, height);
			}
			break;
		case 9:
			if (SaveProgress() == 0)
			{
				DrawMargins(OriginalImage, R, G, B); //Calls draw margins function
				DisplayImage(OriginalImage, width, height);
			}
			else
			{
				DrawMargins(ImageSurface, R, G, B); //Calls draw margins function
			}
			break;
		case 10:
			if (SaveProgress() == 0)
			{
				ApplyRandomEffect(OriginalImage, R, G, B); //Calls random effect function
				DisplayImage(OriginalImage, width, height);
			}
			else
			{
				ApplyRandomEffect(ImageSurface, R, G, B); //Calls random effect function
				DisplayImage(ImageSurface, width, height);
			}
			break;
		case 11:
			SaveImage(ImageSurface,OriginalImage);
			break;
		case 12:
			DisplayDebugInfo(ImageSurface); //Displays height and width of image
			break;
		case 13:
			if (SaveProgress() == 0)
			{
				BlackAndWhiteImage(OriginalImage, R, G, B);
				DisplayImage(OriginalImage, width,height);
			}
			else
			{
				BlackAndWhiteImage(ImageSurface, R, G, B);
				DisplayImage(ImageSurface, width, height);
			}
			break;
		case 14:
			if (SaveProgress() == 0)
			{
				Blur(OriginalImage, R, G, B);
				DisplayImage(OriginalImage, width, height);
			}
			else
			{
				Blur(ImageSurface, R, G, B);
				DisplayImage(ImageSurface, width, height);
			}
			break;
		case 15:
			DisplayImage(OriginalImage, width, height);
			break;
		case 16:
			ImageSurface = NULL;
			ImageSurface = LoadImage(Location.c_str());
			OriginalImage = NULL;
			OriginalImage = LoadImage(Location.c_str());
			break;
		case 17: //Exit program
			// IMPORTANT : Use SDL_FreeSurface once you have finished with any image (including the ones you have loaded up)
			SDL_FreeSurface(ImageSurface);
			SDL_FreeSurface(OriginalImage);
			return 0;
		default:
			cout << "Unrecognised input, try again." << endl << endl;;
			cin >> UserInput;
		}
	} while (OnExit == 0);

}

void DisplaySurfaceUntilClose(SDL_Surface* Surface)
{
	int open = 1; // In C++, one would ordinarily use bool for this. In C, something like this has to be used.
	SDL_Event event;

	// Display the image in the window
	DisplaySurface(Surface);

	// While we aren't closing the window...
	while (open == 1)
	{
		if (SDL_PollEvent(&event))
		{
			// Close the window if it is closed
			if (CheckClosePressed(&event))
			{
				open = 0;
				continue;
			}

			/* This switch statement shows an example of how to check keys that the user has pressed. Most keys on a keyboard can be checked using the SDLK_<key> enum values,
			for instance SDLK_q specifies the 'q' key, or SDLK_RETURN specifies the return/enter key (not the one on the number pad).

			If you are interested, many other events can be checked; however you will have to research the SDL 1.2 documentation yourself! */
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					open = 0;
					break;
				default:
					break;
				}

				break;
			default:
				break;
			}
		}
	}
}

void DisplayMenu() //Shows menu to users
{
	cout << "Welcome to the image editing menu, please select an item: " << endl;
	cout << "1.) Display the original image" << endl;
	cout << "2.) Apply a tint/filter" << endl;
	cout << "3.) Change contrast" << endl;
	cout << "4.) Produce Negative image" << endl;
	cout << "5.) Remove Colour" << endl;
	cout << "6.) Add noise" << endl;
	cout << "7.) Edge Detection" << endl;
	cout << "8.) Adjust Brightness" << endl;
	cout << "9.) Draw Margins" << endl;
	cout << "10.)Apply Random Effect" << endl;
	cout << "11.)Save an image" << endl;
	cout << "12.)ImageInformation" << endl;
	cout << "13.)Black And White" << endl;
	cout << "14.)Blur" << endl;
	cout << "15.)Display back-up image" << endl;
	cout << "16.)Revert to Original" << endl;
	cout << "17,)Exit" << endl;
}

void DisplayImage(SDL_Surface* ImgSurface, int width, int height)
{
	// Creates a window called 'MyImage' at the same width and height as the original image
	CreateWindow("MyImage", width, height);
	DisplaySurfaceUntilClose(ImgSurface); // Display the image in the window
	CloseWindow();
	cout << endl;
}

void ApplyTint(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B)
{
	int choice = 0, RedVal = 0, GreenVal = 0, BlueVal = 0, Selection = 0, Catch = 0; //Variables for new editied values and various error checks
	cout << "1.)Manualy edit values " << endl;
	cout << "2.)Pre-set filters" << endl;

	if (VerifyInput(cin, choice, 3, 0) == 1) //Allows user to manually edit RGB values
	{
		cout << "To keep the original, enter -1 as a value:" << endl;
		cout << "Enter Value for Red: ";
		RedVal = VerifyInput(cin, RedVal, 256, -2);
		cout << "Enter Value for Green: ";
		GreenVal = VerifyInput(cin, GreenVal, 256, -2);
		cout << "Enter Value for Blue: ";
		BlueVal = VerifyInput(cin, BlueVal, 256, -2);

		for (int y = 0; y < ImgSurface->h-1; y++) //Loops through all pixels and applies users colour edits
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B); // If any of the inputs are -1, keep the red green or blue value as its original
				if (RedVal == -1){ SetRGBValues(ImgSurface, x, y, R, GreenVal, BlueVal); }
				else if (GreenVal == -1){ SetRGBValues(ImgSurface, x, y, RedVal, G, BlueVal); }
				else if (BlueVal == -1){ SetRGBValues(ImgSurface, x, y, RedVal, GreenVal, B); }
				else { SetRGBValues(ImgSurface, x, y, RedVal, GreenVal, BlueVal); }
			}

		}
	}
	else  //Allows user to select pre-defined filters
	{
		cout << "1.) Purple Filter" << endl;
		cout << "2.) Yellow Filter" << endl;
		cout << "3.) Cyan Filter " << endl;
		cout << "4.) Green Filter" << endl;
		cout << "5.) Red Filter" << endl;
		cout << "6.) Blue Filter" << endl;

		switch (VerifyInput(cin, Selection, 7, 0))
		{
		case 1:
			for (int y = 0; y < ImgSurface->h; y++) //Applies purple filter
			{
				for (int x = 0; x < ImgSurface->w; x++)
				{
					GetRGBValues(ImgSurface, x, y, &R, &G, &B);
					SetRGBValues(ImgSurface, x, y, R, G = 50, B);
				}

			}
			break;
		case 2:
			for (int y = 0; y < ImgSurface->h; y++) // Yellow filter
			{
				for (int x = 0; x < ImgSurface->w; x++)
				{
					GetRGBValues(ImgSurface, x, y, &R, &G, &B);
					SetRGBValues(ImgSurface, x, y, R, G, B = 50);
				}

			}
			break;

		case 3:
			for (int y = 0; y < ImgSurface->h; y++) // Cyan filter
			{
				for (int x = 0; x < ImgSurface->w; x++)
				{
					GetRGBValues(ImgSurface, x, y, &R, &G, &B);
					SetRGBValues(ImgSurface, x, y, R = 50, G, B);
				}

			}
			break;
		case 4:
			for (int y = 0; y < ImgSurface->h; y++) //Green filter
			{
				for (int x = 0; x < ImgSurface->w; x++)
				{
					GetRGBValues(ImgSurface, x, y, &R, &G, &B);
					SetRGBValues(ImgSurface, x, y, R = 50, G, B = 50);
				}

			}
			break;
		case 5:
			for (int y = 0; y < ImgSurface->h; y++) //Red filter
			{
				for (int x = 0; x < ImgSurface->w; x++)
				{
					GetRGBValues(ImgSurface, x, y, &R, &G, &B);
					SetRGBValues(ImgSurface, x, y, R, G = 50, B = 50);
				}

			}
			break;
		case 6:
			for (int y = 0; y < ImgSurface->h; y++) //Blue filter
			{
				for (int x = 0; x < ImgSurface->w; x++)
				{
					GetRGBValues(ImgSurface, x, y, &R, &G, &B);
					SetRGBValues(ImgSurface, x, y, R=50, G=50, B);
				}

			}
			break;
		}


	}

}

void ChangeContrast(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B)
{
	int contrast = 0;
	cout << "Enter a contrast factor between 0 and 20: " << endl;
	contrast = VerifyInput(cin, contrast, 21, -1);
	for (int y = 0; y < ImgSurface->h; y++)
	{
		for (int x = 0; x < ImgSurface->w; x++) //Alters contrast of each pixel according to input
		{

			GetRGBValues(ImgSurface, x, y, &R, &G, &B);
			int Rnew = (contrast*(R - 128) + 128);
			int Gnew = (contrast*(G - 128) + 128);
			int Bnew = (contrast*(B - 128) + 128);
			if (Rnew > 255){ Rnew = 255; }
			if (Rnew < 0){ Rnew = 0; }
			if (Gnew > 255){ Gnew = 255; }
			if (Gnew < 0){ Gnew = 0; }
			if (Bnew > 255){ Bnew = 255; }
			if (Bnew < 0){ Bnew = 0; }

			SetRGBValues(ImgSurface, x, y, Rnew, Gnew, Bnew);
		}
	}

}

void NegativeImage(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B)//Applies negative filter to image
{
	for (int y = 0; y < ImgSurface->h; y++)
	{
		for (int x = 0; x < ImgSurface->w; x++)
		{
			GetRGBValues(ImgSurface, x, y, &R, &G, &B);
			SetRGBValues(ImgSurface, x, y, 255 - R, 255 - G, 255 - B);
		}
	}
	
}

void RemoveColour(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B) //Removes all but a specified colour from an image
{
	int ColourToBeRemoved = 0;
	cout << "What colour hue do you wish to remain in the image? " << endl;
	cout << "1.) Red-Yellow " << endl;
	cout << "2.) Yellow-Green " << endl;
	cout << "3.) Green-Blue " << endl;
	cout << "4.) Blue-Purple " << endl;
	cout << "5.) Purple-Pink " << endl;
	cout << "6.) Pink-Red " << endl;

	switch (VerifyInput(cin, ColourToBeRemoved, 7, 0))
	{
	case 1:
		for (int y = 0; y < ImgSurface->h; y++)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B); //Formula for calculating hue
				double Formula = atan2(sqrt(3)*(G - B), 2 * R - G - B);
				Formula /= 3.141592654;
				Formula *= 180;
				Formula = abs(Formula);
				if (Formula >= 0 && Formula <60)
				{
					//RED TO YELLOW
					SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 60 && Formula <120)
				{
					//YELLOW TO GREEN
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
				}
				else if (Formula >= 120 && Formula < 180)
				{
					//GREEN TO BLUE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
				}
				else if (Formula >= 180 && Formula < 240)
				{
					//BLUE TO PURPLE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
				}
				else if (Formula >= 240 && Formula < 300)
				{
					//PURPLE TO PINK
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
				}
				else if (Formula >= 300 && Formula < 360)
				{
					//PINK TO RED
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
				}
			}
		}
		break;
	case 2:
		for (int y = 0; y < ImgSurface->h; y++)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				//double Formula = ((atan(sqrt(3)*(G - B) /(2 * (R - G - B))))/3.141592654)*180;
				double Formula = atan2(sqrt(3)*(G - B), 2 * R - G - B);
				Formula /= 3.141592654;
				Formula *= 180;
				Formula = abs(Formula);
				if (Formula >= 0 && Formula <60)
				{
					//RED TO YELLOW
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 60 && Formula <120)
				{
					//YELLOW TO GREEN
					//SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 120 && Formula < 180)
				{
					//GREEN TO BLUE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 180 && Formula < 240)
				{
					//BLUE TO PURPLE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 240 && Formula < 300)
				{
					//PURPLE TO PINK
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 300 && Formula < 360)
				{
					//PINK TO RED
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}

			}
		}

		break;
	case 3:
		for (int y = 0; y < ImgSurface->h; y++)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				double Formula = atan2(sqrt(3)*(G - B), 2 * R - G - B);
				Formula /= 3.141592654;
				Formula *= 180;
				Formula = abs(Formula);
				if (Formula >= 0 && Formula <60)
				{
					//RED TO YELLOW
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 60 && Formula <120)
				{
					//YELLOW TO GREEN
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 120 && Formula < 180)
				{
					//GREEN TO BLUE
					//SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 180 && Formula < 240)
				{
					//BLUE TO PURPLE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 240 && Formula < 300)
				{
					//PURPLE TO PINK
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 300 && Formula < 360)
				{
					//PINK TO RED
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
			}
		}
		break;
	case 4:
		for (int y = 0; y < ImgSurface->h; y++)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				double Formula = atan2(sqrt(3)*(G - B), 2 * R - G - B);
				Formula /= 3.141592654;
				Formula *= 180;
				Formula = (Formula);
				if (Formula >= 0 && Formula <60)
				{
					//RED TO YELLOW
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 60 && Formula <120)
				{
					//YELLOW TO GREEN
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 120 && Formula < 180)
				{
					//GREEN TO BLUE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 180 - 360 && Formula < 240 - 360)
				{
					//BLUE TO PURPLE
					//SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 240 - 360 && Formula < 300 - 360)
				{
					//PURPLE TO PINK
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 300 - 360 && Formula < 360 - 360)
				{
					//PINK TO RED
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
			}
		}
		break;
	case 5:
		for (int y = 0; y < ImgSurface->h; y++)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				double Formula = atan2(sqrt(3)*(G - B), 2 * R - G - B);
				Formula /= 3.141592654;
				Formula *= 180;
				Formula = (Formula);
				if (Formula >= 0 && Formula <60)
				{
					//RED TO YELLOW
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 60 && Formula <120)
				{
					//YELLOW TO GREEN
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 120 && Formula < 180)
				{
					//GREEN TO BLUE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 180 - 360 && Formula < 240 - 360)
				{
					//BLUE TO PURPLE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 240 - 420 && Formula < 300 - 420)
				{
					//PURPLE TO PINK
					//SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 300 - 360 && Formula < 360 - 360)
				{
					//PINK TO RED
					//SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
			}
		}
		break;
	case 6:
		for (int y = 0; y < ImgSurface->h; y++)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				double Formula = atan2(sqrt(3)*(G - B), 2 * R - G - B);
				Formula /= 3.141592654;
				Formula *= 180;
				Formula = (Formula);
				if (Formula >= 0 && Formula <60)
				{
					//RED TO YELLOW
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 60 && Formula <120)
				{
					//YELLOW TO GREEN
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 120 && Formula < 180)
				{
					//GREEN TO BLUE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 180 - 360 && Formula < 240 - 360)
				{
					//BLUE TO PURPLE
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 240 - 360 && Formula < 300 - 360)
				{
					//PURPLE TO PINK
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
				else if (Formula >= 300 - 480 && Formula < 360 - 480)
				{
					//PINK TO RED
					SetRGBValues(ImgSurface, x, y, (R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
					//SetRGBValues(ImgSurface, x, y, R, G, B);
				}
			}
		}
		break;
	default:
		cout << "Invalid Selection" << endl;
	}

}

void AddNoise(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B)
{
	double Rand = 0,UserFactorL=0,UserFactorU =0;
	cout << "Noise Factor lower bound between 0 and 100" << endl;
	UserFactorL = VerifyInput(cin, UserFactorL, 101, -1);
	cout << "Noise Factor upper bound between 0 and 100" << endl;
	UserFactorU = VerifyInput(cin,UserFactorU, 101, -1);
	for (int y = 0; y < ImgSurface->h; y++)
	{
		for (int x = 0; x < ImgSurface->w; x++)
		{
			Rand = rand() % 100; //Adds random black pixels to image
			if (Rand < UserFactorL)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				SetRGBValues(ImgSurface, x, y, 0, 0, 0);
			}
			else if (Rand > 95)
			{
				//Adds random white pixels to image
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				SetRGBValues(ImgSurface, x, y, 255, 255, 255);
			}
			else
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				SetRGBValues(ImgSurface, x, y, R, G, B);
			}
		}
	}

}

void EdgeDetection(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B)
{
	float Luminance = 0, Luminance1 = 0, Luminance2 = 0;
	int Threshold = 0;
	cout << "Enter a factor for edge detection:" << endl << "As the value increases, it will prodice less edges:" << endl;
	cin >> Threshold;
	for (int y = 0; y < ImgSurface->h - 1; y++)
	{
		for (int x = 1; x < ImgSurface->w; x++) //Gets the luminance of each pixel around the neighbours of a pixel
		{
			GetRGBValues(ImgSurface, x, y, &R, &G, &B);
			Luminance = (R + G + B) / 3;
			GetRGBValues(ImgSurface, x, y + 1, &R, &G, &B);
			Luminance1 = (R + G + B) / 3;
			GetRGBValues(ImgSurface, x - 1, y, &R, &G, &B);
			Luminance2 = (R + G + B) / 3;
			//Finds if there is a big change in luminance between adjacent pixels
			if ((Luminance - Luminance1)*(Luminance - Luminance1) <= Threshold || ((Luminance - Luminance2)*(Luminance - Luminance2)) <= Threshold)
			{
				SetRGBValues(ImgSurface, x, y, 0, 0, 0);
			}
			else
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				SetRGBValues(ImgSurface, x, y, 255, 255, 255);
			}
		}
	}

}

void AdjustBrightness(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B)
{

	int DiffR, DiffG, DiffB = 0, BrightnessFactor = 0;
	cout << " Enter a value to alter the brightness between -128 and +128: " << endl;

	BrightnessFactor = VerifyInput(cin, BrightnessFactor, 129, -129);

	for (int y = 0; y <ImgSurface->h; y++)
	{
		for (int x = 0; x < ImgSurface->w; x++) //Adds or removes brightness by adding values to rgb
		{
			GetRGBValues(ImgSurface, x, y, &R, &G, &B);
			DiffR = R + BrightnessFactor;
			DiffG = G + BrightnessFactor;
			DiffB = B + BrightnessFactor;
			if (DiffR > 255){ DiffR = 255; }
			if (DiffR < 0){ DiffR = 0; }
			if (DiffG > 255){ DiffG = 255; }
			if (DiffG < 0){ DiffG = 0; }
			if (DiffB > 255){ DiffB = 255; }
			if (DiffB < 0){ DiffB = 0; }
			SetRGBValues(ImgSurface, x, y, DiffR, DiffG, DiffB);
		}
	}
}

void DrawMargins(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B)
{
	int UserSelect = 0;
	cout << "Select the margin to be drawn to the screen " << endl;
	cout << "1.)Horizontal Half Margin" << endl;
	cout << "2.)Vertical Half Margin" << endl;
	cout << "3.)Horizontal quarter Margin" << endl;
	cout << "4.)Vertical quarter Margin" << endl;
	cout << "5.)Horizontal eighth Margin" << endl;
	cout << "6.)Vertical eighth Margin" << endl;

	switch (VerifyInput(cin, UserSelect, 7, 0))
	{
	case 1: //Draws a black line at various points on the screen
		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				SetRGBValues(ImgSurface, x, ImgSurface->h / 2, 0, 0, 0);
			}
		}
		break;
	case 2:
		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				SetRGBValues(ImgSurface, ImgSurface->w / 2, y, 0, 0, 0);
			}
		}
		break;

	case 3:
		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				SetRGBValues(ImgSurface, x, ImgSurface->h / 4, 0, 0, 0);
			}
		}
		break;

	case 4:
		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				SetRGBValues(ImgSurface, ImgSurface->w / 4, y, 0, 0, 0);
			}
		}
		break;

	case 5:
		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				SetRGBValues(ImgSurface, x, ImgSurface->h / 8, 0, 0, 0);
			}
		}
		break;

	case 6:
		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				SetRGBValues(ImgSurface, ImgSurface->w / 8, y, 0, 0, 0);
			}
		}
		break;

	default:
		cout << "No menu item selected.." << endl;
	}

}

void ApplyRandomEffect(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B)
{
	cout << "Enter a value between 1 and 5 " << endl; // Sets a pre defined filter on the image based on user input
	int Choice = 0;

	switch (VerifyInput(cin, Choice, 6, 0))
	{
	case 1: //Applies filter 1
		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				SetRGBValues(ImgSurface, x, y, R + 0.5*G + 0.25*B, 0.25*R + G + 0.5*B, 0.5*R + 0.25*G + B);
			}
		}
		break;
	case 2: //Applies Filter 2

		for (int y = 0; y < ImgSurface->h; y++)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				SetRGBValues(ImgSurface, x / 2, y / 2, R, G, B);
				SetRGBValues(ImgSurface, x, y, 0, 0, 0);
			}
		}

		break;
	case 3: //Applies filter 3
		for (int y = 0; y < ImgSurface->h - 1; y++)
		{
			for (int x = 1; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				int Luminance = (R + G + B) / 3;
				GetRGBValues(ImgSurface, x, y + 1, &R, &G, &B);
				int Luminance1 = (R + G + B) / 3;
				GetRGBValues(ImgSurface, x - 1, y, &R, &G, &B);
				int Luminance2 = (R + G + B) / 3;
				if ((Luminance - Luminance1)*(Luminance - Luminance1) <= 5 || ((Luminance - Luminance2)*(Luminance - Luminance2)) <= 5)
				{
					SetRGBValues(ImgSurface, x, y, 255, 255, 255);
				}
				else
				{
					GetRGBValues(ImgSurface, x, y, &R, &G, &B);
					SetRGBValues(ImgSurface, x, y, R, G, B);
				}
			}
		}

		break;
	case 4: //Applies Filter 4

		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				SetRGBValues(ImgSurface, x, y, (R + G + B) / 2, (R + G + B) / 2, (R + G + B) / 2);
			}
		}
		break;
	case 5:// Applies Filter 5
		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				SetRGBValues(ImgSurface, x, y, R + 0.5*G + 0.25*B, 0.25*R + G + 0.5*B, 0.5*R + 0.25*G + B);

			}
		}
		break;
	default: //Provides default case and sets colour of image to the original
		for (int y = ImgSurface->h - 1; y >= 0; y--)
		{
			for (int x = 0; x < ImgSurface->w; x++)
			{
				GetRGBValues(ImgSurface, x, y, &R, &G, &B);
				SetRGBValues(ImgSurface, x, y, R, G, B);
			}
		}
	}
}

void Blur(SDL_Surface* ImageSurface, Uint8 R, Uint8 G, Uint8 B)
{
	int NewValR = 0, NewValG = 0, NewValB = 0;
	for (int y = 1; y < ImageSurface->h - 1; y++)
	{
		for (int x = 1; x < ImageSurface->w - 1; x++)
		{
			GetRGBValues(ImageSurface, x, y + 1, &R, &G, &B);
			NewValR = R;
			NewValG = G;
			NewValB = B;
			GetRGBValues(ImageSurface, x + 1, y, &R, &G, &B);
			NewValR += R;
			NewValG += G;
			NewValB += B;
			GetRGBValues(ImageSurface, x + 1, y + 1, &R, &G, &B);
			NewValR += R;
			NewValG += G;
			NewValB += B;
			GetRGBValues(ImageSurface, x, y, &R, &G, &B);
			NewValR += R;
			NewValG += G;
			NewValB += B;
			GetRGBValues(ImageSurface, x - 1, y, &R, &G, &B);
			NewValR += R;
			NewValG += G;
			NewValB += B;
			GetRGBValues(ImageSurface, x, y - 1, &R, &G, &B);
			NewValR += R;
			NewValG += G;
			NewValB += B;
			GetRGBValues(ImageSurface, x - 1, y - 1, &R, &G, &B);
			NewValR += R;
			NewValG += G;
			NewValB += B;
			GetRGBValues(ImageSurface, x - 1, y, &R, &G, &B);
			NewValR += R;
			NewValG += G;
			NewValB += B;
			GetRGBValues(ImageSurface, x - 1, y + 1, &R, &G, &B);
			NewValR += R;
			NewValG += G;
			NewValB += B;
			SetRGBValues(ImageSurface, x + 1, y + 1, NewValR / 9, NewValG / 9, NewValB / 9);
		}
	}
}

void SaveImage(SDL_Surface* ImgSurface, SDL_Surface *SecondImage) //Saves the current image
{
	// Saves the Image
	SaveImageBMP(ImgSurface, "Output1.bmp");
	cout << "Saved Original to Output1.bmp" << endl;
	cout << endl;
	SaveImageBMP(SecondImage, "Output2.bmp");
	cout << "Saved Back-up to Output2.bmp" << endl;
}

void DisplayDebugInfo(SDL_Surface* ImgSurface)
{
	cout << ImgSurface->w << "|||" << ImgSurface->h << endl; // displays the height and width of the image
}

void BlackAndWhiteImage(SDL_Surface* ImgSurface, Uint8 R, Uint8 G, Uint8 B)
{
	for (int y = 0; y < ImgSurface->h; y++)
	{
		for (int x = 0; x < ImgSurface->w; x++)
		{
			GetRGBValues(ImgSurface, x, y, &R, &G, &B);
			SetRGBValues(ImgSurface,x,y,(R + G + B) / 3, (R + G + B) / 3, (R + G + B) / 3);
		}
	}
}

int VerifyInput(istream& Stream, int UserInput, int Val1, int Val2)
{
	for (;;) // Loop forever
	{
		if (Stream >> UserInput && UserInput < Val1 && UserInput > Val2) // if the failbit of cin is not set and the value is in range
		{
			return UserInput;
			break; // break loop and continue program execution
		}
		else
		{
			cin.clear(); // clear the input stream
			cin.ignore(); // ignore its contents
			cout << "Invalid Selection:" << endl;
		}
	}
}

int SaveProgress()
{
	int which = 0;
	cout << "Save changes to original or backup? 1-save to back-up:: 0-save to original." << endl;

	if (VerifyInput(cin,which, 2, -1)== 1) //If user wants to save 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

