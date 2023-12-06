#include<iostream>
#include<queue>
#include<string>
#include <fstream>
#include "vector.h"
using namespace std;
int order = 3;
template <class T>
class Node {
public:
	Vector<T> keys;
	Vector<Node*> child;
	int count;
	Node* parent;
	Node() {
		count = 0;
		child.resize(order + 2, nullptr);
	}
	int partition(Vector<T>& arr, int low, int high) {
		T pivot = arr[high];
		int i = (low - 1);
		for (int j = low; j <= high; j++) {
			if (arr[j] < pivot) {
				i++;
				std::swap(arr[i], arr[j]);
			}
		}
		i++;
		std::swap(arr[i], arr[high]);
		return i;
	}
	void quicksort(Vector<T>& arr, int low, int high) {
		if (low < high) {
			int pivot = partition(arr, low, high);
			quicksort(arr, low, pivot - 1);
			quicksort(arr, pivot + 1, high);
		}
	}
	//simple quick sort to sort the keys in a node
	~Node() {
		child.clear();
		keys.clear();
	}
};
template <class T>
class btree {
public:
	Node<T>* root;
public:
	btree() {
		root = nullptr;
	}
	void merge(Node<T>* root, Node<T>* s, bool& b) {
		int l = 0;
		while (root->child[l] != NULL && root->child[l]->keys[0] != s->keys[0]) l++;
		int m = 0;
		Vector<Node<T>*> temp(order, nullptr);
		int hello = 0;
		while (s->child[m] != NULL) {
			if (root->child[l] && root->child[l] != s) {
				temp[hello] = root->child[l];
				hello++;
			}
			root->child[l] = s->child[m];
			m++;
			l++;
		}
		int d = l;
		while (root->child[d]) {
			temp[hello] = root->child[d];
			hello++;
			d++;
		}
		hello = 0;
		while (temp[hello]) {
			root->child[l] = temp[hello];
			l++;
			hello++;
			b = 1;
		}
	}
	Node<T>* insert(T& k, Node<T>* root, int& i, bool& b) {
		if (root == nullptr)//if root is null simply create a node
		{
			root = new Node<T>;
			root->keys[root->count] = k;
			root->count++;
			return root;
		}
		Node<T>* s = NULL;
		if (k > root->keys[i] && i + 1 < root->count) {
			i = i + 1;
			s = insert(k, root, i, b);
			//if the item to be added is less than the current key
			// increment i (which represents the current index of key)
			//and recursevely call the insert function
			if (s != NULL && root != s)
			{	// if insetion return a value it means the two nodes need to be merged
				merge(root, s, b);
				root->keys[root->count] = s->keys[0];
				root->count++;
				delete s;
				s = NULL;
			}
			// sort the indexes before returning
			root->quicksort(root->keys, 0, root->count - 1);
			return root;
		}

		else if (root->child[i] && k < root->keys[i]) {
			int j = i;
			i = 0;
			s = insert(k, root->child[j], i, b);
			i = j;
		}
		// if the item if less than key it means we need to go to its child
		// left child is always i and right child of key is i+1( its a hint)
		// recursevely call its child  
		else if (root->child[i + 1] && k > root->keys[i]) {
			int j = i + 1;
			i = 0;
			s = insert(k, root->child[j], i, b);
			i = j;
		}
		// recurseve 
		// call
	//the first two conditions were to make sure we are at the leaf node 
		if (root->count < order - 1 && b == 0)
		{	//if count is less than order -1 this means we can insert in this node
			if (s != NULL)
			{
				merge(root, s, b);// if the upper condition returned an s we need to merge it
				//with this root
				delete s;
				s = NULL;
			}
			root->keys[root->count] = k;
			root->count++;
			b = 1;
			//Sort before returning

		}
		else if (root->count == order - 1 && b == 0) {
			// It meand we need to split 
			//For spliting we need to first add the node then split it
			if (s != NULL)
			{
				merge(root, s, b);
				root->keys[root->count] = s->keys[0];
				root->count++;
				delete s;
				s = NULL;
			}
			else {
				root->keys[root->count] = k;//add k
				root->count++;
			}
			splitting(k, root, i, b);
		}
		root->quicksort(root->keys, 0, root->count - 1);
		if (s != NULL && b == 0)
			merge(root, s, b);
		return root;
	}
	void splitting(T& k, Node<T>* root, int& i, bool& b) {
		int n;
		if (order % 2 == 1)
			n = root->count / 2;
		else {
			n = root->count / 2 - 1;
		}
		root->quicksort(root->keys, 0, root->count - 1);
		Vector<Node<T>*> temp(order + 1, nullptr);
		int index = 0;
		//First we will save its child as we are creating newer ones
		while (root->child[index])
		{
			temp[index] = root->child[index];
			root->child[index] = NULL;
			index++;
		}
		int l = 0;
		//recursively save all its values lesser than n in its left child which mean 0 child
		root->child[0] = NULL;
		for (int j = 0; j <= n - 1; j++) {
			root->child[0] = insert(root->keys[j], root->child[0], i, b);
			b = 0;
			l++;
		}
		b = 0;
		index = 0;
		// Give the saved child to newly created 0  indexed child
		while (index <= n && temp[index])
		{
			root->child[0]->child[index] = temp[index];
			index++;
		}
		//recursively save all its values greater than n in its right child which mean 1 indexed
		root->child[1] = NULL;
		for (int j = n + 1; j < root->count; j++) {
			root->child[1] = insert(root->keys[j], root->child[1], i, b);
			b = 0;
			l++;
		}
		int index1 = n + 1;
		int index2 = 0;
		// Give the saved child to newly created 1  indexed child
		while (index1 <= order && temp[index1])
		{
			root->child[1]->child[index2] = temp[index1];
			index1++;
			index2++;
		}
		b = 0;
		k = root->keys[n];
		root->keys[0] = root->keys[n];
		root->count -= l;
	}
	void insertion(T k) {
		Node<T>* temp = root;
		bool b = 0;
		int i = 0;
		root = insert(k, temp, i, b);
	}
	void traverse(Node<T>* root) {
		int i;
		for (i = 0; i < root->count; i++) {
			if (root->child[i] != nullptr) {
				traverse(root->child[i]);
			}

			cout << root->keys[i] << " ";
		}

		if (root->child[i] != nullptr) {
			traverse(root->child[i]);
		}
	}
	void levelOrderTraversal(Node<T>* root) {
		if (!root)
			return;
		std::queue<Node<T>*> q;
		q.push(root);

		while (!q.empty()) {
			int nodesAtCurrentLevel = q.size();

			for (int i = 0; i < nodesAtCurrentLevel; ++i) {
				Node<T>* current = q.front();
				q.pop();
				for (int j = 0; j < current->count; ++j) {
					std::cout << current->keys[j] << " ";
				}
				for (int j = 0; j <= current->count; ++j) {
					if (current->child[j] != nullptr) {
						q.push(current->child[j]);
					}
				}
			}
		}
	}
	void traversal() {
		Node<T>* temp = root;
		levelOrderTraversal(temp);
	}
	void destroyTree(Node<T>* node) {
		if (node != nullptr) {
			for (int i = 0; i < node->count + 1; i++) {
				if (node->child[i])
					destroyTree(node->child[i]);
				//else break;
			}
			if (node) {
				//node->deletenode();
				delete node;
				node = NULL;
			}
		}
	}
	~btree() {
		destroyTree(root);
	}

};


