#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using std::ofstream;
using std::string;
using std::to_string;


unsigned char shift_value(char c, int shift_val);
string generate_token(int optional_seed);
char generate_proxy_val(int seed);

int main ()
{
    // init
    int resultCode = 0;
    ofstream  test_output;
    test_output.open("token.txt");

    // Create token to obfuscate encrypted message later
    string token = generate_token(0);

    // Get input message and populate buffer
    string input = "This Is a PARTICULArly LARGE MESSAGE with emphasis on dynamically typed capitalizetion. (in others, it is dummy THICC)";
    string buffer = "";
    for(char c : input)
    {
        if( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ) { buffer.append(1u, c); }
    }

    // Create shift_code
    int seed = 100;
    string shift_code = "";
    for(char c : buffer)
    {
        shift_code.append(1u, generate_proxy_val(seed));

        // new random val
        srand(seed++);
        seed = rand() % 1000;
    }

    // create proxy message prior to obfuscating
    string proxy = "";
    for(int i = 0; i < shift_code.length(); i++)
    {
        unsigned char temp = shift_value(buffer[i], shift_code[i]);
        proxy.append(1u, temp);
    }

     test_output << "\n" << shift_code;

    // close out file handles and exit
    test_output.close();
    return resultCode;
}


unsigned char shift_value(char c, int shift_val)
{
    // TODO (Luis): consider adding a randomized boolean of some kind, maybe check if a randomly generated val between 0 and 100 is less than 50, 
    // to then randomly change a value from uppercase to lowercase and vice-versa
    unsigned char temp = c + (shift_val - '0');
    char rollOver;
    if (c > 'Z')
    {
        if (temp > 'z')
        {
            rollOver = temp - 'z';
            temp = rollOver + '`';
        }
        // no rollover needed, within bounds.
    }
    else
    {
        if(temp > 'Z')
        {
            rollOver = temp - 'Z';
            temp = rollOver + '@';
        }
    }

    return temp;
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


char generate_proxy_val(int seed)
{
    char result = '0';
    
    // generate by seed, a digit between 1 and 9
    srand(seed);
    int rando = rand() % 10;
    if(!rando && rando != 9) {rando++;}

    // char '0' = 48 in ASCII.
    // 48+1 = 49 in ASCII == '1' 
    return result + rando;
}


//end of file