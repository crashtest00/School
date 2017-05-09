//                     ******INVENTORY MANAGEMENT PROGRAM******       Ver 2.0.8 Last Update: 5/7/17
/* This program provides a means to opening, editing, and reviewing a .csv inventory file.
The .csv file type was selected for its nearly universal compatibility, allowing the inventory
files to be opened and edited in most spreadsheet programs such as Google Sheets and MS Excel. */

#include <iostream>
#include <vector>
#include <string>
#include <fstream> //Needed for file import/export
#include <cstring> //strncmp used in sort function
#include <iomanip> //Is this still required?
#include <stdlib.h> //Needed for casting variable types
#include <sstream> //Used in fileLoad to parse item data

using namespace std;

struct item{ //struct for items
 string sku;
 string description;
 double price;
 int qtyOnHand;
};

struct searchResult{ //holds found and location values for binarySearch;
    bool found;
    int location;
};

//MENU FUNCTIONS
void fileOpen(vector<item>&); //Case 1: Opens an existing file
void itemSearch(vector<item>&); //Case 2: Searches for an item in the inventory vector
void addItem(vector<item>&); //Case 3: Adds item to inventory vector
void showInventory(vector<item>&); //Case 4: Shows all items in inventory vector
void inventoryValue(vector<item>&); //Case 5: Shows current inventory value
void saveFile(vector<item>&); //Case 6: Saves file to disk
int totalInvOnHand(vector<item>&); //Used on main menu screen to show total number of items on hand

//HELPER FUNCTIONS
void fileLoad(vector<item>&, ifstream&); //Loads file into memory and returns name of working file
void sortInventory(vector<item>&); //Bubble sort is used to catch and handle duplicate sku's
void itemSwap(vector<item>&, int, int); //Swap function for sorting
searchResult binarySearch(vector<item>&, string);//Binary search
void placeItem(vector<item>&, item); //Figures out where to place the new item so vector doesn't have to be sorted when new item is added
void rowFormat(item); //Format item output into legible columns
char charCast(string, int);//Checks input string for valid char value, then returns the valid char value. For use with switch menus that have max of 10 options
bool binaryYN(); //Evaluates y/n string and returns true or false
bool fileExists(string); //Checks to see if a file exists

int main()
{
    string menuChoiceStr;
    char menuChoiceChar;
    bool exit = false;
    vector<item> inventory;

    do {
        cout << "                  *** Main Menu ***" << endl;
        cout << "Please select from one of the following options:\n"
                "\t1) Open an inventory file\n"
                "\t2) Search for an item\n"
                "\t3) Add an item to inventory in memory\n"
                "\t4) Show Inventory\n"
                "\t5) Show current inventory value\n"
                "\t6) Save inventory file\n"
                "\t7) Exit Program\n\n";

        //Display stats for current file
            cout << "Total quantity of all items in inventory: " <<totalInvOnHand(inventory) << endl;

        //Main Menu
        cin.clear(); //Bug fix: input buffer would sometimes retain non-char remnants triggering default switch case. Found bug in xcode, couldn't replicate in C:B
        cout << "Enter Your Selection: ";
        getline(cin, menuChoiceStr);
        menuChoiceChar = charCast(menuChoiceStr, 7); //Validates menu choice and casts to char to use in switch. 7 indicates the number of menu options
        switch (menuChoiceChar){
            case '1': //Open inventory file
                fileOpen(inventory);
                break;
            case '2': //Search for item in inventory
                if(inventory.size() == 0){
                    cout << "No items in inventory!" << endl;
                    break;
                }
                else
                    itemSearch(inventory);
                break;
            case '3': //Add item to inventory
                addItem(inventory);
                break;
            case '4': //Show current inventory
                if(inventory.size() == 0){
                    cout << "No items in inventory!" << endl;
                    break;
                }
                else
                    showInventory(inventory);
                break;
            case '5': //Calculate the total value on hand (Sum of qty*price)
                if(inventory.size() == 0){
                   cout << "No items in inventory!" << endl;
                   break;}
                else
                    inventoryValue(inventory);
                break;
            case '6': //Save memory to db file (This should also clear the memory)
                if(inventory.size() == 0){
                    cout << "No items in inventory!\n" << endl;
                    break;
                }
                else
                    saveFile(inventory);
                break;
            case '7': //Exit program
                cout << "Exiting Program\n";
                exit = true;
                break;
            default:
                cout << "Invalid selection. Please try again.\n" << endl;
        } //End Switch menu
    }while(exit == false);
}

