#include <iostream>
#include <vector>

using namespace std;

bool isWord(vector<string>&, string); //checks to see if a word is in the dictionary
int checkScore(string); //checks score
bool oneMoreRound(string); //Checks for valid response to playAgain
void loadDict(vector<string>&);
bool isPoint(vector<char>, char);

int main()
{
    int score;
    string word, playAgain;
    vector<string> dictionary;

    loadDict(dictionary);
    do{
        cout << "Enter a word:\n";
        getline(cin, word); // what if the user enters a space?
        if (isWord(dictionary, word) == false)
            cout << "\nI'm afraid it appears you made that word up. I award you no points. May God have mercy on your soul\n";
        else{
            score = checkScore(word);
            cout << "Your score is: " << score << "!" << endl;
        }
        do{
            cout << "Would you like to play again (Y/N)?\n";
            getline(cin, playAgain);
            if (oneMoreRound(playAgain)==false)
                cout << "Invalid response. Please try again.\n";
        }while(oneMoreRound(playAgain) == false);
    }while(playAgain == "Y" || playAgain == "y");
}

bool oneMoreRound(string playAgain){
    if (playAgain == "Y" || playAgain == "y" || playAgain == "N" || playAgain == "n")
        return true;
    else
        return false;
}

void loadDict(vector<string> &target){ //Loads dictionary into vector
    ifstream inStream;
    //Needs a bit of code to read in each line of the dictionary
        getline()
}

bool isWord(vector<string> &wordList, string word){
    bool result;
    binary sort for word
    return result;
}

int checkScore(string word){ //Calculates score of word
    bool isDouble = false;
    char prevChar;
    int score;
    vector<char> onePoint {'A', 'E', 'I', 'M', 'Q', 'U', 'Y'};
    vector<char> onePoint {'B', 'F', 'J', 'N', 'R', 'V', 'Z'};
    vector<char> onePoint {'C', 'G', 'K', 'O', 'S', 'W'};
    vector<char> onePoint {'D', 'H', 'L', 'P', 'T', 'X'};

    for(iterate through string){
        word[i] = toupper(word[i]);
        if(word[i] == prevChar)
            isDouble = true;
        if (isPoint(word[i],onePoint)==true)
            score = score + 1;
        else if (B F J N R V Z)
            score = score + 2;
        else if (C G K O S W)
            score = score + 3;
        else if (D H L P T X)
            score = score + 5;
        prevChar = word[i];
    }
    if (isDouble == true)
        score = score*2;
    return score
}
