#include "Jug.h"
#include <iostream>
#include <string>

using namespace std;

void one() {
   string solution;
   Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
   if (head.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl << endl;
}

void two() {
   string solution;
   Jug head( 3, 5, 4, 1, 1, 1, 1, 1, 2);
   if(head.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl;
}

int main () {
  one();
  two();
}
