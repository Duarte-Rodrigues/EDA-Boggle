// Grupo 5
// Duarte Rodrigues
// Ricardo Brioso
// Mariana Xavier

#include"Board.h"
using namespace std;

Board::Board(size_t numRows = 4, size_t numCols = 4)
{
	_numRows = numRows;
	_numCols = numCols;

	for (size_t i = 0; i < numRows; i++)
	{
		vector<Cube> row;
		for (size_t j = 0; j < numCols; j++)
		{
			row.push_back(Cube());
		}
		_board.push_back(row);
	}
}

//---------------------------------------------------------------------------------------------------------------
Board::Board(const string& filename)
{
	ifstream f(filename);

	if (f.fail())
		cerr << "Error: \"" << filename << "\" was not found! \n";

	string s1; int n1 = 0, int n2 = 0, char ch;

	if (!(f >> s1 >> n1 >> ch >> n2))
		cerr << "Error: Failed to read board size.";

	_numRows = n1;
	_numCols = n2;

	string header;
	getline(f, header);

	_board.resize(n1);
	for (size_t row = 0; row < n1; row++)
		_board[row].resize(n2);

	int a = 0, b = 0;

	for (size_t i = 0; i < n1 * n2; i++)
	{
		vector<char> faces;
		char face;

		for (size_t j = 0; j < 6; j++) // 6 is the number of faces of a cube.
		{
			f >> face;
			faces.push_back(face);
		}

		_board[a][b] = Cube(faces);

		if (b < n2)
			b++;
		else
		{
			b = 0;
			a++;
		}
	}

}

//---------------------------------------------------------------------------------------------------------------
char Board::getTopLetter(const Position& pos) const
{
	Cube temp = _board[pos.lin][pos.col];
	return temp.getTopLetter();
}

//---------------------------------------------------------------------------------------------------------------
void Board::shuffle()
{
	Board fin=Board(_numRows, _numCols);
	char test,test2;
	for (size_t row = 0; row < _numRows; row++)
	{
		for (size_t col = 0; col < _numCols; col++)
		{
			Cube cube1;
			int randomRow = rand() % _numRows;
			int randomCol = rand() % _numRows;
			Position pos;
			pos.lin = randomRow;
			pos.col = randomCol;
			cube1 = fin.cubeInPosition(pos);
			test = cube1.getTopLetter();
			//se no board fin o cubo na posicao random tiver * entao pode-se meter o cubo novo do _board rolar este
			if (test == '*')
			{
				fin.cubeInPosition(pos) = _board[row][col]; //ser� que substitui? ou � preciso criar uamm fun��o insert?
			}
			else //talvez pudesse ser melhorado se os primeiros termos fossem passados por referencia
			{
				Position pos1;
				do{
					Cube cube2;
					int randomRow1 = rand() % _numRows;
					int randomCol1 = rand() % _numRows;
					
					pos1.lin = randomRow1;
					pos1.col = randomCol1;
					cube2 = fin.cubeInPosition(pos);
					test2 = cube1.getTopLetter();
				} while (test2 != '*');
					fin.cubeInPosition(pos1) = _board[row][col];
			}
		}

	}

	for (size_t row = 0; row < _numRows; row++)
	{
		for (size_t col = 0; col < _numCols; col++)
		{
			Position finpos;
			finpos.lin = row;
			finpos.col = col;
			_board[row][col] = fin.cubeInPosition(finpos);
			_board[row][col].roll();
		}
	}// para que o valor saia em referencia

	// Falta fazer shuffle mas n�o sei em que isso consiste ainda. I think its done
	//Possivelmente, fazer um rand() na posi��o dos cubos.
}

//---------------------------------------------------------------------------------------------------------------
void Board::display(ostream& os) const
{
	os << "  1  2  3  4" << "\n";
	for (size_t row = 0; row < _numRows; row++)
	{
		os << row + 1 << " ";
		for (size_t col = 0; col < _numCols; col++)
		{
			_board[row][col].displayTop(os);
			os << "  ";
		}
		os << "\n" << "\n";
	}
}

//---------------------------------------------------------------------------------------------------------------
bool Board::findWord(const vector<vector<char>>& board, string word, ostream& os)//(string word, vector<Position>& path) -> argumentos usados inicialmente pelo prof
{
	// Mark all characters as not visited 
	vector<vector<bool>> visited(_numRows, vector<bool>(_numCols, false));

	// Initialize test word 
	string str = "";

	//declaration of the path
	vector<Position> path;
	
	// Consider every character and look for 'word', starting with the first character
	//once that is found pass to findWordAux
	int numIter = 0;
	bool found = false;
	for (int i = 0; i < _numRows; i++)
		for (int j = 0; j < _numCols; j++)
			if (board[i][j] == word[0])
			{
				Position firstlett;
				firstlett.lin = i;
				firstlett.col = j;
				path.push_back(firstlett);

				findWordAux(board, visited, i, j, str, word, found, os,path);
			}
				
	return found; //depois ao testar dizer que se saiu true entao ta otimo... se saiu false entao deu asneira
}

//---------------------------------------------------------------------------------------------------------------
bool Board::findWordAux(const vector<vector<char>>& board, vector<vector<bool>>& visited, int i, int j, string& str, const string& word, bool& found, ostream& os, vector<Position>& path)
{
	// Mark current board cell as visited and append current character to 'str'

	visited[i][j] = true; //nesta celula sabemos que temos o primeiro char do inicio da palavra
	str = str + board[i][j]; //str come�a vazio


	// If 'str' is equal to 'word', then "announce" it has been found
	if (str == word)
	{
		found = true;
		for (size_t a=0; a < path.size(); a++)
		{
			os << "(" << path[a].lin << "," << path[a].col << ") \n";
		}

	}
	else
	{
		// Visit 8 adjacent cells of board[i][j] 
		for (int row = i - 1; row <= i + 1 && row < _numRows; row++)
			for (int col = j - 1; col <= j + 1 && col < _numCols; col++) //o if em baixo � genial
				if (row >= 0 && col >= 0 && !visited[row][col] && str.length() < word.length() && !found && word.substr(0, str.length()) == str)
				{
					Position adduplett;
					adduplett.lin = row;
					adduplett.col = col;
					path.push_back(adduplett);
					findWordAux(board, visited, row, col, str, word, found, os,path);
				}
					
					//fazer o vetor de positions path com push_backs (found true) e pull_backs (!found)
		// Erase current character from string, 
		// remove character position from 'path' and
		// mark visited[i][j] as false
		if (!found)
		{
			str.erase(str.length() - 1);
			visited[i][j] = false;
			path.pop_back();
		}
	}
	return found; 
	//se uma das letras falha reposta not found e o findwordaux corre todo outra vez,
	//mas deixando a cellua registada como false, o que nao ativa o if
}

//---------------------------------------------------------------------------------------------------------------
Cube Board::cubeInPosition(const Position& pos)
{
	return _board[pos.lin][pos.col];
}

//---------------------------------------------------------------------------------------------------------------
void Board::displayPath(ostream& os, vector<Position>& path)
{
	for (size_t a = 0; a < path.size(); a++)
	{
		os << "(" << path[a].lin << "," << path[a].col << ") \n";
	}
}
//NO FINAL, DEPOIS DO DISPLAY, O BOARD � UM vector<vector<char>>, e � nisso que o find word se baseia,i think