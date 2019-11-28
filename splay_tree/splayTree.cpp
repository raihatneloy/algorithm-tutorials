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

  void Splay() {
    while (parent != NULL) {
      if (parent->parent != NULL) {
        bool parentIsLeft = parent->parent->child[0] == parent;
        bool isLeft = parent->child[0] == this;

        if (parentIsLeft == isLeft)
          parent->Rotate();
        else Rotate();
      }

      Rotate();
    }
  }

  void Print(string prefix=EMPTY, bool isRight=false, bool isRoot=true) {
    if (child[1])
      child[1]->Print(prefix + (!isRight && !isRoot? "|  ": "   "), true, false);

    cout << prefix;
    cout << (isRoot? "---" : (isRight? ".--" : "`--"));
    cout << v << endl;

    if (child[0])
      child[0]->Print(prefix + (isRight? "|  ": "   "), false, false);
  }
};

int main() {
  SplayTree* w = new SplayTree(1);
  SplayTree* x = new SplayTree(2);
  SplayTree* y = new SplayTree(3);
  SplayTree* z = new SplayTree(4);
  SplayTree* a = new SplayTree(5);
  SplayTree* b = new SplayTree(6);
  SplayTree* c = new SplayTree(7);
  SplayTree* d = new SplayTree(8);
  SplayTree* e = new SplayTree(9);
  SplayTree* f = new SplayTree(10);
  SplayTree* g = new SplayTree(11);

  w->child[1] = x;
  x->parent = w;
  x->child[1] = y;
  y->parent = x;
  y->child[1] = z;
  z->parent = y;
  z->child[1] = a;
  a->parent = z;
  a->child[1] = b;
  b->parent = a;
  b->child[1] = c;
  c->parent = b;
  c->child[1] = d;
  d->parent = c;
  d->child[1] = e;
  e->parent = d;
  e->child[1] = f;
  f->parent = e;
  f->child[1] = g;
  g->parent = f;

  SplayTree* root = w;

  root->Print();
  cerr << "#########################\n";
  return 0;
}