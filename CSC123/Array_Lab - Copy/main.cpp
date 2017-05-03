//                     ******INVENTORY MANAGEMENT PROGRAM******       Ver 2.0 Last Update: 5/2/17
/* This program provides a means to opening, editing, and reviewing a .csv inventory file.
The .csv file type was selected for its nearly universal compatibility, allowing the inventory
files to be opened and edited in most spreadsheet programs such as Google Sheets and MS Excel. */

#include <iostream>
#include <fstream> //Needed for file manip
#include <string>
#include <cstring> //strncmp used in sort function
#include <iomanip> //Doesn't look like this is needed
#include <stdlib.h> //Needed for casting types
#include <vector> //Crucial lib for all the operations!
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
int totalInvOnHand(vector<item>&); //Used on main menu screen to show total number of items on hand
string fileOpen(vector<item>&); //Case 1: Opens working file
void itemSearch(vector<item>&); //Case 2: Searches for an item in the inventory vector
void addItem(vector<item>&); //Case 3: Adds item to inventory vector
void showInventory(vector<item>&); //Case 4: Shows all items in inventory vector
void inventoryValue(vector<item>&); //Case 5: Shows current inventory value
void saveFile(vector<item>&, string); //Case 6: Saves file to disk

//HELPER FUNCTIONS
void fileLoad(vector<item>&, ifstream&); //Loads file into memory and returns name of working file
char charCast(string, int);//Checks input string for valid char value, then returns the valid char value
void sortInventory(vector<item>&); //Bubble sort is used to catch and handle duplicate sku's
int itemCompare(const struct item&, const struct item&); //x=y: 0, x<y: -1, x>y: 1
void itemSwap(vector<item>&, int, int); //Swap function for sorting
searchResult binarySearch(vector<item>&, string);//Binary search
void rowFormat(item); //Format item output into legible columns
void placeItem(vector<item>&, item); //Figures out where to place the new item so vector doesn't have to be sorted again