// Menu Functions
void fileOpen(vector<item>& invVector){ // Case 1: Loads a selected file into memory for edit/review
    string fileNameStr, realFileName;
    ifstream inStream;
    ofstream outStream;

    cout << "\n*** Menu: Open File ***\n";
    cout << "Please enter the name of the file without extension: ";
    getline(cin, fileNameStr);
    realFileName = fileNameStr + ".csv";
    inStream.open(realFileName);
    if(inStream.fail()){
        cout << "File not found.\n";
        return ;
    }
    invVector.clear(); //Prepares the inventory vector to receive file data
    fileLoad(invVector, inStream); //Passes invVector to load data from file
    sortInventory(invVector); //Sorts inventory vector
    inStream.close();
    cout << realFileName << " has been opened and sorted successfully!\n" << endl;
    return;
}

void itemSearch(vector<item> &itemList){ //Case 2: Searches for an item in the inventory vector
    string sku;
    searchResult isFound;

    cout << "\n            *** Menu: Item Search ***\n";
    cout << "Enter the item number to search for: ";
    getline(cin, sku);
    isFound = binarySearch(itemList, sku);
    if(isFound.found == true){
        cout << "Item found!\n";
        cout << setw(12) << "Item Number" << setw(20) << "Description" << setw(10)
          << "Price" << setw(5) << "Qty" << endl;
        //cout << itemList[isFound.location].sku << itemList[isFound.location].description; //debug
        rowFormat(itemList[isFound.location]);
        cout << endl;
    }
    else
        cout << "Item not found!\n\n";
    return;
}

void addItem(vector<item> &itemList){ //Case 3: Add an item to inventory

    item newItem;
    string inputBuffer, overwrite;
    searchResult foundItem;

    cout << "            *** Menu: Add Item ***" << endl;
    cout << "Enter item number: ";
    getline(cin, newItem.sku);
    foundItem = binarySearch(itemList, newItem.sku); //Check if item already in inventory
    if (foundItem.found == true){ //This if() can be removed if duplicate SKU's are allowed BUT itemSearch results would be ambiguous!
        cout << "Item already exists in inventory! \n";
        //cout << itemList[foundItem.location].description; //debug
        rowFormat(itemList[foundItem.location]);
        cout << "\nExisting item data will be overwritten. Do you wish to continue?\n";
        if (binaryYN() == false)
            return;
    }
    cout << "Enter item description: ";
    getline(cin, newItem.description);
    cout << "Enter item price: $";
    getline(cin, inputBuffer);
    newItem.price = atof(inputBuffer.c_str());
    cout << "Enter number of units: ";
    getline(cin, inputBuffer);
    newItem.qtyOnHand = atoi(inputBuffer.c_str());
    //itemList.push_back(newItem); //Debug
    if (itemList.size() == 0) //Cannot use placeItem function if inventory vector is empty
        itemList.push_back(newItem);
    else
        placeItem(itemList, newItem); //Placing item in proper location using binarySearch is probably faster than using sorting after every entry
    cout << "\nItem was added successfully!\n\n";
    return;
    }

