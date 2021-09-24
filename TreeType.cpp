#include "TreeType.h"

struct TreeNode
{
  ItemType info;
  TreeNode *left;
  TreeNode *right;
};

TreeType::TreeType()
{
  root = NULL;
  length = 0;
}

TreeType::~TreeType()
// Calls recursive function destroy to destroy the tree.
{
  destroy(root);
}

void TreeType::makeEmpty()
{
  destroy(root);
  root = NULL;
  length = 0;
}

void TreeType::destroy(TreeNode *&tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    destroy(tree->left);
    destroy(tree->right);
    delete tree;
  }
}

bool TreeType::isEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

int TreeType::getLength() const
{
  return length;
}

void TreeType::putItem(ItemType item)
// Calls recursive function insert to insert item into tree.
{
  insert(root, item);
  length++;
}

// helper Function for putItem
void TreeType::insert(TreeNode *&tree, ItemType item)
// inserts item into tree.
// Post:  item is in tree; binary search property is maintained.
{
  if (tree == NULL)
  { // insertion place found.
    tree = new TreeNode;
    tree->left = NULL;
    tree->right = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    insert(tree->left, item); // insert in left subtree.
  else
    insert(tree->right, item); // insert in right subtree.
}

void TreeType::deleteItem(ItemType item, ofstream &outFile)
// Calls recursive function remove to delete item from tree.
{
  remove(root, item, outFile);
  length--;
}

void TreeType::remove(TreeNode *&tree, ItemType item, ofstream &outFile)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (tree == NULL) {
    outFile << item << " is not in tree." << endl;
    length++;	// if item not found, then this length++ offsets the length-- in deleteItem()
  }
  else if (item < tree->info)
    remove(tree->left, item, outFile); // Look in left subtree.
  else if (item > tree->info)
    remove(tree->right, item, outFile); // Look in right subtree.
  else
    deleteNode(tree, outFile); // Node found; call deleteNode
}

void TreeType::deleteNode(TreeNode *&tree, ofstream &outFile)
// Modify this function to call the getSuccessor function instead of getPredecessor
{
  TreeNode *tempPtr;
  tempPtr = tree;

  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    TreeNode *succNode = getSuccessor(tree->right);
    tree->info = succNode->info;
    remove(tree->right, succNode->info, outFile);
    
    /*
    TreeNode *predNode = getPredecessor(tree->left);
    tree->info = predNode->info;
    remove(tree->left, predNode->info, outFile); // Delete predecessor node.
    */ 
  }
}

//Helper function for deleteNode
TreeNode *TreeType::getPredecessor(TreeNode *tree) const
{
  while (tree->right != NULL)
    tree = tree->right;
  return tree;
}

TreeNode *TreeType::getSuccessor(TreeNode *tree) const
// Implement this function
{
  while (tree->left != NULL) {
    tree = tree->left;
  }
  return tree;
}

void TreeType::print(ofstream &outFile) const
// Calls recursive function inOrderTraverse to print items in the tree.
{
  inOrderTraverse(root, outFile);
  outFile << endl;
}

// Helper function for print
void TreeType::inOrderTraverse(TreeNode *tree, ofstream &outFile) const
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    inOrderTraverse(tree->left, outFile); // Print left subtree.
    outFile << tree->info << " ";
    inOrderTraverse(tree->right, outFile); // Print right subtree.
  }
}

void TreeType::preOrderPrint(ofstream &outFile) const
// Implement this function, You may call a helper function
{
  preOrderHelper(root, outFile);
  outFile << endl;
}

void TreeType::preOrderHelper(TreeNode * tree, ofstream &outFile) const {
  if (tree != NULL) {
    outFile << tree->info << " ";
    preOrderHelper(tree->left, outFile);
    preOrderHelper(tree->right, outFile);
  }
} 

void TreeType::postOrderPrint(ofstream &outFile) const
// Implement this function, You may call a helper function
{
  postOrderHelper(root, outFile);
  outFile << endl;
}

void TreeType::postOrderHelper(TreeNode * tree, ofstream &outFile) const {
  if (tree != NULL) {
    postOrderHelper(tree->left, outFile);
    postOrderHelper(tree->right, outFile);
    outFile << tree->info << " ";
  }
} 

int TreeType::height(TreeNode * tree) const {
  if (tree == NULL) {
    return 0;
  }
  
  int leftHeight = height(tree->left);
  int rightHeight = height(tree->right);
  
  if (leftHeight > rightHeight) {
    return (leftHeight + 1);
  } else {
    return (rightHeight + 1);
  }
}

void TreeType::levelOrderPrint(ofstream &outFile) const
//Implement this function, you May use a data structure
{
  int treeHeight = height(root);
  for (int i = 0; i < treeHeight; i++) {
    printCurrentLevel(root, i, outFile);
  }
  outFile << endl;
}

void TreeType::printCurrentLevel(TreeNode * tree, int level, ofstream &outFile) const {
  if (tree == NULL) {
    return;
  } else if (level == 0) {
    outFile << tree->info << " ";
  } else if (level > 0) {
    printCurrentLevel(tree->left, level - 1, outFile);
    printCurrentLevel(tree->right, level - 1, outFile);
  }
} 

void TreeType::printAncestors(ItemType value, ofstream &outFile) const
// Implement this function, You may call a helper function
{
  if (!isNodeInTree(root, value)) {
    outFile << value << " is not in the tree";
  }
  ancestors(root, value, outFile);
  outFile << endl;
}

bool TreeType::ancestors(TreeNode * tree, ItemType value, ofstream &outFile) const {
  int count = 0;
    
  if (tree == NULL) {
    return false;
  }

  if (tree->info == value) {
    if (tree->info == root->info) {
      outFile << tree->info << " has no ancestors";
    }
    return true;
  }

  if (ancestors(tree->left, value, outFile) || ancestors(tree->right, value, outFile)) {
    outFile << tree->info << " ";
    return true;
  } else {
    return false;
  }
}

bool TreeType::isNodeInTree(TreeNode * tree, ItemType value) const {
  if (tree == NULL) {
    return false;
  }
  
  if (tree->info == value) {
    return true;
  }
  
  bool lCheck = isNodeInTree(tree->left, value);
  if (lCheck) {
    return true;
  }

  bool rCheck = isNodeInTree(tree->right, value);
  if (rCheck) {
    return true;
  } else {
    return false;
  }
}

void TreeType::mirrorImage(TreeType &t) const
// calls the helper function mirror
{
  mirror(t.root, root);
}

// helper function for mirrorImage
void TreeType::mirror(TreeNode *&copy, const TreeNode *originalTree) const
// implement this function
// Post: copy is the root of a tree that is a mirror Image of originalTree.
// HINT: this function can be implemented in a very similar way as the copyTree() function in the slides
{
  if (originalTree == NULL) {
    copy = NULL;
  } else {
    copy = new TreeNode;
    copy->info = originalTree->info;
    mirror(copy->left, originalTree->right);
    mirror(copy->right, originalTree->left);
  }
}
