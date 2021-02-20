#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    struct NODE *left;
    struct NODE *right;
    int key;
    int height;
}NODE;

struct NODE *root = NULL;

struct NODE *INSERT_NODE(int key) {
    struct NODE *temp = (struct NODE*)malloc(sizeof(struct NODE));
    if(temp == NULL) {
        fprintf(stderr, "\nERROR 404 CAUSE OF MALLOC...\n");
        printf("\nERROR 404 CAUSE OF MALLOC....\n");
        return NULL;
    } else {
        temp->key = key;
        temp->left = NULL;
        temp->right = NULL;
        temp->height = 0;
        return temp;
    }
}

struct NODE *BST(struct NODE *node, int KEY) {
    if(node == NULL) {
        return (INSERT_NODE(KEY));
    } if(node->key > KEY) { 
        node->left = BST(node->left, KEY);
    } else if(node->key < KEY) {
        node->right = BST(node->right, KEY);
    }
    return node;
}

int MAXIMUM(int a, int b) {
    if(a>b) {
        return a;
    } 
    return b;
}

int HEIGHT(struct NODE *root) {
    if(root != NULL) {
        int left_height = HEIGHT(root->left);
        int right_height = HEIGHT(root->right);
        return (1+MAXIMUM(left_height, right_height));
    }
    return 404;
}

int BALANCE_FACTOR(struct NODE *root) {
    if(root != NULL) {
        int left_part = HEIGHT(root->left);
        int right_part = HEIGHT(root->right);
        int FINAL_RESULT = abs(left_part-right_part);
        if(FINAL_RESULT == 1 || FINAL_RESULT == 0) {
            return 1; //este un AVL TREE, adica avem si 0 si 1 care spune ca ii AVL tree
        } else {
            return 404; //nu este un AVL TREE
        }
    }
    return 404;
}

void INORDER(struct NODE *node) {
    if(node != NULL) {
        INORDER(node->left);
        printf("%d ", node->key);
        INORDER(node->right);
    }
}

struct NODE *MAXIMUM_FOR_PREDECESSOR(struct NODE *node) {
    if(node == NULL) {
        return node;
    } 
    struct NODE *temp = node;
    while(temp->right != NULL) {
        temp = temp -> right;
    }
    return temp;
}

struct NODE *MINIMUM_FOR_SUCCESSOR(struct NODE *node) {
    if(node == NULL) {
        return node;
    } 
    struct NODE *temp = node;
    while(temp->left != NULL) {
        temp = temp -> left;
    }
    return temp;
}


int count = 0; //check if number is pair or not

struct NODE *DELETE_PREDECESSOR_AND_SUCCESSOR(struct NODE *node, int KEY) {
    int check_pair = 0;
    if(root == NULL) {
        return root;
    } else if(node->key > KEY) {
        node->left = DELETE_PREDECESSOR_AND_SUCCESSOR(node->left, KEY);
    } else if(node->key < KEY) {
        node->right = DELETE_PREDECESSOR_AND_SUCCESSOR(node->right, KEY);
    } else {
        if(node->key % 2 != 0) {
            check_pair = 0;
        } else if(node->key % 2 == 0) {
            check_pair = 1;
        }

        if(check_pair == 0) {
            printf("\nCANT DELETE THIS NUMBER CAUSE NUMBER IS NOT A PAIR NUMER...\n");
            fprintf(stderr, "NON PAIR NUMBER...\n");
            return NULL;
        } 
        else if(check_pair == 1) {
            //WE CAN DELETE CAUSE NUMBER IS PAIR
            if(count % 2 == 0) {
                if(node->left == NULL && node->right == NULL) {
                    free(node);
                    node = NULL;
                } else if(node->left == NULL) {
                    struct NODE *temp = node;
                    node = node -> right;
                    free(temp);
                    temp = NULL;
                } else if(node->right == NULL) {
                    struct NODE *temp = node;
                    node = node -> left;
                    free(temp);
                    temp = NULL;
                } else {
                    struct NODE *temp = MAXIMUM_FOR_PREDECESSOR(node->left);
                    node->key = temp->key;
                    node->left = DELETE_PREDECESSOR_AND_SUCCESSOR(node->left, temp->key); 
                }
            } else if(count % 2 != 0) {
                if(node->left == NULL && node->right == NULL) {
                    free(node);
                    node = NULL;
                } else if(node->left == NULL) {
                    struct NODE *temp = node;
                    node = node -> right;
                    free(temp);
                    temp = NULL;
                } else if(node->right == NULL) {
                    struct NODE *temp = node;
                    node = node -> left;
                    free(temp);
                    temp = NULL;
                } else {
                    struct NODE *temp = MINIMUM_FOR_SUCCESSOR(node->right);
                    node->key = temp->key;
                    node->right = DELETE_PREDECESSOR_AND_SUCCESSOR(node->right, temp->key);
                }
            }
            count++;
        }
    }
    return node;
}

struct NODE *DELETE_PAIR(struct NODE *node) {
    if(node != NULL) {
        DELETE_PAIR(node->left);
        if(node->key % 2 == 0) {
            DELETE_PREDECESSOR_AND_SUCCESSOR(node,  node->key);
        } else if(node->key % 2 != 0) {
            return NULL;
        }
        DELETE_PAIR(node->right);
    }
}

int main () {
    int key;
    printf("\n"); printf("GIVE US THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //12
    printf("\n"); printf("GIVE IS THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //5
    printf("\n"); printf("GIVE US THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //4
    printf("\n"); printf("GIVE US THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //19
    printf("\n"); printf("GIVE IS THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //27
    printf("\n"); printf("GIVE US THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //33
    printf("\n"); printf("GIVE US THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //22
    printf("\n"); printf("GIVE IS THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //18
    printf("\n"); printf("GIVE US THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //25
    printf("\n"); printf("GIVE US THE KEY? "); scanf("%d", &key);
    root = BST(root, key); //3
    printf("\n");
    printf("\nINORDER BEFORE DELETE: "); printf("\n");
    INORDER(root);
    printf("\n\n\n\n");
    DELETE_PAIR(root);
    INORDER(root);
    printf("\n\n");
    if(BALANCE_FACTOR(root) == 404) { //tree is not balanced in AVL style
        printf("TREE IS NOT BALANCED (ARBORELE NU E ECHILIBRAT)...\n");
    } else if(BALANCE_FACTOR(root) == 1) { //tree is balanced in AVL style
        printf("TREE IS BALANCED (ARBORELE E ECHILIBRAT)...\n");
    }
    return 0;
}