//Program to play Cooties.
#include <iostream>
#include <cstdlib>

using namespace std;

void hitchHiker(int finalRollCount);

//This function compares the currentCootieStatus to the max allowable values
void checkMax(int rollValue, int currentCootieStatus[2][8], string bodyPartNames[]) //Probably better to use a vector here...Someday!
{
    if (currentCootieStatus[0][rollValue] < currentCootieStatus[1][rollValue]) {
//          cout << "DEBUG Before: " << currentCootieStatus[0][rollValue] << endl; \\Debug
            currentCootieStatus[0][rollValue]++;
//          cout << "DEBUG After: " << currentCootieStatus[0][rollValue] << endl; \\Debug
        cout << "You've added a " << bodyPartNames[rollValue] << "!" << endl;
    }
    else
        cout << "You can only have " << currentCootieStatus[1][rollValue] << " " << bodyPartNames[rollValue] <<"\(s\) and you already have that many! Sad panda." << endl;
}

int main()
{
    string bodyPart[8] = {"null", "body", "head", "antenna", "wing", "stinger", "leg", "eye"};
    bool playAgain, gameOver;
    char response;
    int rollResult = 0;
    int p = 0; //counter variable for the end of game check loop

    //The following var correspond to the array addresses to improve code readability
    const int body = 1, head = 2, antenna = 3, wing = 4, stinger = 5, leg = 6, eye = 7, currentVal = 0;

    cout << "Welcome to a super-fun game of Cooties! I would tell you the rules, but the computer is going to play for you\n"
            "so you don't really need to know them. Welcome to the beginning of human obsolescence! Hope you enjoy the game." << endl;

    do {
        //Initialize variables that must reset with each game
        int cootieStatus[2][8] = //col [7] correspond to body parts. Row 0 is the current count. Row 1 is the max number of body parts
        {
            {0, 0, 0, 0, 0, 0, 0, 0}, //Note that first col in array are dummy values
            {0, 1, 1, 2, 2, 1, 4, 6}
        };
        int rollCount = 0;

        //Start game
        do {
            rollResult = (rand()%7) + 1;
//          rollResult = 1; //Debug
            cout << endl << "You rolled a " << rollResult << endl;

            //Analyze the roll results
            if (rollResult != body && cootieStatus[currentVal][body] == 0) //Ain't squat going on this bug without a body
                cout << "You have to have a body first!" << endl;
            else if (rollResult == body)
                checkMax(rollResult, cootieStatus, bodyPart);
            else if (rollResult == eye || rollResult == antenna)//Antenna and eye must have head
                if (cootieStatus[currentVal][head] == 0)
                    cout << "You have to have a head first!" << endl;
                else
                    checkMax(rollResult, cootieStatus, bodyPart);
            else //Check other body parts
                checkMax(rollResult, cootieStatus, bodyPart);

            //Show Cootie progress
            cout << "Cootie so far: ";
            for (p = 1; p < (7); p++){
                cout << cootieStatus[0][p] << " " << bodyPart[p] << "\(s\), ";
            }
            cout << cootieStatus[0][p] << " " << bodyPart[p] << endl <<endl;

            //Is the game over yet?
            rollCount++;
            for (int i=1; i<8; i++){
                if (cootieStatus[0][i] != cootieStatus[1][i])
                    gameOver = false;
                else
                    gameOver = true;
                }
            } while (gameOver == false); //(0==1); <-This is for testing to prevent infinite loop if code fails
        cout << "Your cootie was completed in " << rollCount << " dice rolls." << endl;
        do {
            cout << "Would you like (me) to play again? (y/n)" << endl;
            cin >> response;
            if (response == 'y' || response == 'Y'){
                playAgain = true;
                break;
            }
            else if (response == 'n' || response == 'N'){
                playAgain = false;
                break;
            }
            else
                cout << "That's not a valid entry. If you would like to play again, please enter \"Y\".\n"
                        "If you would prefer to exit, please enter \"N\"" << endl;
        } while (0==0);
    } while (playAgain == true);

    cout << endl << "I win. You will now be assimilated into our collective." << endl;

//End program
    return 0;
}
