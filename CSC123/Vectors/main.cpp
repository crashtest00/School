// how to use a vector as an array, where you use the whole thing.

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void printList(vector<string> list);
void addWords(vector<string> &list);  // if you want to change a vector in a function
                                      // you need to make it a reference parameter!


int main()
{
    vector<string> wordList(10, "empty"); // create a vector with 10 strings, each containing the word 'empty'

//    cout << wordList[10] << endl;  // will cause an error
                                     // vectors have range checking!
    printList(wordList);
    addWords(wordList);
    printList(wordList);

    return 0;
}

void printList(vector<string> list)
{
    int i;
    for (i=0; i<list.size(); i++)
    {
        cout << setw(3) << i << ") "<< list[i] << endl;
    }
}

void addWords(vector<string> &list)
{
    int i;
    for (i=0; i<list.size(); i++)
    {
        cout << "Enter word " << i+1 << " of " << list.size() << ":";
        getline(cin, list[i]);
    }
}
