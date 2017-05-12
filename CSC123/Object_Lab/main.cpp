#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <cstdlib>
#include <tuple>

using namespace std;

//Should accessor functions be void?
//Where does the pretty card function go?
//This is sort of in the middle of using a class for Hand and using a vector in main() for Hand
//Should change cards to myCards or even myHand
//Force a 5-card hand. Stick to the reqs

class Card
{
    //string cardID();
public:
    Card(){}
    //Card(int rankInt, int suitInt); //This isn't ever used, since you'd never declare a card outside of declaring a deck

    //Mutator
    void add(int rank, int suit);
    
    //Accessor
    string getRank(); //Needs to translate numbers into names when req. Maybe a switch for this instead of else if?
    string getSuit();
    string getCard(); //This is simply getRank + getSuit
    
    
    int rankInt;
    int suitInt;
private:
    int myRank;
};

class Hand : public Card
{
public:
    Hand();
    Hand(vector<Card> cards); //This constructor is probably not necessary

    //Mutator
    void addCard(Card);
    void clear();
    
    //Accessor
    void showHand(); //Loop through vector using the getCard function
    string getScore(); //Should this call a private rules function?
    void sortHand(); //Sorts the hand by rank
    //Rules
//            if nextCard == (currentCard - 1), increment straight
//                if nextCard === (currentCard) increment ofAKind
//            Of a kind means multiple
//                Need to provide nice clean results with proper plurals and 3 of a kind. Go verbose.

private:
    vector<Card> cards;
    //void sortCards(vector<Card>); //Iterate through hand array using Card.rankInt
    bool compareCards(Card, Card);
};
void buildDeck(vector<Card>&); //This is in main() right now
int randomSeed (int); //Random seed for shuffle function
void shuffleDeck(vector<Card>&); //Needs written
bool binaryYN();

int main()
{
    vector<Card> deck;
    int sizeOfHand = 5; //5 cards in each hand
    //vector<Card> hand;
    Hand myHand;

    buildDeck(deck); //Build the deck
    
    do{
        shuffleDeck(deck); //Shuffle the deck

        for(int i=0; i<sizeOfHand;i++) //Deal the hand
            myHand.addCard(deck[i]);

        cout << "Unsorted hand:\n";
        myHand.showHand(); //Unsorted hand
        myHand.sortHand();
        cout << "Sorted hand:\n";
        myHand.showHand(); //Sorted hand

        cout << myHand.getScore(); //Show result of hand

        cout << "Play again?\n";
        myHand.clear();
    }while (binaryYN()==true); //Need to add this function
}

void buildDeck(vector<Card> &myDeck){
    Card tempCard;

    cout << setw(10) << "Hearts" << setw(10)<< "Clubs" << setw(10) << "Diamonds" << setw(10) << "Spades" << endl; //column headers (suits)
    for(int i=1; i< 14; i++){ //loop through ranks
        for (int j=0; j<4; j++){ //loop through suits
            tempCard.add(i,j);
            myDeck.push_back(tempCard);
            cout << setw(10) << right << myDeck.back().getRank(); //print ranks to screen
            //Need to check column spacing, reference array lab for this
        }
        cout << endl;
    }
    system("pause");
    system("cls");
}

int randomSeed (int i) {return time(0)%i;} //Random seed

