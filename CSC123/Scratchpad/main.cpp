#include <iostream>
#include <cstdlib>    // for malloc()

using namespace std;

int main() {
int *p1, *p2;
int int1, int2;
bool test;
int1 = 1;
int2 = 1;
p1 = &int1;
p2 = &int2;
test = *p1==*p2;
cout << test;
}
