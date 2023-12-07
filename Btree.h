/************************************************************************
TITLE: VECTOR 
DESCRIPTION:
This class was made to serve as a 
replacement for the static array in C++,
to efficiently grow the array and manage
dynamic memory.
REQUIREMENTS: COPY CONSTRUCTOR FOR THE TYPE MUST BE DEFINED
AUTHOR: DANIYAL AHMED [22I-1032]
COAUTHOR: MUHAMMAD AHMAD [22I-1056]
COAUTHOR: HAFIZA IQRA [22I-1299]
DATE: MONDAY 4-12-2023
LASTEDITBY: MUHAMMAD AHMAD
*************************************************************************/
#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
using namespace std;


template <class T>
struct BNode {
    Vector<T> arr;
    Vector<BNode<T>*> links;
    int m;
    int count;
    bool isLeaf;
    int medPos;
    bool evenSplit = 0;
    
    //  CONSTRUCTOR
    BNode(int order) 
    :links(order + 1), arr(order) 
    {
        this->m = order;
        this->isLeaf = false;
        this->count = 0;
        if (m % 2 == 1 || evenSplit == 1) {
            this->medPos = order / 2;
        }else{
            this->medPos = (order /2) - 1;
        }
    }

    //  DESTRUCTOR
    ~BNode() {
      
    }

    //  GET MEDIAN
    int getMedian () {
        return this->arr[this->medPos];
    }
    
    bool isFull() {
        if (count == m -1) {
            return true;
        }else{
            return false;
        }
    }
    
    //  INSERT 
    void insert(const T& val) {
        bool inserted = false;
        for (int i = 0; i < count; i++) {
            if (arr[i] > val) {
                arr.insert_at_index(val,i);
                count++;
                inserted = true;
                break;
            }
        }
        if (!inserted) {
            arr.insert_at_index(val, count++);  
        }
    }

    void insert(const T& data, BNode<T>* left, BNode<T>* right) {
        int idx = -1;
        for (int i = 0; i < count; i++) {
            if (data > arr[i]) {
                idx++;
                continue;
            }
            break;  
        }
        
        arr.insert_at_index(data, idx + 1);
        count++;
        links.set_at_index(left, idx + 1);
        links.insert_at_index(right, idx + 2);
    }
};


template <class T>
class BTree {
private:
    int order;
    BNode<T>* root;
    const int MAX_KEYS;
    const int MAX_LINKS;
    const int MIN_KEYS;
    bool evenSplit = 0;
private:


    //  HELPER FUNCTIONS FOR INSERTION
    void insertNode(BNode<T>*& currNode, const T& data) {
        //  IF CURRENT NODE IS LEAF THEN VALUE NEEDS TO BE INSERTED
        if (currNode->isLeaf) {
            currNode->insert(data);
        }
        //  TRAVERSE TO THE LEAF
        else{
            int idx = -1;
            for (int i = 0; i < currNode->count; i++) {
                if (data > currNode->arr[i]) {
                    idx++;
                }else{
                    break;
                }
            }
            insertNode(currNode->links[idx + 1], data);
            if (currNode->links[idx + 1]->count > MAX_KEYS) {
                splitChild(currNode, currNode->links[idx + 1]);
                //  THIS WILL SPLIT THE CHILD INTO TWO PARTS AND ADD THEIR MEDIAN TO THE PARENT
                //  ON ROLLBACK THE PARENT WILL ALSO GET CHECKED HERE IF IT'S FULL OR NOT
            }
        } 
    }

    void splitChild(BNode<T>*& parent, BNode<T>*& child) {
        T median = child->getMedian();
        BNode<T>* left = child;
        BNode<T>* right = new BNode<T>(order);
        right->isLeaf = left->isLeaf;

        //  COPYING ELEMENTS [KEYS]
        int medianidx;
        //  IF ODD ORDER OR (IF EVEN ORDER EVEN MEDIAN CASE)
        if (order % 2 == 1 || evenSplit == 1) {
            medianidx = order / 2;
        }else{
            medianidx = order / 2 - 1;
        }
        int startIdx = medianidx + 1;
        int count = order - startIdx;

        
        for (int i = 0; i < count; i++) {
            right->arr.insert_at_index(left->arr[i + startIdx], i);
            right->count++;
        }
        for (int i = 0; i < count; i++) {
            left->arr.pop_back();
            left->count--;
        }
        left->arr.pop_back();
        left->count--;

        //  IF NOT LEAF THEN ALSO NEED TO COPY THE [LINKS]
        if (!left->isLeaf) {
            int startIdx;
            if (order % 2 == 1 || evenSplit == 1) {
                startIdx = (order /2) + 1;
            }else{
                startIdx = order/2;
            }
            int count = order + 1 - startIdx;
            for (int i = 0; i < count; i++) {
                right->links.insert_at_index(left->links[i + startIdx], i);
                left->links[i + startIdx] = nullptr;
            }
            for (int i = 0; i < count; i++) {
                left->links.pop_back();
            }
        }

        //  ADD MEDIAN TO PARENT NODE
        parent->insert(median, left, right);
    }


