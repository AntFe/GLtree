#include "bst.h"
#include <stdlib.h>

#pragma region EstruturasBase


#pragma endregion

Node *nodeConstruct(Node *Pai, Node *left, int value, Node *right)
{
    Node *new_node = calloc(1, sizeof(Node));
    new_node->pai = Pai;
    new_node->key = value;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

void nodeDestroy(Node *n)
{
    free(n);
}

BST *btCreate()
{
    return calloc(1, sizeof(BST));
}

/// @brief BT FIND - busca a posição do valor na árvore
/// @param bt
/// @param key
/// @return
Node *btFind(BST *bt, int key)
{
    Node *x = bt->root;
    while (x != NULL && x->key != key)
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

Node *btMaximum(Node *x)
{
    while (x->right != NULL)
        x = x->right;
    return x;
}

Node *btMinimum(Node *x)
{
    while (x->left != NULL)
        x = x->left;
    return x;
}

void btPush(BST *bt, int key)
{
    Node *y = NULL, *x = bt->root;
    while (x != NULL)
    {
        y = x;
        if (x->key > key)
            x = x->left;
        else
            x = x->right;
    }   
    if (y == NULL)
        bt->root = nodeConstruct(NULL, NULL, key, NULL);
    else if (key < y->key)
        y->left = nodeConstruct(y, NULL, key, NULL);
    else
        y->right = nodeConstruct(y, NULL, key, NULL);
    bt->size++;
}

#pragma region Remove

void swap(BST *bt, Node *u, Node *v)
{
    if (u->pai == NULL)
        bt->root = v;
    else if (u == u->pai->left)
        u->pai->left = v;
    else
        u->pai->right = v;
    if (v != NULL)
        v->pai = u->pai;
}

void btRemove(BST *bt, int key)
{
    Node *z = btFind(bt, key), *y = NULL, *to_remove = z;
    if (z->left == NULL)
    {
        swap(bt, z, z->right);
        nodeDestroy(to_remove);
        bt->size--;
        return;
    }
    else if (z->right == NULL)
    {
        swap(bt, z, z->left);
        nodeDestroy(to_remove);
        bt->size--;
        return;
    }
    else
    {
        y = btMinimum(z->right);
        if (y->pai != z)
        {
            swap(bt, y, y->right);
            y->right = z->right;
            y->right->pai = y;
        }
        swap(bt, z, y);
        y->left = z->left;
        y->left->pai = y;
        nodeDestroy(to_remove);
        bt->size--;
    }
}

#pragma endregion

#pragma region DestroyBST
void _subtreeDestroy(Node *n){
    if(n == NULL) return;
    _subtreeDestroy(n->left);
    _subtreeDestroy(n->right);
    nodeDestroy(n);
}

void btDestroy(BST *bt){
    _subtreeDestroy(bt->root);
    free(bt);
}
#pragma endregion