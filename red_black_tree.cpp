#include <iostream>
using namespace std;

struct node {
	node* parent;
	node* leftNode;
	node* rightNode;
	node* root;

	int value{};
	char color;
};

void addElement(node*& root, int value) {
	if (root == NULL) {
		root = new node();
		root->value = value;
		root->parent = NULL;
	}
	else {
		node* temp = root;
		node* temp2 = new node();
		temp2->value = value;

		while (temp != NULL) {
			if (temp->value < value) {
				temp->leftNode = temp2;
				temp2->color = 'RED';
				temp2->parent = temp;

				break;
			}
			else {
				if (temp->rightNode == NULL) {
					temp2->rightNode == temp2;
					temp2->color = 'RED';
					temp2->parent = temp;

					break;
				}
			}
		}
	}
}

void clearTree(node*& newNode) {
	if (newNode == NULL)
		return;

	clearTree(newNode->parent);
	clearTree(newNode->leftNode);
	clearTree(newNode->rightNode);

	delete newNode;
	newNode = nullptr;

	return;
}

node* find(node*& root, int value) {
	node* add = root;
	while (add != NULL && value != add->value) {
		if (value < add->value)
			add = add->leftNode;
		else
			add = add->rightNode;
	}

	return add;
}

bool add(node*& root, int value) {
	node* temp = root;
	node* parent = temp;

	while (temp != NULL && value != temp->value) {
		parent = temp;
		if (value < temp->value)
			temp = temp->leftNode;
		else
			temp = temp->rightNode;
	}

	if (temp != NULL)
		return false;

	node* newNode = new node();
	newNode->value = value;
	newNode->color = 'RED';
	newNode->parent = parent;

	if (value > parent->value)
		parent->rightNode = newNode;
	else
		parent->leftNode = newNode;

}


void leftRotate(node* l) {
	node* newNode = new node();

	if (l->leftNode->rightNode)
		newNode->rightNode = l->rightNode->leftNode;

	newNode->leftNode = l->leftNode;
	newNode->value = l->value;
	newNode->color = l->color;
	l->value = l->rightNode->value;
	l->leftNode = newNode;

	if (newNode->leftNode)
		newNode->leftNode->parent = newNode;

	if (newNode->rightNode)
		newNode->rightNode->parent = newNode;

	newNode->parent = l;

	if (l->rightNode->rightNode)
		l->rightNode = l->rightNode->rightNode;
	else
		l->rightNode = nullptr;

	if (l->rightNode)
		l->rightNode->parent = l;
}

void rightRotate(node* r) {
	node* newNode = new node();

	if (r->rightNode->leftNode)
		newNode->leftNode = r->leftNode->rightNode;

	newNode->rightNode = r->rightNode;
	newNode->value = r->value;
	newNode->color = r->color;
	r->value = r->leftNode->value;
	r->rightNode = newNode;

	if (newNode->rightNode)
		newNode->rightNode->parent = newNode;

	if (newNode->leftNode)
		newNode->leftNode->parent = newNode;

	newNode->parent = r;

	if (r->leftNode->leftNode)
		r->leftNode = r->leftNode->leftNode;
	else
		r->leftNode = nullptr;

	if (r->leftNode)
		r->leftNode->parent = r;
}

void display(node*& newNode) {
	if (newNode == NULL)
		return;

	display(newNode->leftNode);
	cout << newNode->value << endl;
	display(newNode->rightNode);
}


void displayPOrder(node* node1, int value, char color) {
	cout << "<" << color << ">" << value << endl;

	displayPOrder(node1->leftNode, value, color);
	displayPOrder(node1->rightNode, value, color);
}

void displayIOrder(node* node1, int value, char color)
{
	cout << "<" << color << ">" << value << endl;

	displayPOrder(node1->leftNode, value, color);
	displayPOrder(node1->rightNode, value, color);
}

int main()
{
	node* zm = 0;
	addElement(zm, 6);
	clearTree(zm);
	addElement(zm, 7);
	display(zm);
	return 0;
}
