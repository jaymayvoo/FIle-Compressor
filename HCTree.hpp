#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include <stack>
#include <fstream>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <iostream>

using namespace std;

class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;

    void deleteAll(HCNode* n) {
      if( n == nullptr )
        return;

      deleteAll(n->c0);
      deleteAll(n->c1);
      
      delete n;
    }
  
  void printOutHelper(HCNode* n, int indent) {
     if( n == nullptr )
       return;

    
    for( int i = 0; i < indent; i++ ) {
        cout << "| ";
      }
      cout << *n << endl;

      printOutHelper(n->c0, indent+1);
      printOutHelper(n->c1, indent+1);
    }

public:
    explicit HCTree() : root(0) {
        leaves = vector<HCNode*>(256, (HCNode*) 0);
    }

    ~HCTree();

    void build(const vector<int>& freqs);

    void encode(byte symbol, ofstream& out) const;

   int decode(ifstream& in) const;

    void printOut() {
      printOutHelper(root, 0);
    }
};

#endif // HCTREE_H
