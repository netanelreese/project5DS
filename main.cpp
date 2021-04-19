// Data Structures - Spring 2021
// Project 5
// project4_sampleCode.cpp

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
    // we want to retain the ordering of arr for shell sort
    for(int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before
            // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
    int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last

    // Start with a largest increment, then reduce by factors of 3
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i)
        {
            int temp = arr[i];
            j = i - inc;

            numComp++; // incrementing the number of comparisons done right before
            // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arr; // return the not necessarily sorted array = approximately sorted array

            while ((j >= 0) && (arr[j] > temp))
            {
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;

        numComp++; // incrementing the number of comparisons done right before
        // the if condition where the comparison happens each time
        if(numComp >= D) // checking for number of comparisons
            return arr; // return the not necessarily sorted array = approximately sorted array

        while ((j >= 0) && (arr[j] > temp))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
    return arr;
}
int* random_arr(int n, int l, int u) {
    int* randArr = new int[n];

    for(int i = 0; i < n; ++i) randArr[i] = rand() % u + l;

    return randArr;
}
int indexOf(int* arr, int n, int x) {
    int index;
    for (int i = 0; i < n; ++i) {
        if (x == arr[i]) {
            index = i;
        }
    }
    return index;
}
int numOfInversions(int* arr, int n) {
    int i = 0; //number of inversions for one number
    int iTotal = 0; //total number of inversions needed
    int temp;

    for (int i = 0; i < n; ++i) {
        temp = arr[i];
        for (int j = 0; j < n; ++j) {
            if (temp < arr[j]) {
                i++;
            }
        }
        iTotal += i;
        i = 0;
    }
    return iTotal;
}
int chebyshev_distance(int* unsorted, int* sorted, int n) {
    int distanceTemp = 0;
    int distance = 0;

    for(int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (sorted[i] != unsorted[j]) {
                distanceTemp++;
            }
        }
        distance = i - distanceTemp;
        if (distance < 0) {
            distance *= -1;
        }
    }

    return 0;
}
//main function
int main()
{
    int n;
    cin >> n; // read the number of elements
    cout << "Number of elements: " << n << endl;

    int s, l, u, D;

    int* A = new int[n];
    int* sorted = new int[n];
    int* bubble = new int[n];
    int* shell = new int [n];

    cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;

    // generate n random elements with the seed s, within the lower and upper range
    // store the randomly generated UNIQUE set of elements in an array 'A'


    for (int i = 0; i < n; ++i) A[i] = random_arr(n, l, u)[i];

    // you may use the unordered set to help generate unique elements

    cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
    for (int i = 0; i < n; ++i) cout << A[i] << ", ";
    cout << endl;
    // display the array A

    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result

    for (int i = 0; i < n; ++i) sorted[i] = bubbleSort(A, n, n*n)[i];

    cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
    // display the completely sorted array
    for (int i = 0; i < n; ++i) cout << sorted[i] << ", ";
    cout << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;
    for (int i = 0; i < n; ++i) bubble[i] = bubbleSort(A, n, D)[i];

    // display bubResult
    for (int i = 0; i < n; ++i) cout << bubble[i] << ", ";
    cout << endl;
    // find both the quality metrics for bubResult
    cout << "Number of Inversions: " << endl;
    cout << numOfInversions(bubble, n) << endl;
    cout << "Chebyshev distance: " << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
    for (int i = 0; i < n; ++i) shell[i] = shellSort(A, n, D)[i];
    for (int i = 0; i < n; ++i) cout << shell[i] << ", ";
    cout << endl;
    // display shellResult

    // find both the quality metrics for shellResult
    cout << "Number of Inversions: " << endl;
    cout << numOfInversions(shell, n) << endl;
    cout << "Chebyshev distance: " << endl;


    delete [] A;
    delete [] sorted;
    delete [] shell;
    delete [] bubble;

    return 0;
}
