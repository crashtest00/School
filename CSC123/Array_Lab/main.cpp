#include <iostream>

using namespace std;
//This comment is strictly for testing the github functionality
//This functionality works
//Use .csv to make importing to spreadsheet software easy
//Need an object for the inventory items w/ Name(string w/ spaces), SKU(c.string?), price(double), qtyOnHand(int)
//Need to enforce a reasonable character maximum for each field in the object

int main()
{
    /* Main Menu
    1) Add items
    2)List inventory in neat columns, 15 items at a time
    3) Search Inventory for an item by inventory number
    4) Calculate the total value on hand (Sum of qty*price)
    5) Save memory to db file
    6)Overwrite what's in memory from the disk (Clear buffer and load file contents to display)
    7) Exit program

    Provide a running total of inventory qtys
    */
}

// Function Descriptions

/* Load function
load file contents into memory (Use a .csv file). Force file extension (.csv, user only enters the file name NOT the extension)
If file doesn't exist, create it.
 while(getline(linestream,value,','))
    {
        std::cout << "Value(" << value << ")\n";
    }
    std::cout << "Line Finished" << std::endl;
Load the results of the above code into a temporay vector
Access the vector to create the object, casting the variable types as necessary: http://www.cplusplus.com/reference/string/stod/ and stoi and charhttp://www.cplusplus.com/reference/cstring/strcpy/
Load the object into a working vector
Sort the vector (Should be mostly sorted. Pick an algorithm that favors sorted vectors)


/* 1) Add items
Read object data in from user
Use placeItem to put the object in the proper location in the vector */

/*void Need a function to place new object in vector
This function should look at first object and last object and compare with new object. Whichever is closer is where the search should start
Call appropriate findPlaceHigh or findPlaceLow function and assign to newPlace variable
Then inventory.insert the new object at the result returned by the function */

/* int findPlaceHigh
Receives a vector and an item number. Starting at end, look at each object until you pass the item number. Return the result */

/* int findPlaceLow
Receives a vector and an item number. Starting at beginning, look at each object until you pass the item number. Return the result -1 */

/* 6) Need to arrange these items into columns which means each field should have a maximum number of characters
