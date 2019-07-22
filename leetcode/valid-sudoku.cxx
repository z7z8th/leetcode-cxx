/* 36. Valid Sudoku
Medium

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

    Each row must contain the digits 1-9 without repetition.
    Each column must contain the digits 1-9 without repetition.
    Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.


A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

Example 1:

Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true

Example 2:

Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being 
    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

Note:

    A Sudoku board (partially filled) could be valid but is not necessarily solvable.
    Only the filled cells need to be validated according to the mentioned rules.
    The given board contain only digits 1-9 and the character '.'.
    The given board size is always 9x9.

Accepted
249,675
Submissions
570,065
*/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	Solution(bool doPrintBoard = false) {
		this->doPrintBoard = doPrintBoard;
	}

    const int MASK_0_9 = (1<<9) - 1;
	const int MASK_TBD = 1<<31;
	
    void clearBoard(vector<vector<int>>& bb) {
        bb.resize(9);
        for (int i=0; i<9; i++) {
            bb[i].clear();
            bb[i].resize(9);
        }
    }
    void transformCharBoardToBits(vector<vector<char>>& board, vector<vector<int>>& bb) {
        for (int i=0; i<board.size(); i++) {
			for (int j=0; j<board[i].size(); j++) {
				int val = 0;
				int ch = board[i][j];
				if (ch != '.') {
					val = 1 <<  (ch - '1');
				} else {
					val = MASK_TBD | MASK_0_9;
				}
				bb[i][j] = val;
			}
		}
    }

	int validateSmallCube(vector<vector<int>>& bb, int rowBase, int colBase, bool part = false) {
		rowBase = (rowBase / 3) * 3;
		colBase = (colBase / 3) * 3;
		int mask = 0;
		for (int i=rowBase; i<rowBase+3; i++) {
			for (int j=colBase; j<colBase+3; j++) {
				int val = bb[i][j];
				if (!(val & MASK_TBD)) {
					if (val & mask)
						return 0;
					mask |= val;
				}
			}
		}
		return part || mask == MASK_0_9;
	}

	int validateRow(vector<vector<int>>& bb, int row, bool part = false) {
		int mask = 0;
		for (int j=0; j<9; j++) {
			int val = bb[row][j];
			if (!(val & MASK_TBD)) {
				if (val & mask)
					return 0;
				mask |= val;
			}
		}
		return part || mask == MASK_0_9;
	}
	int validateCol(vector<vector<int>>& bb, int col, bool part = false) {
		int mask = 0;
		for (int i=0; i<9; i++) {
			int val = bb[i][col];
			if (!(val & MASK_TBD)) {
				if (val & mask)
					return 0;
				mask |= val;
			}
		}

		return part || mask == MASK_0_9;
	}

	int validateSolve(vector<vector<int>>& bb, bool part = false) {
		for (int i=0; i<9; i+=3) {
			for (int j=0; j<9; j+=3) {
				int ret = validateSmallCube(bb, i, j, part);
				if (!ret) {
					//cout << "validate cube failed " << i << ", " << j << endl;
					return ret;
				}
			}
		}
		for (int i=0; i<9; i++) {
			int ret = validateRow(bb, i, part);
			if (!ret) {
				//cout << "validate row failed " << i << endl;
				return ret;
			}
		}
		for (int j=0; j<9; j++) {
			int ret = validateCol(bb, j, part);
			if (!ret) {
				//cout << "validate col failed " << j << endl;
				return ret;
			}
		}
		return 1;
	}

	int validatePos(vector<vector<int>>& bb, int i, int j) {
		int ret = validateSmallCube(bb, i, j, true);
		if (!ret) {
			//cout << "validate cube failed " << i << ", " << j << endl;
			return ret;
		}
		ret = validateRow(bb, i, true);
		if (!ret) {
			//cout << "validate row failed " << i << endl;
			return ret;
		}
		ret = validateCol(bb, j, true);
		if (!ret) {
			//cout << "validate col failed " << j << endl;
			return ret;
		}
		return 1;
	}

	void printBoard(vector<vector<char>>& board, string subject = "") {
		if (!doPrintBoard)
			return;
		if (subject.length())
			cout << subject << endl;
		for (int i=0; i<board.size(); i++) {
			if (i % 3 == 0)
				cout << endl;
			for (int j=0; j<board[i].size(); j++) {
				char ch = board[i][j];
				if (j % 3 == 0)
					cout << "  ";
				cout << ch << " ";
			}
			cout << endl;
		}
	}

    bool isValidSudoku(vector<vector<char>>& board) {
		printBoard(board, "original:");
		vector<vector<int>> bb;
        clearBoard(bb);
		transformCharBoardToBits(board, bb);

		return validateSolve(bb, true) == 1;
    }

