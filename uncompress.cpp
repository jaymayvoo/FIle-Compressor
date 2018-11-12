#include "HCTree.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    ifstream inFile;
    unsigned char nextChar;
    vector<int> vect = vector<int>(256, 0);

    inFile.open( argv[1] );
    string line;
    for( int i = 0; i < 256; i++ ) {
      getline(inFile, line);
      vect[i] = stoi(line);
    }

    ofstream oFile;
    oFile.open( argv[2] );

    HCTree tree;
    tree.build(vect);
    int symbol;
    while( 1 ) {
      oFile << "run while loop ";
      if( inFile.eof() ) break;
      symbol = tree.decode( inFile ); 
      oFile << symbol << " ";
    }

    return 0;
 }