    //  HELPER FUNCTIONS FOR DELETION
    void checkDeficiency(BNode<T>* currNode, BNode<T>* child, int childidx) {
        if (child->count >= MIN_KEYS) {
            return;
        }
        bool resolved = false;
        //  CHECK RIGHT SIBLING
        if (childidx + 1 <= currNode->count) {
            BNode<T>* nRight = currNode->links[childidx + 1];
            if (nRight->count > MIN_KEYS) {
                int temp = nRight->arr[0];
                nRight->arr.remove_at_index(0);
                nRight->count--;

                int currNodeVal = currNode->arr[childidx];
                currNode->arr[childidx] = temp;

                child->insert(currNodeVal);
                resolved = true;
            }
        }  
        if (resolved) {
            return;
        }

        //  CHECK LEFT SIBLING
        if (childidx - 1 >= 0) {
            BNode<T>* nLeft = currNode->links[childidx - 1];
            if (nLeft->count > MIN_KEYS) {
                int temp = nLeft->arr[nLeft->count-1];
                nLeft->arr.pop_back();
                nLeft->count--;

                int currNodeVal = currNode->arr[childidx];
                currNode->arr[childidx] = temp;

                child->insert(currNodeVal);
                resolved = true;
            }
        }

        if (resolved) {
            return;
        }


        //  MERGE LEFT
        if (childidx - 1 >= 0) {
            //BNode<T>* mergedNode = new BNode<T>(order);
          
            BNode<T>* nLeft = currNode->links[childidx -1];
            nLeft->arr.push_back(currNode->arr[childidx -1]);
            nLeft->count++;
            currNode->arr.remove_at_index(childidx -1);
            currNode->count--;
            for (int i = 0 ; i < child->count; i++) {
                nLeft->arr.push_back(child->arr[i]);
                nLeft->count++;
            }
            if (!child->isLeaf) {
                for (int i = 0; i <= child->count; i++) {
                    nLeft->links.push_back(child->links[i]);
                }
            }
            delete child;
            child = nullptr;
            currNode->links.set_at_index(nLeft, childidx);
            currNode->links.remove_at_index(childidx -1);
           
            if (currNode->count == 0 && currNode == this->root) {
                this->root = nLeft;
            }
            return;
        }

        //  MERGE RIGHT
        if (childidx + 1 <= currNode->count) {
            BNode<T>* nRight = currNode->links[childidx + 1];
            nRight->arr.push_front(currNode->arr[childidx]);
            nRight->count++;
            currNode->arr.remove_at_index(childidx);
            currNode->count--;
            for (int i = 0; i < child->count; i++) {
                nRight->arr.push_front(child->arr[i]);
                nRight->count++;
            }
            
            if (!child->isLeaf) {
                for (int i = child->count; i >= 0; i--) {
                    nRight->links.push_front(child->links[i]);
                }
            }
            delete child;
            child = nullptr;
            currNode->links.set_at_index(nRight, childidx);
            currNode->links.remove_at_index(childidx + 1);

            if (currNode->count == 0 && currNode == this->root) {
                this->root = nRight;
            }
            return;
        } 
    }
    void deleteNode(BNode<T>*& currNode, const T& data) {
        if (currNode == nullptr) {
            return;
        }
        int idx = -1;
        for (int i = 0; i < currNode->count; i++) {
            if (data > currNode->arr[i]){
                idx++;
            }else{
                break;
            }
        }
        //  VALUE FOUND IN CURRENT NODE
        if (data == currNode->arr[idx + 1]) {
            if (currNode->isLeaf) {
                //currNode->arr.remove_at_index(idx + 1);
                //currNode->count--;
                deleteAtLeaf(currNode, data);
            }else{
                deleteAtInternal(currNode, data);
            }
        }
        //  FIND VALUE IN SUBTREE
        else{
            deleteNode(currNode->links[idx + 1], data);
            checkDeficiency(currNode, currNode->links[idx + 1], idx + 1);
        }
        
    }
    void deleteAtLeaf(BNode<T>*& currNode, const T& data) {
        for (int i = 0; i < currNode->count; i++) {
            if (currNode->arr[i] == data) {
                currNode->arr.remove_at_index(i);
                currNode->count--;
                break;
            }
        }
    }
    void deleteAtInternal(BNode<T>*& currNode, const T& data) {
        int idx = -1;
        for (int i = 0; i < currNode->count; i++) {
            if (data > currNode->arr[i]) {
                idx++;
            }else{
                break;
            }
        }
        
        BNode<T>* child = currNode->links[idx + 2];
        int currData = child->arr[0];
        currNode->arr[idx + 1] = currData;
        deleteNode(child, currData);
        checkDeficiency(currNode, child, idx + 2);
    }
    

