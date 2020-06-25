#include <iostream>
#include <string>
#include <fstream>
#include <list>


using namespace std;



struct entry_t {
  string artistName;
  int year;
};


// Taken from examples on geeksforgeeks.org/list-cpp-stl/
list<entry_t> grammyList;

void addName(string tempName, int y) {

  entry_t newEntry;
  newEntry.artistName = tempName;
  newEntry.year = y;
  
  grammyList.push_back(newEntry);
}

void removeName() {
    string tempName;
    cout << "Enter artist name: ";
    cin.ignore();
    cin.clear();
    getline(cin, tempName);
    
    // Iterator usage comes from lecture example and geeksforgeeks.org/list-cpp-stl/
    for(list<entry_t>::iterator iter = grammyList.begin(); iter != grammyList.end(); ++iter) {
      if(iter->artistName == tempName) {
        grammyList.erase(iter); // erase function comes from cplusplus.com/references/list/list/
        return;
      }
    }

}


void printNames() {
    // Iterator usage comes from lecture example and geeksforgeeks.org/list-cpp-stl/
    for(list<entry_t>::iterator iter = grammyList.begin(); iter != grammyList.end(); iter++) {
      cout << iter->artistName << endl << iter->year << endl;
    }
}


void deleteList() {
  //cplusplus.com/references/list/list
  grammyList.clear();
}


void searchName() {
    string tempName;
    cout << "Enter artist name: ";
    cin.ignore();
    cin.clear();
    getline(cin, tempName);
  
  // Iterator usage comes from lecture example and geeksforgeeks.org/list-cpp-stl/
  for(list<entry_t>::iterator iter = grammyList.begin(); iter != grammyList.end(); iter++) {
    if(iter->artistName == tempName) {
      cout << "Name: " << iter->artistName << endl;
      cout << "Year: " << iter->year << endl;
    }
  }
  


}


void getInfo() {                 
  cout << "Enter artist name: ";
  string name;
  int year;
  cin.ignore();
  cin.clear();
  getline(cin, name);
  cout << "Enter year: ";
  cin >> year;
  addName(name, year); 
}


void populate() {
  ifstream file("lab05.txt");
  for(int i = 0; i < 20; i++) {
    string artistName;
    int year;
    
    file >> year;
    file.ignore();
    file.clear();
    getline(file, artistName);
    
    addName(artistName, year);
  }

}



int main(){

  populate();      // Populate the list with entries from text file

	int choice = 0;
	while(choice != 5){
		cout << "What function would you like? \n 1 to add new artist \n 2 to remove artist \n 3 to print list \n 4 to search \n 5 to delete and exit \n";
	
		cin >> choice;
	
	
		switch(choice){
			case 1:
        getInfo(); 
        break;
			case 2: removeName(); break;
			case 3: printNames(); break;
			case 4: searchName(); break;
			case 5: deleteList(); return 0;
			default: cout << "Invalid number.";
		}
		
	}
	return 0;
}


