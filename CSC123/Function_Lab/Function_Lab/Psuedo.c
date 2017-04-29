//Program to play Cooties.
#include <iostream>

using namespace std;

int main()
{
    Roll a 7 sided die using a random function
    If the player rolls a one, theyget a body
    Everything else is contingent on having a body except:
        Antenna
        Eyes
    Both of these are contingent on having a head
    The player can have up to 4 legs and up to 6 eyes
    The total number of rolls should be tallyed and then the user should be asked if they want to play again. This is also probably a loop while answer is yes
        Might as well make this the main function. Return the number of rolls
}
Create a 2 dimensional array for this so the max values can be kept in the same array
Body names should be in a separate string array with a null value in 0 so the names match the rollResult

Do While (playAgain = true)

if rollResult != body && cootieParams[body][curNum] = 0
    Print failure "You have to have a body first!"
Elseif rollResult = body
    If checkRoll = true add to array and print success
If checkRoll = false print maxFailure "You can only have " cootieParams[rollResult][maxNum] " " bodyPart[rollResult] " and you already have that many! Sad panda."
Elseif rollResult = eyes OR rollResult = antenna
    If cootieParams[head][countPart] = 0
        Print Failure cuz you got no head
    Elseif
        Check function
            If checkRoll = true add to array and print success
            If checkRoll = false print failure
Else
    If checkRoll = true add to array and print success
    If checkRoll = false print maxFailure "You can only have " maxNum " " bodyPart " and you already have that many! Sad panda."

    All these messages should be the same so the parts names and such can be filled in automagically from the array
    Increment rollsTotal on each iteration
    Loop continues until array matches the winning array. When met
        Exit loop
        Print awesome success
        Show roll total
        Ask if play again
        Return to main loop
        Main loop should be do while (Cuz awesome)

Check function
    Read in roll number
    Check to see status of roll number against max value
        If does exist and max is not met, return true
        If max is met, return false
