#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//Creation of function to print a menu to user
void printMenu() {
	cout<< endl << "------------- \n";
	cout<< "Enter 0 to exit \n";
  cout<< "Enter 1 to search by number \n";
  cout<< "Enter 2 to search by activity \n";
}

//Main function
int main() {
  //Opening the text file
  ifstream inFile("Lab1_Schedule.txt");
  
  //Initialization of variables
  int choice = 0;
  int hour[24] = {0};
  string activity[24] = {"empty"};
  
  //For loop to go through text file and save information to two arrays for hour and activity
  for(int i=0;i<24;i++){
    inFile>>hour[i]>>activity[i];
    //cout<<hour[i]<<" "<<activity[i]<<endl;
  }	

  // Do while function to print menu first and then loop
  do{
    //Prompt user and store choice
    printMenu();
    cin>>choice;
    
    //Initialize variables to store user input
    int number;
    string chosen_activity;
    int i;
    bool found;
    
    //Go through algorithm to search for number
    if(choice == 1) {
      //Prompt user to enter number to search for
      cout<<"Enter an hour \n";
      cin>>number;
      //Go through number array and search for the user's selection
      for(i=0;i<24;i++){
        if((hour[i] == number)&&(number <=24)){
          cout<<activity[i]<<endl;
          //once the number is found set found to true and break
          found = true;
          break;
        }
      }
      //If the number was not found
      if(!found){
        cout<<"Activity not found."<<endl;
      }
    }
    //Same thing as the number search but looking for activity instead
    else if(choice == 2) {
      cout<<"Enter an activity \n";
      cin>>chosen_activity;
      for(i=0;i<24;i++){
        if(activity[i] == chosen_activity){
          cout<<hour[i]<<endl;
          found = true;
          break;
        }
      }
      //If the activity couldn't be found
      if(!found){
        cout<<"Could not find time."<<endl;
      }
    }
    //If the user's choice was 0 then exit the program
    else if(choice == 0) {
      break;
    }
    //If the user didn't choose a real option
    else{
      cout<<"Not an option. Choose again.";
    }
  }while(choice != 0);
}
