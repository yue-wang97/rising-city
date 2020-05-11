/**
* C++ 语言: 二叉查找树
*
* @author skywang
* @date 2013/11/07
*/

#include <iostream>
#include <vector>
#include "RBTree.h"
#include "MinHeap.h"

using namespace std;

/*void testRB()
{
	//***********************test rb tree*************************	
	building a[5] =

	{

		building(1,0, 65),

		building(2,1, 45),

		building(3,2, 95),

		building(4,3, 85),

		building(5,4, 75)

	};
int check_insert = 1;    // "插入"动作的检测开关(0，关闭；1，打开)
int check_remove = 1;    // "删除"动作的检测开关(0，关闭；1，打开)
int i;
int ilen = (sizeof(a)) / (sizeof(a[0]));
RBTree* tree = new RBTree();

cout << "== 原始数据: ";
for (i = 0; i < ilen; i++)
{
	a[i].printbuilding();
	cout << " ";
}

cout << endl;

for (i = 0; i<ilen; i++)
{
	tree->insert(a[i]);
	// 设置check_insert=1,测试"添加函数"
	if (check_insert)
	{
		cout << "== 添加节点: " << a[i] << endl;
		cout << "== 树的详细信息: " << endl;
		tree->print();
		cout << endl;
	}

}

cout << "== 前序遍历: ";
tree->preOrder();

cout << "\n== 中序遍历: ";
tree->inOrder();

cout << "\n== 后序遍历: ";
tree->postOrder();
cout << endl;

cout << "== 最小值: " << tree->minimum() << endl;
cout << "== 最大值: " << tree->maximum() << endl;
cout << "== 树的详细信息: " << endl;
tree->print();

// 设置check_remove=1,测试"删除函数"
if (check_remove)
{
	for (i = 0; i<ilen; i++)
	{
		tree->remove(a[i]);

		cout << "== 删除节点: " << a[i] << endl;
		cout << "== 树的详细信息: " << endl;
		tree->print();
		cout << endl;
	}
}

// 销毁红黑树
//	tree->destroy();
//***********************test rb tree end*************************	
}*/

void testMH()
{	
//	int a[] = { 80, 40, 30, 60, 90, 70, 10, 50, 20 };
	int bn, et, tt;
	cout << "Input the first building Num:";
	cin >> bn;
	cout << "Input the first executed time:";
	cin >> et;
	cout << "Input the first total time:";
	cin >> tt;
	building a[] =

	{
		building(bn, et, tt)
	};

	int i, len = (sizeof(a)) / (sizeof(a[0]));
	MinHeap* tree = new MinHeap();

	/*cout << "== 依次添加: ";
	for (i = 0; i<len; i++)
	{
		a[i].printbuilding();
		tree->insert(a[i]);
		if (i < len - 1)
			cout << ", ";
	}*/

	i = 1;
	cout << "== insert the first element:";
	tree->insert(a[0]);

	cout << "\n== 最 小 堆: ";
	tree->print();
	while (1)
	{
		string command;
		cout << "Please input the action code(insert, removemin, end):";
		cin >> command;
		if (command == "insert")
		{
			i++;
			cout << "Input the new insertion building num:";
			cin >> bn;
			cout << "Input the new insertion executed time:";
			cin >> et;
			cout << "Input the new insertion total time:";
			cin >> tt;
			building ii(bn, et, tt);
			tree->insert(ii);
			cout << "\n== 添加元素: " << i;
			cout << "\n== 最 小 堆: ";
			tree->print();
		}

		if (command == "removemin")
		{
			i--;
			tree->removemin();
			cout << "\n== 删除最小元素: ";
			cout << "\n== 最 小 堆: ";
			tree->print();
		}

		if (command == "end")
			break;
		else
			cout << "Please input the right action code(hint: The code should be: insert, removemin or end):" << endl;
	}

}

int main() {
	testMH();
	return 0;
}