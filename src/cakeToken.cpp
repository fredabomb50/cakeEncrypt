#include <fstream>

using std::ofstream;
using std::to_string;
using std::stoi;

// argv[1] - *optional* Token to be shared and used. 
int main (int argc, char** argv)
{ 
    // init
    ofstream output;
    int res = 0, seed = 0;

    // validate arg
    seed = argc < 2 ? 0 : stoi(argv[1]);
    if(!seed) { srand(seed); } else { srand(time(NULL)); }
   
    // store token
    output.open("token.cake");
    output << to_string(rand() % 100000);

    // exit and close
    output.close();
    return res;
}