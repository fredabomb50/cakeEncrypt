#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <exception>

using std::ofstream;
using std::string;
using std::to_string;
using std::exception;
using std::ifstream;
using std::stringstream;
using std::stoi;

// Encrypt
char shift_value(char c, int shift_val);
char generate_proxy_val(int seed);
char generate_obfuscating_val( int seed );


/*
 argv[1] - Token used to encrypt. Can be a file path or number
 argv[2] - Path to text file to encrypt
 argv[3] - [optional]Filename for .cake output. Defaults to safe-ish.cake
*/
int main ( int argc, char** argv )
{
    // init
    int res = 0;
    ifstream input, token_stream;
    token_stream.exceptions(ifstream::failbit | ifstream::badbit);
    stringstream input_buffer, token_buffer;

    // argc validation
    if (!(argc > 1)) { return res; }

    string token = "32165";
    try
    {
        // if the token arg can't be converted to an integer, it may be the file path to one
        if ( stoi(argv[1]) ) { token = argv[1]; }
    }
    catch (std::invalid_argument invalid)
    { 
        // try to read arg as a file path containing the token
        try
        {
            token_stream.open(argv[1]);
            token_buffer << token_stream.rdbuf();
            token = token_buffer.str();
        }
        catch(ifstream::failure read_fail) { return 0; }
    }

    string input_path = argv[2];
    string output_name = "safe";

    // argv[3] validation
    if (argc > 3) { output_name = argv[3]; }
        

    // file handler validation    
    ofstream input_file, debug, output_file;
    try
    {
        debug.open("output_file.txt");
        input.open(input_path);
        input_buffer << input.rdbuf();
        output_file.open(output_name + ".cake");
        
    }
    catch ( exception failure )
    {
        debug << "ERROR:: Failed to open input or create output!";
        debug.close();
        return res;
    }

    // Get input message
    string input_string = input_buffer.str();


    // Create shift_code
    int seed = 100;
    string shift_code = "";
    for(char c : input_string)
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
        char temp = shift_value(input_string[i], shift_code[i]);
        proxy.append(1u, temp);
    }


    string encryptedMessage;
    seed = 100;
    int tokenPosition = 0;
    for ( int i = 0; i < proxy.length(); i++ )
    {
        // check if we have exceeded token, at which point loop back to start of token
        if ( tokenPosition > token.length() - 1 ) {tokenPosition = 0;}
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

    output_file << encryptedMessage;

    // close out file handles and exit
    debug.close();
    output_file.close();
    input_file.close();
    return res;
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

//end of file