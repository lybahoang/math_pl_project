#include "Lexer.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

string fileToString(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error: Cannot open file\n";
        exit(EXIT_FAILURE);
    }

    ostringstream ss;
    ss << file.rdbuf(); // Read the entire file buffer into the stream
    return ss.str();    // Convert stream to string
}

int main()
{
    const string filePath = "H:/My Drive/University/TROYCS/8 Spring 2026 (2025.2)/CS 370/project/math_pl_project/source.dsl";
    Lexer lexer(fileToString(filePath));
    lexer.displayTokens();
    
    return 0;
}