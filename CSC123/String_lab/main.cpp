#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>

using namespace std;

bool isWord(vector<string>&, string); //checks to see if a word is in the dictionary
int checkScore(string); //checks score
void loadDict(vector<string>&);
int isMatch(char);
bool isPoint(vector<char>, char);
bool binaryYN();

struct letterGroup{ //Letter groups and associated point values
    string letters;
    int point;
};

class LetterIter{
public:
    char currentLetter;
//    iterates through an array of letters and returns a result struct of letter and point if it finds an input letter


    struct result{
    char ltr;
    int pnt;
    };
};

int main()
{
    bool playAgain;
    int score;
    string word;
    vector<string> dictionary;

    loadDict(dictionary);

    do{
        cout << "Enter a single word with no spaces: \n";
        getline(cin, word); // what if the user enters a space?
        if (isWord(dictionary, word) == false)
            cout << "\nI'm afraid it appears you made that word up. I award you no points. May God have mercy on your soul.\n";
        else{
            score = checkScore(word);
            cout << "Your score is: " << score << "!" << endl;
        }
        cout << "Would you like to play again?\n";
        playAgain = binaryYN();
    }while(playAgain == true);
    cout << "\nThanks for playing! See you next time!\n";
    return 0;
}

void loadDict(vector<string> &target){ //Loads dictionary into vector
    cout << "\nOpening dictionary file\n";
    ifstream inStream;
    string strBuffer;
    inStream.open("web2-Short.txt");

    cout << "Loading dictionary file\n";
    while(!inStream.eof()){
        getline(inStream, strBuffer); //Get word from dictionary file
        target.push_back(strBuffer); //add word to dictionary vector
    }
    cout << "Dictionary loaded successfully!\n";
    return;
}

bool isWord(vector<string> &wordList, string word){
    int mid, low = 0, high = wordList.size()-1;
    bool result = false;
    if(low > high){
        cout << "isWord failed! Dictionary is probably empty.";
        result = false;
    }

    while(low <= high){
        mid  = (low + high)/2;
        if(wordList[mid] == word)
            result = true;
        else if(wordList[mid] < word)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return result;
}


int checkScore(string word){ //Calculates score of word
    bool isDouble = false;
    char prevChar;
    int score=0;

    for(int i = 0; i < word.size(); i++){
        word[i] = toupper(word[i]);
        score = score + isMatch(word[i]);
        if(word[i] == prevChar) //Flips the flag once (and only once) if 2 letters are consecutive
            isDouble = true;
        prevChar = word[i];
        //cout << "\nScore of " << word[i] << " is " << isMatch(word[i]) << endl; //debug Enter entire alphabet to verify each letter point value.
    }
    if (isDouble == true)
        score = score*2;
    return score; //If dictionary check is disabled and entire alphabet is entered, total score should be 69
}

int isMatch(char searchTerm){
    int charScore = 0;
    letterGroup onePoint, twoPoint, threePoint, fivePoint;


    //Letter and point declaration
    onePoint.letters = "AEIMQUY";
    onePoint.point = 1;
    twoPoint.letters = "BFJNRVZ";
    twoPoint.point = 2;
    threePoint.letters = "CGKOSW";
    threePoint.point = 3;
    fivePoint.letters = "DHLPTX";
    fivePoint.point = 5;

    letterGroup allLists[] = {onePoint, twoPoint, threePoint, fivePoint}; //Declare array of letter groups

    for(int i = 0; i < 4; i++){ //go through each list of letters
        for(int j = 0; j < allLists[i].letters.size(); j++){ //go through each letter in the list
            if (allLists[i].letters[j] == searchTerm) //check for match to search term
                charScore = allLists[i].point; //return the point value that corresponds to that letter group
        }
    }
    return charScore;
}

bool binaryYN(){ //Check Y/N, return bool
    string userChoice;
    //bool invalidEntry;

    cout << "Enter (Y/N): ";
    getline(cin, userChoice);
    if (userChoice == "y" || userChoice == "Y")
        return true;
    else if (userChoice == "n" || userChoice == "N")
        return false;
    else{
        //invalidEntry = true;
        cout << "Invalid Entry. Please try again.\n";
        return binaryYN();
    }
}
