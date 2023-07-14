#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using std::ofstream;
using std::string;
using std::to_string;
using std::stoi;

string generate_token(int optional_seed);

/*
 argv[1] - *optional* Token used to decrypt. 
*/
int main (int argc, char** argv)
{ 
    int seed;
    if (argc < 2 ) { seed = 0; }
    else { seed = stoi(argv[1]); }
    

    ofstream output;
    output.open("token.cake");
    output << generate_token(seed);

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
    
    // 5-digit random number
    return to_string(rand() % 100000); 
}