void showInventory(vector<item> &itemList){ //Case 4: Lists inventory in memory
    cout << "\n            *** List Inventory ***\n";
     cout << setw(12) << "Item Number" << setw(20) << "Description" << setw(10)
          << "Price" << setw(5) << "Qty" << endl;
    for(int i=0; i < itemList.size(); i++){
        rowFormat(itemList[i]);
        cout << endl;
        if(i%15 == 14){
            system("pause");
            system("cls");
        }
    }
    cout << endl;
    return;
}

void inventoryValue(vector<item> &itemList){ //Case 5: Show current inventory value
    double totalValue = 0;
    double itemValue;

    cout << "\n            *** Menu: Show Total Value On Hand ***\n";
    for(int i=0; i < itemList.size(); i++){
        itemValue = itemList[i].qtyOnHand * itemList[i].price;
        totalValue = totalValue + itemValue;
    }
    cout.precision(2);
    cout << "Total value of all inventory: $" << showpoint << fixed << totalValue << endl;
    return;
}

void saveFile(vector<item> &itemList){ //Case 6: Saves inventory vector to disk
    string fileName, realFileName;
    ofstream outStream;
    bool overwrite, clearMem;

    cout << "\n            *** Menu: Save File ***\n";
    do{
        cout << "Enter file name without extension: " << endl;
        getline(cin, fileName);
        realFileName = fileName + ".csv";
        //does this file exist?
        if (fileExists(realFileName)==true){
            cout << "This file already exists! Do you wish to overwrite it?\n";
            overwrite = binaryYN();
        }
        else
            overwrite = true;
    }while (overwrite==false);
    outStream.open(realFileName);
    outStream << "SKU" << "," << "DESCRIPTION" << "," << "PRICE" << "," << "QUANTITY" << endl; //Print column labels to file

    //Print inventory vector to file
    for(int i=0; i < itemList.size(); i++){
        outStream << itemList[i].sku << "," << itemList[i].description << ","
                  << itemList[i].price << "," << itemList[i].qtyOnHand << endl;
    }
    outStream.close();
    cout << realFileName << " has been saved.\n";
    cout << "Do you wish to clear the memory?\n";
    clearMem = binaryYN();
    if (clearMem==true)
        itemList.clear();
    return;
}

int totalInvOnHand(vector<item> &itemList) { //iterate through the vector and add qtys, display total number of units on hand
    int totalQty = 0;
    if (itemList.size() == 0)
        return totalQty;
    else{
        for(int i=0; i < itemList.size(); i++){
        totalQty = itemList[i].qtyOnHand + totalQty;
        }
    }
    return totalQty;
}

//HELPER FUNCTIONS


void fileLoad (vector<item> &itemList, ifstream& inputFile){ //Helper function to load file contents into memory
    vector<string> itemBuffer;
    string strBuffer, metaBuffer;
    item addItem;

    while(!inputFile.eof()){ //Read in a row of data
        stringstream rowData;
        getline(inputFile, strBuffer);
        if(!inputFile.eof()){
            // cout << "strBuffer is: " << strBuffer; //DEBUG
            rowData << strBuffer;
            // cout << "\nRow data is: " << rowData << endl; //DEBUG
            while(rowData.good()){ //Parse row of data into separate strings
                getline(rowData, metaBuffer, ',');
                // cout << "metaBuffer is: " << metaBuffer << endl; // DEBUG
                itemBuffer.push_back(metaBuffer);
            }

            if(itemBuffer.size() != 4){ //Makes sure item has all necessary details!
                cout << "\nFile is incompatible or corrupt. Item was found with missing data!\n" << itemBuffer.size() << endl;
                return;
            }

            else if (itemBuffer[0] == "SKU") //Makes sure header labels aren't imported into the inventory vector
                itemBuffer.clear();

            else {
                addItem.sku = itemBuffer[0];
                addItem.description = itemBuffer[1];
                addItem.price = atof(itemBuffer[2].c_str());
                addItem.qtyOnHand = atoi(itemBuffer[3].c_str());
                itemList.push_back(addItem);
                itemBuffer.clear();
            }
        }
    }
    return;
}

