#include<bits/stdc++.h>
using namespace std;

//BST Node
struct BstNode{
    int data;
    BstNode* left;
    BstNode* right;
};

//Binary Search Tree class
class BST{
    BstNode *root;
    public:
    BST(){
        root = NULL;
    }
    bool isEmpty(){
        if(root == NULL) return true;
        return false;
    }
    void insertNode(int val){
        BstNode* node = new BstNode;
        BstNode* parent = NULL;
        node->data = val;
        node->left = NULL;
        node->right = NULL;
        if(isEmpty()){
            root = node;
        }
        else{
            BstNode* ptr = root;
            while(ptr != NULL){
                parent = ptr;
                if(val > ptr->data) ptr = ptr->right;
                else ptr = ptr->left;
            }
            if(val < parent->data) parent->left = node;
            else parent->right = node;
        }
    }
    void Delete(int val){
        root = DeleteRec(root, val);
    }
    BstNode* DeleteRec(BstNode* root, int val){
        if(root == NULL) return root;
        else if(val < root->data) root->left = DeleteRec(root->left, val);
        else if(val > root->data) root->right = DeleteRec(root->right, val);
        else{
            if(root->left == NULL && root->right == NULL){
                delete root;
                root = NULL;
            } 
            else if(root->left == NULL){
                BstNode* temp = root;
                root = root->right;
                delete temp;
            }
            else if(root->right == NULL){
                BstNode* temp = root;
                root = root->left;
                delete temp;
            }
            else{
                BstNode* temp = root->right;
                while(temp->left != NULL) temp = temp->left;
                root->data = temp->data;
                root->right = DeleteRec(root->right, temp->data);
            }
        }
        return root;
    }
    void breadthFirstTraverse(){
        if(root == NULL) return;

        queue<BstNode*> Q;
        Q.push(root);
        while(!Q.empty()){
            BstNode* current = Q.front();
            cout << current->data << " ";
            if(current->left != NULL)
                Q.push(current->left);
            if(current->right != NULL)
                Q.push(current->right);
            Q.pop();
         }
    }
    void inOrderTraverse(){
        inOrderRec(root);
    }
    void inOrderRec(BstNode* root){
        if(root != NULL){
            inOrderRec(root->left);
            cout << root->data << " ";
            inOrderRec(root->right);
        }
    }
    void preOrderTraverse(){
        preOrderRec(root);
    }
    void preOrderRec(BstNode* root){
        if(root != NULL){
            cout << root->data << " ";
            preOrderRec(root->left);
            preOrderRec(root->right);
        }
    }
    void postOrderTraverse(){
        postOrderRec(root);
    }
    void postOrderRec(BstNode* root){
        if(root != NULL){
            postOrderRec(root->left);
            postOrderRec(root->right);
            cout << root->data << " ";
        }
    }
    int findMin(){
        if(root == NULL) return -1;
        BstNode* temp = root;
        while(temp->left != NULL)
            temp = temp->left;
        return temp->data;
    }
    int findMax(){
        if(root == NULL) return -1;
        BstNode* temp = root;
        while(temp->right != NULL)
            temp = temp->right;
        return temp->data;
    }
    int findHeight(){
        return Height(root);
    }
    int Height(BstNode* root){
        if(root == NULL) return -1;
        return max(Height(root->left), Height(root->right)) + 1;
    }
    bool isbST(){
        return isBSTRec(root, INT_MIN, INT_MAX);
    }
    bool isBSTRec(BstNode* root, int min, int max){
        if(root == NULL) return true;

        if(root->data <= max && root->data > min
        && isBSTRec(root->left, min, root->data) && isBSTRec(root->right, root->data, max))
            return true;
        return false;
    }
    int inorderSuccessor(int val){
        BstNode* current = root;
        while(current->data != val && current != NULL){
            if(val < current->data) current = current->left;
            else if(val > current->data) current = current->right;
        }
        if(current == NULL) return -1;
        if(current->right != NULL){
            BstNode* temp = current->right;
            while(temp->left != NULL) temp = temp->left;
            return temp->data;
        }
        else{
            BstNode* successor = NULL;
            BstNode* ancestor = root;
            while(ancestor != current){
                if(current->data < ancestor->data){
                    successor = ancestor;
                    ancestor = ancestor->left;
                }
                else
                    ancestor = ancestor->right;
            }
            if(successor == NULL) return -1;
            return successor->data;
        }
    }
};

//Test function
int main(){
    BST b;
    b.insertNode(52);
    b.insertNode(25);
    b.insertNode(50);
    b.insertNode(15);
    b.insertNode(40);
    b.insertNode(45);
    b.insertNode(20);
    b.insertNode(55);
    b.insertNode(60);

    //Traversal
    cout << "Level order(Bredth first): ";
    b.breadthFirstTraverse();
    cout << "\nInorder: ";
    b.inOrderTraverse();
    cout << "\nPreorder: ";
    b.preOrderTraverse();
    cout << "\nPosrorder: ";
    b.postOrderTraverse();

    //Minimum and Maximum elements
    int min = b.findMin();
    int max = b.findMax();
    cout << "\nMinimum: " << min << "\tMaximum: " << max << endl;

    //height(or max depth) of the tree
    cout << "Height of the tree: " << b.findHeight() << endl;

    //Check if the tree is BST or not
    b.isbST() ? cout << "BST\n" : cout << "Not BST\n";

    //Delete node from tree
    b.Delete(15);
    b.inOrderTraverse();

    //Inorder Successor
    cout << endl;
    cout << "InOrder successor of 40:  " << b.inorderSuccessor(40);
    cout << "\nInOrder successor of 60:  " << b.inorderSuccessor(60) << endl;

    return 0;
}
