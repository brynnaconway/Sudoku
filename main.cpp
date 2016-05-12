// Brynna Conway, Lab 5, Part 1 
#include <iostream> 
#include <string> 
#include <vector>       
#include <cstdlib>   
#include <fstream>      
#include "Puzzle2.h"        
using namespace std;                 
  
int main() {                         
       
    Puzzle<int> Sudoku("medium.txt");        
    cout << endl << "Unsolved board: " << Sudoku << endl;         
	Sudoku.solve(); // play Sudoku game     
	cout << "Solved board: " << Sudoku << endl;                          
	                
	return 0;     
}            
