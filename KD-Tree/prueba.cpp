#include <iostream>
using namespace std;
 
void square(int *);
 
int main() {
   int number = 8;
   int *pn = &number;
   cout <<  "In main(): " << &number << endl;  // 0x22ff1c
   //cout << number << endl;  // 8
   square(pn);
   cout<<(bool) pn;        // Implicit referencing (without '&')
   //cout << number << endl;  // 64
}
 
void square(int * rNumber) {  // Function takes an int reference (non-const)
   //cout <<  "In square(): " << &rNumber << endl;  // 0x22ff1c
   rNumber = NULL;        // Implicit de-referencing (without '*')
}