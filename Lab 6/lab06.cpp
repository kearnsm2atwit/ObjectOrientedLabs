#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>


using namespace std;


struct entry_t {
  string artistName;
  int numWins;
  int year[5];
  entry_t *next;
  entry_t *previous;
};


class winner {
  private:
    
    entry_t entry_struct; 
    entry_t *List;
  
  public:
    
    
 
    
    winner(string fileName, int size) {
      List = 0;
      // Read in the file
      // Get each grammy winners information
      // Call addName(artistName, year) function for every single
      ifstream file(fileName.c_str());
      for(int i = 0; i < size; i++) {
        string artistName;
        int year;
        file >> year;
        file.ignore();
        file.clear();
        getline(file, artistName);
        addName(artistName, year);
      }
    }
    
    
    void addName(string tempName, int y){       
    	entry_t *temp = List;            // Using temp pointer to navigate the list      	
      
      
    	if(List) {
    		entry_t *newEntry = new entry_t;
       
    		if(List->artistName[0] > tempName[0]) {
    			if(List->artistName == tempName) {
           // If this artist has already won at least once
            List->numWins++;
            List->year[List->numWins - 1] = y;
            //cout << "This artist has won already" << endl;
            return; 
          }
          newEntry->next = List;
          List->previous = newEntry;
    			List = newEntry;
          newEntry->previous = 0;
          
    			newEntry->artistName = tempName;
    			newEntry->numWins = 1;
          newEntry->year[0] = y;
    			return;
    		}
    		for( ; temp->next != 0; temp = temp->next) {
          if(temp->artistName == tempName) {
              temp->numWins ++;
              temp->year[temp->numWins -1] = y;
              //cout << "This artist has already won " << temp->artistName << endl;
              return;
          }
          
          
          if (temp->artistName[0] == tempName[0]) {  // If the first letters match. Need to check next letters
            for(int i = 1; i < (min(sizeof(temp->artistName), sizeof(tempName))); i++) {
              if(tempName[i] < temp->artistName[i]) {      // The new entry is higher in order than the current one 
                if(temp->previous == 0) {                  // If the new entry needs to be put in the front
                  List->previous = temp;
                  newEntry->previous = temp->previous;
                  newEntry->next = temp;
                  List = newEntry;
                  newEntry->artistName = tempName;
                  newEntry->year[0] = y;
                  newEntry->numWins = 1;
                  return;
                }
                else {
                  newEntry->next = temp;
                  newEntry->previous = temp->previous;
                  newEntry->previous->next = newEntry;
                  temp->previous = newEntry;
                  
                  newEntry->artistName = tempName;
                  newEntry->year[0] = y;
                  newEntry->numWins = 1;
                  return;
                }
    
              }
              else {
                newEntry->next = temp->next;
                newEntry->previous = temp;
                temp->next->previous = newEntry;
                temp->next = newEntry;
                
                newEntry->artistName = tempName;
                newEntry->numWins = 1;
                newEntry->year[0] = y;
                return;
              }
            }
          }
          // Need to sort alphabetically
          // Need to also account for artists that start with the same name
          
          
          if(tempName[0] > temp->artistName[0]  && tempName[0] < temp->next->artistName[0]) {
            // Belongs in between wherever temp is and the next entry
            newEntry->next = temp->next;  // Make new entry point to the next entry (it is taking its spot)
            newEntry->previous = temp;
            temp->next->previous = newEntry;        // Make the current entry point to our new entry
            temp->next = newEntry;
            
            newEntry->artistName = tempName;
            newEntry->numWins = 1;
            newEntry->year[0] = y;
            
            // Now, the new entry is pointing to the entry that got its spot taken and the current entry is pointing to the new entry
            return;
            
            
    			}
       }
        // Only time the function gets this far is if the new entry belongs at the back
        
        newEntry->next = 0;    // Ground the new entry
            
        // The last place our temp pointer would be pointing is to the current last spot
        // So when temp->next == 0
        // Make the new temp->next equal to our new entry
        
        temp->next = newEntry;
        newEntry->previous = temp;
        
        newEntry->artistName = tempName;
        newEntry->numWins = 1;
        newEntry->year[0] = y;
      }
    	else { //Starting from an empty list, so this is the first one.
    		List = new entry_t;
    		List->artistName = tempName;
    		List->numWins = 1;
        List->year[0] = y;
    		List->next = 0;
    	}
    }
    
