#include <iostream>

using namespace std;

struct Node{
    int key = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* root = nullptr;
};

struct BinTree{
    Node* ROOT = nullptr;
    Node* NIL = nullptr;
};

BinTree* create_tree(){
    Node* NIL = new Node;
    BinTree* tree = new BinTree;
    tree->NIL = NIL;
    tree->ROOT = tree->NIL;
    return tree;
}

BinTree* push(BinTree* tree, int key){
    if (tree == nullptr){
        return nullptr;
    }
    if (tree->ROOT == tree->NIL){
        Node* new_node = new Node;
        new_node->key = key;
        new_node->left = tree->NIL;
        new_node->right = tree->NIL;
        new_node->root = tree->NIL;
        tree->ROOT = new_node;
        return tree;
    }
    Node* current = tree->ROOT;
    while (current != tree->NIL){
        if (key < current->key){
            if (current->left == tree->NIL){
                Node* new_node = new Node;
                new_node->key = key;
                new_node->left = tree->NIL;
                new_node->right = tree->NIL;
                new_node->root = current;
                current->left = new_node;
                break;
            }
            current = current->left;
        } else {
            if (current->right == tree->NIL){
                Node* new_node = new Node;
                new_node->key = key;
                new_node->left = tree->NIL;
                new_node->right = tree->NIL;
                new_node->root = current;
                current->right = new_node;
                break;
            }
            current = current->right;
        }
    }
    return tree;
}

Node* find(BinTree* tree, int key){
    if ((tree == nullptr) or (tree->ROOT == tree->NIL)){
        return nullptr;
    }
    if (key < tree->ROOT->key){
        BinTree* subtree = create_tree();
        subtree->NIL = tree->NIL;
        subtree->ROOT = tree->ROOT->left;
        return find(subtree, key);
    } else if (key > tree->ROOT->key){
        BinTree* subtree = create_tree();
        subtree->NIL = tree->NIL;
        subtree->ROOT = tree->ROOT->right;
        return find(subtree, key);
    } else {
        return tree->ROOT;
    }
}

void pop(BinTree* tree, int key){
    Node* dead_node = find(tree, key);
    if (dead_node == nullptr){
        return;
    }
    if ((dead_node->left == tree->NIL) & (dead_node->right == tree->NIL)){
        if (dead_node->root->right == dead_node){
            dead_node->root->right = tree->NIL; 
        } else {
            dead_node->root->left = tree->NIL;
        }
        delete dead_node;
        return;
    } else if ((dead_node->left == tree->NIL) & (dead_node->right != tree->NIL)){
        if (dead_node->root->right == dead_node){
            dead_node->root->right = dead_node->right; 
        } else {
            dead_node->root->left = dead_node->right;
        }
        delete dead_node;
        return;
    } else if ((dead_node->right == tree->NIL) & (dead_node->left != tree->NIL)){
        if (dead_node->root->right == dead_node){
            dead_node->root->right = dead_node->left; 
        } else {
            dead_node->root->left = dead_node->right;
        }
        delete dead_node;
        return;
    } else {
        Node* next = dead_node->right;
        while (next->left != tree->NIL){
            next = next->left;
        }
        if (next->root->right == next){
            next->root->right = tree->NIL; 
        } else {
            next->root->left = tree->NIL;
        }
        if (dead_node->root->right == dead_node){
            dead_node->root->right = next; 
        } else {
            dead_node->root->left = next;
        }
        next->right = dead_node->right;
        next->left = dead_node->left;
        delete dead_node;
        return;
    }
}

int get_depth(BinTree* tree){
    if (tree == nullptr){
        return -1;
    }
    if (tree->ROOT == tree->NIL){
        return 0;
    } else if (tree->ROOT->left == tree->ROOT->right){
        return 1;
    }
    BinTree* left_subtree = create_tree();
    BinTree* right_subtree = create_tree();
    left_subtree->ROOT = tree->ROOT->left;
    right_subtree->ROOT = tree->ROOT->right;
    int l = get_depth(left_subtree), r = get_depth(right_subtree);
    return max(l, r)+1;
}

void pop_subtree(BinTree* tree, int key){
    Node* subroot = find(tree, key);
    if ((tree == nullptr) or (subroot == nullptr)){
        return;
    } else {
        pop_subtree(tree, subroot->left->key);
        pop_subtree(tree, subroot->right->key);
        pop(tree, subroot->key);
    }
}

void destroy_tree(BinTree* tree){
    pop_subtree(tree, tree->ROOT->key);
}

void clear_tree(BinTree* tree){
    pop_subtree(tree, tree->ROOT->left->key);
    pop_subtree(tree, tree->ROOT->right->key);
    tree->ROOT = tree->NIL;
}

int main(){
    BinTree* tree = create_tree();
    tree = push(tree, 8);
    tree = push(tree, 3);
    tree = push(tree, 10);
    tree = push(tree, 1);
    tree = push(tree, 6);
    tree = push(tree, 14);
    tree = push(tree, 4);
    tree = push(tree, 7);
    tree = push(tree, 13);
    destroy_tree(tree);
    return 0;
}