void sortInventory(vector<item>& rawList){ //Bubble sort that catches duplicates
    int compareResult;

    for(int i=rawList.size()-1; i>0; i--){
        for(int j=0; j < i; j++){
            compareResult = strcmp(rawList[j].sku.c_str(), rawList[j+1].sku.c_str());
            if(compareResult > 0)
                itemSwap(rawList, j, j+1);
            else if(compareResult == 0){ //Merges duplicate items by summing their quantities. Advanced conflict resolution is beyond the scope of this version
                rawList[j].qtyOnHand = (rawList[j].qtyOnHand + rawList[j+1].qtyOnHand);
                rawList.erase(rawList.begin()+j+1);
            }
        }
    }
    return;
}

void itemSwap(vector<item>& swapVector, int x, int y) { //Swap x and y in the vector argument
    item tempItem;

    //cout << "\n x = " << a << " y = " << y; //debug
    tempItem = swapVector[x];
    swapVector[x] = swapVector[y];
    swapVector[y] = tempItem;
    return;
}

searchResult binarySearch(vector<item> &itemList, string searchTerm){ //Search function, faster than simple iterative search
    int mid, low = 0, high = itemList.size()-1;
    searchResult result;
    if(low > high){
        //cout << "binarySearch failed! Inventory is probably empty.";
        result.found = false;
        result.location = 0; //This should only happen if the inventory is empty
        return result;
    }

    while(low <= high){
        mid  = (low + high)/2;
        if(itemList[mid].sku == searchTerm){
            result.found = true;
            result.location = mid;
            return result;
        }
        else if(itemList[mid].sku < searchTerm)
            low = mid + 1;
        else
            high = mid - 1;
    }
    result.found = false;
    result.location = mid;
    return result;
}

void placeItem(vector<item> &targetList, item newItem){
    searchResult result;
    result = binarySearch(targetList, newItem.sku);
    if(newItem.sku == targetList[result.location].sku)
        targetList[result.location] = newItem; //Overwrites item if duplicate
    else if(newItem.sku > targetList[result.location].sku)
        targetList.insert(targetList.begin()+result.location+1, newItem); //Places item after the result of binarySearch
    else
        targetList.insert(targetList.begin()+result.location, newItem); //Places item before the result of binarySearch
    return;
}

void rowFormat(item output){ //Formats the data into neat and tidy columns.
    cout << setw(12) << output.sku << setw(20) << output.description << setw(10)
         << setprecision(2) << fixed <<output.price << setw(5) <<output.qtyOnHand;
    return;
}

char charCast(string input, int maxOptions){ //custom string-to-char cast for using string input with switch menus (max 10 options)
    char error = maxOptions + 1; //Any value outside 1-maxOptions is invalid and triggers the default switch case
    char result;
    int menuInt = atoi(input.c_str()); //convert input to integer value

    if(input.length() != 1) //Length > 1 indicates invalid user entry, assuming menu has fewer than 10 options
        return error;
    for(int i = 1; i <= maxOptions; i++) //Checks to make sure user input is a valid menu selection
        if(menuInt == i)
        {
            result = menuInt + '0';
            return result;
        }
    return error;
}

bool binaryYN(){ //Prompts the user for Y/N response, returns bool, includes invalid response handling
    string userChoice;

    cout << "Enter (Y/N): ";
    getline(cin, userChoice);
    if (userChoice == "y" || userChoice == "Y")
        return true;
    else if (userChoice == "n" || userChoice == "N")
        return false;
    else{
        cout << "Invalid Entry. Please try again.\n";
        return binaryYN(); //My First Recursive Function. Yay!
    }
}

bool fileExists(string fileName){
    if (ifstream(fileName).fail()){
        return false;
    }
    else{
        ifstream(fileName).close();
        return true;
    }
}
