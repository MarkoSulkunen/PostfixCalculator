/*********************************************************************

 1.  NAME
       PostfixCalculator.cpp

 2.  DESCRIPTION
       Reverse polish notation, the operators follow their operands

 3.  VERSIONS
       Original:
         07.03.2022 / Marko Sulkunen

**********************************************************************/

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/

#include "Stack.h"
#include "Stack.cpp"

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

void introduction();
void instructions();
char getCommand();
bool doCommand(char command, Stack &numbers);
double sumStack(Stack &numbers);
int countStack(Stack &numbers);

/*********************************************************************
*    MAIN PROGRAM                                                    *
**********************************************************************/

int main()
{
  Stack storedNumbers;
  introduction();
  instructions();
  while (doCommand(getCommand(), storedNumbers));
}

/*********************************************************************
  F U N C T I O N    D E S C R I P T I O N
---------------------------------------------------------------------
 NAME: getCommand
 DESCRIPTION: Asks command character from user and returns given 
              character.

 Input: void
 Output: character
*********************************************************************/

char getCommand()
{
  char command;
  bool waiting = true;
  cout << "Select command and press < Enter > :";
  while (waiting) 
    {
      cin >> command;
      command = tolower(command);
      if (command == '?' || command == '=' || command == '+' ||
          command == '-' || command == '*' || command =='/' ||
          command ==  'x' || command == 's' || command == 'a' ||
          command == 'q')
        waiting = false;
      else 
        {
          cout << "Please enter a valid command:" << endl;
          cout << "[Q] quit." << endl;
          cout << "[?] push to stack." << endl;
          cout << "[=] print top" << endl;
          cout << "[+] [-] [*] [/] are arithmetic operations." << endl;
          cout << "[X] stack element exchange" << endl;
          cout << "[S] sum of the stack" << endl;
          cout << "[A] average of the stack \n" << endl;
        }
    }
  return command;
}

/*********************************************************************
  F U N C T I O N    D E S C R I P T I O N
---------------------------------------------------------------------
 NAME: doCommand
 DESCRIPTION: The first parameter specifies a valid calculator command.
              The command specified by the first parameter has been applied 
              to the Stack of numbers given by the second parameter. 
              A result of true is returned unless command == 'q'.
 Input: char command, Stack &numbers
 Output: bool
*********************************************************************/

bool doCommand(char command, Stack &numbers)
{ 
  double p, q;
  int counter;

  switch (command) 
    {
      /* enter an integer onto a stack */
      case '?':
        cout << "Enter a real number: " << flush; 
        cin >> p;

        if (numbers.push(p) == overflow)
          {
            cout << "Warning: Stack full, lost number" << endl; 
          }

        break;
      
      /* print the top integer in the stack */
      case '=':
        if (numbers.top(p) == underflow)
          {
            cout << "Stack empty" << endl;
          }
        else
          {
            cout << p << endl;
          }

        break;

      /* addition operation */
      case '+':
        if (numbers.top(p) == underflow)
          {
            cout << "Stack empty" << endl;
          }
        else 
          {
            numbers.pop();
            if (numbers.top(q) == underflow) 
              {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
              }
            else 
              {
                numbers.pop();
                if (numbers.push(q + p) == overflow)
                  cout << "Warning: Stack full, lost result" << endl;
              }
          } 

        break;

      /* subtraction operation */
      case '-':
        if(numbers.top(p) == underflow)
          {
            cout << "Stack empty" << endl;
          }
        else
          {
            numbers.pop();
            if(numbers.top(q) == underflow)
              {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
              }
            else
              {
                numbers.pop();
               if(numbers.push(q - p) == overflow)
                 {
                   cout << "Warning: Stack full, lost result" << endl;
                 }
              }
          }

        break;

      /* multiplication operation */
      case '*':
        if(numbers.top(p) == underflow)
          {
            cout << "Stack empty" << endl;
          }
        else
          {
            numbers.pop();
            if(numbers.top(q) == underflow)
              {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
              }
            else
              {
                numbers.pop();
                if(numbers.push(q * p) == overflow)
                  {
                    cout << "Warning: Stack full, lost result" << endl;
                  }
              }
          }

        break;

      /* division operation */
      case '/':
        if(numbers.top(p) == underflow)
          {
            cout << "Stack empty" << endl;
          }
        else if(p == 0.0)
          {
            cerr << "Division by 0 fail" << endl;
            numbers.push(p);
          }
        else
          {
            numbers.pop();
            if(numbers.top(q) == underflow)
              {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
              }
            else
              {
                numbers.pop();
                if(numbers.push(q / p) == overflow)
                  {
                    cout << "Warning: Stack full, lost result" << endl;
                  }
              }
          }

        break;

      /* stack element exchange */
      case 'x':
        if(numbers.top(p) == underflow)
          {
            cout << "Stack empty" << endl;
          }
        else
          {
            numbers.pop();
            if(numbers.top(q) == underflow)
              {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
              }
            else
              {
                numbers.pop();
                if(numbers.push(p) == overflow)
                  {
                    cout << "Warning: Stack full, lost result" << endl;
                  }
                if(numbers.push(q) == overflow)
                  {
                    cout << "Warning: Stack full, lost result" << endl;
                  }
              }
          }

        break;

      /* sum of the stack */
      case 's':
        p = sumStack(numbers);
        if(numbers.push(p) == overflow)
          {
            cout << "Warning: Stack full, lost result" << endl;
          }

        break;

      /* average of the stack */
      case 'a':
        p = sumStack(numbers);
        counter = countStack(numbers);
        
        if(counter <= 0)
          {
            cout << "Stack empty" << endl;
          }
        else if(numbers.push(p / ((double)counter)) == overflow)
          {
            cout << "Warning: Stack full, lost result" << endl;
          }

        break;

      /* quit */
      case 'q': 
        cout << "Calculation finished.\n";
        return false;
    } 

  return true; 
}

