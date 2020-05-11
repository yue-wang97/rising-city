#include <iomanip>
#include <iostream>
using namespace std;

enum RBTColor { RED, BLACK };


class RBTNode {
public:
	RBTColor color;    // color
	int key;  // key=buidingNumber
	int executed_time;
	int total_time;
	RBTNode* left;    // left child
	RBTNode* right;    // right child
	RBTNode* parent; // parent node


	RBTNode(int value, int et, int tt, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :
		key(value), executed_time(et), total_time(tt), color(c), parent(), left(l), right(r){}
};


class RBTree {
public:
	RBTNode* rbroot;    // root node

public:
	RBTree();
	~RBTree();



	// (non-recursive implementation) look for nodes with buildingNum in the red-black tree
	RBTNode* lookfor(int key);

	// find mini node, return key
	int mini();
	// find max node, return key
	int maxnode();

	// Find the successor of the node (x).That is, look for the smallest node in the red-black tree where the data value is greater than that node.
	RBTNode* after(RBTNode* x);
	// Find the before of the node (x).That is, look for the largest node in the red-black tree where the data value is less than that node.
	RBTNode* before(RBTNode* x);

	// Insert the node (buildingNum is the node key) into the red-black tree
	RBTNode* insert(int key, int executed_time, int total_time);

	// Delete node (buildingNum is the node key)
	void deletenode(int key);

	// delete the whole tree
	void deletetree();

	//return building number=num1
	string  buildingnum(int num1);
	//return building between num1 and num2
	string  buildingnum(int num1,int num2);
	void getinOrder(RBTNode* tree, int num1, int num2,string* a);
public:

	// (non-recursive implementation) look for nodes with buildingNum in the red-black tree
	RBTNode* lookfor(RBTNode* x, int key) const;
	// Find minimum: returns the minimum of a red-black tree whose tree is the root.
	RBTNode* mini(RBTNode* tree);
	// Find the largest node: returns the largest node of a red-black tree whose tree is the root.
	RBTNode* maxnode(RBTNode* tree);

