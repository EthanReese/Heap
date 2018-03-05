//Read in numbers and turn them into a heap
//Created by: Ethan Reese
//March 1, 2017

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>

void addHeap(int element, int heap[128]);
void printHeap(int heap[128]);
void destroyHeap(int heap[128]);

using namespace std;

int main(){
     bool going = true;
     //Keep getting inputs until the user asks to stop
     int counter = 0;
     char* input;
     int heap[128] = { 0 };
     cout << "Enter the character I if you would like to be prompted for input: " << endl;
     char* input_1;
     input_1 = new char[80];
     cin >> input_1;
     if(strcmp(input_1, "I") == 0){     
          cout << "Enter your numbers and enter the character N when done." << endl;
             while(going){
                  cout << "Number: ";
                  input = new char[80];
                  cin >> input;
                  //If the user inputs the N then it needs to stop
                  if(strcmp(input, "N") == 0){
                       going = false;
                       delete input;
                       printHeap(heap);
                       destroyHeap(heap);  
                  }
                  else if(counter == 100){
                       going = false;
                       delete input;
                       printHeap(heap);  
                  }
                  else if(strcmp(input, "0") == 0){
                       //If its zero is screws things up so just ignore it since its not in the range anyway.
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
     }
     else{
          cout << "Please enter the filename of the file you would like to read in: ";
          input = new char[1000];
          cin >> input;
          //Create a stream to open the file
          ifstream inFile;
          inFile.open(input);
          if(!inFile){
               return 1;
          }
          int x;
          while( inFile >> x){
               addHeap(x, heap);
          }
          printHeap(heap);
          destroyHeap(heap);
          delete input;
     }
     delete input_1;
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
//Take apart the heap piece by piece
void destroyHeap(int heap[128]){
     int max;
     int maxInd;
     while(heap[2] != 0){
          //Print out the root so that its output for sure.
          cout << heap[1] << endl;
          int parentInd = 1;
          int leftInd = 2;
          int rightInd = 3;
          //Remove the element that has been printed out
          while(heap[leftInd] != 0 || heap[rightInd] != 0){
               //Elevate the larger child and keep looping through
               if(heap[leftInd] >= heap[rightInd]){
                    heap[parentInd] = heap[leftInd];
                    heap[leftInd] = 0;
                    parentInd = leftInd;
               }
               else if(heap[rightInd] > heap[leftInd]){
                    heap[parentInd] = heap[rightInd];
                    heap[rightInd] = 0;
                    parentInd = rightInd;
               }
               //If they're equal check which has the biggest next child
               else{
                    max = 0;
                    maxInd = 0;
                    //If none of them have any children it will just default to left bc it doesn't matter
                    if(heap[(leftInd*2)] >= max){
                         max = heap[(leftInd*2)];
                         maxInd = leftInd;
                    }
                    if(heap[((leftInd*2)+1)] > max){
                         max = heap[((leftInd*2)+1)];
                         maxInd = leftInd; 
                    }
                    if(heap[(rightInd*2)] > max){
                         max = heap[(rightInd*2)];
                         maxInd = rightInd;
                    }
                    if(heap[((rightInd*2)+1)] > max){
                         max = heap[((rightInd*2)+1)];
                         maxInd = rightInd;
                    }
                    heap[maxInd] = 0;
                    parentInd = maxInd;
               }
               //Adjust the child measurments
               leftInd = 2*parentInd;
               rightInd = (2*parentInd)+1;
          }
     }
     cout << heap[1] << endl;
}
