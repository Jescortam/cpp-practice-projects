#pragma once
#include <iostream>
#include <queue>

// Asks for the user's choice
int inputChoice(int limit);

// Ask for the user's value
int inputValue();

class BinarySearchTree
{
private:
	class Node
	{
	private:
		// Value of the element
		int data = 0;

		// Child nodes
		Node* left = nullptr;
		Node* right = nullptr;

	public:
		// Constructor
		Node(int p_data) : data(p_data) {}

		// Gets the data or the address of the child nodes
		int getData() { return data; }
		Node* getLeft() { return left; }
		Node* getRight() { return right; }

		// Sets the data or the address of the child nodes
		void setData(int new_data) { data = new_data; }
		void setLeft(Node* new_left) { left = new_left; }
		void setRight(Node* new_right) { right = new_right; }

		// Prints the data of the node in square brackets
		void printData() { std::cout << "[" << data << "]"; }
	};

	// Root node
	Node* root = nullptr;

	// Number of nodes
	int nodeCount = 0;

public:

	// Adds a value in the tree
	bool add(int elem);

	// Removes a value from the tree
	bool remove(int elem);

	// Checks if a value is in the tree
	bool contains(int elem) { return contains(root, elem); }

	// Traverse the tree
	void traverse();

	// Clears the tree
	void clearTree();

	// Checks if the tree is empty
	bool isEmpty() { return nodeCount == 0; }

private:
	// Does the adding
	Node* add(Node* node, int elem);

	// Does the removal
	Node* remove(Node* node, int elem);

	// Does the checking
	bool contains(Node* node, int elem);

	// In-order
	void trav_inOrder(Node* node);

	// Reverse In-order
	void trav_revInOrder(Node* node);

	// Pre-order
	void trav_preOrder(Node* node);

	// Post-order
	void trav_postOrder(Node* node);

	// Level Order
	void trav_levelOrder(Node* node);

	// Finds the "lesser" (?) value
	Node* findMin(Node* node);

	// Clears the tree of nodes
	Node* clearTree(Node* node);
};


// Adds a value in the tree
bool BinarySearchTree::add(int elem)
{
	// If the value is already there, don't do anything
	if (contains(elem)) return false;

	// Leave the recursion do its job
	root = add(root, elem);
	nodeCount++;
	return true;
}

// Removes a value from the tree
bool BinarySearchTree::remove(int elem)
{
	if (contains(elem))
	{
		root = remove(root, elem);
		nodeCount--;
		return true;
	}

	return false;
}

// Traverse the tree
void BinarySearchTree::traverse()
{
	// Displays every option available
	std::cout << "\nChoose the type of traversal.\n";
	std::cout << "1. In-order			(In ascending order).\n";
	std::cout << "2. Reverse In-order	(In descending order).\n";
	std::cout << "3. Pre-order			(First the parent, then the children).\n";
	std::cout << "4. Post-order			(First the children, then the parten).\n";
	std::cout << "5. Level Order		(Visits every node in a level, then goes to the next one).\n\n";

	// Chooses a traversal type
	int choice = inputChoice(5);

	std::cout << "\n\nSize: " << nodeCount;

	switch (choice)
	{
	case 1:	// In-order
		std::cout << "\n\nIn-order:\n";
		trav_inOrder(root);
		break;
	case 2:	// Reverse In-order
		std::cout << "\n\n Reverse In-order:\n";
		trav_revInOrder(root);
		break;
	case 3:	// Pre-order
		std::cout << "\n\nPre-order:\n";
		trav_preOrder(root);
		break;
	case 4:	// Post-order
		std::cout << "\n\nPost-order:\n";
		trav_postOrder(root);
		break;
	case 5:	// Level Order
		std::cout << "\n\n Level Order:\n";
		trav_levelOrder(root);
		break;
	}
}

// Clears the tree
void BinarySearchTree::clearTree()
{
	root = clearTree(root);
	if (isEmpty()) std::cout << "\nTree cleared successfully.\n";
	else std::cout << "\nERROR: Something went wrong.\n";
}

