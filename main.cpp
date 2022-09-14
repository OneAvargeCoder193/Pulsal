#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

std::vector<std::string> split(std::string text)
{
    std::vector<std::string> res;
    std::string temp;
    bool isstring = false;

    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == ' ' && !isstring || text[i] == '\n')
        {
            res.push_back(temp);
            temp = "";
        }
        else
        {
            if (text[i] == '"') isstring = !isstring;
            temp += text[i];
        }
    }

    res.push_back(temp);

    res.erase(std::remove_if(res.begin(), res.end(), [] (std::string s) { return s == ""; }), res.end());

    return res;
}

bool isvalidint(std::string str)
{
    int start = 0;
    int i;
    bool valid = true;  // assume a valid integer
    bool sign = false;  // assume no sign
    // Check for an empty string
    if (int(str.length()) == 0) valid = false;
    // Check for a leading sign
    if (str.at(0) == '-' || str.at(0) == '+')
    {
        sign = true;
        start = 1;  // start checking for digits after the sign
    }
    if (sign && int(str.length()) == 1)
        valid = false;
    i = start;
    while (valid && i < int(str.length()))
    {
        if (!isdigit(str.at(i)))
        valid = false;  //found a non-digit character
        i++;  // move to next character
    }
    return valid;
}

std::pair<std::string, std::vector<std::string>> parse(std::string inp, std::string res)
{
    std::ifstream file(inp);
    std::stringstream ss;
    ss << file.rdbuf();
    std::string code = ss.str();
    file.close();

    std::vector<std::string> toks = split(code);

    std::ifstream header("header.cpp");
    std::stringstream start;
    if (res != "") start << header.rdbuf() << "\n";
    header.close();

    std::stringstream imports;

    std::stringstream main;
    main << "int main(int argc, char* argv[]) {\n";

    bool infunc = false;
    
    std::vector<std::string> funcs;

    int strid = 0;

    int i = 0;
    while (i < toks.size())
    {
        std::string tok = toks[i];

        std::stringstream *res = &main;
        if (infunc) res = &start;

        if (isvalidint(tok))
        {
            *res << "push(" << std::stol(tok.c_str()) << ");\n";
        } else if (tok[0] == '\\' && tok.size() == 2)
        {
            *res << "push(" << (int)tok[1] << ");\n";
        } else if (tok[0] == '"' && tok[tok.length() - 1] == '"')
        {
            std::string str = tok.substr(1, tok.length() - 2);
            strid++;
            *res << "char str" << strid << "[] = \"" << str << "\";\n";
            *res << "push((long)&str" << strid << ");\n";
        } else if (tok == "at")
        {
            *res << "push((long)(*(char*)pop()));\n";
        } else if (tok == "setmem")
        {
            *res << "a = pop();\nb = pop();\n*((char*)a) = b;\n";
        } else if (tok == "include")
        {
            i++;
            std::string filename = toks[i];
            if (filename.find('.') != std::string::npos) filename.replace(filename.find("."), 1, "/");
            filename += ".psl";
            std::pair<std::string, std::vector<std::string>> inc = parse(filename, "");
            start << inc.first << "\n";
            funcs.insert(funcs.end(), inc.second.begin(), inc.second.end());
        } else if (tok == "ret")
        {
            *res << "return;\n";
        } else if (tok == "and")
        {
            *res << "push((pop() != 0?1:0) && (pop() != 0?1:0));\n";
        } else if (tok == "or")
        {
            *res << "push((pop() != 0?1:0) || (pop() != 0?1:0));\n";
        } else if (tok == "+")
        {
            *res << "a = pop(); b = pop(); push(a + b);\n";
        } else if (tok == "-")
        {
            *res << "a = pop(); b = pop(); push(b - a);\n";
        } else if (tok == "*")
        {
            *res << "a = pop(); b = pop(); push(a * b);\n";
        } else if (tok == "/")
        {
            *res << "a = pop(); b = pop(); push(b / a);\n";
        } else if (tok == "%")
        {
            *res << "a = pop(); b = pop(); push(b % a);\n";
        } else if (tok == ".")
        {
            *res << "std::cout << (char)pop() << std::flush;\n";
        } else if (tok == ",")
        {
            *res << "std::cout << pop() << std::flush;\n";
        } else if (tok == ":")
        {
            *res << "push(getch());\n";
        } else if (tok == ";")
        {
            *res << "push(getlong());\n";
        } else if (tok == "dup")
        {
            *res << "stack.push_back(stack.back());\n";
        } else if (tok == "swap")
        {
            *res << "a = pop(); b = pop(); push(a); push(b);\n";
        } else if (tok == "third")
        {
            *res << "a = *(stack.end() - 3);\nstack.erase(stack.end() - 3);\npush(a);\n";
        } else if (tok == "[")
        {
            *res << "do {\n";
        } else if (tok == "]")
        {
            *res << "} while (pop() != 0);\n";
        } else if (tok == "{")
        {
            *res << "if (pop() != 0) {\n";
        } else if (tok == "}")
        {
            *res << "}\n";
        } else if (tok == "inp")
        {
            *res << "getinp();\n";
        } else if (tok == "!")
        {
            *res << "push(pop() == 0 ? 1 : 0);\n";
        } else if (tok == "pop")
        {
            *res << "stack.pop_back();\n";
        } else if (tok == "==")
        {
            *res << "push(pop() == pop() ? 1 : 0);\n";
        } else if (tok == "<")
        {
            *res << "a = pop();\nb = pop();\npush(b < a ? 1 : 0);\n";
        } else if (tok == ">")
        {
            *res << "a = pop();\nb = pop();\npush(b > a ? 1 : 0);\n";
        } else if (tok == "<=")
        {
            *res << "a = pop();\nb = pop();\npush(b <= a ? 1 : 0);\n";
        } else if (tok == ">=")
        {
            *res << "a = pop();\nb = pop();\npush(b >= a ? 1 : 0);\n";
        } else if (tok == "e")
        {
            *res << "push(stack.size() == 0 ? 1 : 0);\n";
        } else if (tok == "~")
        {
            *res << "std::reverse(stack.begin(), stack.end());\n";
        } else if (tok == "quit")
        {
            *res << "exit(0);\n";
        } else if (tok == "func")
        {
            i++;
            std::string name = toks[i];
            start << "void " << name << "()";
            i++;
            if (toks[i] != "(")
            {
                start << ";\n";
                i--;
            } else {
                start << " {\n";
                infunc = true;
            }

            funcs.push_back(name);
        } else if (tok == ")")
        {
            infunc = false;
            start << "}\n";
        } else {
            if (std::count(funcs.begin(), funcs.end(), tok) != 0)
            {
                *res << tok << "();\n";
            } else {
                std::cout << "Unknown token: " << tok << std::endl;
            }
        }

        i++;
    }

    main <<
"return 0;\n"
"}";

    if (res != "")
    {
        std::ofstream f(res);
        f << imports.str();
        f << start.str() << "\n";
        f << main.str();
        f.close();
    }

    return std::make_pair(start.str(), funcs);
}

int main(int argc, const char *argv[])
{
    std::string res = argv[1];
    res.replace(res.find(".psl"), 4, ".cpp");
    parse(argv[1], res);

    std::string compcommand = "g++ " + res + " -o res -O2 -std=c++2a";

    system(compcommand.c_str());
    system("./res");
    // remove("res.cpp");

    return 0;
}