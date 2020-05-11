/**
* C++ ����: ���������
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
int check_insert = 1;    // "����"�����ļ�⿪��(0���رգ�1����)
int check_remove = 1;    // "ɾ��"�����ļ�⿪��(0���رգ�1����)
int i;
int ilen = (sizeof(a)) / (sizeof(a[0]));
RBTree* tree = new RBTree();

cout << "== ԭʼ����: ";
for (i = 0; i < ilen; i++)
{
	a[i].printbuilding();
	cout << " ";
}

cout << endl;

for (i = 0; i<ilen; i++)
{
	tree->insert(a[i]);
	// ����check_insert=1,����"��Ӻ���"
	if (check_insert)
	{
		cout << "== ��ӽڵ�: " << a[i] << endl;
		cout << "== ������ϸ��Ϣ: " << endl;
		tree->print();
		cout << endl;
	}

}

cout << "== ǰ�����: ";
tree->preOrder();

cout << "\n== �������: ";
tree->inOrder();

cout << "\n== �������: ";
tree->postOrder();
cout << endl;

cout << "== ��Сֵ: " << tree->minimum() << endl;
cout << "== ���ֵ: " << tree->maximum() << endl;
cout << "== ������ϸ��Ϣ: " << endl;
tree->print();

// ����check_remove=1,����"ɾ������"
if (check_remove)
{
	for (i = 0; i<ilen; i++)
	{
		tree->remove(a[i]);

		cout << "== ɾ���ڵ�: " << a[i] << endl;
		cout << "== ������ϸ��Ϣ: " << endl;
		tree->print();
		cout << endl;
	}
}

// ���ٺ����
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

	/*cout << "== �������: ";
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

	cout << "\n== �� С ��: ";
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
			cout << "\n== ���Ԫ��: " << i;
			cout << "\n== �� С ��: ";
			tree->print();
		}

		if (command == "removemin")
		{
			i--;
			tree->removemin();
			cout << "\n== ɾ����СԪ��: ";
			cout << "\n== �� С ��: ";
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