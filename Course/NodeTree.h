#pragma once
#pragma once
enum Color {
	black,
	red,
};
template <typename Key, typename Value>
class NodeTree
{
public:
    Color color;
	NodeTree<Key, Value>* left, *right, *parent;
	Key key;
	Value value;

	NodeTree() : color(red), left(nullptr), right(nullptr), parent(nullptr) {}
	NodeTree(Key key, Value value) : color(red), left(nullptr), right(nullptr), parent(nullptr), key(key), value(value) {}
	bool isOnLeft() { return this == parent->getLeft(); }
	NodeTree<Key, Value>* brother() {
		 
		if (parent == nullptr)					//brother null if no parent
			return nullptr;
		if (isOnLeft())
			return parent->right;
		return parent->left;
	}
	bool hasRedChild() {
		return (left != nullptr && left->getColor() == red) || (right != nullptr && right->getColor() == red);
	}

	void setColor(Color color) {
		this->color = color;
	}

	Color getColor() {
		if (this == nullptr)
			return black;
		return color;
	}

	void setLeft(NodeTree* ptr)
	{
		left = ptr;
	}

	NodeTree* getLeft()
	{
		return left;
	}

	void setRight(NodeTree* ptr)
	{
		right = ptr;
	}

	NodeTree* getRight()
	{
		return right;
	}

	void setParent(NodeTree* parent) {
		this->parent = parent;
	}

	NodeTree* getParent() {
		return parent;
	}

	void setKey(Key key)
	{
		this->key = key;
	}

	Key getKey()
	{
		return key;
	}

	void setValue(Value value)
	{
		this->value = value;
	}

	Value getValue()
	{
		return value;
	}
};
