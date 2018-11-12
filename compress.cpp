#include "HCTree.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {

    ifstream inFile;
    unsigned char nextChar;
    vector<int> vect = vector<int>(256, 0);

    inFile.open( argv[1] );
    while( 1 ) {
        nextChar = inFile.get();
        if( inFile.eof() ) break;

        ++vect[(int)nextChar]; 
     }
     cout << endl;
     inFile.close();

    HCTree tree;
    tree.build( vect );
  
    ofstream oFile;
    oFile.open( argv[2] );
    
    for(int i = 0; i < 256; ++i) {
      oFile << vect[i] << endl;
    }

    inFile.open( argv[1] );

    while( 1 ) {
      nextChar = inFile.get();
      if( inFile.eof() ) break;
      tree.encode( nextChar, oFile );

    }
    tree.printOut();
    inFile.close();
    oFile.close();
}

 
