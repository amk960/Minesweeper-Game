//Asma M. Khursheed
//Recitation 3
//This is the minesweeper game
//This program is  a 10x10 board filled with mines
//The miines have a 10% probability of being at a box
//The player gets to pick a box to display
//If the player displas a bomb, they die.
// If the player displays all boxes except for the bombs, they win

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct Tile {
	bool isbomb, isVisible;
	int bombsAround;

};
class Minesweeper {
	vector<vector<Tile>> board;
	int numCol = 10, numRow = 10;
	bool gameOver = false;
	int totalNumBombs = 0;
private:
	void makeVisible(vector<vector<int>>& doCord) {
		vector<vector<int>> doneCord;
		while (doCord.size() != 0) {
			int varRow, varCol;
			int ind = 0;
			for (const vector<int>& elem : doneCord) {
				for (auto todo = doCord.begin();todo != doCord.end();) {
					if (elem == (*todo)) {
						todo = doCord.erase(todo);
					}
					else {
						++todo;
					}
				}
			}
			if (doCord.size() == 0) {
				break;
			}
			vector<int> currInd = doCord.back();
			varRow = currInd[0];
			varCol = currInd[1];
			board[varRow][varCol].isVisible = true;
			if (varCol > 0 && varRow > 0) { //topleft
				if (board[varRow - 1][varCol - 1].bombsAround != 0) {
					board[varRow][varCol].isVisible = true;
				}
				else {
					vector<int> anotherTodo;
					anotherTodo.push_back(varRow - 1);
					anotherTodo.push_back(varCol - 1);
					doCord.push_back(anotherTodo);
				}
			}
			if (varRow > 0) { //top
				if (board[varRow - 1][varCol].bombsAround != 0) {
					board[varRow - 1][varCol].isVisible = true;
				}
				else {
					vector<int> anotherTodo;
					anotherTodo.push_back(varRow - 1);
					anotherTodo.push_back(varCol);
					doCord.push_back(anotherTodo);
				}
			}
			if (varCol < numCol - 1 && varRow >0) { //topright
				if (board[varRow - 1][varCol + 1].bombsAround != 0) {
					board[varRow - 1][varCol + 1].isVisible = true;
				}
				else {
					vector<int> anotherTodo;
					anotherTodo.push_back(varRow - 1);
					anotherTodo.push_back(varCol + 1);
					doCord.push_back(anotherTodo);
				}
			}
			if (varCol > 0) {//left
				if (board[varRow][varCol - 1].bombsAround != 0) {
					board[varRow][varCol - 1].isVisible = true;
				}
				else {
					vector<int> anotherTodo;
					anotherTodo.push_back(varRow);
					anotherTodo.push_back(varCol - 1);
					doCord.push_back(anotherTodo);
				}
			}
			if (varCol < numCol - 1) {//right
				if (board[varRow][varCol + 1].bombsAround != 0) {
					board[varRow][varCol + 1].isVisible = true;
				}
				else {
					vector<int> anotherTodo;
					anotherTodo.push_back(varRow);
					anotherTodo.push_back(varCol + 1);
					doCord.push_back(anotherTodo);;
				}
			}
			if (varCol > 0 && varRow < numRow - 1) { //bottomleft
				if (board[varRow + 1][varCol - 1].bombsAround != 0) {
					board[varRow + 1][varCol - 1].isVisible = true;
				}
				else {
					vector<int> anotherTodo;
					anotherTodo.push_back(varRow + 1);
					anotherTodo.push_back(varCol - 1);
					doCord.push_back(anotherTodo);;
				}
			}
			if (varRow < numRow - 1) { //bottom
				if (board[varRow + 1][varCol].bombsAround != 0) {
					board[varRow + 1][varCol].isVisible = true;
				}
				else {
					vector<int> anotherTodo;
					anotherTodo.push_back(varRow + 1);
					anotherTodo.push_back(varCol);
					doCord.push_back(anotherTodo);
				}
			}
			if (varRow < numRow - 1 && varCol < numCol - 1) { //bottomright
				if (board[varRow + 1][varCol + 1].bombsAround != 0) {
					board[varRow + 1][varCol + 1].isVisible = true;
				}
				else {
					vector<int> anotherTodo;
					anotherTodo.push_back(varRow + 1);
					anotherTodo.push_back(varCol + 1);
					doCord.push_back(anotherTodo);
				}
			}
			vector<int> lookedIt;
			lookedIt.push_back(varRow);
			lookedIt.push_back(varCol);
			doneCord.push_back(lookedIt);
		}
	}
	bool allbombsInvis() {
		int numInvTiles = 0;
		for (const vector<Tile>& currRow : board) {
			for (const Tile currTile : currRow) {
				if (!currTile.isVisible) {
					numInvTiles += 1;
				}
			}
		}
		if (numInvTiles == totalNumBombs) {
			return true;
		}
		else {
			return false;
		}
	}
public:
	Minesweeper() {
		srand(time(NULL));
		for (int j = 0; j < numCol; j++) {
			vector<Tile> currRow;
			for (int i = 0; i < numRow; i++) {
				int n = rand() % 100;
				if (n < 10) {
					Tile newTile;
					newTile.isbomb = true;
					newTile.isVisible = false;
					newTile.bombsAround = 0;
					currRow.push_back(newTile);
					totalNumBombs += 1;
				}
				else {
					Tile newTile;
					newTile.isbomb = false;
					newTile.isVisible = false;
					newTile.bombsAround = 0;
					currRow.push_back(newTile);
				}
			}
			board.push_back(currRow);
		}

		for (int i = 0; i <= numRow - 1; ++i) {
			for (int j = 0; j <= numCol - 1; ++j) {
				int adjBomb = 0;
				if (j > 0 && i > 0) { //topleft
					if (board[i - 1][j - 1].isbomb == true) {
						adjBomb += 1;
					}
				}
				if (i > 0) { //top
					if (board[i - 1][j].isbomb == true) {
						adjBomb += 1;
					}
				}
				if (j < numCol - 1 && i >0) { //topright
					if (board[i - 1][j + 1].isbomb == true) {
						adjBomb += 1;
					}
				}
				if (j > 0) {//left
					if (board[i][j - 1].isbomb == true) {
						adjBomb += 1;
					}
				}
				if (j < numCol - 1) {//right
					if (board[i][j + 1].isbomb == true) {
						adjBomb += 1;
					}
				}
				if (j > 0 && i < numRow - 1) { //bottomleft
					if (board[i + 1][j - 1].isbomb == true) {
						adjBomb += 1;
					}
				}
				if (i < numRow - 1) { //bottom
					if (board[i + 1][j].isbomb == true) {
						adjBomb += 1;
					}
				}
				if (i < numRow - 1 && j < numCol - 1) { //bottomright
					if (board[i + 1][j + 1].isbomb == true) {
						adjBomb += 1;
					}
				}
				board[i][j].bombsAround = adjBomb;
			}
		}
	}
	void display(const bool& bombShow) {
		if (bombShow == true) {
			gameOver = true;
			for (const vector<Tile>& row : board) {
				for (const Tile& elem : row) {
					if (elem.isbomb) {
						cout << "x";
					}
					else {
						cout << elem.bombsAround;
					}
				}
				cout << endl;
			}
		}
		else {
			for (const vector<Tile>& row : board) {
				for (const Tile& elem : row) {
					if (elem.isVisible) {
						cout << elem.bombsAround;
					}
					else {
						cout << "-";
					}
				}
				cout << endl;
			}
		}
	}
	bool done() {
		return allbombsInvis() || gameOver;
	}
	bool validRow(const size_t& r) {
		if ((r < board.size()) && (r >= 0)) {
			return true;
		}
		return false;
	}
	bool validCol(const size_t& c) {
		if ((c < board[1].size()) && (c >= 0)) {
			return true;
		}
		return false;
	}
	bool isVisible(const int& r, const int& c) {
		return (board[r][c].isVisible);
	}
	bool play(const int& r, const int& c) {
		if (board[r][c].isbomb) {
			return false;
		}
		else if (board[r][c].bombsAround == 0) {
			vector<vector<int>> doCord;
			vector<int> enteredVec;
			enteredVec.push_back(r);
			enteredVec.push_back(c);
			doCord.push_back(enteredVec);
			board[r][c].isVisible = true;
			makeVisible(doCord);
			return true;
		}
		else {
			board[r][c].isVisible = true;
			return true;
		}
	}
};

