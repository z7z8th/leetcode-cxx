/* 37. Sudoku Solver
Hard

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

    Each of the digits 1-9 must occur exactly once in each row.
    Each of the digits 1-9 must occur exactly once in each column.
    Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.

Empty cells are indicated by the character '.'.


A sudoku puzzle...


...and its solution numbers marked in red.

Note:

    The given board contain only digits 1-9 and the character '.'.
    You may assume that the given Sudoku puzzle will have a single unique solution.
    The given board size is always 9x9.

Accepted
135,621
Submissions
359,354
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
	//const int MASK_TRY = 1<<30;
	//const int MASK_INVAL = 1<<29;
	
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

	inline bool isValUniq(int val) {
		int bitCnt = 0;
		for (int i=0; i<9; i++) {
			if (val & (1<<i))
				bitCnt++;
		}
		return bitCnt == 1;
	}

	int UpdatePosByFlag(vector<vector<int>>& bb, int i, int j, int pivVal) {
		int& val = bb[i][j];
		if (!(val & MASK_TBD)) {
			return 0;
/* 			if (!(val & MASK_TRY))
				return 0;
			if (val & MASK_0_9 & pivVal) {
				val |= MASK_INVAL;
				bb[i][j] = val;
				return -1;
			} */
		}
		val &= ~pivVal;
		if (val == MASK_TBD)
			cout << "warning: no candidate for [" << i << "][" << j << "]" << endl;
		if (isValUniq(val)) {
			val &= ~MASK_TBD;
			//val |= MASK_TRY;
			updateQueue.emplace_back(i, j);
		}
		bb[i][j] = val;
		return 0;
	}
	
	int updateSmallCubeBy(vector<vector<int>>& bb, int row, int col) {
		int pivVal = bb[row][col];
		if (pivVal & MASK_TBD) {
			cout << "unexpected pivVal masked TBD" << endl;
			return -1;
		}

		int cubeRowBase = (row / 3) * 3;
		int cubeColBase = (col / 3) * 3;
		for (int i=cubeRowBase; i<cubeRowBase+3; i++) {
			for (int j=cubeColBase; j<cubeColBase+3; j++) {
				if (UpdatePosByFlag(bb, i, j, pivVal) < 0)
					return -1;
			}
		}

		return 0;
	}
	/* TODO: optimize duplicated update with small cube */
	int updateRowBy(vector<vector<int>>& bb, int row, int col) {
		int pivVal = bb[row][col];
		if (pivVal & MASK_TBD) {
			cout << "unexpected pivVal masked TBD" << endl;
			return -1;
		}
		for (int j=0; j<9; j++) {
			if (UpdatePosByFlag(bb, row, j, pivVal) < 0)
				return -1;
		}
		
		return 0;
	}
	/* TODO: optimize duplicated update with small cube */
	int updateColBy(vector<vector<int>>& bb, int row, int col) {
		int pivVal = bb[row][col];
		if (pivVal & MASK_TBD) {
			cout << "unexpected pivVal masked TBD" << endl;
			return -1;
		}
		for (int i=0; i<9; i++) {
			if (UpdatePosByFlag(bb, i, col, pivVal) < 0)
				return -1;
		}

		return 0;
	}
	int updateBoardBy(vector<vector<int>>& bb, int row, int col) {
		if (updateSmallCubeBy(bb, row, col) < 0)
			return -1;
		if (updateRowBy(bb, row, col) < 0)
			return -1;
		if (updateColBy(bb, row, col) < 0)
			return -1;
		return 0;
	}
	int procUpdateQueue(vector<vector<int>>& bb) {
		while(!updateQueue.empty()) {
			auto pos = updateQueue.front();
			updateQueue.pop_front();
			if (updateBoardBy(bb, pos.first, pos.second) < 0) {
				updateQueue.clear();
				return -1;
			}
		}
		return 0;
	}
	void updateBoard(vector<vector<int>>& bb) {
		for (int i=0; i<bb.size(); i++) {
			for (int j=0; j<bb[i].size(); j++) {
				if (!(bb[i][j] & MASK_TBD))
					updateQueue.emplace_back(i, j);
			}
		}
		procUpdateQueue(bb);
	}
	int validateSet(map<int, int>& tmp, bool part = false) {
		if (!part && tmp.size() != 9)
			return 0;
		for (int i=0; i<9; i++) {
			auto it = tmp.find(1<<i);
			if (!part && it == tmp.end())
				return 0;
			if (part && it != tmp.end() && it->second > 1) {
				return 0;
			}
		}
		return 1;
	}
	int validateSmallCube(vector<vector<int>>& bb, int rowBase, int colBase, bool part = false) {
		rowBase = (rowBase / 3) * 3;
		colBase = (colBase / 3) * 3;
		map<int, int> tmp;
		for (int i=rowBase; i<rowBase+3; i++) {
			for (int j=colBase; j<colBase+3; j++) {
				int val = bb[i][j];
				if (!(val & MASK_TBD))
					++tmp[val];
			}
		}
		return validateSet(tmp, part);
	}

	int validateRow(vector<vector<int>>& bb, int row, bool part = false) {
		map<int, int> tmp;
		for (int j=0; j<9; j++) {
			int val = bb[row][j];
			if (!(val & MASK_TBD))
				++tmp[val];
		}
		return validateSet(tmp, part);
	}
	int validateCol(vector<vector<int>>& bb, int col, bool part = false) {
		map<int, int> tmp;
		for (int i=0; i<9; i++) {
			int val = bb[i][col];
			if (!(val & MASK_TBD))
				++tmp[val];
		}
		return validateSet(tmp, part);
	}
	int fastValidateSolve(vector<vector<int>>& bb) {
        for (int i=0; i<9; i++) {
			for (int j=0; j<9; j++) {
				if (bb[i][j] & MASK_TBD)
					return 0;
			}
        }
		return 1;
	}

	int validateSolve(vector<vector<int>>& bb) {
		if (!fastValidateSolve(bb)) {
			return 0;
		}

		for (int i=0; i<9; i+=3) {
			for (int j=0; j<9; j+=3) {
				int ret = validateSmallCube(bb, i, j);
				if (!ret) {
					//cout << "validate cube failed " << i << ", " << j << endl;
					return ret;
				}
			}
		}
		for (int i=0; i<9; i++) {
			int ret = validateRow(bb, i);
			if (!ret) {
				//cout << "validate row failed " << i << endl;
				return ret;
			}
		}
		for (int j=0; j<9; j++) {
			int ret = validateCol(bb, j);
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

	int isSolved(vector<vector<int>>& bb) {
		if (bb.size() != 9)
			return 0;
		int solved = 1;
		for (int i=0; i<bb.size(); i++) {
			for (int j=0; j<bb[i].size(); j++) {
				if (bb[i][j] == MASK_TBD)
					return 2;
				if (bb[i][j] & MASK_TBD)
					solved = 0;
			}
		}
		if (solved == 1) {
			int ret = validateSolve(bb);
			cout << "validateSolve ret " << ret << endl;
			//solved = ret;
		}
		
		return solved;
	}
	char bitToChar(int val, int row=-1, int col=-1) {
		if (val & MASK_TBD) {
			//cout << "[" << row << "][" << col << "] " << hex << val << dec << endl;
			return '.';  // not determined
		}
		for (int i=0; i<9; i++) {
			if (val & (1<<i)) {
				if ((val & ~(1<<i)) == 0) {
					return i + '1';
				} else {
					//cout << "[" << row << "][" << col << "] " << hex << val << dec << endl;
					return '_'; // more than one candi
				}
			}
		}
		return 'X'; // no candi
	}
	void transformBitsBoardToChar(vector<vector<int>>& bb, vector<vector<char>>& board) {
        for (int i=0; i<board.size(); i++) {
			for (int j=0; j<board[i].size(); j++) {
				board[i][j] = bitToChar(bb[i][j], i, j);
			}
		}
	}
	void printBitBoard(vector<vector<int>>& bb, string subject = "") {
		if (!doPrintBoard)
			return;
		if (subject.length())
			cout << subject << endl;
		for (int i=0; i<bb.size(); i++) {
			if (i % 3 == 0)
				cout << endl;
			for (int j=0; j<bb[i].size(); j++) {
				char ch = bitToChar(bb[i][j]);
				if (j % 3 == 0)
					cout << "  ";
				cout << ch << " ";
			}
			cout << endl;
		}
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

	void copyBoard(vector<vector<int>>& bdst, vector<vector<int>>& bb) {
		//cout << "copyBoard" << endl;
        bdst.resize(9);
        for (int i=0; i<9; i++) {
			bdst[i].resize(9);
			for (int j=0; j<9; j++) {
				bdst[i][j] = bb[i][j];
			}
        }
	}

	bool tryTbdFrom(vector<vector<int>> bb, int si, int sj) {
		//cout << "try next " << si << ", " << sj << endl;
		vector<vector<int>> bs;  // copy of bb
		int j = sj;
		for (int i=si; i<9; i++) {
			//cout << "try i "<< i << endl;
			for (; j<9; j++) {
				int val = bb[i][j];
				if (!(val & MASK_TBD))
					continue;
				//cout << "try TBD " << i << ", " << j << "" << endl;
				for (int bi=0; bi<9; bi++) {
					if (!(val & (1<<bi)))
						continue;
#if 0
					//cout << "try TBD " << i << ", " << j << " bit " << bi << endl;
					copyBoard(bs, bb);
					int& valRef = bs[i][j];
					int val = valRef;
					valRef = 1 << bi;
					updateQueue.emplace_back(i, j);
					if (procUpdateQueue(bs) < 0) {
						valRef = val;
						continue;
					}
					int ret = isSolved(bs);
					if (ret == 1) {
						//cout << "solved by try" << endl;
						transformBitsBoardToChar(bs, *pbd);
						printBoard(*pbd, "solved by try:");
						return true;
					}
					if (ret == 2) {  // invalid board
						valRef = val;
						continue;
					}
					ret = tryTbdFrom(bs, i, j+1);
					if (ret)
						return ret;
					valRef = val;
#else
					int& valRef = bb[i][j];
					int val = valRef;
					valRef = 1 << bi;
					if (!validatePos(bb, i, j)) {
						valRef = val;
						continue;
					}
					//cout << "validatePos ok "<< i << ", " << j << endl;
					if (lastTbd.first == i && lastTbd.second == j
						 && validateSolve(bb)) {
						printBitBoard(bb, "solved by try not update by rule");
						transformBitsBoardToChar(bb, *pbd);
						return true;
					}
					int ret = tryTbdFrom(bb, i, j+1);
					if (ret)
						return ret;
					valRef = val;
#endif
				}
				return false;
			}
			j = 0;
		}
		//cout << "try next " << si << ", " << sj << " return false" << endl;

		return false;
	}
	pair<int, int> findLastTbd(vector<vector<int>>& bb) {
		for (int i=8; i>=0; i--) {
			for (int j=8; j>=0; j--) {
				if (bb[i][j] & MASK_TBD)
					return {i, j};
			}
		}
		cout << "lastTbd not found" << endl;
		return {-1, -1};
	}

    void solveSudoku(vector<vector<char>>& board) {
		printBoard(board, "original:");
		vector<vector<int>> bb;
        clearBoard(bb);
		transformCharBoardToBits(board, bb);

		updateBoard(bb);
		if (isSolved(bb) == 1) {
			transformBitsBoardToChar(bb, board);
			printBoard(board, "solved:");
			return;
		} else {
			transformBitsBoardToChar(bb, board);
			printBoard(board, "not solved:");
		}

		pbd = &board;
		lastTbd = findLastTbd(bb);
		//cout << "lastTbd " << lastTbd.first << ", " << lastTbd.second << endl;
		bool ret = tryTbdFrom(bb, 0, 0);
    }

private:
    //vector<vector<int>> bb;
	vector<vector<char>> *pbd = nullptr;
	vector<vector<int>> bsolv;
	deque<pair<int, int>> updateQueue;
	bool doPrintBoard = false;
	pair<int, int> lastTbd {-1, -1};
};

int main() {
	using sudokuBoard = vector<vector<char>>;
	sudokuBoard tcs[] = {
/* 		{
			{'5','3','.','.','7','.','.','.','.'},
			{'6','.','.','1','9','5','.','.','.'},
			{'.','9','8','.','.','.','.','6','.'},
			{'8','.','.','.','6','.','.','.','3'},
			{'4','.','.','8','.','3','.','.','1'},
			{'7','.','.','.','2','.','.','.','6'},
			{'.','6','.','.','.','.','2','8','.'},
			{'.','.','.','4','1','9','.','.','5'},
			{'.','.','.','.','8','.','.','7','9'}
		}, */
		{
			{'.','.','9', '7','4','8','.','.','.'},
			{'7','.','.', '.','.','.','.','.','.'},
			{'.','2','.', '1','.','9','.','.','.'},
			{'.','.','7', '.','.','.','2','4','.'},
			{'.','6','4', '.','1','.','5','9','.'},
			{'.','9','8', '.','.','.','3','.','.'},
			{'.','.','.', '8','.','3','.','2','.'},
			{'.','.','.', '.','.','.','.','.','6'},
			{'.','.','.', '2','7','5','9','.','.'}
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
		}, */
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
		}
	};

	for (auto tc : tcs) {
		Solution sln(true);
		sln.solveSudoku(tc);
	}
}