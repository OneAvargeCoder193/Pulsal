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

void start();
void drawer();
void sink();
void chase();
void shrink();
void tower();
void start() {
char str1[] = "0: Check the drawers\n";
push((long)&str1);
print();
char str2[] = "1: Look through the sink\n";
push((long)&str2);
print();
push(getlong());
push(1);
push(pop() == pop() ? 1 : 0);
if (pop() != 0) {
sink();
return;
}
drawer();
return;
}
void drawer() {
char str3[] = "\nYou saw a long stick in the drawer.\nCould this be used anywhere?\n";
push((long)&str3);
print();
push(256);
start();
}
void shrink() {
char str4[] = "\nWith the shrinking device, you escape your cell.\n";
push((long)&str4);
print();
chase();
}
void chase() {
char str5[] = "You unshrink.\n";
push((long)&str5);
print();
char str6[] = "A guard notices you.\nDo you run away, or bribe him?\n";
push((long)&str6);
print();
char str7[] = "0: Run Away\n";
push((long)&str7);
print();
char str8[] = "1: Bribe\n";
push((long)&str8);
print();
push(getlong());
push(1);
push(pop() == pop() ? 1 : 0);
if (pop() != 0) {
char str9[] = "The guard doesn't accept your bribe.\nHe puts you in solitary confinement.\nGAME OVER\n";
push((long)&str9);
print();
exit(0);
}
char str10[] = "You manage to escape the guard.\n";
push((long)&str10);
print();
tower();
}
void tower() {
char str11[] = "There is a guard tower nearby.\nDo you sneak past,\nOr take him out?\n";
push((long)&str11);
print();
char str12[] = "0: Sneak past\n";
push((long)&str12);
print();
char str13[] = "1: Take out\n";
push((long)&str13);
print();
push(getlong());
push(1);
push(pop() == pop() ? 1 : 0);
if (pop() != 0) {
char str14[] = "You take out the guard.\nYou escape the prison and are now a free man.\n";
push((long)&str14);
print();
exit(0);
}
char str15[] = "You are noticed by the guard, who promptly sends you to solitary confinement.\n";
push((long)&str15);
print();
char str16[] = "GAME OVER\n";
push((long)&str16);
print();
}
void sink() {
push(256);
push(pop() == pop() ? 1 : 0);
if (pop() != 0) {
char str17[] = "\nYou used the stick you found to get the object out of the sink.\nIt seems to be a shrinking device.\n";
push((long)&str17);
print();
shrink();
return;
}
char str18[] = "\nThere seemed to be something at the back of the sink,\nBut you couldn't get it out\n";
push((long)&str18);
print();
start();
}

int main(int argc, char* argv[]) {
char str19[] = "ADVENTURE GAME\n\n";
push((long)&str19);
print();
char str20[] = "You are locked in a prison cell for a crime you didn't commit,\nYou must find a way to escape.\n";
push((long)&str20);
print();
start();
return 0;
}