int main() {
	Minesweeper sweeper;
	//Continue until only invisible cells are bombs
	while (!sweeper.done()) {
		sweeper.display(false); // display board without bombs
		int row_sel = -1, col_sel = -1;
		while (row_sel == -1) {
			//Get a valid move
			int r, c;
			cout << "row? ";
			cin >> r;
			r -= 1;
			if (!sweeper.validRow(r)) {
				cout << "Row out of bounds" << endl;
				continue;
			}
			cout << "col? ";
			cin >> c;
			c -= 1;
			if (!sweeper.validCol(c)) {
				cout << "Column out of bounds" << endl;
				continue;
			}
			if (sweeper.isVisible(r, c)) {
				cout << "Square already visible" << endl;
				continue;
			}
			row_sel = r;
			col_sel = c;
		}
		// Set selected square to be visible. May effect other cells.
		if (!sweeper.play(row_sel, col_sel)) {
			cout << "Sorry you died..." << endl;
			sweeper.display(true); //final board with bombs shown.
			string otpt;
			cin >> otpt;
			exit(0);
		}
	}
	// Ah! All invisible cells are bombs, so you won!
	cout << "You won!!" << endl;
	sweeper.display(true); //final board with bombs shown
	string seeOutput;
	cin >> seeOutput;

}