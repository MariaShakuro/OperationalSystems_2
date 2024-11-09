// Laba2.cpp: определяет точку входа для приложения.
#include "Laba2.h"
#include<thread>
#include<chrono>
using namespace std;


void MaxAndMin(int arr[],int size,int& max,int& min) {
   
    max = 0;
    min = 0;
    for (int i = 0; i < size;i++) {
    if (arr[i] > arr[max]) {
      max = i;
      }
   
     this_thread::sleep_for(chrono::milliseconds(7));
    
      if (arr[i] < arr[min]) {
      min = i;
      }
      
     this_thread::sleep_for(chrono::milliseconds(7));
    }
    cout <<"Max value " <<max <<" and min value  " <<min << endl;
    
}

void ArithmeticMean(int arr[],int size,int av) {
    int sum_ = 0;
    for (int i = 0; i < size;i++) {
        sum_ += arr[i];
        this_thread::sleep_for(chrono::milliseconds(12));
    }
    av = sum_ / size;
    cout <<"Arithmetic mean "<< av << endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int av;
    int max, min;
	int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int* arr = new int[size];

    cout << "Enter " << size << " elements of array:" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
    cout << "Elements of array: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    int average = sum / size;
    // Finding the indices of the maximum and minimum elements
    int maxIndex = 0, minIndex = 0;
    for (int i = 1; i < size; ++i) {
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    // Replacing the maximum and minimum elements with the average value
    arr[maxIndex] = average;
    arr[minIndex] = average;
    cout << "Changed array:";
    for (int i = 0; i < size;i++) {
        cout << arr[i]<<" ";
    }
    cout << endl;

    thread min_max([&]() {MaxAndMin(arr,size,max, min); });
    thread average_([&]() { ArithmeticMean(arr,size,av); });
  
    cout << "RESULTS:" << endl;
    min_max.join();
    average_.join();
	delete[]arr;
   

	return 0;
}