    void removeName(){
    
    	if(List){ // if there is a list at all
    	  entry_t *temp = List;
    	  string tempName;
    		cout << "Enter the artist name: ";
    		cin.ignore();
        cin.clear();
        getline(cin, tempName);
        	
          // Need to handle the case of only one entry in list but user inputs wrong name
          if(List->next == 0 && List->artistName != tempName) {
            cout << "Name not found. Try again." << endl;
            return;
          }
          
          
        	if(List->artistName == tempName){  //First one needs to be deleted
             if(List->next == 0) {
               delete List;
               List = 0;
               cout << "List is now empty" << endl;
               return;
            }
            temp = List;
        		List = List->next;
            List->previous = 0;
        		delete temp;
        		return;
        	}
        	for(temp = List; temp->next->next != 0; temp = temp->next){
        			// FILL IN HERE
    			    if(temp->next->artistName == tempName) {        // Deleting from somewhere in the middle of the list
                temp->next = temp->next->next;
                delete temp->next->previous;
                temp->next->previous = temp;
        			  cout << "Taking: " << tempName << " off of the list. \n";
        			  return;
        		  }
        	}
         // Now, delete the last entry
         // temp->next is equal to 0 now
          //cout << "Made it to the last entry" << endl;
          if (temp->next->artistName == tempName) {
            delete temp->next; 
            temp->next = 0;
            return;
          }
          cout << "Name not found. Try again." << endl;
    	}
        else
            cout << "Empty list.  Nothing to remove." << endl;
    }

    void searchName(){
    	//  Need to let user search by name, year, or number of wins
      // Use if statements to avoid creating a new function to fix the "cin" and switch case issue
      cout << "1 to search by name" << endl << "2 to search by year" << endl << "3 to search by number of Grammys" << endl;
    	int choice = 0;
      cin >> choice;
      
      if(choice == 1) {
        string tempName;
        cout << "Enter name: ";
        cin.ignore();
        cin.clear();
        getline(cin, tempName);
      	if(List) {
          	for(entry_t *temp = List; temp != 0; temp = temp->next){
          		if(temp->artistName == tempName){
          			cout << "Name: " << temp->artistName << endl << "Number of Grammys: " << temp->numWins << endl << "Years: ";
                for(int i = 0; i < temp->numWins; i++) {
                  cout << temp->year[i] << " ";
                }
                cout << endl;
          			return;
          		}	
          	}
          	cout << "Not found\n";
          	return;
          }
          else
              cout << "Empty list.  Nothing to print." << endl;
      }
      else if(choice == 2) {
        int temp_year;
        cout << "Enter year: ";
        cin >> temp_year;
          	if(List) {
          	for(entry_t *temp = List; temp != 0; temp = temp->next){
         		  for(int i = 0; i < temp->numWins; i++) {
                if(temp->year[i] == temp_year){
            			cout << "Name: " << temp->artistName << endl << "Number of wins: " << temp->numWins << endl << "Years: ";
                  for(int i = 0; i < temp->numWins; i++) {
                    cout << temp->year[i] << " ";
                  }
                  cout << endl;
            			return;
            		}
              }	
          	}
          	cout << "Not found\n";
          	return;
          }
          else
              cout << "Empty list.  Nothing to print." << endl;
      }
      
      else if(choice == 3) {
        int temp_wins;
        int if_found = 0;
        cout << "Enter number of Wins: ";
        cin >> temp_wins;
          	if(List) {
          	for(entry_t *temp = List; temp != 0; temp = temp->next){
              if(temp->numWins == temp_wins){
              if_found = 1;
          			cout << "Name: " << temp->artistName << endl << "Number of Grammys: " << temp->numWins << endl << "Years: ";
                for(int i = 0; i < temp->numWins; i++) {
                  cout << temp->year[i] << " ";
                }
                cout << endl;
          		}	
          	}
          	if(if_found == 0) {
              cout << "Not found" << endl; 
            }
          	return;
          }
          else
              cout << "Empty list.  Nothing to print." << endl;
      }
      else {
        cout << "Not an option. Please try again" << endl;
      }
    }
    
    
    void printNames(){
        if(List) {
        	for(entry_t *temp = List; temp != 0; temp = temp->next){
        		cout << "Name: " << temp->artistName << endl << "Number of Wins: " << temp->numWins << endl << "Years: "; 
            for(int i = 0; i < temp->numWins; i++) {
              cout << temp->year[i] << " ";
            }
            cout << endl;
        	}
        }
        else
            cout << "Empty list.  Nothing to print." << endl;
    }
      
      
    void deleteList(){
    	if(List){
    		entry_t *tempDelete = List;
    		entry_t *tempHolder = tempDelete->next;
    		while(tempDelete != 0){
    			delete tempDelete;
    			tempDelete = tempHolder;
    			if(tempHolder)
    				tempHolder = tempHolder->next;
    		}
    	}
    }
    
