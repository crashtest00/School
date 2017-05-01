//                     ******INVENTORY MANAGEMENT PROGRAM******
/* This program provides a means to opening, editing, and reviewing a .csv inventory file.
The .csv file type was selected for its universal compatibility which allows this inventory
file to be opened and edited in most spreadsheet programs such as Google Sheets and MS Excel. */

#include <iostream>
#include <fstream> //Needed for file manip
#include <string>
#include <cstring> //strncmp used in sort function
//#include <iomanip> //Doesn't look like this is needed
#include <stdlib.h> //Needed for casting types
#include <vector> //Crucial lib for all the operations!
#include <sstream> //Used in fileLoad to parse item data

using namespace std;

struct item //Class for items
{
 string sku;
 string description;
 double price;
 int qtyOnHand;
};

//MENU FUNCTIONS
int totalInvOnHand(vector<item>&); //Used below menu to show total number of items on hand
string fileOpen(vector<item>&); //Case 1: Opens working file
//itemSearch //Case 2: Searches for an item in the inventory vector
void addItem(vector<item>&); //Case 3: Adds item to inventory vector
void showInventory(vector<item>&); //Case 4: Shows all items in inventory vector
void inventoryValue(vector<item>&); //Case 5: Shows current inventory value
void saveFile(vector<item>&, string); //Case 6: Saves file to disk

//HELPER FUNCTIONS
void fileLoad(vector<item>&, ifstream&); //Loads file into memory and returns name of working file
char charCast(string, int);//Checks input string for valid char value, then returns the valid char value
void sortInventory(vector<item>&); //Bubble sort is used to catch and handle duplicate sku's
int itemCompare(const struct item&, const struct item&); //x=y: 0, x<y: -1, x>y: 1
void itemSwap(vector<item>& swapVector, int a, int b); //Swap function for sorting

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
            cout << "Current number of items in inventory: " <<totalInvOnHand(inventory) << endl; //Needs updated to show number of items in inventory
        }
        //Main Menu
        cout << "Enter Your Selection: ";
        getline(cin, menuChoiceStr);
        menuChoiceChar = charCast(menuChoiceStr, 7); //Ye Olde cast-char-to-string function now improved to simplify handling for different number of menu options (7 in this case)
        switch (menuChoiceChar){
            case '1': //Open file or create one if file name doesn't exist
                fileName = fileOpen(inventory); //Needs replaced with a function that returns a tuple
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
                    cout << "Search for item\n"; //itemSearch
                break;
            case '3': //Add item to inventory
                if(isOpen == false){
                    cout << "Please open a file first.\n" << endl;
                    break;
                }
                else
                    addItem(inventory);
                cout << "Number of items in inventory " << inventory.size();
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
    cout << "Ending Program\n";
}

// Menu Functions
string fileOpen(vector<item>& invVector) // Case 1: Loads a selected file into memory for edit/review
{
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
    fileLoad(invVector, inStream); //Passes invVector to function so datacan be loaded from file
    //invSorted = fileSort(invVector); //Sorts vector to facilitate searching
    inStream.close();
    return realFileName;
}

/* void itemSearch  //Case 2: Search for item
string sku
cout << "*** Menu: Item Search ***"
getline(cin, sku);
Iterate through vector until found
    if found
        cout: object at the address where the item number was found
If end of vector && not found
    cout << "Item not found!"
return to main menu
*/

void addItem(vector<item> &itemList) //Case 3: Add an item to inventory
{
    item newItem;
    int newQty, itemAddress;
    string inputBuffer;

    cout << "*** Menu: Add Item ***" << endl;

    cout << "Enter item number:";
    getline(cin, newItem.sku);
        //if(doesContain = itemAddress != -1)
            //add one to itemList[itemAddress].qtyOnHand

    cout << "Enter item description:";
    getline(cin, newItem.description);
    cout << "Enter item price:";
    getline(cin, inputBuffer);
    newItem.price = atof(inputBuffer.c_str());
    cout << "Enter number of new units to add to inventory:";
    getline(cin, inputBuffer);
    newQty = atoi(inputBuffer.c_str());
    cout << "New Quantity: " << newQty << endl;
    cout << "prior qtyOnHand: " << newItem.qtyOnHand << endl;
    newItem.qtyOnHand = newQty;
    cout << "New item Qty" << newItem.qtyOnHand << endl;
    itemList.push_back(newItem); //Temporary fix until placeItem is functioning
    // placeItem(newItem, itemList)
    cout << "\nItem was added successfully!\n";
    return;
    }

