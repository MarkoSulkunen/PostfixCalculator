#ifndef _STACK_H
#define _STACK_H

#include "Utility.h"

// Section 2.2:

typedef double Stack_entry;

const int maxstack = 1000;   //  small value for testing

class Stack {
public:
   Stack();
   bool empty() const;
   Error_code pop();
   Error_code top(Stack_entry &item) const;
   Error_code push(const Stack_entry &item);
   void print_contents();

private:
   int count;
   Stack_entry entry[maxstack];
};
#endif