#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

class Card
{
public:
    int rankInt;
    int suitInt;
    //Constructor
    Card(){}

    //Mutator
    void add(int rank, int suit);

    //Accessor
    string getRank(); //Needs to translate numbers into names for K, Q, J, A
    string getSuit();
    string getCard(); //This is simply getRank + getSuit
};

class Hand : public Card
{
public:
    Hand();

    //Mutator
    void addCard(Card);
    void clear();

    //Accessor
    void showHand(); //Loop through vector using the getCard function
    string getScore(); //Should this call a private rules function?
    void sortHand(); //Sorts the hand by rank

private:
    vector<Card> myHand;
};

//Card class functions
void Card::add(int rank, int suit) //Mutator: Add a card
{
    if(rank >13 || rank < 1 || suit > 3 || suit < 0){
        cout << "Invalid card! Ending program.";
        exit(1);
    }
    else{
        rankInt = rank;
        suitInt = suit;
    }
}

string Card::getRank() //Accessor: Need to translate numbers into names for ace and face cards
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

string Card::getSuit() //Accessor: Convert suitInt to suit string
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
    return (getRank() + " of " + getSuit());
}

//Hand class functions
Hand::Hand()
{
    vector<Card> cards;
    myHand = cards; //initializes a vector myHand
}

void Hand::addCard(Card newCard)
{
    myHand.push_back(newCard); //Adds a card to the hand

}


void Hand::showHand(){ //Loop through vector using the getCard function
    for(int i=0; i < myHand.size()-1; i++) //This needs some help
        cout << myHand[i].getRank() << " of " << myHand[i].getSuit() << ", ";
    cout << myHand.back().getRank() << " of " << myHand.back().getSuit() << endl << endl;
}

string Hand::getScore(){

    int straight = 1; //A single card is a straight with length=1
    int ofKindInt = 1; //A single card is 1 of a kind. Just like you. :)
    int flush = 1; //A single card is a flush of 1
    vector<tuple<int, string>> ofAKind; //Theoretical max size of 2, change this to an array? Pushback becomes array[1]
    string result;
    bool aceHigh = false;

    //Evaluate hand
    for(int i=0; i<myHand.size()-1; i++){
        if(myHand[i].suitInt == myHand[i+1].suitInt) //Check for suit match. NOT an accurate count but works for flush=5
            flush++;
        if(myHand[i].rankInt+1 == myHand[i+1].rankInt){ //Check for straight
            straight++;
            ofKindInt = 1; //No longer a matching rank so ofKindInt counter must be reset
        }
        else if (myHand[i].rankInt == myHand[i+1].rankInt){ //Evaluate for ofKind. Cannot be straight and cannot be flush
            ofKindInt++;
            if(ofKindInt == 2) //Adds an ofAKind tuple and sets as pair
                ofAKind.push_back(make_tuple(ofKindInt,myHand[i].getRank()));
            else if(ofKindInt == 3) //Sets recent/working ofAKind tuple to 3 of a kind
                ofAKind.back() = make_tuple(ofKindInt,myHand[i].getRank());
            else if(ofKindInt == 4) //Sets recent/working ofAKind tuple to 3 of a kind
                ofAKind.back() = make_tuple(ofKindInt,myHand[i].getRank());
        }
         else{ //Reset ofKindInt counter
            ofKindInt = 1;
        }
    }
    if (myHand.front().rankInt == 1 && myHand.back().rankInt ==13){ //Handling for Aces high. King and Ace increments straight by 1
        straight++;
        aceHigh = true;
    }

    //Evaluate scoring
    if(straight==5){//Straight
        if((myHand.back().rankInt == 13) && (aceHigh == true))
            result = "Ace-high straight";
        else
            result = myHand.back().getRank() + "-high straight";
        if (flush==5)
            result = result + " flush!";
    }
    else if(flush==5)//Flush
        result = myHand.back().getSuit() + " flush";
    else if(ofAKind.size()>0){ // Check ofAKind conditions
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
            result = "Something has gone horribly wrong :(";
    }
    else
        result = "You got nothing. Sad panda.";
    return result;
}

void Hand::sortHand(){ //
    sort(myHand.begin(), myHand.end()); //Something isn't right about this

}

void Hand::clear(){ // Clears hand between deals
    myHand.clear();

}

bool operator<(const Card &c1, const Card &c2) {return (c1.rankInt < c2.rankInt);} //used for sort

#endif // CARD_H_INCLUDED
