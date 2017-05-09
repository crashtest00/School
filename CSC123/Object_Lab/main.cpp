#include <iostream>
#include <algorithm>

using namespace std;

    Create a card class
        Card class should include an accessor that translates
        {jack queen king} as well as suit:
            int main()
        Add a show card function that outputs strings instead of int
{
  cout << "\003" << endl;
  cout << "\004" << endl;
  cout << "\005" << endl;
  cout << "\006" << endl;
  return 0;
}
        Maybe a switch for this instead of else if?

    create a hand subclass
        All of these should be private functions
        Add a sort function
            Sort by rank
        Add a show hand function
            Iterate through hand array using the showCard method
        Score the hand
        Look at the dice game for how to score
            Remember, the hand has been sorted. Which means a straight has multiple rank in a row
                if nextCard == (currentCard - 1), increment straight
                if nextCard === (currentCard) increment ofAKind
            Of a kind means multiple
                Need to provide nice clean results with proper plurals and 3 of a kind. Go verbose.

int main()
{
    need two loops to create the deck
       From 1-4 i
        Add a card from 1-14 j
        Load the deck into a vector<cards>
    Display the deck in 4 neat columns (reference array lab for this)
        Should call the
    system(break);
    system(cls);
    Shuffle the vector with random_shuffle
    "Deal" 5 cards into the hand class
    display the unsorted hand
    sort the hand
    display the sorted hand
}

Ace can be high or low
    Only matters for straights and the numeric assignment
