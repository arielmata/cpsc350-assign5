//BST.h - template class
class TreeNode{
  public:
    TreeNode();
    TreeNode(int k);
    ~TreeNode();

    int key;
    /* int key; int value */
    TreeNode *left;
    TreeNode *right;
}

TreeNode::TreeNode(){
  left = NULL;
  right = NULL;
}

TreeNode:TreeNode(int k){
  key = k;
  left = NULL;
  right = NULL;
}

TreeNode::~TreeNode(){
  //character development
}

class BST{
  private:
    TreeNode *root;
  public:
    BST();
    ~BST();

    bool searchNode(int value);// our key is the value in this example
    void insertNode(int value);
    bool deleteNode(int value);

    //helper functions
    bool is Empty();
    unsigned int getSize();
    TreeNode* getMin(); //can return value but here we are returning tree node
    TreeNode* getMax();
    void recPrint(TreeNode *node);

    TreeNode* getSuccessor(TreeNode *d);//returns successor of node we will delete d

    //traversal methods

};

BST::BST(){
  root = NULL;
}

BST:~BST(){
  //iterate and delete => O(n)
}

void BST::recPrint(TreeNode *node){
  if(node != NULL){
    recPrint(node->left);
    cout << node->key << endl; //=> cout << node->value << endl;
    recPrint(node->left);
  }
}

void BST:printEntireTree(){
  recPrint(root); // i don't understand
}

int BST::getMax(){
  TreeNode *current = root;// because we are not deleting a value just returning it

  if(isEmpty())
    return null;

  while(current->right != NULL){
    current = current->right;
  }

  return current->key;
}

voidBST::insertNode(int value){
  TreeNode *node = new TreeNode(value);

  if(isEmpty()){
    root = node;
  }else{
    //tree is not empty
    TreeNode *parent = root;
    TreeNode *parent = NULL;///idkidkidk

    while(true){
      parent = current;

      if(value < current->key){
        current = current->left;
        if(current == NULL){
          //found insertion point
          parent->left = node;
          break;
        }
      }else{
        //we go right
        current = current->right;
        if(current == NULL){
          parent->left = node;
          break;
        }
      }
    }
  }
}

bool BST::seachNode(int value){

  if(isEmpty())
    return false;
  else{
    //tree is not empty, let's and find the value
    TreeNode *current = root;
    while (current->key != value){
      if(val < current->key)
        current = current->left;
      else
        current = current->right;

      if(current == NULL)
        return false;
    }
  }
  return true;
}

bool BST::deleteNode(int k){

  if(isEmpty())
    return false;
  //you can leverage search to determine whether value before proceeding

  TreeNode *current = root;
  TreeNode *parent = root;
  bool isLeftNode = true;

  //usual code to find a TreeNode

  while(current->key != k){
    parent = current;

    if(k < current->key){
      //go left
      isLeftNode = true;
      current = current->left;
    }else{
      //go right
      isLeftNode = false;
      current = current->right;
    }

    if(current == NULL){
      return false;
    }
  }

  //if we make here, we found our key/value
  //let's proceed to delete

  //case: node to deleted has no children, AKA leaf node
  if(current->left == NULL && current->right == NULL){
    if(current == root){
      root = NULL;
    }else if(isLeftNode){
      parent->left = NULL;
    }else{
      //right child
      parent->right = NULL;
    }
  }
  //case: node to be deleted has one child. need to determine whether node has
  //left or right child
  else if(current->right == NULL){
    //node has one childe and it's a left
    //no right child

    if(current == root){
      root = current->left;
    }
    else if (isLeftNode){
      parent->left = current->left;
    }
    else{
      parent->right = current->left;
    }
  }
  else if(current->left == NULL){
    //node has one childe and it's a right
    //no left child

    if(current == root){
      root = current->right;
    }
    else if (isLeftNode){
      parent->left = current->right;
    }
    else{
      parent->right = current->right;
    }
  }
  else{
    //node to be deleted has two children
    TreeNode *successor = getSuccessor(current);

    if(current == root){
      root = successor;
    }
    else if(isLeftNode){
      parent->left = successor;
    }
    else{
      parent->right = successor;
    }

    successor->left = current->left;
  }
  //delete current; //QUESTION do WE garbage collect in the delete function?????
  return true;
}

TreeNode* BST::getSuccessor(TreeNode *d){

  TreeNode *sp = d;
  TreeNode *successor = d;
  TreeNode *current = d->right;

  while(current != NULL){
    sp = successor;
    successor = current;
    current = current->left;
  }
  //once we exit the while loop, pointers should be in correct positions

  //we need to check whether or not successor is descendant of right child
  if(successor != d->right){
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}
