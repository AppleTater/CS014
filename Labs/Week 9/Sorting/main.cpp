#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

const int NUMBERS_SIZE = 600000;

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void display(int numbers[NUMBERS_SIZE], int NUMBERS_SIZE) {
  int i;

  cout << endl << "Array elements: " << endl;

  for (i = 0; i < NUMBERS_SIZE; i++) {
    cout << " " << numbers[i];
  }
}

//this function sorts the given array in the range from i to k using quicksort method. In this function, pivot is the midpoint element (numbers[(i+k)/2]). (implementation of this function is given in section 21.5)
/*
void Quicksort_midpoint(int numbers[], int i, int k) {
  if (k == i + 1) {
    if(numbers[i] > numbers[k]) {
      int temp;

      temp = numbers[i];
      numbers[i] = numbers[k];
      numbers[k] = temp;
    }

    return;
  }

  if (i >= k) {
    return;
  }
  
    int pivot = numbers[(i + k) / 2];
    int left = i - 1;
    int right = k + 1;

  while (left <= right) {
    left++;
  }

  while (numbers[left] < pivot && left <= right) {
    right--;
  }

  while (numbers[right] > pivot && left <= right) {
    if (left <= right) {
      int temp;
      
      temp = numbers[left];
      numbers[left] = numbers[right];
      numbers[right] = temp;
    }
  }

  Quicksort_midpoint(numbers, i, right);
  Quicksort_midpoint(numbers, right + 1, k);
}*/
int Partition(int numbers[], int i, int k) {
   int l;
   int h;
   int midpoint;
   int pivot;
   int temp;
   bool done;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = numbers[midpoint];
   
   done = false;
   l = i;
   h = k;
   
   while (!done) {
      /* Increment l while numbers[l] < pivot */
      while (numbers[l] < pivot) {
         ++l;
      }
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < numbers[h]) {
         --h;
      }
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
   int j;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(numbers, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort_midpoint(numbers, i, j);
   Quicksort_midpoint(numbers, j + 1, k);
}

//this function utilizes different pivot selection technique in quicksort algorithm. The pivot is the median of the following three values: leftmost (numbers[i]), midpoint (numbers[(i+k)/2]) and rightmost (numbers[k]). You should modify the partition function given in section 21.5 to select the pivot using median-of-three technique
void Quicksort_medianOfThree(int numbers[], int i, int k){
    int pivotIndex = i;
    int pivotIndexSmall = (i+k)/2;
    int pivot = i;

	//find which is bigger (i or (i+k)/2)
    if(numbers[i] <= numbers[(i+k)/2]){
        pivotIndex = (i+k)/2;
        pivotIndexSmall = i;
    }
	
	//find how big k is compared to i and (i+k)/2 and set median to pivot
    if(numbers[k] <= numbers[pivotIndexSmall]){
        pivot = pivotIndexSmall;
    }else if(numbers[k] <= numbers[pivotIndex]){
        pivot = k;
    }else{
        pivot = pivotIndex;
    }

	//Set (i+k)/2 to pivot so can call Quicksort_midpoint
    if(pivot != (i+k)/2){
        int temp = numbers[pivot];
        numbers[pivot] = numbers[(1+k)/2];
        numbers[(i+k)/2] = temp;
    }

	
    Quicksort_midpoint(numbers, i, k);

}

//function sorts the given array using InsertionSort method. (implementation of this method is provided in section 21.3)
void InsertionSort(int numbers[], int size) {
  int i, j = 0;
  
  for(i = 1; i < size; i++) {
    j = i;
    while(j > 0 && numbers[j] < numbers[j - 1]) {
      swap(numbers[j], numbers[j - 1]);
      j--;
    }
  }
}

int main () {
  srand(time(0));

  const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
  int array1[NUMBERS_SIZE], array2[NUMBERS_SIZE], array3[NUMBERS_SIZE];

  fillArrays(array1, array2, array3);

  clock_t Start1 = clock();
  Quicksort_midpoint(array1, 0, NUMBERS_SIZE - 1);
  clock_t End1 = clock();

  int elapsedTime1 = (End1 - Start1)/CLOCKS_PER_MS;
  cout << "Quicksort_midpoint runtime: " << elapsedTime1 << " ms" << endl;

  clock_t Start2 = clock();
  Quicksort_medianOfThree(array2, 0, NUMBERS_SIZE);
  clock_t End2 = clock();
  
  int elapsedTime2 = (End2 - Start2)/CLOCKS_PER_MS;
  cout << "Quicksort_medianOfThree runtime: " << elapsedTime2 << " ms" << endl;


  clock_t Start3 = clock();
  InsertionSort(array3, NUMBERS_SIZE);
  clock_t End3 = clock();

  int elapsedTime3 = (End3 - Start3)/CLOCKS_PER_MS; 
  cout << "InsertionSort runtime: " << elapsedTime3 << " ms" << endl;
  
  
  return 0;
}
