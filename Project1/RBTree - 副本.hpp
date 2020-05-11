#pragma once

#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_ 

#include <iomanip>
#include <iostream>
#include"MinHeap.hpp"
using namespace std;

enum RBTColor { RED, BLACK };


class RBTNode {
public:
	RBTColor color;    // ��ɫ
	int buildingNum;  // �ؼ���(��ֵ) �������
	RBTNode* left;    // ����
	RBTNode* right;    // �Һ���
	RBTNode* parent; // �����
	int executed_time; //�ѽ�ʱ��
	int total_time; //�ܺ�ʱ


	RBTNode(int value, int et, int tt, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :
		buildingNum(value), executed_time(et), total_time(tt), color(c), parent(), left(l), right(r){}
};


class RBTree {
private:
	RBTNode* mRoot;    // �����

public:
	RBTree();
	~RBTree();

	// ǰ�����"�����"
	void preOrder();
	// �������"�����"
	void inOrder();
	// �������"�����"
	void postOrder();

	// (�ݹ�ʵ��)����"�����"�м�ֵΪbuildingNum�Ľڵ�
	RBTNode* search(int buildingNum);
	// (�ǵݹ�ʵ��)����"�����"�м�ֵΪbuildingNum�Ľڵ�
	RBTNode* iterativeSearch(int buildingNum);

	// ������С��㣺������С���ļ�ֵ��
	int minimum();
	// ��������㣺���������ļ�ֵ��
	int maximum();

	// �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
	RBTNode* successor(RBTNode* x);
	// �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
	RBTNode* predecessor(RBTNode* x);

	// �����(buildingNumΪ�ڵ��ֵ)���뵽�������
	void insert(int buildingNum, int executed_time, int total_time);

	// ɾ�����(buildingNumΪ�ڵ��ֵ)
	void remove(int buildingNum);

	// ���ٺ����
	void destroy();

	// ��ӡ�����
	void print();
private:
	// ǰ�����"�����"
	void preOrder(RBTNode* tree) const;
	// �������"�����"
	void inOrder(RBTNode* tree) const;
	// �������"�����"
	void postOrder(RBTNode* tree) const;

	// (�ݹ�ʵ��)����"�����x"�м�ֵΪbuildingNum�Ľڵ�
	RBTNode* search(RBTNode* x, int buildingNum) const;
	// (�ǵݹ�ʵ��)����"�����x"�м�ֵΪbuildingNum�Ľڵ�
	RBTNode* iterativeSearch(RBTNode* x, int buildingNum) const;

	// ������С��㣺����treeΪ�����ĺ��������С��㡣
	RBTNode* minimum(RBTNode* tree);
	// ��������㣺����treeΪ�����ĺ����������㡣
	RBTNode* maximum(RBTNode* tree);

	// ����
	void leftRotate(RBTNode*& root, RBTNode* x);
	// ����
	void rightRotate(RBTNode*& root, RBTNode* y);
	// ���뺯��
	void insert(RBTNode*& root, RBTNode* node);
	// ������������
	void insertFixUp(RBTNode*& root, RBTNode* node);
	// ɾ������
	void remove(RBTNode*& root, RBTNode* node);
	// ɾ����������
	void removeFixUp(RBTNode*& root, RBTNode* node, RBTNode* parent);

	// ���ٺ����
	void destroy(RBTNode*& tree);