// Does the adding
BinarySearchTree::Node* BinarySearchTree::add(Node* node, int elem)
{
	// If there isn't a node, insert it there
	if (node == nullptr)
		node = new Node(elem);

	else
	{
		// Check if it's going to be in the left or right branch
		int comparison = elem - node->getData();

		// Left branch
		if (comparison < 0)
			node->setLeft(add(node->getLeft(), elem));

		// Right branch
		else if (comparison > 0)
			node->setRight(add(node->getRight(), elem));
	}

	// Return to the root node
	return node;
}

// Does the removal
BinarySearchTree::Node* BinarySearchTree::remove(Node* node, int elem)
{
	// Check if it's going to be in the left or right branch
	int comparison = elem - node->getData();

	// Left branch
	if (comparison < 0)
		node->setLeft(remove(node->getLeft(), elem));

	// Right branch
	else if (comparison > 0)
		node->setRight(remove(node->getRight(), elem));

	else
	{
		// If the left branch is empty, use the right node
		if (node->getLeft() == nullptr)
			return node->getRight();

		// If the right branch is empty, use the left node
		else if (node->getRight() == nullptr)
			return node->getLeft();

		// If no branch is empty, find the minimum (?) value in the right branch
		else
		{
			// Make that node the parent
			Node* temp = findMin(node);
			node->setData(temp->getData());

			// Remove the repeated node below
			node->setRight(remove(node->getRight(), temp->getData()));
		}
	}

	return node;
}

// Does the checking
bool BinarySearchTree::contains(Node* node, int elem)
{
	// If where the node would be is empty, return false
	if (node == nullptr) return false;

	// Check if it's going to check at the left or right branch
	int comparison = elem - node->getData();

	// Left branch
	if (comparison < 0)
		return contains(node->getLeft(), elem);

	// Right branch
	else if (comparison > 0)
		return contains(node->getRight(), elem);

	// If found, return true
	else return true;
}

// In-order
void BinarySearchTree::trav_inOrder(Node* node)
{
	if (node == nullptr) return;

	trav_inOrder(node->getLeft());
	node->printData();
	trav_inOrder(node->getRight());
}

// Reverse In-order
void BinarySearchTree::trav_revInOrder(Node* node)
{
	if (node == nullptr) return;

	trav_revInOrder(node->getRight());
	node->printData();
	trav_revInOrder(node->getLeft());
}

// Pre-order
void BinarySearchTree::trav_preOrder(Node* node)
{
	if (node == nullptr) return;
	
	node->printData();
	trav_preOrder(node->getLeft());
	trav_preOrder(node->getRight());
}

// Post-order
void BinarySearchTree::trav_postOrder(Node* node)
{
	if (node == nullptr) return;

	trav_postOrder(node->getLeft());
	trav_postOrder(node->getRight());
	node->printData();
}

// Level Order
void BinarySearchTree::trav_levelOrder(Node* node)
{
	if (node == nullptr) return;

	std::queue<Node*> printQueue;
	printQueue.push(node);
	while (!printQueue.empty())
	{
		Node* front = printQueue.front();
		front->printData();

		if (front->getLeft() != nullptr) 
			printQueue.push(front->getLeft());
		if (front->getRight() != nullptr) 
			printQueue.push(front->getRight());

		printQueue.pop();
	}
}

// Finds the "lesser" (?) value
BinarySearchTree::Node* BinarySearchTree::findMin(Node* node)
{
	// Keep going left until it founds a leaf node and return that node
	while (node->getLeft() != nullptr) node = node->getLeft();
	return node;
}

// Clears the tree of nodes
BinarySearchTree::Node* BinarySearchTree::clearTree(Node* node)
{
	if (node != nullptr)
	{
		node->setLeft(clearTree(node->getLeft()));
		node->setRight(clearTree(node->getRight()));
		delete node;
		nodeCount--;
	}
	return nullptr;
}

// Asks for the user's choice
int inputChoice(int limit)
{
	int choice;
	while ((std::cout << "Enter your choice: ") && (!(std::cin >> choice) || (choice < 1) || (choice > limit)))
	{
		std::cerr << "\tError: Invalid choice.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return choice;
}

// Ask for the user's value
int inputValue()
{
	int value;
	while ((std::cout << "Enter the value: ") && (!(std::cin >> value)))
	{
		std::cerr << "\tError: Invalid choice.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return value;
}