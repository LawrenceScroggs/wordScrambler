/* Lawrence Scroggs  CS162  Word Scrambler game
 * The purpose of this program is to create a game for two 
 * players.  This game will take input from player one being a word
 * the game will then jump 100 lines to clear the screen so player 
 * 2 cant see it.  The program will then scramble the letter by
 * 1:If the first letter is less than last letter swap
 * 2:If the second letter is vowel swap 2nd and 3rd
 * 3:If 4th letter is less than k swap 3rd and 4th
 * 4:If word is even swap 2nd letter with first
 * Program will then display scrambled word to player two. If player 
 * two guesses correctly player two gets 1 point if player 2 gets
 * it wrong player one gets 1 point. Repeat until either player reaches 
 * five points.  Prompt players if they would like to play again?
 *
 */

using namespace std;
#include <iostream>
#include <cstring>
#include <cctype>

//Prototypes
void displayRules(); // displays rules of game
int getWord(char word[]); // gets the word from player one
void makeCopy(char copy[], char word[]); // gets copy of original unscrambled word
void lineJump(); // jumps one hundred lines to clear screen
void scrambleWord(char word[], int wordLen); // scrambles the word for the player
void playerGuess(char guess[]); // takes guess from player two
bool compareWord(char copy[], char guess[], bool found); // compares users guess and increments points
char playAgain(char userInput); // asks if player wants to play again




//Constants
const int SIZE = 21;




int main()
{
	
	int playerOne = 0;
	int playerTwo = 0;
	int wordLen = 0;
	char word[SIZE];
	char guess[SIZE]; 
	char copy[SIZE];
	char userInput = 'Y';	
	bool found = false;


	
	do
	{
		displayRules();

		while(playerOne != 5 && playerTwo != 5)
		{
			
			wordLen = getWord(word);
			makeCopy(copy, word);
			lineJump();
			scrambleWord(word, wordLen);

			cout << "Scrambled Word: " << word << endl;

			playerGuess(guess);

			found = compareWord(copy, guess, found);
				if(found == 1)
				{
					++playerTwo;
					cout << "Player Two is correct!!" << endl;
					cout << "The Score is P1: " << playerOne << " P2: " << playerTwo << endl << endl;
					cout << "Player One's word: " << copy << endl;
					cout << "Your word: " << guess << endl << endl;
				}
				else
				{
					++playerOne;
					cout << "Wrong guess. Player One wins this round" << endl;
					cout << "The Score is P1: " << playerOne << " P2: " << playerTwo << endl << endl;
					cout << "Player One's word: " << copy << endl;
					cout << "Your word: " << guess << endl << endl;
				}
			if(playerOne == 5)
				cout << "PLAYER ONE WINS!!!!!!!" << endl << endl;
			else if(playerTwo == 5)
				cout << "PLAYER TWO WINS!!!!!!!" << endl << endl;
		}

		userInput = playAgain(userInput);
			if(userInput == 'Y')
			{
				playerOne = 0;
				playerTwo = 0;
			}
			else
				cout << "Invalid Input please try again " << endl;

	}while(userInput != 'N');



	return 0;
}
// this will compare p1 with p2 and give points accordingly
bool compareWord(char copy[], char guess[], bool found)
{

	if(strcmp(copy, guess) == 0)
	{
		found = true;
	}
		
	else
	{
		found = false;
	}

	return found;

}
// this will ask if player wants to play again
char playAgain(char userInput)
{
	cout << "Would you like to play Again? ";
	cin >> userInput;
	cin.ignore(100, '\n');

	userInput = toupper(userInput);

	return userInput;

}
// this will get the guess from the user
void playerGuess(char guess[])
{
	int len = 0;

	cout << "Player 2 please make your guess: ";
	cin.get(guess, SIZE);
	cin.ignore(100, '\n');\

	len = strlen(guess);

	for(int i = 0; i < len; ++i)
	{
		guess[i] = toupper(guess[i]);
	}
	cout << endl << endl;

}
// This will scramble the word 
void scrambleWord(char word[], int wordLen)
{
	char hold = '&'; // these hold values for switching array values
	char hold2 = '@';
	int even = 0; // used to determine if word is even

	even = (wordLen % 2);

	if(word[0] < word[wordLen - 1])
	{
		hold = word[0];
		hold2 = word[wordLen - 1];

		word[wordLen - 1] = hold;
		word[0] = hold2;
	}

	if(word[1] == 'A' || word[1] == 'E' || word[1] == 'I' || word[1] == 'O' || word[1] == 'U')
	{
		hold = word[1];
		hold2 = word[2];

		word[2] = hold;
		word[1] = hold2;
	}

	if(word[3] < 'K')
	{
		hold = word[2];
		hold2 = word[3];

		word[3] = hold;
		word[2] = hold2;	
		
	}
	if(even > 0)
	{
		hold = word[1];
		hold2 = word[0];

		word[0] = hold;
		word[1] = hold2;

	}


}
// This will clear the screen with a line jump 
void lineJump()
{
	for(int i = 0; i < 100; ++i)
		cout << endl;

}
// makes copy of word for comparison later
void makeCopy(char copy[], char word[])
{

	strcpy(copy, word);


}

// This will get the word from player one and return the length of the array for later use
int getWord(char word[])
{
	int valid = 0;

	while(valid < 4)
	{
		cout << "Please instruct player 2 to look away \n"
			"Player one please enter your word(Word must be for or more characters): ";

		cin.get(word, SIZE);
		cin.ignore(100, '\n');

		valid = strlen(word);

		for(int i = 0; i < valid; ++i) // capitilizes word for comparison 
		{
			word[i] = toupper(word[i]);
		}
		if(valid < 4)
			cout << "Invalid Input.  Word must be 4 characters or more. " << endl;
	}
	//get word length
	return strlen(word);
}
// This will display the rules of the game
void displayRules()
{
	cout << "Welcome to the word scramble game!!!!" << endl << endl << endl;
	cout << "Rules of the Game:" << endl << "Player one will type in the word " << endl <<
		"while player two looks away" << endl << "The game will then jump 100 lines" << endl << 
		"scramble word will then display" << endl << "Player 2 will then enter guess" << endl <<
		"If player 2 is correct they will get 1 point" << endl << "If player 2 is wrong player "
		"1 gets 1 point" << endl << "First to 5 points win" << endl << endl << endl;

}


