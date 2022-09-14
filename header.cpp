#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <any>
#include <iomanip>
#include <cmath>

#ifdef _WIN32
#include <conio.h>

long getch()
{
    return _getch();
}
#else
#include <termios.h>

long getch()
{
    long ch;
    struct termios oldt, newt;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(0, TCSANOW, &oldt);
    return ch;
}
#endif

bool isvalidlong(std::string str)
{
   long start = 0;
   long i;
   bool valid = true;  // assume a valid longeger
   bool sign = false;  // assume no sign
   // Check for an empty string
   if (str.length() == 0) return false;
   // Check for a leading sign
   if (str.at(0) == '-' || str.at(0) == '+')
   {
       sign = true;
       start = 1;  // start checking for digits after the sign
   }
   if (sign && long(str.length()) == 1)
       valid = false;
   i = start;
   while (valid && i < long(str.length()))
   {
   if (!isdigit(str.at(i)))
       valid = false;  //found a non-digit character
       i++;  // move to next character
   }
   return valid;
}

long getlong()
{
    std::string inp;
    std::getline(std::cin, inp);
    while (!isvalidlong(inp))
    {
        std::getline(std::cin, inp);
    }
    return std::stol(inp);
}

std::vector<long> stack;
long a, b;

void push(long x)
{
    stack.push_back(x);
}

long pop()
{
    long x = stack.back();
    stack.pop_back();
    return x;
}

std::string getinp() {
    std::string inp;
    std::getline(std::cin, inp);
    
    push((long)(inp.c_str()));

    return inp;
}