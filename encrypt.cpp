/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

char shift_value(char c, int shift_val);
std::string generate_token(int optional_seed);
char generate_proxy_val(int seed);

int main ()
{
    // init
    int resultCode = 0;
    ofstream  test_output;
    test_output.open("token.txt");

    // Create token to obfuscate encrypted message later
    std::string token = generate_token(0);

    // Get input message and populate buffer
    std::string input = "This is a big ass, motherfucking, test message.";
    std::string buffer = "";
    for(char c : input)
    {
        if(c != ' ' && c != ',' && c != '.') { buffer.append(1u, c); }
    }

    // Create shift_code and new random for this session
    srand(time(NULL));
    int seed_increment = rand() % 1000;
    std::string shift_code = "";

    for(char c : buffer)
    {
        shift_code.append(1u, generate_proxy_val(seed_increment));
        seed_increment++;
    }

    // create proxy message prior to obfuscating
    std::string proxy = "";

    for(int i = 0; i < shift_code.length(); i++)
    {
        char temp = shift_value(buffer[i], (int)shift_code[i]);
        test_output << temp;
        proxy.append(1u, temp);
    }


    test_output << "\n";
    for(char c : shift_code)
    {
        test_output << c;
    }
     
    // close out file handles and exit
    test_output.close();
    return resultCode;
}

char shift_value(char c, int shift_val)
{
    char temp = c + (shift_val - '0');
    if ( temp > 'Z' )
    {
        char roll_over = temp - 'Z';
        temp = '@' + roll_over;
    }

    return temp;
}



std::string generate_token(int optional_seed)
{
    if(!optional_seed)
    {
        srand(optional_seed);
    }
    else
    {
        srand(time(NULL));
    }
    
    return std::to_string(rand() % 100000); // generate 5-digit random number
}


char generate_proxy_val(int seed)
{
    char result = '0';
    
    // generate by seed, a digit between 1 and 9
    srand(time(NULL));
    int rando = rand() % 10;
    if(!rando && rando != 9) {rando++;}

    // char '0' = 48 in ASCII.
    // 48+1 = 49 in ASCII == '1' 
    return result + rando;
}