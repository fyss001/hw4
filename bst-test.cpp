#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    bt.insert(std::make_pair('c',3));
    bt.insert(std::make_pair('d',4));
    bt.print();
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    //cout << "Erasing c" << endl;
    //bt.remove('c');
    bt.print();
    cout << "Erasing a" << endl;
    bt.remove('a');
    cout << "a Erased" << endl;
    bt.print();
    cout<<"----------"<<endl;
    // AVL Tree Tests
    /*AVLTree<char,int> at;
    at.insert(std::make_pair('c',1));
    at.print();
    at.insert(std::make_pair('b',2));
    at.print();
    at.insert(std::make_pair('a',3));
    at.print();*/
    AVLTree<int,int> at;
    at.insert(std::make_pair(1,1));
    at.print();
    at.insert(std::make_pair(2,2));
    at.print();
    at.remove(1);
    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<int,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
    return 0;
}
