#include <cstdlib>
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    //Problem 1
    cout << 4.54 * 34.2 << 34.4 + 34 << endl;

    //Problem 2
    cout << (char) 67;
    cout << (char) 83;
    cout << (char) 67;
    cout << (int) '{';

    cout << endl;

    //Problem 3
    cout << 'ANOTHER';
    cout << "PROGRAM";

    cout << endl;

    /*Problem 4
    int i;
    cout << "Enter an integer from 1 to 10 then press enter --->";
    cin >> i;

    cout << "The output number is " << i/2;
    cout << endl;*/

     //Problem 5
    double i;
    cout << "Enter an integer from 1 to 10 then press enter --->";
    cin >> i;

    cout << "The output number is " << i/2;
    cout << endl;

    float x;
    x = 3.0/4.0 + (3+2)/5;
    cout << "The answe to 14 is " << x;

    //End Program and show how long it ran
    system("PAUSE");
    return EXIT_SUCCESS;
}
