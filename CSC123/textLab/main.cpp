//This program is a 3 menu program that is used to read names in from a file, add a name to a file, and display a list of all the
//files the program has access to.

#include <iostream>
#include <stdio.h>
#include <shlwapi.h>

using namespace std;

void pressEnterToContinue

int main()
{
//Display Menu options
//open do While loop until the option selected is 3 -> exit
//If option 1: Call The displayContents function
//Option 2: Add name to list
    return 0;
}

void displayContents
{
    //Request file name
    //check if file name is valid and return error if invalid. Return to main menu
    //Display the first 20 items (careful with your while loop!)
    //The pressEnterToContinue function should be called inside the loop
    //return to main function
}

void addName
{
    //This is an append function
    //Use getline
    //Print success to screen, then return to main menu (return 0)
}

void showAllLists
{

    //No idea how to do this. Need a function that displays the contents of the parent directory with file extensions .txt or .list. Probably need a *
}

void pressEnterToContinue
{
    cout << "Press Enter To Continue..." << endl;
    cin.get()
}
