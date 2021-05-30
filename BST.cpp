#include <iostream>
#include <time.h>
#include <math.h>

#include <fstream>

using namespace std;

struct S_NODE{
    int value;
    S_NODE *lNext;
    S_NODE *rNext;
};

class C_bst{
    public:
        C_bst();
        ~C_bst();
        S_NODE* createNode(int);
        void insert(int);
        void print();
        void sort();
        int height();
    private:
        S_NODE *head;
        int nodeCount;

        void p_CreateTree(int*, int, int);
        S_NODE* p_insert(S_NODE*, S_NODE*);
        void p_InOrderprint(S_NODE*);
        void p_sort();
        void p_populateArray(S_NODE*, int*, int);
        void recursiveDelete(S_NODE*);
        int p_height(S_NODE*);
};

C_bst::C_bst(void){
    this->head = NULL;
    this->nodeCount = 0;
}

C_bst::~C_bst(void){
    this->recursiveDelete(this->head);

}

void C_bst::sort(){
    this->p_sort();
}

void C_bst::p_sort(){
    // start sorting and create array
  int *tempArray = new int[this->nodeCount];
  this->p_populateArray(this->head, tempArray, 0);
  // delete the tree, so that we can create new tree next line
  this->recursiveDelete(this->head);
  // set head equal to null
  this->head = NULL;
  // 0 is the first node and nodeCount is the last node
  // create new tree
  this->p_CreateTree(tempArray, 0, this->nodeCount - 1);

  //for(int i = 0; i < this->nodeCount; ++i){
  //    cout << tempArray[i] << endl;
  //}
}

void C_bst::p_CreateTree(int *myArray, int start, int end){    
    //our start is smaller than the end
    //our end is larger than our start
    if(start > end){
        return;
    } else {
        // find middle node
        // round down by using floor function
        int middle = floor((start + end) / 2);
        //insert middle node into myArray using public function
        this->insert(myArray[middle]);
        // go left side of tree
        this->p_CreateTree(myArray, start, middle - 1);
        // go right side of tree
        this->p_CreateTree(myArray, middle + 1, end);
    }
}
// similar to inordertraversal
void C_bst::p_populateArray(S_NODE* node, int *myArray, int index){
    if(NULL == node){
        return;
    } else {
        // go left and add 1 to index
        this->p_populateArray(node->lNext, myArray, index + 1);
        // insert the node
        myArray[index] = node->value;
        // go right and add 1 to index
        this->p_populateArray(node->rNext, myArray, index + 1);
    }
}

void C_bst::recursiveDelete(S_NODE *node){
    if(NULL == node){
        return;
    } else {
        // go left and go right, and if nothing lose go back up
        this->recursiveDelete(node->lNext);
        this->recursiveDelete(node->rNext);
        delete node;
    }
}

S_NODE* C_bst::createNode(int value){
    S_NODE *temp = new S_NODE;

    temp->value = value;
    temp->lNext = NULL;
    temp->rNext = NULL;

    return temp;
}

void C_bst::insert(int value){
    S_NODE *node = this->createNode(value);

    // if not root node, then call p_insert
    if(NULL == this->head) {
        this->head = node;
    } else {
        this->p_insert(this->head, node);
    }
    // increase node count 
    this->nodeCount++;
    return;
}

void C_bst::print(){
    if(NULL != this->head){
        this->p_InOrderprint(this->head);
    } else {
        cout << "Empty Tree" << endl;
    }
}

int C_bst::height(void){
    return this->p_height(this->head);
}

int C_bst::p_height(S_NODE *node){
    if(NULL == node){
       return 0;
    } else {
        int lHeight = 0;
        int rHeight = 0;
        // move through the tree, store left and right height 
        lHeight = this->p_height(node->lNext);
        rHeight = this->p_height(node->rNext);

        // Return whichever node is the largest
        if(lHeight > rHeight) {
            return lHeight + 1;
        } else {
            return rHeight + 1;
        }
    }
}

void C_bst::p_InOrderprint(S_NODE *node){
    if(NULL == node){
        return;
    } else {
        this->p_InOrderprint(node->lNext);
        cout << node->value << endl;
        this->p_InOrderprint(node->rNext);
    }
}

S_NODE* C_bst::p_insert(S_NODE* parent, S_NODE *nodeToInsert){
    if(NULL == parent){
        return nodeToInsert;
    } else {
        // if current node is smaller than parent go left
        if(nodeToInsert->value < parent->value){
            parent->lNext = this->p_insert(parent->lNext, nodeToInsert);
        } else {
            // if current node is larger than parent go right
            parent->rNext = this->p_insert(parent->rNext, nodeToInsert); 
        }
    }
    return parent;
}

int main(int argc, char *argv[]){
    C_bst myTree;
    ifstream myFile;

    int input;
    int incrementor = 0;

    myFile.open("treeNumbers.txt");

    if(myFile.is_open() ){
        while( !myFile.eof() ){
            myFile >> input;
            myTree.insert(input);
        }
    }
    myTree.sort();
    myTree.print();

    myFile.close();

    return 0;
}