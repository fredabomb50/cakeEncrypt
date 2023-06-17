#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


#define ARRAY_SIZE(arr) ( sizeof(arr) / sizeof(arr[0]) ) 


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
//3161517655311334589161231771536838469

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

    // Create proxy and new random for this session
    srand(time(NULL));
    int seed_increment = rand() % 1000;
    std::string proxy = "";

    for(char c : buffer)
    {
        char temp = generate_proxy_val(seed_increment);
        test_output << temp;
        proxy.append(1u, temp);
        seed_increment++;
    }

    //test_output << input << "\n" << buffer << "\n" << proxy;

    
    
    // close out file handles and exit
    test_output.close();
    return resultCode;
}

/*
    char input[] = "This is my test message. Hallelujah";
    char salt[] = ""; // randomized numbers array for character shifting
    char proxy_message[] = ""; // input message after having been shifted by salt

    // 1 - remove spaces/punctuations

    for(int i = 0; i <= ARRAY_SIZE(input); i++)
    {

    }
*/