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
void print() {
push(1);
a = pop(); b = pop(); push(b - a);
do {
push(1);
a = pop(); b = pop(); push(a + b);
stack.push_back(stack.back());
push((long)(*(char*)pop()));
stack.push_back(stack.back());
std::cout << (char)pop() << std::flush;
push(256);
a = pop(); b = pop(); push(b % a);
} while (pop() != 0);
stack.pop_back();
}
void strlen() {
stack.push_back(stack.back());
push(1);
a = pop(); b = pop(); push(b - a);
do {
push(1);
a = pop(); b = pop(); push(a + b);
stack.push_back(stack.back());
push((long)(*(char*)pop()));
push(256);
a = pop(); b = pop(); push(b % a);
} while (pop() != 0);
a = pop(); b = pop(); push(a); push(b);
a = pop(); b = pop(); push(b - a);
}
void strend() {
strlen();
a = pop(); b = pop(); push(a + b);
push(1);
a = pop(); b = pop(); push(b - a);
}
void charat() {
a = pop(); b = pop(); push(a); push(b);
stack.push_back(stack.back());
a = *(stack.end() - 3);
stack.erase(stack.end() - 3);
push(a);
a = pop(); b = pop(); push(a + b);
push((long)(*(char*)pop()));
}
void setchar() {
a = pop(); b = pop(); push(a); push(b);
a = *(stack.end() - 3);
stack.erase(stack.end() - 3);
push(a);
stack.push_back(stack.back());
a = *(stack.end() - 3);
stack.erase(stack.end() - 3);
push(a);
a = pop(); b = pop(); push(a + b);
a = *(stack.end() - 3);
stack.erase(stack.end() - 3);
push(a);
a = pop(); b = pop(); push(a); push(b);
a = pop();
b = pop();
*((char*)a) = b;
}
void strcat() {
a = pop(); b = pop(); push(b - a);
}


int main(int argc, char* argv[]) {
char str1[] = "";
push((long)&str1);
push(10);
a = pop(); b = pop(); push(b % a);
push(1);
a = pop(); b = pop(); push(a + b);
stack.push_back(stack.back());
std::cout << pop() << std::flush;
do {
stack.push_back(stack.back());
char str2[] = "Choose a number (1 - 10): ";
push((long)&str2);
print();
push(getlong());
stack.push_back(stack.back());
a = *(stack.end() - 3);
stack.erase(stack.end() - 3);
push(a);
a = pop();
b = pop();
push(b < a ? 1 : 0);
if (pop() != 0) {
char str3[] = "The number is greater than your guess.\n";
push((long)&str3);
print();
}
stack.push_back(stack.back());
a = *(stack.end() - 3);
stack.erase(stack.end() - 3);
push(a);
a = pop();
b = pop();
push(b > a ? 1 : 0);
if (pop() != 0) {
char str4[] = "The number is smaller than your guess.\n";
push((long)&str4);
print();
}
push(pop() == pop() ? 1 : 0);
} while (pop() != 0);
return 0;
}