//
//
//
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
	string food, animal, singNoun, teacher, adjective, buddy, presentVerb1,
	pastVerb, pluralNoun, favTV, presentVerb2, bankPassword;

    //Read in grammatical input from user, assign to variables
    cout <<"Let's make a fun story using basic parts of speech and harmless personal information!\n"
            "First, let's start with some words." << endl << endl;
    _sleep(500);

    cout <<"Enter a singular noun: ";
    getline(cin, singNoun);

	cout << "Enter a plural noun: ";
	getline(cin, pluralNoun);

    cout << "Enter an adjective: ";
	getline(cin, adjective);

	cout << "Enter a present tense verb: ";
	getline(cin, presentVerb1);

	cout << "Enter another present tense verb: ";
	getline(cin, presentVerb2);

	cout << "Enter a past tense verb: ";
	getline(cin, pastVerb);

	//Read in personal info from user, assign to variables
    cout << "\nAwesome! That's the hard part. Now let's learn a little bit about you, shall we?\n"
            "Let's start with the password to your bank account: ";
    getline(cin, bankPassword);

    _sleep(3000); //pause for effect...
    cout << "\nUmmm...that was a joke. I sincerely hope that \"" << bankPassword << "\" isn't really the password to your bank account.\n"
            "Seriously though, let's get back to business." << endl << endl;
    _sleep(500);

    cout << "What's your least favorite food? ";
    getline(cin, food);

    cout << "What kind of pet do you have? ";
    getline(cin, animal);

    cout << "What's your teacher's name? ";
	getline(cin, teacher);

	cout << "What's your friend's name? ";
	getline(cin, buddy);

	cout << "What's your favorite TV show? ";
	getline(cin, favTV);

    //Output
    cout << "\nI just hate it when..." << endl << endl;

    cout << "Mom serves " << food << " for dinner.\n"
            "My pet " << animal << " chews my " << singNoun << ".\n"
            << teacher << " gets mad at the class for being " << adjective << ".\n"
            "My best friend " << buddy << " decides to " << presentVerb1 << " with somebody else.\n"
            "I get " << pastVerb << " for something I didn't do.\n"
            "Dad makes me wear " << pluralNoun << " to school.\n"
            "My favorite TV show \"" << favTV << "\" gets canceled because the station has to broadcast a news conference.\n"
            "People " << presentVerb2 << " into my bedroom without knocking." << endl << endl;

	//Password warning
    _sleep(2000);
    cout << "Side note: if \"" << bankPassword << "\" is really your bank account password, you should probably change it. Just sayin'." << endl << endl;

	return 0;
}
