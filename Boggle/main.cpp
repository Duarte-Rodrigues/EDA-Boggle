// Grupo 5
// Duarte Rodrigues
// Ricardo Brioso
// Mariana Xavier

#include"Game.h"
using namespace std;

void set(Game& game)
{
	game.readPlayers();
	game.readConfig("BOGGLE_CONFIG.txt");
	game.readDictionary("WORDS_PT.txt");
	game.readBoard("BOARD_INT.txt");

	// This also works
	/*Config gameConfig = game.getConfig();
	game.readDictionary(gameConfig.getFilenameDictionary());
	game.readBoard(gameConfig.getFilenameBoard());
	gameConfig.displayConfig(cout);*/
}

void loop(Game game)
{
	do {
		game.readPlayersWords();
		game.roundPoints(cout);//esta funcao ja tem os testes todos
	} while (game.checkForVictory() == false);
}

int main()
{
 srand(time(NULL));
 Game game;
 set(game);
 loop(game);
 game.displayWinner(cout);
}