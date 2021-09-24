#include <string>
#include <iostream>
#include <fstream>
using namespace std;

typedef int ItemType;
struct TreeNode;

class TreeType
{
public:
  TreeType();  // constructor
  ~TreeType(); // destructor
  void makeEmpty();
  bool isEmpty() const;
  int getLength() const;
  void putItem(ItemType item);
  void deleteItem(ItemType item, ofstream &);
  void print(ofstream &outFile) const;
  void levelOrderPrint(ofstream &outFile) const;
  void preOrderPrint(ofstream &outFile) const;
  void postOrderPrint(ofstream &outFile) const;
  void printAncestors(ItemType value, ofstream &outFile) const;
  void mirrorImage(TreeType &t) const;
  
private:
  TreeNode *root;
  int length;
  void destroy(TreeNode *&tree);
  void insert(TreeNode *&tree, ItemType item);
  void remove(TreeNode *&tree, ItemType item, ofstream &outFile);
  void deleteNode(TreeNode *&tree, ofstream &outFile);
  TreeNode *getPredecessor(TreeNode *tree) const;
  TreeNode *getSuccessor(TreeNode *tree) const;
  void inOrderTraverse(TreeNode *tree, ofstream &outFile) const;
  void mirror(TreeNode *&copy, const TreeNode *originalTree) const;
  // define additional private helper functions here
  int height(TreeNode * tree) const;
  void preOrderHelper(TreeNode * tree, ofstream &outFile) const;
  void postOrderHelper(TreeNode * tree, ofstream &outFile) const;
  void printCurrentLevel(TreeNode * tree, int level, ofstream &outFile) const;
  bool ancestors(TreeNode * tree, ItemType value, ofstream & outFile) const;
  bool isNodeInTree(TreeNode * tree, ItemType value) const;
};
