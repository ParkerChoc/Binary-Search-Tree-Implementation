/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Parker Choc
 * Email: chocp@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bst.h"

struct bst_node
{
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};

struct bst
{
  struct bst_node* root;
};

struct bst* bst_create()
{
  struct bst* b = malloc(sizeof(struct bst));
  b->root = NULL;
  return b;
}

bool is_leaf(struct bst_node* b)
{
  if(b->right == NULL && b->left == NULL)
    return 1;
  return 0;
}

void terminate(struct bst_node* b)
{
  if(b->right != NULL)
    terminate(b->right);
  
  if(b->left != NULL)
    terminate(b->left);

  free(b);
}

void bst_free(struct bst* bst)
{
  terminate(bst->root);
  free(bst);
}

struct bst_node* create_node(int key, void* value)
{
  struct bst_node* b = malloc(sizeof(struct bst_node));
  b->left = NULL;
  b->right = NULL;
  b->value = value;
  b->key = key;
  return b;
}

void recursive_increment(struct bst_node* b, int* total)
{
  if(b->left != NULL)
  {
    (*total)++;
    recursive_increment(b->left, total);
  }
  
  if(b->right != NULL)
  {
    (*total)++;
    recursive_increment(b->right, total);
  }
}

int bst_size(struct bst* bst)
{
  if(bst->root == NULL)
    return 0; //empty bst

  int total = 1;  //counting root
  recursive_increment(bst->root, &total);
  return total;
}

void insert(struct bst_node* b, int key, void* value)
{ 
  if(key < b->key)
  {
    if(b->left != NULL)
      insert(b->left, key, value);  //go left
    else
      b->left = create_node(key, value);
  }
  else if (key > b->key)
  {
    if(b->right != NULL)
      insert(b->right, key, value);  //go right
    else
      b->right = create_node(key, value);
  }
  else  //b->key == key
  {
    printf("Key already exists\n");
    return;
  }
}

void bst_insert(struct bst* bst, int key, void* value)
{
  if(bst->root == NULL)
    bst->root = create_node(key, value);
  else
    insert(bst->root, key, value);  //recursive
}

struct bst_node* find_successor(struct bst_node* b)
{
  if(b == NULL)
    return b;

  struct bst_node* a = b;

  while(a->left != NULL)
    a = a->left;

  return a;
}

struct bst_node* case_1_and_2_(struct bst_node* b)
{
  struct bst_node* temp;

  if(b->left == NULL)
  {
    temp = b->right;
    free(b);
    return temp;
  }
  else  //b->right == NULL
  {
    temp = b->left;
    free(b);
    return temp;
  }
  //returning a pointer to the place I just removed the node from
}

struct bst_node* delete(struct bst_node* b, int k)
{
  if(b == NULL)
    return NULL;
  
  if(k == b->key) //found it!
  {
    if(b->left == NULL || b->right == NULL)
      return case_1_and_2_(b);  //case 1 and 2 handled here (1 or 0 children)

    //case 3: The node I am removing has two children
    struct bst_node* temp = find_successor(b->right);  //right once, then left until NULL

    b->key = temp->key;
    b->value = temp->value;

    //This can only be case 1 or 2. Neither will reach this point again.
    b->right = delete(b->right, temp->key);
  }
  else if(k < b->key)
    b->left = delete(b->left, k);
  else
    b->right = delete(b->right, k);

  return b;
}

void bst_remove(struct bst* bst, int key)
{
  if(bst == NULL)
  {
    printf("bst passed was NULL\n");
    return;
  }

  struct bst_node* temp = delete(bst->root, key);
  if(temp != NULL)
    bst->root = temp;
  else
    printf("This node does not exist\n");
}

void* find(struct bst_node* b, int key)
{
  if(b == NULL)
    return NULL;
  
  if(key < b->key)  //go left
    find(b->left, key);

  else if(key > b->key)  //go right
    find(b->right, key);

  else //found it!
    return b->value;
}

void* bst_get(struct bst* bst, int key)
{
  return find(bst->root, key);
}