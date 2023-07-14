#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using std::ofstream;
using std::string;
using std::to_string;
using std::exception;
using std::ifstream;
using std::stringstream;


// declarations
char origin_value( char c, int shift_val );
string remove_filler_values( string message, string token );

/*
 argv[1] - Token used to decrypt. Can be a file path or number
 argv[2] - Path to text file to decrypt
 argv[3] - [optional]Filename for final output. Defaults to cake.txt
*/
int main (int argc, char** argv)
{ 
    // init
    int res = 0;
    ifstream input;
    stringstream buffer;

    // argc validation
    if (!(argc > 1)) { return res; }

    // argv[] usage
    string token = argv[1];
    string input_path = argv[2];
    string output_name = "cake.txt";

    // argv[3] validation
    if (argc > 2) { output_name = argv[3]; }
        

    // file handler validation    
    ofstream input_file, debug, output_file;
    try
    {
        debug.open("output_file.txt");
        input.open(input_path);
        buffer << input.rdbuf();
         
        output_file.open(output_name + ".txt");
        
    }
    catch ( exception failure )
    {
        debug << "ERROR:: Failed to open input or create output!";
        debug.close();
        return res;
    }

    // pull buffer into string for decryption
    string temp = buffer.str();

    // remove filler values
    string unobfuscated_text = remove_filler_values( temp, token );
    string final_result;
    for (int i = 0; i < unobfuscated_text.length() - 1; i++)
    {
        if ( i == 1 ) { continue; }

        if ( i % 2 == 0 )
        {
           final_result.append(1u, origin_value( unobfuscated_text[i], unobfuscated_text[i + 1] ) ); 
        }
    }
    
    output_file << final_result;
    debug << unobfuscated_text << "\n";
    
    // free memory and close
    input_file.close();
    output_file.close();
    debug.close();
    return 0;
}


char origin_value( char c, int shift_val )
{
    unsigned char temp = c - (shift_val - '0');
    char rollOver;

    if ( temp < 32 )
    {
        rollOver = 32 - temp;
        temp = 127 - rollOver;
    }

    return temp;
}

string remove_filler_values( string message, string token )
{
    string result = "";
    int tokenIndex = 0;
    int tokenCounter = 0;
    int messageIndex = 0;

    result.append(1u, message[messageIndex]);
    messageIndex++;

    while (messageIndex < message.length())
    {
        if (tokenIndex > (token.length() - 1))
        {
            tokenIndex = 0;
        }

        while(tokenCounter < (token[tokenIndex] - '0') && messageIndex < message.length())
        {
            messageIndex++;
            tokenCounter++;
        }
        tokenCounter = 0;
        result.append(1u, message[messageIndex]);
        tokenIndex++;
        messageIndex++;
        if ((messageIndex < message.length()))
        {
            result.append(1u, message[messageIndex]);
            messageIndex++;
        }
        else { break; }
    }

    result.append(1u, message[(message.length() - 1)]);

    return result;
}