private:
	bool doPrintBoard = false;
};

int main() {
	using sudokuBoard = vector<vector<char>>;
	sudokuBoard tcs[] = {
		{
			{'5','3','.','.','7','.','.','.','.'},
			{'6','.','.','1','9','5','.','.','.'},
			{'.','9','8','.','.','.','.','6','.'},
			{'8','.','.','.','6','.','.','.','3'},
			{'4','.','.','8','.','3','.','.','1'},
			{'7','.','.','.','2','.','.','.','6'},
			{'.','6','.','.','.','.','2','8','.'},
			{'.','.','.','4','1','9','.','.','5'},
			{'.','.','.','.','8','.','.','7','9'}
		},
		{
			{'8','3','.','.','7','.','.','.','.'},
			{'6','.','.','1','9','5','.','.','.'},
			{'.','9','8','.','.','.','.','6','.'},
			{'8','.','.','.','6','.','.','.','3'},
			{'4','.','.','8','.','3','.','.','1'},
			{'7','.','.','.','2','.','.','.','6'},
			{'.','6','.','.','.','.','2','8','.'},
			{'.','.','.','4','1','9','.','.','5'},
			{'.','.','.','.','8','.','.','7','9'}
		},
		{
			{'.','8','7','6','5','4','3','2','1'},
			{'2','.','.','.','.','.','.','.','.'},
			{'3','.','.','.','.','.','.','.','.'},
			{'4','.','.','.','.','.','.','.','.'},
			{'5','.','.','.','.','.','.','.','.'},
			{'6','.','.','.','.','.','.','.','.'},
			{'7','.','.','.','.','.','.','.','.'},
			{'8','.','.','.','.','.','.','.','.'},
			{'9','.','.','.','.','.','.','.','.'}
		},
		/* {
			{'.','.','.',  '7','4','8',  '.','.','.'},
			{'.','.','.',  '.','.','.',  '.','.','.'},
			{'.','.','.',  '1','.','9',  '.','.','.'},

			{'.','.','7',  '.','.','.',  '2','4','.'},
			{'.','6','4',  '.','1','.',  '5','9','.'},
			{'.','9','8',  '.','.','.',  '3','.','.'},

			{'.','.','.',  '8','.','3',  '.','.','.'},
			{'.','.','.',  '.','.','.',  '.','.','.'},
			{'.','.','.',  '2','7','5',  '.','.','.'}
		},
		{
			{'1','.','.','.','7','.','.','3','.'},
			{'8','3','.','6','.','.','.','.','.'},
			{'.','.','2','9','.','.','6','.','8'},
			{'6','.','.','.','.','4','9','.','7'},
			{'.','9','.','.','.','.','.','5','.'},
			{'3','.','7','5','.','.','.','.','4'},
			{'2','.','3','.','.','9','1','.','.'},
			{'.','.','.','.','.','2','.','4','3'},
			{'.','4','.','.','8','.','.','.','9'}
		} */
	};

	int tcIdx = 0;
	for (auto tc : tcs) {
		Solution sln(true);
		bool ret = sln.isValidSudoku(tc);
		cout << "case " << tcIdx++ << (ret ? "" : " *NOT*") << " valid" << endl;
	}
}