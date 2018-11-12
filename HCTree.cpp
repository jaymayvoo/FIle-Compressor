#include "HCTree.hpp"

typedef std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> node_PQ;

void HCTree::build(const vector<int> & freqs) {
  // Create MinHeap
  node_PQ nodeMinHeap;
  // For every present letter, add to the minHeap
  for( unsigned int i = 0; i < freqs.size(); i++ ) {
    if( freqs[i] > 0 ) {
      byte symbol = i;
      HCNode* newNode = new HCNode( freqs[i], symbol, nullptr, nullptr, nullptr );
      nodeMinHeap.push( newNode );
      leaves[i] = newNode;
    }
  }

  // Take the two lowest node and create parent node and link everything.
  while( !nodeMinHeap.empty() ) {
    HCNode* child0 = nodeMinHeap.top();
    nodeMinHeap.pop();
    // If there is only one node left it is the root. There are no more nodes
    // to add to the tree.
    if( nodeMinHeap.empty() ) {
      root = child0;
    } else {
      HCNode* child1 = nodeMinHeap.top();
      nodeMinHeap.pop();
      // Make new parent node
      int nCount = child0->count + child1->count;
      byte nSymb = child0->symbol;
      HCNode* nParent = new HCNode( nCount, nSymb, child0, child1, nullptr);
      child0->p = nParent;
      child1->p = nParent;
      nodeMinHeap.push(nParent);
    }
  }
  return;
}

void HCTree::encode(byte symbol, ofstream& out) const {
  int index = (int)symbol;
  HCNode* curr = leaves[index];
  HCNode* parent = curr->p;
  stack<char> code; 
  while( curr->p != nullptr ) {
      if (curr == parent->c0)
          code.push('0');
      else 
          code.push('1');

     curr = parent;
     parent = curr->p;
    }

   while( !code.empty() ) {
      out << code.top();
      code.pop();
   }
}

int HCTree::decode( ifstream& in ) const  {
  unsigned char nextChar = 0;
  HCNode* curr = root;
  while( 1 ) {
    nextChar = in.get();
    if( in.eof() ) break;
    if( nextChar == '0' ) {
      curr = curr->c0;
    } else {
    curr = curr->c1;
    }
    if( curr == leaves[(int)curr->symbol] ) {
      return (int)curr->symbol;
    }
  }
}



HCTree::~HCTree() {
    deleteAll(root);
}