    void searchYear(int year) {
 	    if(List) {
        	for(entry_t *temp = List; temp != 0; temp = temp->next){
       		  for(int i = 0; i < temp->numWins; i++) {
              if(temp->year[i] == year){
          			cout << "Name: " << temp->artistName << endl << "Number of wins: " << temp->numWins << endl << "Years: ";
                for(int i = 0; i < temp->numWins; i++) {
                  cout << temp->year[i] << " ";
                }
                cout << endl;
          			return;
          		}
            }	
        	}
        	cout << "Not found\n";
        	return;
        }
        else
            cout << "Empty list.  Nothing to print." << endl;
    
    }
   
      
};







void getInfo(winner w) {                      // Function that gets called if user wants to add an entry
  cout << "Enter name: ";      // Had troubles with "cin" inside of switch case so function was created to handle it outside scope of switch
  string name;
  int year;
  cin.ignore();
  cin.clear();
  getline(cin, name);
  cout << "Enter year: ";
  cin >> year; 
  w.addName(name, year);
}


void choseList(winner w) {
  int choice = 0;
	
  cout << "What function would you like? \n 1 to add new entry \n 2 to remove entry \n 3 to print list \n 4 to search \n 5 to delete and exit \n";

	cin >> choice;


	switch(choice){
		case 1:
      getInfo(w); 
      break;
		case 2: w.removeName(); break;
		case 3: w.printNames(); break;
		case 4: w.searchName(); break;
		case 5: w.deleteList(); return;
		default: cout << "Invalid number.";
	}
  
  return;

}


void searchBoth(winner g, winner em) {
  cout << "Please enter a year to search for: ";
  int y;
  cin >> y;
  g.searchYear(y);
  em.searchYear(y);
  return;
}



int main(){

  winner grammy("lab05.txt", 20);      // Populate the list with entries from text file
  
  winner em("Lab6_EM_List.txt", 13);
  
  
  
	int choice = 0;
	while(choice != 4){
    cout << "Please enter your choice: " << endl << "Press 1 for Grammy List" << endl << "Press 2 for Eckert-Mauchly List" << endl << "Press 3 to search both lists by year" << endl << "Press 4 to exit" << endl;
    cin >> choice;
    
    
    switch (choice){
      case 1:
        choseList(grammy);
        break;
      case 2:
        choseList(em);
        break;
      case 3:
        searchBoth(grammy, em);
        break;
      case 4:
        return 0;
      default:
        cout << "Not an option, please try again";
        break;
    }
    
	}
	return 0;
}