void shuffleDeck(vector<Card> &myDeck){
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

//Card class functions
void Card::add(int rank, int suit)
{
    if(rank >13 || rank < 1) //Combine all IF conditions on this line and get rid of the elseif
        cout << "Invalid rank"; //Then what?
    else if(suit > 3 || suit < 0)
        cout << "Invalid suit"; //Then what?
    else{
        rankInt = rank;
        suitInt = suit;
    }
}

    //Accessor
string Card::getRank()  //Needs to translate numbers into names when req. Maybe a switch for this instead of else if?
{
    switch (rankInt) {
        case 1:
            return "Ace";
            break;
        case 2:
            return "2";
            break;
        case 3:
            return "3";
            break;
        case 4:
            return "4";
            break;
        case 5:
            return "5";
            break;
        case 6:
            return "6";
            break;
        case 7:
            return "7";
            break;
        case 8:
            return "8";
            break;
        case 9:
            return "9";
            break;
        case 10:
            return "10";
            break;
        case 11:
            return "Jack";
            break;
        case 12:
            return "Queen";
            break;
        case 13:
            return "King";
            break;
        default:
            return "Invalid Rank";
            break;
    }
}

string Card::getSuit()
{
    switch (suitInt) {
        case 0:
            return "Hearts";
            break;
        case 1:
            return "Clubs";
            break;
        case 2:
            return "Diamonds";
            break;
        case 3:
            return "Spades";
            break;
        default:
            return "Invalid Suit";
            break;
    }
}

string Card::getCard() //This is simply getRank + getSuit
{
    return (getRank() + " of " + getSuit()); //This might not be the correct way to do this
}

//Hand class functions
Hand::Hand()
{
    vector<Card> myCards;
    cards = myCards; //Should initialize a vector cards
}

void Hand::addCard(Card newCard)
{
    cards.push_back(newCard); //Adds a card to the hand
    
}


void Hand::showHand(){ //Loop through vector using the getCard function
    for(int i=0; i < cards.size()-1; i++) //This needs some help
        cout << cards[i].getRank() << " of " << cards[i].getSuit() << ", ";
    cout << cards.back().getRank() << " of " << cards.back().getSuit() << endl;
}

string Hand::getScore(){ //Should this call a private rules function?
    //Use one for loop
    //Track ofKind matches in the ofAKind tuple vector
    //use ofAKind.push_back(make_tuple(numOfMatches, rank)
    //Each iteration should increment the flush counter and the straight counter
    //For straight logic, if last card is King and first card is Ace, straight++
    //ofKind should initialize (and reset) at 1, since a card always matches itself
    //Straight should also initialize to 1. No need to reset since only 5 triggers the straight result
    
    int straight = 1; //A single card is a straight with length=1
    int ofKindInt = 1; //A single card is 1 of a kind. Just like you. :)
    int flush = 1; //A single card is a flush of 1
    vector<tuple<int, string>> ofAKind; //Theoretical max size of 2, change this to an array? Pushback becomes array[1]
    string result;
    bool aceHigh = false;
    
    //Evaluate hand
    if (cards.front().rankInt == 1 && cards.back().rankInt ==13){ //Handling for Aces high. If King and Ace are present, straight length equals 2
        straight++;
        aceHigh = true;
    }
    for(int i=0; i<cards.size(); i++){
        if(cards[i].suitInt == cards[i+1].suitInt) //Check for suit match. Could be a straight, doesn't have to be.
            flush++;
        
        //Evaluate for straight. Could be flush, doesn't have to be
        if(cards[i].rankInt+1 == cards[i+1].rankInt){ //Check for straight
            straight++; //increment straight counter
            ofKindInt = 1; //Reinitialize
        }

        //Evaluate for ofKind. Cannot be straight and cannot be flush
        else if (cards[i].rankInt == cards[i+1].rankInt){
            ofKindInt++;
            if(ofKindInt == 2)
                ofAKind.push_back(make_tuple(ofKindInt,cards[i].getRank()));
            else if(ofKindInt == 3) //Explicit check but could probably be combined with 4ofKind and changed to else
                ofAKind.back() = make_tuple(ofKindInt,cards[i].getRank());
            else if(ofKindInt == 4)
                ofAKind.back() = make_tuple(ofKindInt,cards[i].getRank());
        }
    }
    //Straight
    if(straight==5){
        if((cards.back().rankInt == 13) && (aceHigh == true))
            result = "Ace-high straight";
        else
            result = cards.back().getRank() + "-high straight";
        if (flush==5)
            result = result + " flush!";
    }
    //Flush
    else if(flush==5)
        result = cards.back().getSuit() + " flush";
    //Pair
    else if ((get<0>(ofAKind[0]) == 2)&&(ofAKind.size()==1))
        result = "Pair of " + get<1>(ofAKind[0]);
    //Two Pair
    else if ((get<0>(ofAKind[0])) + (get<0>(ofAKind[1])) == 4) //This has to be 2 pairs
        result = "Pair of " + get<1>(ofAKind[0]) + " and pair of " + get<1>(ofAKind[1]);
    //Three of a kind
    else if ((get<0>(ofAKind[0]) == 2)&&(ofAKind.size()==1))
    //Full House
    else if ((get<0>(ofAKind[0])) + (get<0>(ofAKind[1])) == 5)
        result = "Full house " front " over " back;
    //Four of a kind
    else if ((get<0>(ofAKind[0]) == 2)&&(ofAKind.size()==1))
            
    return result;
}

    //Translate results into human readable goodness
    if(flush==4)//Straight
        cout << cards[0].getSuit() << "flush";
    if(pair == 2)
        
    //Rules
    //            if nextCard == (currentCard - 1), increment straight
    //                if nextCard === (currentCard) increment ofAKind
    //            Of a kind means multiple
    //                Need to provide nice clean results with proper plurals and 3 of a kind. Go verbose.
    return ("Score goes here\n");
}

void Hand::sortHand(){ //
    sort(cards.begin(), cards.end()); //Something isn't right about this
    
}

void Hand::clear(){ //
    cards.clear(); //Something isn't right about this
    
}


bool operator<(const Card &c1, const Card &c2) {return (c1.rankInt < c2.rankInt);}


bool Hand::compareCards(Card a, Card b){
    if(a.rankInt < b.rankInt)
        return true;
    else
        return false;
}