void showInventory(vector<item> &itemList){ //Case 4: Lists inventory in memory (If file is open)
    cout << "*** List Inventory ***" << endl;
    for(int i=0; i < itemList.size(); i++)
        cout << itemList[i].sku << " " << itemList[i].description << " " << itemList[i].price
             << " " << itemList[i].qtyOnHand << endl;

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

void saveFile(vector<item> &itemList, string workingFile){ //Saves inventory vector to disk using working file name
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
            if(itemBuffer.size() != 4) //Make sure item has all necessary details!
                cout << "\nINCOMPATIBLE FILE! Size is: \n" << itemBuffer.size() << endl;
            addItem.sku = itemBuffer[0];
            addItem.description = itemBuffer[1];
            addItem.price = atof(itemBuffer[2].c_str());
            addItem.qtyOnHand = atoi(itemBuffer[3].c_str());
            itemList.push_back(addItem);
            itemBuffer.clear();
        }
    }
    sortInventory(itemList);
    cout << "\nInventory file has been loaded and sorted.\n";
    return;
}

void sortInventory(vector<item>& rawList){
    int compareResult;

    for(int i=rawList.size()-1; i>0; i--){
        for(int j=0; j < i; j++){
            compareResult = strcmp(rawList[j].sku.c_str(), rawList[j+1].sku.c_str());
            //compareResult = itemCompare(rawList[j], rawList[j+1]);
            cout << compareResult;
            if(compareResult > 0)
                itemSwap(rawList, j, j+1);
            else if(compareResult = 0){
                rawList[j].qtyOnHand = rawList[j].qtyOnHand + rawList[j+1].qtyOnHand;
                rawList.erase(rawList.begin()+j+1);
            }
        }
    }
    return;
}

int itemCompare(const struct item &x, const struct item &y){
    cout << "x sku = " << x.sku << " y sku = " << y.sku;
    if(x.sku == y.sku)
        return 0;
    else if (x.sku < y.sku)
        return -1;
    else if (x.sku > y.sku)
        return 1;
}

void itemSwap(vector<item>& swapVector, int a, int b) { //Swap a and b in the inventory vector
    item tempItem;

    cout << "\n a = " << a << " b = " << b;
    cout << "\n itemSwap launch successfull!\n";
    tempItem = swapVector[a];
    swapVector[a] = swapVector[b];
    swapVector[b] = tempItem;
    cout << "\n itemSwap finish successfull!\n";
    return;
}

/*void invSort(vector<item> inventoryRaw) //Sorts the vector of item structs
http://stackoverflow.com/questions/18759920/sort-vector-of-structs-by-a-variable-within-the-struct*/

/*void placeItem(newItem, inventoryVector[])
{
item newItem
vector<item> inventoryVector[]
tuple locTuple<bool, int>

if (newItem.sku <= (inventoryVector.size/2))
    locTuple = findPlaceFirst(newItem.sku, inventoryVector[]);
else if (newItem.sku > (inventoryVector.size/2))
    locTuple = findPlaceLast(newItem.sku, inventoryVector[]);
else if inventoryVector.size == 0)
    inventoryVector[0] = newItem

if (<0>locTuple == true)
    inventoryVector[<1>locTuple].qty++
else
    inventoryVector.insert(newItem, <1>locTuple)
}

/*tuple findPlaceLast(int searchTerm, list <inventoryStruct>) //Helper function to find place for new item starting at end of vector
for (int i=list.end; i >= list.start; i--){
if(list[i].sku == searchTerm
    return make_tuple<true, i>;
else (list[i].sku < searchTerm
    return make_tuple<false, ++i>
}
*/

/*tuple findPlaceFirst //Helper function to find place for new item starting at beginning of vector
for (int i=list.start; i <= list.end; i++){
if(list[i].sku == searchTerm
    return make_tuple<true, i>;
else (list[i].sku > searchTerm
    return make_tuple<false, i>
}*/

char charCast(string input, int maxOptions) //custom charcast with robust error handling
{
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

