#include <iostream>
#include <stdexcept>
#include <vector>
#include <time.h>

using namespace std;
/* Part 1
 * unsigned min_index(const vector<T> &vals, unsigned index):
 *  Passes in an index of type int and a vector of type T (T could be string, double or int).
 *  The function returns the index of the min value starting from "index" to the end of the "vector".
 * selection_sort(vector<T> &vals):
 *  Passes in a vector of type T and sorts them based on the selection sort method.
 *  This function should utilize the min_index function to find the index of the min value in the
 *  unsorted portion of the vector. */
template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned indexMin = index;

    if(index != vals.size()-1){
        for(unsigned i = index+1; i < vals.size(); i++) {
            if(vals[i] < vals[indexMin]) {
                indexMin = i;
            }
        }
    }
    return indexMin;
}

template <typename T>
void selection_sort(vector<T> &vals) {
    if(vals.size() != 0) {
        for(unsigned i = 0; i < vals.size(); i++) {
            unsigned nextMinIndex = min_index(vals, i);
            T minValue = vals[nextMinIndex];
            vals[nextMinIndex] = vals[i];
            vals[i] = minValue;
        }
    }
}

/* Part 2
 * T getElement(vector<T> vals, int index):
 *  Passes in a vector of type T (T could be string, double or int) and an index of type int.
 *  The function returns the element located at the index of the vals.
 *  You should write up a try catch block in main function so that when the index
 *  is out of the range of the vector, the "std::outofrange" exception will be
 *  caught by the catch (const std::outofrange& excpt).
 *  Once the exception is caught, it should output "out of range exception occured" followed by a new line. */

template <typename T>
T getElement(vector<T> vals, int index) {
    return vals[index];
}

vector<char> createVector() {
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++) {
        vals.push_back(c);
        c++;
    }

    return vals;
}

int main() {

    //Part B
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0){
        cout << "Enter a number: " << endl;
        cin >> index;
        try{
            curChar = getElement(vals,index);
            int size = vals.size(); //this is my stupid solution to circumventing the type issue zybooks is having - roy
            if(index >= size){ // OH MY GOD IT ACTUALLY WORKS HOLY CRAP THAT WAS SO LOW IQ I DIDNT THINK THAT WOULD FIX IT
                throw std::out_of_range(""); //not sure how this is supposed to work //nvm, got it kinda
            }
            cout << "Element located at " << index << ": is " << curChar << endl;

        }
        catch (const std::out_of_range& excpt) {
            cout << "out of range exception occured" << endl;
            return 1;
        }
        cout << "Element located at " << index << ": is " << curChar << endl;
    }
    return 0;
}
