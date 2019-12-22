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

  void Destroy() {
    SplayTree* par = parent;

    if (par != NULL) {
      bool isRight = (par->child[1] == this);

      par->child[isRight] = NULL;
    }

    parent = NULL;
  }

  SplayTree* FindNode(int v) {
    SplayTree *x = this;
    SplayTree *xx = NULL;

    while (x != NULL) {
      xx = x;

      if (x->v > v) {
        x = x->child[0];
      }

      else if (x->v < v) {
        x = x->child[1];
      }

      else return x;
    }

    return xx;
  }

  SplayTree* Search(int v) {
    SplayTree* x = FindNode(v);

    x->Splay();
    return x;
  }

  SplayTree* Insert(int v) {
    SplayTree* par = FindNode(v);

    if (par->v == v) {
      par->Splay();
      return par;
    }

    SplayTree* x = new SplayTree(v);

    if (par->v < v) {
      par->child[1] = x;
    }
    else if (par->v > v) {
      par->child[0] = x;
    }

    x->parent = par;
    x->Splay();

    return x;
  }

  SplayTree* FindMax(SplayTree* root) {
    SplayTree* x = NULL;

    while (root != NULL) {
      x = root;
      root = root->child[1];
    }

    return x;
  }

  SplayTree* Delete(int v) {
    SplayTree* x = FindNode(v);
    x->Splay();

    if (x->v != v) {
      return x;
    }

    SplayTree* leftSubTree = x->child[0];
    SplayTree* rightSubTree = x->child[1];

    x->child[0] = x->child[1] = NULL;

    if (leftSubTree != NULL)
      leftSubTree->parent = NULL;
    if (rightSubTree != NULL)
      rightSubTree->parent = NULL;

    if (leftSubTree != NULL) {
      SplayTree* maxNode = FindMax(leftSubTree);

      maxNode->child[1] = rightSubTree;

      if (rightSubTree != NULL)
        rightSubTree->parent = maxNode;

      maxNode->Splay();
      return maxNode;
    }

    return rightSubTree;
  }

  pair<SplayTree*, SplayTree*> SplitByValue(int v) {
    SplayTree* x = FindNode(v);
    x->Splay();

    SplayTree *leftTree, *rightTree;

    if (x->v <= v) {
      // Destroy right edge

      leftTree = x;
      rightTree = x->child[1];

      if (x->child[1] != NULL)
        x->child[1]->Destroy();
    }

    else {
      // Destroy left edge
      leftTree = x->child[0];
      rightTree = x;

      if (x->child[0] != NULL)
        x->child[0]->Destroy();
    }

    return make_pair(leftTree, rightTree);
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

  g->Splay();
  root = g;
  root->Print();
  cerr << "#########################\n";

  c->Splay();
  root = c;
  root->Print();
  cerr << "#########################\n";

  root = root->Search(6);
  root->Print();
  cerr << "#########################\n";

  if (root->v == 6) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  root = root->Search(0);
  root->Print();
  cerr << "#########################\n";

  if (root->v == 0) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  root = root->Insert(13);
  root->Print();
  cerr << "#########################\n";

  root = root->Insert(12);
  root->Print();
  cerr << "#########################\n";

  root = root->Delete(8);
  root->Print();
  cerr << "#########################\n";

  root = root->Delete(9);
  root->Print();
  cerr << "#########################\n";

  root = root->Delete(5);
  root->Print();
  cerr << "#########################\n";

  pair<SplayTree*, SplayTree*> roots = root->SplitByValue(5);
  if (roots.first != NULL) {
    cerr << "First Tree\n";
    roots.first->Print();
    cerr << "#########################\n";
  }

  if (roots.second != NULL) {
    cerr << "Second Tree\n";
    roots.second->Print();
    cerr << "#########################\n";
  }

  return 0;
}