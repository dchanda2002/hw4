#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int longestLeaf(Node *);

bool equalPaths(Node * root)
{
    // Add your code below
    if(root == NULL){
        return true;
    }
    if(longestLeaf(root) == -1){
        return false;
    }
    return true;
}


int longestLeaf(Node * root){

    //if at a leaf node, return length of one
    if(root->left == NULL && root->right == NULL){
        return 1;
    } 

    //if there is only a right node, call longestLeaf on it and add 
    //one to the length
    if(root->left == NULL){
        int rightLeaf = longestLeaf(root->right) + 1;
        if(rightLeaf > 0){
            return rightLeaf;
        }
        return -1;
    }

    //if there is only a left node, call longestLeaf on it and add 
    //one to the length
    if(root->right == NULL){
        int leftLeaf = longestLeaf(root->left) + 1;
        if(leftLeaf > 0){
            return leftLeaf;
        }
        return -1;
    }

    //if there are two children, call it on both.
    int leftLength = longestLeaf(root->left);
    int rightLength = longestLeaf(root->right);
    if(leftLength == rightLength && leftLength > 0 && rightLength > 0){
        return leftLength + 1;
    }
    return -1;
    
}