/*********************************************************************
  F U N C T I O N    D E S C R I P T I O N
---------------------------------------------------------------------
 NAME: introduction
 DESCRIPTION: displays program introduction

 Input: void
 Output: void
*********************************************************************/

void introduction()
{
  cout << "Postfix calculator \n\n" << endl;
}

/*********************************************************************
  F U N C T I O N    D E S C R I P T I O N
---------------------------------------------------------------------
 NAME: instructions
 DESCRIPTION: displays program instructions

 Input: void
 Output: void
*********************************************************************/

void instructions()
{
  cout << "Valid commands:" << endl;
  cout << "[Q] quit." << endl;
  cout << "[?] push to stack." << endl;
  cout << "[=] print top" << endl;
  cout << "[+] [-] [*] [/] are arithmetic operations." << endl;
  cout << "[X] stack element exchange" << endl;
  cout << "[S] sum of the stack" << endl;
  cout << "[A] average of the stack \n" << endl;
}

/*********************************************************************
  F U N C T I O N    D E S C R I P T I O N
---------------------------------------------------------------------
 NAME: sumStack
 DESCRIPTION: calculates sum of stack elements and returns result

 Input: Stack &numbers
 Output: double
*********************************************************************/

double sumStack(Stack &numbers)
{
  double p, sum = 0.0;
  Stack copy;

  /* while stack is not empty sum stack elements */
  while(!numbers.empty())
    {
      numbers.top(p);
      copy.push(p);
      sum += p;
      numbers.pop();
    }

  /* push copied stack values back to original stack */
  while(!copy.empty())
    {
      copy.top(p);
      numbers.push(p);
      copy.pop();
    }

  return sum;
}

/*********************************************************************
  F U N C T I O N    D E S C R I P T I O N
---------------------------------------------------------------------
 NAME: countStack
 DESCRIPTION: counts stack elements and returns result of count

 Input: Stack &numbers
 Output: int
*********************************************************************/

int countStack(Stack &numbers)
{
  double p;
  int count = 0;
  Stack copy;

  /* counts stack elements while stack is not empty */
  while(!numbers.empty())
    {
      numbers.top(p);
      copy.push(p);
      count++;
      numbers.pop();
    }

  /* push copied stack values back to original stack */
  while(!copy.empty())
    {
      copy.top(p);
      numbers.push(p);
      copy.pop();
    }

  return count;
}