int main()
{
    string menuChoiceStr, fileName;
    char menuChoiceChar;
    bool exit = false;
    bool isOpen = false;
    vector<item> inventory;

    do {
        cout << "\n                  *** Main Menu ***" << endl;
        cout << "\tPlease select from one of the following options:\n"
                "\t1) Open an inventory file\n"
                "\t2) Search for an item\n"
                "\t3) Add an item to inventory\n"
                "\t4) Show Inventory\n"
                "\t5) Show current inventory value\n"
                "\t6) Save inventory file\n"
                "\t7) Exit Program\n\n";

        //Display stats for current file
        if(isOpen == false)
            cout << "No inventory file has been opened. Inventory Quantity is unavailable." << endl;
        else {
            cout << "Current Working File: " << fileName << endl;
            cout << "Total quantity of all items in inventory: " <<totalInvOnHand(inventory) << endl;
        }

        //Main Menu
        cout << "Enter Your Selection: ";
        getline(cin, menuChoiceStr);
        menuChoiceChar = charCast(menuChoiceStr, 7); //Ye Olde cast-char-to-string function now improved to handle different number of menu options (7 in this case)
        switch (menuChoiceChar){
            case '1': //Open file or create one if file name doesn't exist
                fileName = fileOpen(inventory);
                if(fileName == "")
                    break;
                isOpen = true;
                break;
            case '2': //Search for item in inventory
                if(isOpen == false){
                    cout << "Please open a file first.\n" << endl;
                    break;
                }
                else
                    itemSearch(inventory);
                break;
            case '3': //Add item to inventory
                if(isOpen == false){
                    cout << "Please open a file first.\n" << endl;
                    break;
                }
                else
                    addItem(inventory);
                break;
            case '4': //Show current inventory
                if(isOpen == false){
                    cout << "Please open a file first.\n" << endl;
                    break;
                }
                else
                    showInventory(inventory);
                break;
            case '5': //Calculate the total value on hand (Sum of qty*price)
                if(isOpen == false){
                    cout << "Please open a file first.\n" << endl;
                    break;}
                else
                    inventoryValue(inventory);
                break;
            case '6': //Save memory to db file (This should also clear the memory)
                if(isOpen == false){
                    cout << "Please open a file first.\n" << endl;
                    break;}
                else
                    saveFile(inventory, fileName);
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
string fileOpen(vector<item>& invVector){ // Case 1: Loads a selected file into memory for edit/review
    string fileNameStr, realFileName;
    ifstream inStream;
    ofstream outStream;

    cout << "Please enter the name of the file without extension: ";
    getline(cin, fileNameStr);
    realFileName = fileNameStr + ".csv";
    inStream.open(realFileName);
    if(inStream.fail()){
        outStream.open(realFileName);
        if (outStream.fail()){
            cout << "Invalid file name." << endl << endl;
            return "";
        }
        cout << "File not found. New inventory file " << realFileName << " has been created.\n";
        outStream.close();
        return realFileName;
    }
    invVector.clear(); //Prepares the inventory vector to receive file data
    fileLoad(invVector, inStream); //Passes invVector to load data from file
    sortInventory(invVector); //Sorts inventory vector
    inStream.close();
    cout << realFileName << " has been opened and sorted successfully!\n";
    return realFileName;
}

void itemSearch(vector<item> &itemList){ //Case 2: Searches for an item in the inventory vector
    string sku;
    searchResult isFound;

    cout << "\n*** Menu: Item Search ***\n";
    cout << "Enter the item number to search for: ";
    getline(cin, sku);
    isFound = binarySearch(itemList, sku);
    if(isFound.found == true){
        cout << "Item found!\n";
        cout << setw(12) << "Item Number" << setw(20) << "Description" << setw(10)
          << "Price" << setw(5) << "Qty" << endl;
        //cout << itemList[isFound.location].sku << itemList[isFound.location].description; //debug
        rowFormat(itemList[isFound.location]);
    }
    else
        cout << "Item not found!";
    return;
}

void addItem(vector<item> &itemList){ //Case 3: Add an item to inventory

    item newItem;
    string inputBuffer, overwrite;
    searchResult foundItem;

    cout << "*** Menu: Add Item ***" << endl;
    cout << "Enter item number: ";
    getline(cin, newItem.sku);
    foundItem = binarySearch(itemList, newItem.sku); //Check if item already in inventory
    if (foundItem.found == true){ //This if() can be removed if duplicate SKU's are allowed BUT itemSearch results would be ambiguous!
        cout << "Item already exists in inventory! /n";
        //cout << itemList[foundItem.location].description; //debug
        rowFormat(itemList[foundItem.location]);
        cout << "If you continue, existing item data will be overwritten. Do you wish to continue (Y/N)?";
        getline(cin, overwrite);
        if (overwrite != "y" && overwrite != "Y")
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
    cout << "New item Qty" << newItem.qtyOnHand << endl;
    //itemList.push_back(newItem); //Debug
    placeItem(itemList, newItem);
    cout << "\nItem was added successfully!\n";
    return;
    }

void showInventory(vector<item> &itemList){ //Case 4: Lists inventory in memory (If file is open)
    cout << "            *** List Inventory ***\n";
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
    return;
}

void inventoryValue(vector<item> &itemList){ //Case 5: Show current inventory value
    double totalValue = 0;
    double itemValue;

    cout << "\n*** Menu: Show Total Value On Hand ***\n";
    for(int i=0; i < itemList.size(); i++){
        itemValue = itemList[i].qtyOnHand * itemList[i].price;
        totalValue = totalValue + itemValue;
    }
    cout.precision(2);
    cout << "Total value of all inventory: $" << showpoint << fixed << totalValue << endl;
    return;
}

void saveFile(vector<item> &itemList, string workingFile){ //Case 6: Saves inventory vector to disk using working file name
    ofstream outStream;
    outStream.open(workingFile);

    //Print column labels to file
    outStream << "SKU" << "," << "DESCRIPTION" << "," << "PRICE" << "," << "QUANTITY" << endl;

    //Print inventory vector to file
    for(int i=0; i < itemList.size(); i++){
        outStream << itemList[i].sku << "," << itemList[i].description << ","
                  << itemList[i].price << "," << itemList[i].qtyOnHand << endl;
    }
    return;
}


//HELPER FUNCTIONS

int totalInvOnHand(vector<item> &itemList) { //iterate through the vector and add qtys very similar to the price function
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
            while(rowData.good()){ //Parse row of data into separate bits
                getline(rowData, metaBuffer, ',');
                // cout << "metaBuffer is: " << metaBuffer << endl; // DEBUG
                itemBuffer.push_back(metaBuffer);
            }

            if(itemBuffer.size() != 4){ //Make sure item has all necessary details!
                cout << "\nFile is incompatible or corrupt. Item was found with missing data!\n" << itemBuffer.size() << endl;
                return;
            }

            else if (itemBuffer[0] == "SKU") //Skip header row
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

void sortInventory(vector<item>& rawList){ //Bubble sort that catches matching items
    int compareResult;

    for(int i=rawList.size()-1; i>0; i--){
        for(int j=0; j < i; j++){
            compareResult = strcmp(rawList[j].sku.c_str(), rawList[j+1].sku.c_str());
            if(compareResult > 0)
                itemSwap(rawList, j, j+1);
            else if(compareResult = 0){ //Really ought to have conflict resolution (price? description?) but beyond the scope of this version
                rawList[j].qtyOnHand = (rawList[j].qtyOnHand + rawList[j+1].qtyOnHand);
                rawList.erase(rawList.begin()+j+1);
            }
        }
    }
    return;
}

int itemCompare(const struct item &x, const struct item &y){ //compare SKU's of two items
    cout << "x sku = " << x.sku << " y sku = " << y.sku;
    if(x.sku == y.sku)
        return 0;
    else if (x.sku < y.sku)
        return -1;
    else
        return 1;
}

void itemSwap(vector<item>& swapVector, int a, int b) { //Swap a and b in the vector argument
    item tempItem;

    //cout << "\n a = " << a << " b = " << b; //debug
    tempItem = swapVector[a];
    swapVector[a] = swapVector[b];
    swapVector[b] = tempItem;
    return;
}

searchResult binarySearch(vector<item> &itemList, string searchTerm){
    int mid, low = 0, high = itemList.size()-1;
    searchResult result;
    if(low > high){
        //cout << "binarySearch failed! Inventory is probably empty.";
        result.found = false;
        result.location = -1; //This should only happen if the inventory is empty
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
    searchResult result = binarySearch(targetList, newItem.sku);

    if(newItem.sku == targetList[result.location].sku)
        targetList[result.location] = newItem; //Overwrites item if duplicate
    else if(newItem.sku > targetList[result.location].sku)
        targetList.insert(targetList.begin()+result.location+1, newItem); //Places item after the result of binarySearch
    else
        targetList.insert(targetList.begin()+result.location, newItem); //Places item before the result of binarySearch
    return;
}

void rowFormat(item output){ //Formats the data into neat and tidy columns. Column widths should probably be enforced during item entry to avoid overflow
    cout << setw(12) << output.sku << setw(20) << output.description << setw(10)
         << setprecision(2) << fixed <<output.price << setw(5) <<output.qtyOnHand;
    return;
}

char charCast(string input, int maxOptions){ //custom charcast with robust error handling

    char error = maxOptions + 1; //out of bound value that will trigger the default switch case
    char result;
    int menuInt = atoi(input.c_str()); //convert input to integer value

    if(input.length() != 1) //Length > 1 indicates invalid user entry
        return error;
    for(int i = 1; i <= maxOptions; i++) //Checks to make sure user input is valid menu selection
        if(menuInt == i)
        {
            result = menuInt + '0';
            return result;
        }
    return error; //Any value outside 1-4 is invalid and triggers the error message
}

