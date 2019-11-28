#include <bits/stdc++.h>

using namespace std;

const string EMPTY="";

struct SplayTree {
  int v; // Value of node
  SplayTree *child[2]; // Left child -> [0], right child -> [1]
  SplayTree *parent; // Parent of node

  SplayTree(int _v) {
    v = _v;
    child[0] = child[1] = parent = NULL;
  }

  void Rotate() {
    SplayTree *g = parent->parent;

    bool isLeft = (parent->child[0] == this);
    // isLeft == True -> rightRotate
    // isLeft == False -> leftRotate

    parent->child[isLeft^1] = child[isLeft];
    if (child[isLeft] != NULL)
      child[isLeft]->parent = parent;
    child[isLeft] = parent;
    parent->parent = this;

    if (g != NULL) {
      bool parentIsLeft = (g->child[0] == parent);

      g->child[parentIsLeft ^ 1] = this;
    }

    parent = g;
  }
};

int main() {

  return 0;
}