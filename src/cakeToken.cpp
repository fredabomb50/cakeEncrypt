#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using std::ofstream;
using std::string;
using std::to_string;
using std::exception;

string generate_token(int optional_seed);

int main ()
{ 
    ofstream output;
    output.open("token.cake");
    output << generate_token(0);

    output.close();
    return 0;
}


string generate_token(int optional_seed)
{
    if(!optional_seed)
    {
        srand(optional_seed);
    }
    else
    {
        srand(time(NULL));
    }
    
    return to_string(rand() % 100000); // generate 5-digit random number
}