	// ��ӡ�����
	void print(RBTNode* tree, int buildingNum, int direction);

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};

/*
 * ���캯��
 */

RBTree::RBTree() :mRoot(NULL)
{
	mRoot = NULL;
}

/*
 * ��������
 */

RBTree::~RBTree()
{
	destroy();
}

/*
 * ǰ�����"�����"
 */

void RBTree::preOrder(RBTNode* tree) const
{
	if (tree != NULL)
	{
		cout << "(" << tree->buildingNum << "," << tree->executed_time << "," << tree->total_time << ") ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}


void RBTree::preOrder()
{
	preOrder(mRoot);
}

/*
 * �������"�����"
 */

void RBTree::inOrder(RBTNode* tree) const
{
	if (tree != NULL)
	{
		inOrder(tree->left);
		cout << "(" << tree->buildingNum << "," << tree->executed_time << "," << tree->total_time << ") ";
		inOrder(tree->right);
	}
}


void RBTree::inOrder()
{
	inOrder(mRoot);
}

/*
 * �������"�����"
 */

void RBTree::postOrder(RBTNode* tree) const
{
	if (tree != NULL)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout << "(" << tree->buildingNum << "," << tree->executed_time << "," << tree->total_time << ") ";
	}
}


void RBTree::postOrder()
{
	postOrder(mRoot);
}

/*
 * (�ݹ�ʵ��)����"�����x"�м�ֵΪbuildingNum�Ľڵ�
 */

RBTNode* RBTree::search(RBTNode* x, int buildingNum) const
{
	if (x == NULL || x->buildingNum == buildingNum)
		return x;

	if (buildingNum < x->buildingNum)
		return search(x->left, buildingNum);
	else
		return search(x->right, buildingNum);
}


RBTNode* RBTree::search(int buildingNum)
{
	search(mRoot, buildingNum);
}

/*
 * (�ǵݹ�ʵ��)����"�����x"�м�ֵΪbuildingNum�Ľڵ�
 */

RBTNode* RBTree::iterativeSearch(RBTNode* x, int buildingNum) const
{
	while ((x != NULL) && (x->buildingNum != buildingNum))
	{
		if (buildingNum < x->buildingNum)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}


RBTNode* RBTree::iterativeSearch(int buildingNum)
{
	iterativeSearch(mRoot, buildingNum);
}

/*
 * ������С��㣺����treeΪ�����ĺ��������С��㡣
 */

RBTNode* RBTree::minimum(RBTNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}


int RBTree::minimum()
{
	RBTNode* p = minimum(mRoot);
	if (p != NULL)
		return p->buildingNum;

	return (int)NULL;
}

/*
 * ��������㣺����treeΪ�����ĺ����������㡣
 */

RBTNode* RBTree::maximum(RBTNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}


int RBTree::maximum()
{
	RBTNode* p = maximum(mRoot);
	if (p != NULL)
		return p->buildingNum;

	return (int)NULL;
}

/*
 * �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
 */

RBTNode* RBTree::successor(RBTNode* x)
{
	// ���x�����Һ��ӣ���"x�ĺ�̽��"Ϊ "�����Һ���Ϊ������������С���"��
	if (x->right != NULL)
		return minimum(x->right);

	// ���xû���Һ��ӡ���x���������ֿ��ܣ�
	// (01) x��"һ������"����"x�ĺ�̽��"Ϊ "���ĸ����"��
	// (02) x��"һ���Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ��������"���ҵ������"��͵ĸ����"����"x�ĺ�̽��"��
	RBTNode* y = x->parent;
	while ((y != NULL) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
 * �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
 */

RBTNode* RBTree::predecessor(RBTNode* x)
{
	// ���x�������ӣ���"x��ǰ�����"Ϊ "��������Ϊ���������������"��
	if (x->left != NULL)
		return maximum(x->left);

	// ���xû�����ӡ���x���������ֿ��ܣ�
	// (01) x��"һ���Һ���"����"x��ǰ�����"Ϊ "���ĸ����"��
	// (01) x��"һ������"�������"x����͵ĸ���㣬���Ҹø����Ҫ�����Һ���"���ҵ������"��͵ĸ����"����"x��ǰ�����"��
	RBTNode* y = x->parent;
	while ((y != NULL) && (x == y->left))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
 * �Ժ�����Ľڵ�(x)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�x��������)��
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(����)-->           / \                #
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 *
 *
 */

void RBTree::leftRotate(RBTNode*& root, RBTNode* x)
{
	// ����x���Һ���Ϊy
	RBTNode* y = x->right;

	// �� ��y�����ӡ� ��Ϊ ��x���Һ��ӡ���
	// ���y�����ӷǿգ��� ��x�� ��Ϊ ��y�����ӵĸ��ס�
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// �� ��x�ĸ��ס� ��Ϊ ��y�ĸ��ס�
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
		else
			x->parent->right = y;    // ��� x�������ڵ���Һ��ӣ���y��Ϊ��x�ĸ��ڵ���Һ��ӡ�
	}

	// �� ��x�� ��Ϊ ��y�����ӡ�
	y->left = x;
	// �� ��x�ĸ��ڵ㡱 ��Ϊ ��y��
	x->parent = y;
}

/*
 * �Ժ�����Ľڵ�(y)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�y��������)��
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(����)-->            /  \                     #
 *        x   ry                           lx   y
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 *
 */

void RBTree::rightRotate(RBTNode*& root, RBTNode* y)
{
	// ����x�ǵ�ǰ�ڵ�����ӡ�
	RBTNode* x = y->left;

	// �� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ���
	// ���"x���Һ���"��Ϊ�յĻ����� ��y�� ��Ϊ ��x���Һ��ӵĸ��ס�
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// �� ��y�ĸ��ס� ��Ϊ ��x�ĸ��ס�
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // ��� y�������ڵ���Һ��ӣ���x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
		else
			y->parent->left = x;    // (y�������ڵ������) ��x��Ϊ��x�ĸ��ڵ�����ӡ�
	}

	// �� ��y�� ��Ϊ ��x���Һ��ӡ�
	x->right = y;

	// �� ��y�ĸ��ڵ㡱 ��Ϊ ��x��
	y->parent = x;
}

/*
 * �����������������
 *
 * ���������в���ڵ�֮��(ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
 */

void RBTree::insertFixUp(RBTNode*& root, RBTNode* node)
{
	RBTNode* parent, * gparent;

	// �������ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ��
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);

		//�������ڵ㡱�ǡ��游�ڵ�����ӡ�
		if (parent == gparent->left)
		{
			// Case 1����������ڵ��Ǻ�ɫ
			{
				RBTNode* uncle = gparent->right;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
			if (parent->right == node)
			{
				RBTNode* tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);
		}
		else//����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
		{
			// Case 1����������ڵ��Ǻ�ɫ
			{
				RBTNode* uncle = gparent->left;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
			if (parent->left == node)
			{
				RBTNode* tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
			rb_set_black(parent);
			rb_set_red(gparent);
			leftRotate(root, gparent);
		}
	}

	// �����ڵ���Ϊ��ɫ
	rb_set_black(root);
}

/*
 * �������뵽�������
 *
 * ����˵����
 *     root ������ĸ����
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�node
 */

void RBTree::insert(RBTNode*& root, RBTNode* node)
{
	RBTNode* y = NULL;
	RBTNode* x = root;

	// 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
	while (x != NULL)
	{
		y = x;
		if (node->buildingNum < x->buildingNum)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != NULL)
	{
		if (node->buildingNum < y->buildingNum)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;
	//2. point to MinHeap

	// 3. ���ýڵ����ɫΪ��ɫ
	node->color = RED;

	// 3. ������������Ϊһ�Ŷ��������
	insertFixUp(root, node);
}

/*
 * �����(buildingNumΪ�ڵ��ֵ)���뵽�������
 *
 * ����˵����
 *     tree ������ĸ����
 *     buildingNum ������ļ�ֵ
 */

void RBTree::insert(int buildingNum, int executed_time, int total_time)
{
	RBTNode* z = NULL;

	// ����½����ʧ�ܣ��򷵻ء�
	if ((z = new RBTNode(buildingNum, executed_time, total_time, BLACK, NULL, NULL, NULL)) == NULL)
		return;
	
	insert(mRoot, z);


}

/*
 * �����ɾ����������
 *
 * �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node �������Ľڵ�
 */

void RBTree::removeFixUp(RBTNode*& root, RBTNode* node, RBTNode* parent)
{
	RBTNode* other;

	while ((!node || rb_is_black(node)) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (rb_is_red(other))
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->right || rb_is_black(other->right))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					rb_set_black(other->left);
					rb_set_red(other);
					rightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (rb_is_red(other))
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->left || rb_is_black(other->left))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					rb_set_black(other->right);
					rb_set_red(other);
					leftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		rb_set_black(node);
}

/*
 * ɾ�����(node)�������ر�ɾ���Ľ��
 *
 * ����˵����
 *     root ������ĸ����
 *     node ɾ���Ľ��
 */

void RBTree::remove(RBTNode*& root, RBTNode* node)
{
	RBTNode* child, * parent;
	RBTColor color;

	// ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
	if ((node->left != NULL) && (node->right != NULL))
	{
		// ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
		// ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
		RBTNode* replace = node;

		// ��ȡ��̽ڵ�
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			// "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
			root = replace;

		// child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
		// "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
		child = replace->right;
		parent = rb_parent(replace);
		// ����"ȡ���ڵ�"����ɫ
		color = rb_color(replace);

		// "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child��Ϊ��
			if (child)
				rb_set_parent(child, parent);
			parent->left = child;

			replace->right = node->right;
			rb_set_parent(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}

	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	// ����"ȡ���ڵ�"����ɫ
	color = node->color;

	if (child)
		child->parent = parent;

	// "node�ڵ�"���Ǹ��ڵ�
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
		removeFixUp(root, child, parent);
	delete node;
}

/*
 * ɾ��������м�ֵΪbuildingNum�Ľڵ�
 *
 * ����˵����
 *     tree ������ĸ����
 */

void RBTree::remove(int buildingNum)
{
	RBTNode* node;

	// ����buildingNum��Ӧ�Ľڵ�(node)���ҵ��Ļ���ɾ���ýڵ�
	if ((node = search(mRoot, buildingNum)) != NULL)
		remove(mRoot, node);
}

/*
 * ���ٺ����
 */

void RBTree::destroy(RBTNode*& tree)
{
	if (tree == NULL)
		return;

	if (tree->left != NULL)
		return destroy(tree->left);
	if (tree->right != NULL)
		return destroy(tree->right);

	delete tree;
	tree = NULL;
}


void RBTree::destroy()
{
	destroy(mRoot);
}

/*
 * ��ӡ"���������"
 *
 * buildingNum        -- �ڵ�ļ�ֵ
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */

void RBTree::print(RBTNode* tree, int buildingNum, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree�Ǹ��ڵ�
			cout << setw(2) << tree->buildingNum << "(B) is root" << endl;
		else                // tree�Ƿ�֧�ڵ�
			cout << setw(2) << tree->buildingNum << (rb_is_red(tree) ? "(R)" : "(B)") << " is " << setw(2) << buildingNum << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->left, tree->buildingNum, -1);
		print(tree->right, tree->buildingNum, 1);
	}
}


void RBTree::print()
{
	if (mRoot != NULL)
		print(mRoot, mRoot->buildingNum, 0);
}

#endif