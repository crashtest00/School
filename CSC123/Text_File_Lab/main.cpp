/* This program allows the user to review and edit lists of data (specifically names). These lists exist in the working directory. If a user attempts to
add a name to a list that does not exist, a list will be created with the filename and extension that the user specified.*/

#include <iostream> //Main
#include <fstream> //displayName, addName
#include <string> //Used throughout
#include <iomanip> //Used throughout
#include <windows.h> //showFiles

using namespace std;

void displayName(); //Lists names in a specified file
void addName(); //Adds name to file or create file if it doesn't already exist
void showFiles(const char *extension); //Shows files with a specified extension, uses Windows API
char charCast(string input); //Checks input string for valid char value, then returns the valid char value

int main()
{
    string menuChoiceStr;
    char menuChoiceChar;
    bool exit = false;

    do
    {
        cout << "MAIN MENU\n"
                "Please select from the following menu by entering the number that corresponds to your desired menu option:"  << endl;
        cout <<"\t1. Display the names in a list\n"
               "\t2. Add a name to a list\n"
               "\t3. Show all the lists \n"
               "\t4. Exit" << endl;
        getline(cin, menuChoiceStr);
        menuChoiceChar = charCast(menuChoiceStr);
        switch (menuChoiceChar)
        {
            case '1':
                cout << "\n**LIST ALL NAMES IN FILE**\n";
                displayName();
                break;
            case '2':
                cout << "\n**ADD NEW NAME**\n"
                        "Note: If the file specified does not exist, it will be created.\n";
                addName();
                break;
            case '3':
                cout << "\n**SHOW ALL .txt & .list FILES IN CURRENT DIRECTORY**\n";
                showFiles("*.txt"); //Show all text files
                showFiles("*.list"); //Show all list files
                cout << endl;
                break;
            case '4':
                exit = true;
                break;
            default:
                cout << "That is not a valid menu option. Please select an option from the menu." << endl;
                break;
        }
    } while (exit == false);
    cout << "Exiting program." << endl;
    return 0;
}

void displayName() //Display the names in a list
{
    ifstream inStream;
    string filename;
    string line;
    bool endOfFile;

    cout << "Enter the name of the file you wish to open, including the extension:" << endl;
    getline(cin, (filename));
    inStream.open(filename);
    if (inStream.fail()) //Return to main menu if a file does not exist
    {
        cout << "File does not exist. Check filename AND extension!" << endl << endl;
        return;
    }
    // Display the content of that file, 20 items at a time w/ a pause after 20
    //close the file and return to the main menu
    cout << endl;
    while (!inStream.eof()) //Display the contents of the file
    {
        for(int i=0; i<20; i++) //Show 20 lines at a time
        {
            getline(inStream,line);
            if (!inStream.eof())
                cout << line << endl;
        }
        if (!inStream.eof()) //If there are more than 20 items in the list, press any key to continue
            system("PAUSE");
    }
    cout << "**End of list**" << endl << endl;
    inStream.close();
}

void addName()
// This function allows the user to add names to a specified file (which will be created if it doesn't exist). The user can add multiple names before
// returning to the main menu. File names can include spaces! They cannot include system-restricted symbols like "\"!
{
    string doAgain;
    string filename;
    string newName;
    bool exit = false;
    ofstream outStream;

    cout << "Please enter file name:" << endl;
    getline(cin, filename);
    outStream.open(filename, ios::app);

    if(outStream.fail()) //Prevents the user from creating a file with an invalid name
    {
        cout << "Invalid file name." << endl << endl;
        return;
    }

    do {
        cout << "Please enter name:" << endl;
        getline(cin, newName);
        outStream << newName << endl;
        cout << "\"" << newName << "\"" << " has been added. \n"
                "Enter \"Y\" to enter another name or any other character to return to the main menu." << endl;
        getline(cin, doAgain); //Does the user want to enter another name? fast way to build long lists without notepad
        if(doAgain != "Y" && doAgain != "y")
            exit = true;
    } while(exit == false);
    outStream.close();
}

void showFiles(const char *extension) //Uses Windows API to show all files in current(working) directory
{
    WIN32_FIND_DATA ffd;
    HANDLE handle = FindFirstFile(extension, &ffd);

    while (handle != INVALID_HANDLE_VALUE)
    {
        cout << setw(20) << ffd.cFileName << endl; //Display file name for current file
        if (FindNextFile(handle, &ffd)== FALSE)
            break;
    }
    return;
}

char charCast(string input) //custom charcast with robust error handling
{
    char error = '5'; //arbitrary value that will trigger the default (error) switch case
    char result;
    int menuInt = atoi(input.c_str()); //convert input to integer value

    if(input.length() != 1) //Length > 1 indicates invalid user entry
        return error;
    for(int i = 1; i <= 4; i++) //Checks to make sure user input is valid 1-4 menu selection
        if(menuInt == i)
        {
            result = menuInt + '0';
            return result;
        }
    return error; //Any value outside 1-4 is invalid and triggers the error message
}

