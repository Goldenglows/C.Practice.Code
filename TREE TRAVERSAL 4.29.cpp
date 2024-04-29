#include <iostream>
#include <queue>
using namespace std;

struct CNode {
	char data;
	CNode* child;
	CNode* brother;
};

CNode* createNode(char data) {
	CNode* newnode = new CNode;
	newnode->data = data;
	newnode->child = nullptr;
	newnode->brother = nullptr;
	return newnode;
}

void addtree(CNode*& root, char data) {
	if (root == nullptr)
		root = createNode(data);
	else {
		CNode* current = root;
		while (current->brother != nullptr)
			current = current->brother;
		current->brother = createNode(data);
	}	
}

void pretraversal(CNode* root) {
	if (root == nullptr) return;
	cout << root->data << " ";
	pretraversal(root->child);	
	pretraversal(root->brother);
}

void inordertraversal(CNode* root) {
	if (root == nullptr) return;
	inordertraversal(root->child);
	cout << root->data << " ";
	inordertraversal(root->brother);
}

void posttraversal(CNode* root) {
	if (root == nullptr) return;
	posttraversal(root->child);
	posttraversal(root->brother); 
	cout << root->data << " ";
}

int main() {
	CNode* root = nullptr;
	queue<char> nodeQueue;
	cout << "please input data (input # means end:"<<endl;
	char input;
	while (cin >> input && input != '#')
		nodeQueue.push(input);
	while (!nodeQueue.empty()) {
		addtree(root, nodeQueue.front());
		nodeQueue.pop();
	}

	cout << "PreorderTraversal:" << endl;
	pretraversal(root);
	cout << endl;

	cout << "InorderTraversal:" << endl;
	inordertraversal(root);
	cout << endl;

	cout << "PostoderTraversal:" << endl;
	posttraversal(root);
	cout << endl;

	return 0;

}