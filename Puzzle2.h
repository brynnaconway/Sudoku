// Brynna Conway, Lab 6, Part 1
#include <iostream> 
#include <vector>
#include <algorithm> 
#include <cstdlib> 
#include <fstream> 
#include <string> 
#ifndef PUZZLE_H
#define PUZZLE_H
using namespace std; 

template <typename T> 
class Puzzle { 

	template <typename T2> 
	friend ostream &operator<<( ostream &, Puzzle<T2> &); // display the Sudoku board 
	
	public:
		Puzzle(string = "sudoku.txt"); 
		void solve(); // solve the Sudoku 
		int check(int a, int b, int number); // check if a given number can be placed in a given cell
		int win(); // check if the board is completed
		void clearCounts(vector< vector< int > > &counts); // re-initialize the counts vector to all zeros
		void clear_possNums(vector< vector< vector< T > > > &possNums); // reinitialize the possNums vector to all zeros 
	private: 
		vector< vector<T> > PuzzleBoard; 

};

template <typename T>
Puzzle<T>::Puzzle(string fileInput) { // constructor 

	int i = 0; 
	vector<T > tmp(9); // temporary vector used to fill up PuzzleBoard vector with vectors 
	string file = fileInput; 
	ifstream File( file.c_str() ); // prepare file for reading in 
	
	if (File.is_open() ) { // check to make sure file was opened  
		while (i < 9) { 
			PuzzleBoard.push_back(tmp); // fill up puzzle board vector with vectors 
			for (int j = 0; j < 9; j++) { 
				File >> PuzzleBoard[i][j]; // stores character in vector 
			}
			i++; 		
		}
	} 
	else 
		cout << "Unable to open file" << endl; 
} 

template <typename T2> 
ostream &operator<<(ostream &output, Puzzle<T2> &P) {

	int count1 = 0, count2 = 0;
	output << endl;
	output << "-----------------------" << endl;
	for (int i = 0; i < P.PuzzleBoard.size(); i++) { // display the board
		count2++;
		for (int j = 0; j < P.PuzzleBoard[i].size(); j++) { 
			output << P.PuzzleBoard[i][j];  
			output << " "; 
			count1++; 
			if (count1 == 3) { 
				output << "| ";
				count1 = 0;
			} 
			
		}
		output << endl; // new row on the board 
		if (count2%3 == 0) { 
				output << "-----------------------" << endl;
		}
	}
	
	return output; 
	
} 	

template <typename T>
int Puzzle<T>::check(int a, int b, int number) { // checks if a given number can be placed in a given cell 

	int j = 0, i = 0, up, down, left, right; 
		while (j < 9) { // check if number is already in row
			if (j != b) { 
				if (PuzzleBoard[a][j] == number) 
					return 1; 
			}
			j++;
		}
		while (i < 9) { // check if number is already in column 
			if (i != a) { 
				if (PuzzleBoard[i][b] == number)  
					return 1;
			}
			i++;
		} 
		if ((b+1)%3 == 0) // calculates number of spaces in the mini-grid to left of chosen cell 
			right = 0; 
		if ((b+1)%3 == 2)
			right = 1;
		if ((b+1)%3 == 1) 
			right = 2; 
		left = 2 - right;  // calculates numbers of spaces to left of chosen cell  
		if ((a+1)%3 == 0) // calculates number of spaces in mini-grid below the chosen cell 
			down = 0; 
		if ((a+1)%3 == 2)
			down = 1;
		if ((a+1)%3 == 1) 
			down = 2; 
		up = 2 - down; // calculates the number of spaces in mini-grid above the chosen cell 
		for ( i=1; i <= up; i++) { // check up 
			for (j = 1; j <= left; j++) { // check up and to the left of chosen cell 
				if (PuzzleBoard[a-i][b-j] == number) {
					j = 10; 
					return 1;
				}
			}  
			for (j = 1; j<= right; j++) { // check up and to right of chosen cell
				if (PuzzleBoard[a-i][b+j] == number) { 
					j = 10; 
					return 1; 
				} 
			}  
		}
		for ( i=1; i <= down; i++) { // check down 
			for (j = 1; j <= left; j++) { // check down and to left 
				if (PuzzleBoard[a+i][b-j] == number) {
					j = 10; 
					return 1;
				}
			} 
			for (j = 1; j<= right; j++) { // check down and to right 
				if (PuzzleBoard[a+i][b+j] == number) { 
					j = 10; 
					return 1; 
				} 
			} 
		}

		return 0; 
}