    //  SEARCH
    const T& helpSearch(BNode<T>* currNode, const T& data) {
        if (currNode == nullptr) {
            return T();
        }
        int idx = -1;
        for (int i = 0; i < currNode->count; i++) {
            if (currNode->arr[i] < data) {
                idx++;
            }else{
                break;
            }
        }
        if (currNode->arr[idx + 1] == data) {
            return currNode->arr[idx + 1];
        }else{
            return helpSearch(currNode->links[idx + 1], data);
        }
    }

public:
    //  CONSTRUCTOR
    BTree(int order) 
        :order(order), MAX_KEYS(order-1),MAX_LINKS(order),MIN_KEYS(ceil(order/2.0) - 1),root(nullptr)
    {
    }

    //  DESTRUCTOR
    ~BTree() {
        while (this->root != nullptr) 
        {
            remove(this->root->arr[0]);
        }
        
    }

    //  INSERT
    void insert(const T& data) {
        //  IF ROOT IS NULL
        if (this->root == nullptr) {
            BNode<T>* newNode = new BNode<T>(order);
            newNode->isLeaf = true;
            newNode->arr.insert_at_index(data, 0);
            newNode->count++;
            this->root = newNode;
            return;
        }
        //  IF ROOT IS NOT NULL
        else{
            insertNode(this->root, data);
            
            //  IF ROOT GETS FULL
            if (this->root->arr.size() > MAX_KEYS) {
                BNode<T>* newParent = new BNode<T>(order);
                newParent->links.insert_at_index(this->root, 0);
                this->root = newParent;
                splitChild(this->root, this->root->links[0]);
            }
        }
    }

    //  REMOVE
    void remove(const T& data) {
        deleteNode(this->root, data);
    }

    const T& search(const T& data) {
        return this->helpSearch(this->root, data);
    }

    //  GETTERS
    BNode<T>* getRoot() {
        return this->root;
    }
    
    //  VISUALIZATION
    void visualizeTree(const string& dotCode) {
        ofstream dotFile("btree.dot");
        dotFile << dotCode;
        dotFile.close();
        string command = "dot -Tpng btree.dot -o btree.png";
        system(command.c_str());
        system("start btree.png");
    }

    string generateDotCode(BNode<T>* btreeRoot) {
    std::string dotCode = "digraph BTree {\n";
        dotCode += "\tnode [shape=record, height=.1];\n\n";

        std::queue<BNode<T>*> levelOrderQueue;
        vector<int> idQ;
        levelOrderQueue.push(btreeRoot);
        int count = 0;
        idQ.push_back(count);
        while (!levelOrderQueue.empty()) {
            BNode<T>* current = levelOrderQueue.front();
            levelOrderQueue.pop();
            int j = idQ[0];
            idQ.erase(idQ.begin());
            dotCode += "\tnode" + std::to_string(j) + " [label=\"";
            for (int i= 0; i < current->arr.size(); i++) {
                //char ch = current->arr[i];
                dotCode += "|";
                dotCode += current->arr[i];
            }
            dotCode += "|\"];\n";

            for (size_t i = 0; i < current->links.size(); ++i) {
                count++;
                dotCode += "\tnode" + std::to_string(j) + " -> node" + std::to_string(count) + ";\n";
                idQ.push_back(count);
                if (current->links[i]) {
                    levelOrderQueue.push(current->links[i]);
                }
            }
        }

        dotCode += "}\n";
        return dotCode;
}

/*
    void toGraphViz() {
        string x = "digraph g { node [shape = record,height=.1];";
        int i = -1;
        queue<BNode*> q;
        q.push(this->root);
        int count = 0;
        while (q.empty() == false) {
            for (int i = 0; i < q.size(); i++) {
                q.pop();
            }
            
            i++;
            string keys = "node" + to_string(i) +"[label = \"";
            BNode* n = q.front();
            q.pop();
            int k = -1;
            for (int i = 0; i < n->count; i++) {
                k++;
                keys += "<f" + to_string(k) + "> |" + to_string(n->arr[i]) + "|";
                q.push(n->links[i]);
            }
            keys += "\"];";
            q.push(n->links[n->count]);
            string strLinks = "";
            
        }
    }   
*/
};



int main() {

    BTree<char> t(5);
    t.insert('C');
    t.insert('N');
    t.insert('G');
    t.insert('A');
    t.insert('H');
    t.insert('E');
    t.insert('K');
    t.insert('Q');
    t.insert('M');
    t.insert('F');
    t.insert('W');
    t.insert('L');
    t.insert('T');
    t.insert('Z');
    t.insert('P');
    t.insert('R');
    t.insert('X');
    t.insert('Y');
    t.insert('D');
    t.insert('S');

    
    //  CHECK LEAVES
    //t.remove('H');
    //t.remove('T');
    //t.remove('R');
    //t.remove('E');
    
    //  CHECK INTERNAL
    t.remove('H');
    t.remove('T');
    t.remove('D');

    //  SEARCH
    // char ch = t.search('S');

    string code = t.generateDotCode(t.getRoot());
    t.visualizeTree(code);
    return 0;
}
