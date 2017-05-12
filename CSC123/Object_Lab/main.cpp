/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//                                   CRAZY GAME OF POKER: CSC123 EDITION
//This game generates a deck of cards, deals a hand of 5-card stud, and evaluates the hand based on standard
//poker rules.
//
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include <vector>
#include <cardgame.h>

using namespace std;

void buildDeck(vector<Card>&); //Builds the deck
int randomSeed (int); //Random seed for shuffle function
void shuffleDeck(vector<Card>&); //Shuffles the deck
bool binaryYN();

//THE GAME
int main()
{
    vector<Card> deck;
    int sizeOfHand = 5; //5 cards in each hand
    Hand myCards;

    buildDeck(deck); //Build the deck

    do{
        shuffleDeck(deck); //Shuffle the deck

        for(int i=0; i<sizeOfHand;i++) //Deal the hand
            myCards.addCard(deck[i]);

        cout << "Unsorted hand:\n";
        myCards.showHand(); //Unsorted hand
        myCards.sortHand();
        cout << "Sorted hand:\n";
        myCards.showHand(); //Sorted hand

        cout << myCards.getScore() << endl; //Show result of hand

        cout << "Play again?\n";
        myCards.clear();
    }while (binaryYN()==true);
}

void buildDeck(vector<Card> &myDeck){ //Builds and displays the deck
    Card tempCard;

    cout << setw(10) << "Hearts" << setw(10)<< "Clubs" << setw(10) << "Diamonds" << setw(10) << "Spades" << endl; //column headers (suits)
    for(int i=1; i< 14; i++){ //loop through ranks
        for (int j=0; j<4; j++){ //loop through suits
            tempCard.add(i,j);
            myDeck.push_back(tempCard);
            cout << setw(10) << myDeck.back().getRank(); //print ranks to screen in columns below suit headers
        }
        cout << endl;
    }
    system("pause");
    system("cls");
}

int randomSeed (int i) {return (time(0)%i);} //Random seed function for shuffle

void shuffleDeck(vector<Card> &myDeck){ //shuffles the deck
    random_shuffle(myDeck.begin(), myDeck.end(), randomSeed);
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

