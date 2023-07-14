#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using std::ofstream;
using std::string;
using std::to_string;
using std::exception;


// Encrypt
unsigned char shift_any_value(char c, int shift_val);
char shift_value(char c, int shift_val);
string generate_token(int optional_seed);
char generate_proxy_val(int seed);
char generate_obfuscating_val( int seed );

// Decrypt
string decrypt(string message, string token);
string remove_filler_values( string message, string token );
char origin_value( char c, int shift_val );

/*
 argv[1] - Token used to encrypt. Can be a file path or number
 argv[2] - Path to text file to encrypt
 argv[3] - [optional]Filename for .cake output. Defaults to safe-ish.cake
*/
int main ( int argc, char** argv )
{
    // init
    int res = 0;
    exception e_handler;

    // argc validation
    if (!(argc > 1)) { return res; }

    // argv[] usage
    string token = argv[1];
    string input_path = argv[2];
    string output_name = "safe-ish.cake";

    // argv[3] validation
    if (argc > 2) { output_name = argv[3]; }
        

    // file handler validation    
    ofstream input_file, debug, output_file;
    try
    {
        debug.open("output_file.txt");
        input_file.open(input_path);
        output_file.open(output_name + ".cake");
        
    }
    catch ( exception failure )
    {
        debug << "ERROR:: Failed to open input or output!";
        debug.close();
        return res;
    }
    

    // Create token to obfuscate encrypted message later
    string token = generate_token(0);

    // Get input message and populate buffer
    string input = "zxckjnalishfo98q34lkjna.sdc";
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

    string unobfuscated_text = remove_filler_values( encryptedMessage, token );
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


    // close out file handles and exit
    debug.close();
    output_file.close();
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


//end of file