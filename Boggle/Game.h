// Grupo 5
// Duarte Rodrigues
// Ricardo Brioso
// Mariana Xavier

#pragma once
#include"Player.h"
#include"Config.h"
#include"Dictionary.h"
#include"Board.h"
#include"Console.h"
#include<vector>
#include<sstream>
#include<windows.h>
using namespace std;

class Game
{
public:
	Game(); // Reads default configuration, board and dictionary.
	void setGame(const string& filenameConfig); // Reads configuration, board and dictionary.
	void readPlayers(); // Reads players' info.
	void readPlayersWords(); // Shows the board and reads the words from consecutive players.
	void roundPoints(ostream& os); // Reads words and calculates points.
	bool checkForVictory(); // Checks if the players have reached the necessary points to win.
	void displayWinner(ostream& os); // Shows the winner.
private: 
	vector<Player> _players;
	Config _config;
	Dictionary _dictionary;
	Board _board;
	Player _winner;
	bool minLetters(const string word); // Checks if the word has minumum letters.
	bool findInBoard(const string word, vector<Position>& wordPath); // Checks if the word can be found on the board.
	void showWordPath(const string& word,vector<Position>& wordPath, ostream& os = cout); // Shows the path of the found word.
	bool findInDictionary(const string word); // Checks if the word can be found on the dictionary.
	bool repeatedWord(const string wordSearch); // Checks if more than one player has chosen that word.
	int charsToPoints(const string word); // Converts valid word into points.
};
