#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int depth(Node * rt){
    if(rt->left==nullptr && rt->right==nullptr){
        return 1;
    }
    if(rt->left==nullptr){
        return depth(rt->right)+1;
    }else if(rt->right==nullptr){
        return depth(rt->left)+1;
    }
    int lheight=depth(rt->left), rheight=depth(rt->right);
    return 1+(lheight>rheight?lheight:rheight);
}

bool equalPaths(Node * root)
{
    // Add your code below
    if(root==nullptr) return true;
    if(root->left && root->right){
        //return depth(root->left) == depth(root->right);
        if(depth(root->left) != depth(root->right)) return false;
        return equalPaths(root->left) & equalPaths(root->right);
    }
    if(root->left == nullptr && root->right == nullptr) return true;
    if(root->left){ 
        return equalPaths(root->left);
    }else{
        return equalPaths(root->right);
    }
}