	// left rotation
	void llro(RBTNode*& root, RBTNode* x);
	// right rotatiod
	void rrro(RBTNode*& root, RBTNode* y);
	// insert node
	void insert(RBTNode*& root, RBTNode* node);
	// Insertion correction function
	void fixtree(RBTNode*& root, RBTNode* node);
	// delete node
	void deletenode(RBTNode*& root, RBTNode* node);
	// fix up after delete
	void fixAfterDelete(RBTNode*& root, RBTNode* node, RBTNode* parent);
	// delete tree
	void deletetree(RBTNode*& tree);


#define find_parent(r)   ((r)->parent)
#define find_co(r) ((r)->color)
#define red_node(r)   ((r)->color==RED)
#define black_node(r)  ((r)->color==BLACK)
#define define_black(r)  do { (r)->color = BLACK; } while (0)
#define define_red(r)  do { (r)->color = RED; } while (0)
#define define_father(r,p)  do { (r)->parent = (p); } while (0)
#define define_col(r,c)  do { (r)->color = (c); } while (0)
};

/*
 * constructor function
 */

RBTree::RBTree() :rbroot(NULL)
{
	rbroot = NULL;
}

/*
 * 析构函数
 */

RBTree::~RBTree()
{
	deletetree();
}

/*
 * (non-recursive implementation) look for nodes with buildingNum in "red-black tree x"
 input:x: the node beginning search
		data:look for the node which builidng number=data
output: return searched node.
 */

RBTNode* RBTree::lookfor(RBTNode* x, int data) const
{
	while ((x != NULL) && (x->key != data))
	{
		if (data < x->key)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}


RBTNode* RBTree::lookfor(int buildingNum)
{
	return lookfor(rbroot, buildingNum);
}

/*
 * Find mini: returns the mini of a red-black tree whose tree is the root.
 */

RBTNode* RBTree::mini(RBTNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}


int RBTree::mini()
{
	RBTNode* p = mini(rbroot);
	if (p != NULL)
		return p->key;

	return (int)NULL;
}

/*
 * Find the largest node: returns the largest node of a red-black tree whose tree is the root.
 */

RBTNode* RBTree::maxnode(RBTNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}


int RBTree::maxnode()
{
	RBTNode* p = maxnode(rbroot);
	if (p != NULL)
		return p->key;

	return (int)NULL;
}

/*
 * Find the after of the node (x).That is, look for the smallest node in the red-black tree where the data value is greater than that node.
 */

RBTNode* RBTree::after(RBTNode* x)
{
	// If x has a right child, then "the successor of x" is "the smallest node of a subtree with its right child as root".
	if (x->right != NULL)
		return mini(x->right);

	// if x has no right child.Then x has the following two possibilities:
	// (01) x is "a left child", then "the successor of x" is "its parent".
	// (02) x is "a right child", look for "the lowest parent of x, and the parent must have a left child", and find the "lowest parent" is "the successor of x".
	RBTNode* y = x->parent;
	while ((y != NULL) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
 * Find the precursor of the node (x).That is, look for the largest node in the red-black tree where the data value is less than that node.
 */

RBTNode* RBTree::before(RBTNode* x)
{
	// if x has a left child, then "the precursor of x" is "the largest node of a subtree with its left child as root".
	if (x->left != NULL)
		return maxnode(x->left);

	// if x has no left child.Then x has the following two possibilities:
	// (01) x is "a right child", then "the precursor of x" is "its parent".
	// (01) x is "a left child", then find "the lowest parent of x, and the parent must have a right child", and find the "lowest parent" is "the precursor of x".
	RBTNode* y = x->parent;
	while ((y != NULL) && (x == y->left))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
 *Rotate the node (x) of the red-black tree to the left
*
* sinistral diagram (sinistral on node x) :
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(left rotation)-->  / \                #
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 *
 *
 */

void RBTree::llro(RBTNode*& root, RBTNode* x)
{
	
	RBTNode* y = x->right;

	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// set "father of x" to "father of y"
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;           // if the "father of x" is an empty node, set y as the root node
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // if x is the left child of its parent node, set y to be the "left child of the parent node of x"
		else
			x->parent->right = y;   // if x is the right child of its parent node, set y to be the right child of the parent node of x.
	}

	// set "x" to "left child of y"
	y->left = x;
	// set "parent node of x" to "y"
	x->parent = y;
}

/*
 * Rotate the node (y) of the red-black tree to the right
*
* dextrorotatory diagram (sinistral on node y) :
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(r rotation         /  \                     #
 *        x   ry                           lx   y
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 *
 */

void RBTree::rrro(RBTNode*& root, RBTNode* y)
{
	RBTNode* x = y->left;

	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x;            
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;   
		else
			y->parent->left = x;   
	}


	x->right = y;


	y->parent = x;
}

/*
 * / *
* red-black tree inserts correction function
*
* call this function after inserting a node into the red-black tree (losing balance);
* the aim is to recreate it as a red-black tree.
*
* parameter description:
* root of a red-black tree
* the node inserted by node // corresponds to z in introduction to algorithms
* /
 */

void RBTree::fixtree(RBTNode*& root, RBTNode* node)
{
	RBTNode* parent, * gparent;

	// if "parent node exists and the color of parent node is red"
	while ((parent = find_parent(node)) && red_node(parent))
	{
		gparent = find_parent(parent);

		
		if (parent == gparent->left)
		{
			// Case 1// condition: uncle node is red
			{
				RBTNode* uncle = gparent->right;
				if (uncle && red_node(uncle))
				{
					define_black(uncle);
					define_black(parent);
					define_red(gparent);
					node = gparent;
					continue;
				}
			}

			// Case 2Condition: uncle is black, and the current node is right child
			if (parent->right == node)
			{
				RBTNode* tmp;
				llro(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3Condition: uncle is black, and the current node is left child.
			define_black(parent);
			define_red(gparent);
			rrro(root, gparent);
		}
		else//If "the father of z" is "the right child of the grandfather of z"
		{
			// Case 1Condition: uncle node is red
			{
				RBTNode* uncle = gparent->left;
				if (uncle && red_node(uncle))
				{
					define_black(uncle);
					define_black(parent);
					define_red(gparent);
					node = gparent;
					continue;
				}
			}

			// Case 2Condition: uncle is black, and the current node is left child
			if (parent->left == node)
			{
				RBTNode* tmp;
				rrro(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3Condition: uncle is black, and the current node is right child。
			define_black(parent);
			define_red(gparent);
			llro(root, gparent);
		}
	}

	// Set the root node to black
	define_black(root);
}

/*
 *Insert the node into the red-black tree
*
* parameter description:
* root of the red-black tree
* the node inserted      
 */
void RBTree::insert(RBTNode*& root, RBTNode* node)
{
	RBTNode* y = NULL;
	RBTNode* x = root;

	//1. Treat the red-black tree as a binary search tree and add nodes to the binary search tree.
	while (x != NULL)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != NULL)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	node->color = RED;

	// Fix it to a binary search tree
	fixtree(root, node);
}

/*
 * / *
* insert the node (buildingNum is the node key) into the red-black tree
*
* parameter description:
* the root of a red-black tree
* buildingNum inserts the key of the node
* /
 */

RBTNode* RBTree::insert(int buildingNum, int executed_time, int total_time)
{
	RBTNode* z = NULL;

	if ((z = new RBTNode(buildingNum, executed_time, total_time, BLACK, NULL, NULL, NULL)) == NULL)
		return NULL;
	
	insert(rbroot, z);
	return z;


}

/*
 * Delete the redblack tree correction function
*
* call this function after removing the insert node from the red-black tree (the red-black tree is out of balance);
* the aim is to recreate it as a red-black tree.
*
* parameter description:
* root of a red-black tree
* node to be fixed
 */

void RBTree::fixAfterDelete(RBTNode*& root, RBTNode* node, RBTNode* parent)
{
	RBTNode* other;

	while ((!node || black_node(node)) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (red_node(other))
			{
			
				define_black(other);
				define_red(parent);
				llro(root, parent);
				other = parent->right;
			}
			if ((!other->left || black_node(other->left)) &&
				(!other->right || black_node(other->right)))
			{
		
				define_red(other);
				node = parent;
				parent = find_parent(node);
			}
			else
			{
				if (!other->right || black_node(other->right))
				{
					
					define_black(other->left);
					define_red(other);
					rrro(root, other);
					other = parent->right;
				}
			
				define_col(other, find_co(parent));
				define_black(parent);
				define_black(other->right);
				llro(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (red_node(other))
			{
				 
				define_black(other);
				define_red(parent);
				rrro(root, parent);
				other = parent->left;
			}
			if ((!other->left || black_node(other->left)) &&
				(!other->right || black_node(other->right)))
			{
		
				define_red(other);
				node = parent;
				parent = find_parent(node);
			}
			else
			{
				if (!other->left || black_node(other->left))
				{
				  
					define_black(other->right);
					define_red(other);
					llro(root, other);
					other = parent->left;
				}
			
				define_col(other, find_co(parent));
				define_black(parent);
				define_black(other->left);
				rrro(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		define_black(node);
}

/** delete the node (node) and return the deleted node
*
* parameter description:
* root of the red-black tree
* node deleted
 */

void RBTree::deletenode(RBTNode*& root, RBTNode* node)
{
	RBTNode* child, * parent;
	RBTColor color;

	
	if ((node->left != NULL) && (node->right != NULL))
	{

		RBTNode* replace = node;

	
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;


		if (find_parent(node))
		{
			if (find_parent(node)->left == node)
				find_parent(node)->left = replace;
			else
				find_parent(node)->right = replace;
		}
		else
		
			root = replace;

		child = replace->right;
		parent = find_parent(replace);
	
		color = find_co(replace);

	
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
		
			if (child)
				define_father(child, parent);
			parent->left = child;

			replace->right = node->right;
			define_father(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
			fixAfterDelete(root, child, parent);

		delete node;
		return;
	}

	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;

	color = node->color;

	if (child)
		child->parent = parent;


	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == BLACK)
		fixAfterDelete(root, child, parent);
	delete node;
}

/*
 * Delete the node in the red-black tree with buildingNum key
*
* parameter description:
* the root of a red-black tree
 */

void RBTree::deletenode(int buildingNum)
{
	RBTNode* node;
	// 查找buildingNum对应的节点(node)，找到的话就删除该节点
	if ((node = lookfor(rbroot, buildingNum)) != NULL)
		deletenode(rbroot, node);
}

/*
 * delete rbtree
 */

void RBTree::deletetree(RBTNode*& tree)
{
	if (tree == NULL)
		return;

	if (tree->left != NULL)
		return deletetree(tree->left);
	if (tree->right != NULL)
		return deletetree(tree->right);

	delete tree;
	tree = NULL;
}


void RBTree::deletetree()
{
	deletetree(rbroot);
}

//input: num=building numer waiting to print
//return will output the (buildingNum,executed_time,total_time) triplet if the buildingNum exists. If not return (0,0,0).
string RBTree::buildingnum(int num)
{
	string triplet1 = "(0,0,0)";
	RBTNode* aa = lookfor(rbroot, num);
	if (aa) {
		triplet1 = "(" + to_string(aa->key) + "," + to_string(aa->executed_time) + "," 
			+ to_string(aa->total_time) + ")";
		return triplet1;
	}
	else return triplet1;
}

//will output all (buildingNum,executed_time,total_time)
//triplets separated by commas in a single line including buildingNum1 and buildingNum2;
//if they exist. If there is no building in the specified range, output (0,0,0). 
//You should not print an additional comma at the end of the line.
//input:num1=begin builidng number; num2=end building number
string RBTree::buildingnum(int num1, int num2)
{
	string triplet1 = "";
	string *tring = &triplet1;
	getinOrder(rbroot, num1, num2, tring);
	triplet1 = triplet1.substr(0, triplet1.length() - 1);
	if (triplet1 != "")
		return triplet1;
	else return "????";
}
//input:
//tree=red black tree;num1=begin building number;num2:end building number; tripliet=a string
//saving the tuples between num1 and num2
//funciton: search the builidngs which builidng number is between num1 and num2, and save these
//builidngs data(building number,excuted time, total time) to triplet1
void RBTree::getinOrder(RBTNode* tree, int num1,int num2,string* triplet1)
{
	if (tree != NULL)
	{
		getinOrder(tree->left, num1, num2, triplet1);
		if(num1<= tree->key && tree->key <=num2)
			*triplet1 += "(" + to_string(tree->key) + "," 
			+ to_string(tree->executed_time) + "," + to_string(tree->total_time) + "),";
		getinOrder(tree->right, num1, num2, triplet1);
	}
}
/***  stack
string RBTree::getBuilding(int num1, int num2) {
	RBTNode *list = new RBTNode[];
	if (num1 > num2 || rbroot == NULL) {
		return list;
	}

	Stack<Node> stack = new Stack<>();
	stack.push(dummy);
	while (!stack.isEmpty()) {
		Node node = stack.pop();
		if (node != dummy) {
			int nodeNum = node.lou.getNum();
			if (nodeNum >= num1 && nodeNum <= num2) {
				list.add(node.lou);
			}
			if (nodeNum > num2) {
				break;
			}
		}

		if (node.right != null) {
			node = node.right;
			while (node != null) {
				stack.push(node);
				node = node.left;
			}
		}
	}

	return list;
}
*/