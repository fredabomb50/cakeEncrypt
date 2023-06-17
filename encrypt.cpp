#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


#define ARRAY_SIZE(arr) ( sizeof(arr) / sizeof(arr[0]) ) 


std::string generate_token()
{
    srand(time(NULL));
    return std::to_string(rand() % 100000); // generate 5-digit random number
}


int main ()
{
    int resultCode = 0;
    ofstream  test_output;
    test_output.open("token.txt");


    std::string input = "This is a big ass, motherfucking, test message.";
    std::string buffer = "";
    for(char c : input)
    {
        if(c != ' ' && c != ',' && c != '.') { buffer.append(1u, c); }
    }

    test_output << buffer;

    // Create token to obfuscate encrypted message
    std::string token = generate_token();
    
    
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