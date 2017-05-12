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
    void makeHand(int,int,int,int,int,int,int,int,int,int);

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
void makeHand(Hand&, int, int, int, int, int, int, int, int, int, int);


int main()
{
    vector<Card> deck;
    int sizeOfHand = 5; //5 cards in each hand
    //vector<Card> hand;
    Hand myHand;

    //Test the test
    //makeHand(myHand, 5,3,7,2,7,3,6,1,9,1);

    //Flush Passed!
    //makeHand(myHand, 5,1, 7,1, 4,1, 2,1, 10,1);

    //Full House
    //makeHand(myHand, 2,1, 2,0, 5,2, 5,1, 5,3);

    //Straight Flush
    //makeHand(myHand, 1,1, 10,1, 11,1, 12,1, 13,1);

    //Two Pair
    //makeHand(myHand, 2,0, 2,1, 11,1, 12,0, 12,1);

    //Previous fail test
    makeHand(myHand, 1,2, 2,1, 11,0, 12,0, 13,2);

    do{
        cout << "Unsorted hand:\n";
        myHand.showHand(); //Unsorted hand
        myHand.sortHand();
        cout << "Sorted hand:\n";
        myHand.showHand(); //Sorted hand

        cout << myHand.getScore() << endl; //Show result of hand

        cout << "Play again?\n";
        myHand.clear();
    }while (binaryYN()==true);
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

void makeHand(Hand &dealHand, int r1, int s1, int r2, int s2, int r3, int s3, int r4, int s4, int r5, int s5){
    Card card1;
    card1.add(r1,s1);
    Card card2;
    card2.add(r2,s2);
    Card card3;
    card3.add(r3,s3);
    Card card4;
    card4.add(r4,s4);
    Card card5;
    card5.add(r5,s5);

    dealHand.addCard(card1);
    dealHand.addCard(card2);
    dealHand.addCard(card3);
    dealHand.addCard(card4);
    dealHand.addCard(card5);
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
    cards = myCards; //Initialize a vector cards
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

    int straight = 1; //A single card is a straight with length=1
    int ofKindInt = 1; //A single card is 1 of a kind. Just like you. :)
    int flush = 1; //A single card is a flush of 1
    vector<tuple<int, string>> ofAKind; //Theoretical max size of 2, change this to an array? Pushback becomes array[1]
    string result;
    bool aceHigh = false;

    //Evaluate hand
    for(int i=0; i<cards.size()-1; i++){
        if(cards[i].suitInt == cards[i+1].suitInt) //Check for suit match. NOT an accurate count but works for flush=5
            flush++;
        if(cards[i].rankInt+1 == cards[i+1].rankInt){ //Check for straight
            straight++;
            ofKindInt = 1; //No longer a matching rank so ofKindInt counter must be reset
        }

        else if (cards[i].rankInt == cards[i+1].rankInt){ //Evaluate for ofKind. Cannot be straight and cannot be flush
            ofKindInt++;
            if(ofKindInt == 2) //Adds an ofAKind tuple and sets as pair
                ofAKind.push_back(make_tuple(ofKindInt,cards[i].getRank()));
            else if(ofKindInt == 3) //Sets recent/working ofAKind tuple to 3 of a kind
                ofAKind.back() = make_tuple(ofKindInt,cards[i].getRank());
            else if(ofKindInt == 4) //Sets recent/working ofAKind tuple to 3 of a kind
                ofAKind.back() = make_tuple(ofKindInt,cards[i].getRank());
        }
        else{ //Reset ofKindInt counter
            ofKindInt = 1;
            straight = 1;
        }

    }
    if (cards.front().rankInt == 1 && cards.back().rankInt ==13){ //Handling for Aces high. If King and Ace are present, straight length equals 2
        straight++;
        aceHigh = true;
    }
    cout << "Made it to output section!" << endl;
    cout << "Straight counter: " << straight << endl;
    cout << "Flush counter: " << flush << endl;
    cout << "Number of matching sets: " << ofAKind.size() << endl;
    if(ofAKind.size()>0){
        for(int i=0; i<ofAKind.size(); i++)
        cout << get<0>(ofAKind[i]) << "of a kind: " << get<1>(ofAKind[i]) << endl;
    }

    //Evaluate scoring
    if(straight==5){//Straight
        if((cards.back().rankInt == 13) && (aceHigh == true))
            result = "Ace-high straight";
        else
            result = cards.back().getRank() + "-high straight";
        if (flush==5)
            result = result + " flush!";
    }
    else if(flush==5)//Flush
        result = cards.back().getSuit() + " flush";
    else if(ofAKind.size()>0){ // Check ofAKind conditions
        cout << "Evaluating ofAKind\n";
        if ((get<0>(ofAKind[0]) == 2)&&(ofAKind.size()==1))//Pair
            result = "Pair of " + get<1>(ofAKind[0]) + "s";
        else if ((get<0>(ofAKind[0])) + (get<0>(ofAKind[1])) == 4) //Two Pair
            result = "Pair of " + get<1>(ofAKind[0]) + "s and pair of " + get<1>(ofAKind[1]) + "s";
        else if ((get<0>(ofAKind[0]) == 3)&&(ofAKind.size()==1))//Three of a kind
            result = "Three " + get<1>(ofAKind[0]) + "s";
        else if ((get<0>(ofAKind[0])==2) && (get<0>(ofAKind[1])==3)) //Full House, pair rank is low
            result = "Full house: " + get<1>(ofAKind[1]) + "s over " + get<1>(ofAKind[0]) + "s";
        else if ((get<0>(ofAKind[0])==3) && (get<0>(ofAKind[1])==2)) //Full House, pair rank is high
            result = "Full house: " + get<1>(ofAKind[0]) + "s over " + get<1>(ofAKind[1]) + "s";
        else if (get<0>(ofAKind[0]) == 4) //Four of a kind
            result = "Four " + get<1>(ofAKind[0]) + "s";
        else
            result = "Did not catch!";
    }
    else
        result = "You got nothing. Sad Panda.";
    return result;
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
