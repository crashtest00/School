#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//Should accessor functions be void?
//Where does the pretty card function go?
//This is sort of in the middle of using a class for Hand and using a vector in main() for Hand

class Card
{
    //string cardID();
public:
    Card();
    Card(int rankInt, int suitInt);

    //Mutator
    void add(int, int);

    //Accessor
    string getCard(); //This is simply getRank + getSuit
    string getRank(); //Needs to translate numbers into names when req. Maybe a switch for this instead of else if?
    string getSuit();

private:
    int rankInt;
    int suitInt;
};

class Hand : public Card
{
public:
    Hand();
    Hand(vector<Card> cards);

    //Mutator
    void addCard(Card);
//        cards.push_back(Card) //How to write this function?


    //Accessor
    string showHand(); //Loop through vector using the getCard function
    string getScore(); //Should this call a private rules function?
    void sortCards(); // sort(myHand.begin(), hand.end(), compareCards()); //
    //Rules
//            if nextCard == (currentCard - 1), increment straight
//                if nextCard === (currentCard) increment ofAKind
//            Of a kind means multiple
//                Need to provide nice clean results with proper plurals and 3 of a kind. Go verbose.

private:
    vector<Card> cards;
    void sort(vector<Card>); //Iterate through hand array using Card.rankInt
};
void buildDeck(vector<Card>&); //This is in main() right now
void shuffleDeck(vector<Card>&); //Needs written
//void? binaryYN

int main()
{
    vector<Card> deck;
    int sizeOfHand = 5; //5 cards in each hand
    //vector<Card> hand;
    Hand myHand;

    buildDeck(deck); //Build the deck
    shuffleDeck(deck); //Shuffle the deck

    for(int i=0; i<sizeOfHand;i++) //Deal the hand
        myHand.addCard(deck[i]);

    myHand.showHand(); //Unsorted hand
    myHand.sortCards();
    myHand.showHand(); //Sorted hand

    cout << myHand.getScore(); //Show result of hand

    cout << "Play again?";
    binaryYN; //Need to add this function
}

void buildDeck(vector<Card> &myDeck){
    Card tempCard;

    cout << "Column headers go here"; //column headers (suits)
    for(int i=0; i< 14; i++){ //loop through ranks
        for (int j=0; j<4; j++){ //loop through suits
            tempCard.add(i,j);
            myDeck.push_back(tempCard);
            cout << myDeck.back().getRank(); //print ranks to screen
            cout << setw(10); //Need to check column spacing, reference array lab for this
        }
        cout << endl;
    }
    system("pause");
    system("cls");
}

void shuffleDeck(vector<Card> &myDeck){
    cout << "This will shuffle the deck"; //Use random_shuffle, this function needs written
}
