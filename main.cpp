//Read in numbers and turn them into a heap
//Created by: Ethan Reese
//March 1, 2017

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

void addHeap(int element, int heap[128]);
void printHeap(int heap[128]);

using namespace std;

int main(){
     bool going = true;
     cout << "Enter your numbers and enter the character N when done." << endl;
     //Keep getting inputs until the user asks to stop
     int counter = 0;
     char* input;
     int heap[128] = { 0 };
     while(going){
          cout << "Number: ";
          input = new char[80];
          cin >> input;
          //If the user inputs the N then it needs to stop
          if(strcmp(input, "N") == 0){
               going = false;
               delete input;
               printHeap(heap);  
          }
          else if(counter == 100){
               going = false;
               delete input;
               printHeap(heap);  
          }
          else{
                  //put the input into a string stream to convert it into aninteger for comparison
                  stringstream convert;
                  convert << input;
                  int element = 0;
                  convert >> element;
                  counter++;
                  delete input;
                  addHeap(element, heap);
          }

     }
     return 0;
}

//Add an element to the preexisting heap
void addHeap(int element, int heap[128]){
     int index;
     //Loop through and find what the last index is
     for(int i = 1; i < 128; i++){
          if(heap[i] == 0){
               index = i;
               heap[i] = element;
               break;
          }
     }
     //If the index is too low to divide then it needs to break bc it will already be organized
     if(index == 1){
          return;
     }
     //Check if the parent located at k/2 index is smaller and if so swap them
     int parentIndex = (int)(index/2);
     //Keep going up the tree if the values above it are lower
     while(heap[parentIndex] < heap[index]){
          //Swap the values
          int temp = heap[parentIndex];
          heap[parentIndex] = heap[index];
          heap[index] = temp;
          //Make the indexes comensurate
          index = parentIndex;
          if(index == 1){
               break;
          }
          parentIndex = (index/2);
     }
}
//Print out the tree that the heap is based on
void printHeap(int heap[128]){
     //Loop through the tree and print out all of the values
     for(int i = 1; i < 128; i++){
          //If it gets past the point of the initialized array
          if(heap[i] == 0){
               return;
          }
          cout << "Parent: " << heap[i];
          if(heap[2*i] != 0){
               cout << " Left: " << heap[2*i];
          }
          if(heap[(2*i)+1] != 0){
               cout << " Right: " << heap[(2*i) + 1];
          }
          cout << endl;
     }
}
