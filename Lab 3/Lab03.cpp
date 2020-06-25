#include <iostream>
#include <fstream>
#include <string> 	

//#define SIZE 10
#define SIZE 12

using namespace std;

// Function prototypes. Passes the grid, word, row, and column. Returns integer.
int searchUp(char (&grid)[SIZE][SIZE], string, int, int);
int searchDown(char (&grid)[SIZE][SIZE], string, int, int);
int searchLeft(char (&grid)[SIZE][SIZE], string, int, int);
int searchRight(char (&grid)[SIZE][SIZE], string, int, int);
int search(char (&grid)[SIZE][SIZE], string);


// Main function definition
int main(){
	// Create grid based on defined size
  char grid[SIZE][SIZE];
	
////////////////// Populate grids

	//ifstream file("Lab3_WordSearch1.txt");
	//ifstream file("Lab3_WordSearch2.txt");
  ifstream file("Lab3_WordSearch3.txt");
	if(!file.is_open())
		cout << "File error. Check name/location.\n";
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			file >> grid[i][j];
		}
	}

////////////////// populated, now search/UI

	int user = 0;
	string searchWord;
	
  // Print menu to user and continue to loop until user decides to exit
  do{
		cout << "Press 1 to search."<<endl<<"Press 0 to exit."<<endl;
		cin >> user;
		if(user==0)
			break;
		cout << "What word? ";
		cin >> searchWord;

    // Call search function. All printing is done inside of function
    search(grid, searchWord);
    
    
	}while(user!=0);
 
	return 0;
}

int search(char (&grid)[SIZE][SIZE], string searchWord){
	
  // Set up variables to track where a word is found for each direction
  int found_up = 0;
  int found_down = 0;
  int found_right = 0;
  int found_left = 0;
  
  // Loop through each entry in the gird
  for(int row = 0; row < SIZE; row++){
		for(int col = 0; col < SIZE; col++){
			
      // If a character in the grid matches the first letter of the word being searched for
      if(searchWord[0] == grid[row][col]){
         
         // Search up and continue searching up until either the word is found or the mismatch is found
         if((searchUp(grid, searchWord, row, col)) && ((row - 1 - searchWord.length()) >= 0)) {
           for(int i = 0; i < searchWord.length(); i++) {
             //cout << "Searching up again"<<endl;
             if (grid[row-i][col] == searchWord[i]) {
               found_up = 1;
             }
             else {
               found_up = 0;
               break;
             }
           }
           
           // If the entire word was found, print out where it was found and what direction it was going
           if (found_up) {
             cout << "Word found at "<<row<<","<<col<<" going up"<<endl;
           }
         }
         
         
         
         //////// The same process is repeated for searching down, right, and left
         
         // Search down
         if ((searchDown(grid, searchWord, row, col)) && ((row + searchWord.length()) <= SIZE)) {
           for(int i = 0; i < searchWord.length(); i++) {
             //cout << "Searching down again"<<endl;
             if (grid[row+i][col] == searchWord[i]) {
               found_down = 1;
             }
             else {
               found_down = 0;
               break;
             }
           }
           if(found_down) {
             cout << "Word found at "<<row<<","<<col<<" going down"<<endl;
           }
         }
         
         // Search right
         if (searchRight(grid, searchWord, row, col) && (col + searchWord.length()) < SIZE) {
           for(int i = 0; i < searchWord.length(); i++) {
             //cout << "Searching right again"<<endl;
             if(grid[row][col+i] == searchWord[i]) {
               found_right = 1;
             }
             else {
               found_right = 0;
               break;
             }
           }
           if (found_right) {
             cout<<"Word found at "<<row<<","<<col<<" going right"<<endl;
           }
         }
         
         // Search left
         if (searchLeft(grid, searchWord, row, col) && (col - searchWord.length()) < SIZE) {
           for(int i = 0; i < searchWord.length(); i++) {
             //cout << "Searching right again"<<endl;
             if(grid[row][col-i] == searchWord[i]) {
               found_left = 1;
             }
             else {
               found_left = 0;
             }
           }
           if (found_left) {
             cout<<"Word found at "<<row<<","<<col<<" going left"<<endl;
           }
         }
      } 
		}
	}
  
  // If no words were found in the grid. So all found variables are still at 0
  if (found_up == 0 && found_down == 0 && found_right == 0 && found_left == 0) {
    cout << "Not found!"<<endl;
  }
  
  return 0;
}


// Directional searches being defined

// Returns either a 0 or 1 so they can be used inside as conditionals of if-statements 
int searchUp(char (&grid)[SIZE][SIZE], string searchWord, int row, int col){
  //cout << "Searching up"<<endl;
  if(searchWord[1] == grid[row-1][col]) {
    return 1;
  }
  else {
	  return 0;
 }
}

int searchDown(char (&grid)[SIZE][SIZE], string searchWord, int row, int col){
  //cout << "Searching down"<<endl;
  if(searchWord[1] == grid[row+1][col]) {
    return 1;
  }
  else {
	  return 0;
  }
}

int searchRight(char (&grid)[SIZE][SIZE], string searchWord, int row, int col){
  //cout<<"Searching right"<<endl;
  if (searchWord[1] == grid[row][col+1]) {
    return 1;
  }
  else {
	  return 0;
  }
}

int searchLeft(char (&grid)[SIZE][SIZE], string searchWord, int row, int col){
  //cout<<"Searching left"<<endl;
  if (searchWord[1] == grid[row][col-1]) {
    return 1;
  }
  else {
	  return 0;
  }
}