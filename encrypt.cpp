#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using std::ofstream;
using std::string;
using std::to_string;

// Encrypt
unsigned char shift_any_value(char c, int shift_val);
char shift_value(char c, int shift_val);
string generate_token(int optional_seed);
char generate_proxy_val(int seed);
char generate_obfuscating_val( int seed );

// Decrypt
string decrypt(string message, string token);
string remove_filler_values( string message, string token );


int main ()
{
    // init
    int resultCode = 0;
    ofstream  test_output, finalOutput;
    test_output.open("token.txt");
    finalOutput.open("encrypted.txt");

    // Create token to obfuscate encrypted message later
    string token = generate_token(0);

    // Get input message and populate buffer
    string input = "tezties!";
    string buffer = "";
    for(char c : input)
    {
        // if( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ') )
        buffer.append(1u, c);
    }

    // Create shift_code
    int seed = 100;
    string shift_code = "";
    for(char c : buffer)
    {
        srand(seed++);
        seed = rand() % 1000;

        // check for a space, and ignore
        // if (c == ' ') { shift_code.append(1u, c);  continue;}
        shift_code.append(1u, generate_proxy_val(seed));
    }

    // create proxy message prior to obfuscating
    string proxy = "";
    for(int i = 0; i < shift_code.length(); i++)
    {
        char temp = shift_value(buffer[i], shift_code[i]);
        proxy.append(1u, temp);
    }


    string encryptedMessage;
    seed = 100;
    int tokenPosition = 0;
    for ( int i = 0; i < proxy.length(); i++ )
    {
        // check if we have exceeded token, at which point loop back to start of token
        if ( tokenPosition > token.length() ) {tokenPosition = 0;}
        encryptedMessage.append(1u, proxy[i] );

        // obfuscate 
        for (int k = 1; k <= (token[tokenPosition] - '0'); k++)
        {
            srand(seed + rand() % 1000);
            seed = rand();
            encryptedMessage.append(1u, generate_obfuscating_val( seed ) );
        }
        
        encryptedMessage.append(1u, shift_code[i] );
        tokenPosition++;
    }

    test_output << token << "\n";
    test_output << shift_code << "\n";
    test_output << proxy << "\n";
    finalOutput << encryptedMessage;
    test_output << remove_filler_values( encryptedMessage, token );

    // close out file handles and exit
    test_output.close();
    finalOutput.close();
    return resultCode;
}


char shift_value(char c, int shift_val)
{
    unsigned char temp = c + (shift_val - '0');
    char rollOver;

    if ( temp > 126 )
    {
        rollOver = temp - 126;
        temp = rollOver + 31;
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


// min + (rand() % (int)(max - min + 1))
char generate_obfuscating_val( int seed )
{
    srand(seed);

    int temp = rand() % 101;
    if( temp > 0 && temp < 33 ) { temp = ('A' + ( rand() % ('Z' - 'A' + 1) )); }
    else if( temp > 33 && temp < 66 ) { temp = ('a' + ( rand() % ('z' - 'a' + 1) )); }
    else if( temp > 66 && temp < 101 ) { temp = ('0' + ( rand() % ('9' - '0' + 1) )); }
    else { temp = 63; }
    

    return char(temp);
}


string decrypt(string message, string token)
{
    return "yiy";
}


// fuck this shjit is fucking fucked
string remove_filler_values( string message, string token )
{
    string result = "";
    int tokenIndex = 0;
    int tokenCounter = 0;

    result.append(1u, message[0]);

    for( int i = 1; i < message.length(); i++ )
    {
        if (i != 1) { result.append(1u, message[i]); }

        while( tokenCounter <= (token[tokenIndex] - '0') )
        {
            i++;
            tokenCounter++;
        }

        result.append(1u, message[i]);
        if ( tokenIndex < token.length() ) { tokenIndex++; }
        else { tokenIndex = 0; }

        tokenCounter = 0;
    }

    return result;
}


//end of file