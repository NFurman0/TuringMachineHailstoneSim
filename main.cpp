#include <iostream>
#include <bitset>
#include <bits/stdc++.h> 
using namespace std;

char *turingMachine;
int pointer = 0;
int length = 0;
int extraBuffer = 16;

void printMachine() {
  cout << "[";
  for(int i = 0; i < length-1; i++) {
    cout << turingMachine[i] << ", ";
  }
  cout << turingMachine[length-1] << "]\nPointer at " << pointer << endl;
}

void halt() {
  printMachine();
  cout << "Halted.";
  exit(0);
}

void rightShift() {
  char temp1 = '2';
  char temp2 = '2';
  for(int i = 0; i < length-1; i++) {
    temp2 = turingMachine[i+1];
    turingMachine[i+1] = temp1;
    temp1 = temp2;
  }
  pointer++;
}

void div2() {
  turingMachine[pointer] = '2';
  pointer--;
}

void mult2() {
  pointer++;
  turingMachine[pointer] = '0';
}

void searchRight() {
  pointer++;
  search:
  if(turingMachine[pointer] == '0' || turingMachine[pointer] == '1') {
    pointer++;
    goto search;
  }
  if(turingMachine[pointer] == '2') {
    pointer--;
  }
}

void checkHalt() {
  pointer--;
  if(turingMachine[pointer] == '0' || turingMachine[pointer] == '1') {
    pointer++;
  }
  else if(turingMachine[pointer] == '2') {
    halt();
  }
}

void mult3Add1() {
  mult2();
  turingMachine[pointer] = '1';
  
  multLoop1: //Used when not carrying the 1
  //printMachine();
  pointer--;
  if(turingMachine[pointer] == '0') {
    goto multLoop1;
  }
  if(turingMachine[pointer] == '1') {
    pointer++;
    if(turingMachine[pointer] == '0') {
      turingMachine[pointer] = '1';
      pointer--;
      goto multLoop1;
    }
    else if(turingMachine[pointer] == '1') {
      turingMachine[pointer] = '0';
      pointer--;
      turingMachine[pointer] = '0';
      goto multLoop2;
    }
  }
  if(turingMachine[pointer] == '2') return;

  multLoop2: //Used when carrying the 1
  //printMachine();
  pointer--;
  if(turingMachine[pointer] == '0' || turingMachine[pointer] == '2') {
    turingMachine[pointer] = '1';
    goto multLoop1;
  }
  if(turingMachine[pointer] == '1') {
    pointer++;
    turingMachine[pointer] = '1';
    pointer--;
    turingMachine[pointer] = '0';
    goto multLoop2;
  }
}

void hailstone() {
  hailstone:
  if(pointer < length - 3) {
    rightShift();
  }
  printMachine();
  if(turingMachine[pointer] == '0') {
    div2();
    checkHalt();
    goto hailstone;
  }
  if(turingMachine[pointer] == '1') {
    mult3Add1();
    searchRight();
    goto hailstone;
  }
}

int main() {
  cout << "Please enter the test number: ";
  int testNum;
  cin >> testNum;
  if(testNum == 0) length = 3+extraBuffer;
  else length = 3 + extraBuffer + (int)log2(testNum);
  turingMachine = new char[length];

  for(int i = 0; i < length; i++) {
    turingMachine[i] = '2';
  }

  string binary = bitset<32>(testNum).to_string().substr((34+extraBuffer)-length);
  pointer = length-3-binary.size();

  for(int i = 0; i < binary.size(); i++) {
    turingMachine[pointer] = binary.at(i);
    pointer++;
  }
  pointer--;

  hailstone();
}