template <typename T>
int Puzzle<T>::win() { 

	for (int i = 0; i < 9; i++) { // checks if they have won by ensuring that every cell has a non-zero number in it 
		for (int j = 0; j < 9; j++) {
			if (PuzzleBoard[i][j] == 0) {
				return 0; // have not won, because a zero was found on the board 
			}
			else if ( i == 8 && j == 8 && PuzzleBoard[i][j] != 0 ) {
				return 1; 
			}
		}
	}
	return 1; // have won because no zeros on board 
	
}

template <typename T>  
void Puzzle<T>::clearCounts(vector< vector< int > > &counts) { // reinitializes counts vector to all zeros 

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
				counts[i][j] = 0;
		}
	}
			
	return;	
}

template <typename T>  
void Puzzle<T>::clear_possNums(vector< vector< vector< T > > > &possNums) { // reinitializes possNums vector to all zeros

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k <9; k++) {
				possNums[i][j][k] = 0;
			}
		}
	}
	return;	
}
		
	
template <typename T> 
void Puzzle<T>::solve() { 

	vector< vector< vector< T > > > possNums (9, vector< vector< T > >(9, vector <T>(9, 0))); 
	vector< vector< int > > counts(9, vector < int > (3, 0)); 
	int number, right, left, up, down, i =0, j=0, error =0, count=0, single, complete = 0, gridRow, gridCol, numRow, numCol, a, b, c, row, col, num;
	
	while (complete == 0) { // keeps looping until the board is solved 
		for (a = 0; a < 9; a++) { // loops through rows 
			for (b = 0; b < 9; b++) { // loops through cells 
				for (c = 0; c < 9; c++) { // loops through possible numbers to be placed in cell 
					number = c+1; 
					if (PuzzleBoard[a][b] == 0) { // only checks if a number hasn't already been placed 
						error = check(a, b, number); // determines if number can be placed in this cell 
						if (error == 0) { // number can be placed in this cell 
							possNums[a][b][c] = 1; // store that this number can be placed in this cell 
							count++; // counts how many different numbers could be placed in this cell 
							single = number; // stores most recent number that could be placed in this cell 
						}
						else {
							possNums[a][b][c] = 0; // stores that number could not be placed in cell
						}
						error = 0;
						j = 0;
						i = 0;
					}
				}
				if (count == 1) { // only one number could be placed in that cell 
					PuzzleBoard[a][b] = single; // fill in cell with the single number that could be placed there
				} 
				count = 0;
			}	
		}
		for (a = 0; a < 3; a++) { // determines row position of top left of mini-grid
			clear_possNums(possNums); // resets vector 
			for (b = 0; b < 3; b++) { // determines column position of top left of mini-grid 
				gridRow = a*3; // gives actual locaton of cell
				gridCol = b*3; // gives actual number of column of top-left cell of mini-gird 
				clearCounts(counts); // resets 
				for (i = 0; i < 3; i++) { // loops through each row in mini-grid
					for (j = 0; j < 3; j++) { // loops through each column in mini-grid
						row = gridRow+i; // location determined based on where upper left corner of mini-grid is
						col = gridCol+j;
						if (PuzzleBoard[row][col] == 0) { // only checks if number isn't already placed here
							 for (num = 0; num < 9; num++) { // loops through to see which numbers can be placed in cell
							 	if ( check(row, col, num+1) == 0) { // number can be placed in cell 
							 		possNums[row][col][num] = 1; // store that the number can be placed 
							 		counts[num][0]++; // count how many times this number has been able to be placed in mini-grid
							 		counts[num][1] = row; // stores the row of cell where number could most recently be placed
							 		counts[num][2] = col; // stores column 
							 	}
							 	else 
							 		possNums[row][col][num] = 0;
							 }
						}
					}
				}
				for (i = 0; i < 9; i++) { // after each cell in mini-grid has been checked, loops through all possible #s
					if (counts[i][0] == 1) { // specific number could only be placed in one spot in whole mini-grid 
						numRow = counts[i][1]; 
						numCol = counts[i][2];
						PuzzleBoard[numRow][numCol] = i+1; // place number in the cell that could place this number
					}
				}
				clearCounts(counts); // reset 
			}
		}
		complete = win(); // check if board is complete before moving on to next mini-grid 
	}
	 
} // end solve function 
	

#endif
	
