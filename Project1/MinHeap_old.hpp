/**
* �����(��С��)
*
* @author skywang
* @date 2014/03/07
*/

#include <iomanip>
#include <iostream>
using namespace std;

class lou {
public:
	int buildingNum;
	int excuted_time;
	int total_time;
public:
	lou();
	lou(int a, int b,int c);
	
	int getbuildingNum() { return buildingNum; };
	int getexcuted_time() { return excuted_time; };
	int gettotal_time() { return total_time; };
	void printbuilding() { cout << "(" << getbuildingNum() << "," << getexcuted_time() << "," << gettotal_time() << ")"; };
};
/*
* ���캯��
*/
lou::lou()
{
	new (this)lou(0,0,0);
}

lou::lou(int a, int b,int c)
{
	buildingNum = a;
	excuted_time = b;
	total_time = c;
}





class MinHeap {
public:
	lou *mHeap;        // ����
	int mCapacity;    // �ܵ�����
	int mSize;        // ʵ������

public:
	// ��С�ѵ����µ����㷨
	void filterdown(int start, int end);
	// ��С�ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
	void filterup(int start);
public:
	MinHeap();
	MinHeap(int capacity);
	~MinHeap();

	// ����data�ڶ�����е�����
	int getIndex(lou data);
	// ɾ����С���е�data
	int remove(lou data);
	// ��data���뵽�������
	int insert(lou data);
	// ��ӡ�����
	void print();
};

/*
* ���캯��
*/
MinHeap::MinHeap()
{
	new (this)MinHeap(30);
}

MinHeap::MinHeap(int capacity)
{
	mSize = 0;
	mCapacity = capacity;
	mHeap = new lou[mCapacity];
}
/*
* ��������
*/
MinHeap::~MinHeap()
{
	mSize = 0;
	mCapacity = 0;
	delete[] mHeap;
}

/*
* ����data�ڶ�����е�����
*
* ����ֵ��
*     ���� -- ����data�������е�����
*     ������ -- -1
*/
int MinHeap::getIndex(lou data)
{
	for (int i = 0; i<mSize; i++)
		if (
			data.getbuildingNum()== mHeap[i].getbuildingNum())
			return i;

	return -1;
}

/*
* ��С�ѵ����µ����㷨
*
* ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
*
* ����˵����
*     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
*     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
*/

void MinHeap::filterdown(int start, int end)
{
	int c = start;          // ��ǰ(current)�ڵ��λ��
	int l = 2 * c + 1;     // ��(left)���ӵ�λ��
	lou tmp = mHeap[c];    // ��ǰ(current)�ڵ�Ĵ�С

	while (l <= end)
	{
		// "l"�����ӣ�"l+1"���Һ���
		if (l < end && mHeap[l].excuted_time > mHeap[l + 1].excuted_time)
			l++;        // ������������ѡ���С�ߣ���mHeap[l+1]
		if (l < end && mHeap[l].excuted_time == mHeap[l + 1].excuted_time)
		{
			if (mHeap[l].buildingNum > mHeap[l + 1].buildingNum)
				l++;
		}
		if (tmp.excuted_time < mHeap[l].excuted_time)
			break;        //��������
		if (tmp.excuted_time == mHeap[l].excuted_time)
		{
			if (tmp.buildingNum< mHeap[l].buildingNum)
				break;
			else
			{
				mHeap[c] = mHeap[l];
				c = l;
				l = 2 * l + 1;
			}
		}
		else
		{
			mHeap[c] = mHeap[l];
			c = l;
			l = 2 * l + 1;
		}
	}
	mHeap[c] = tmp;
}

/*
* ɾ����С���е�data
*
* ����ֵ��
*      0���ɹ�
*     -1��ʧ��
*/
int MinHeap::remove(lou data)
{
	int index;
	// ���"��"�ѿգ��򷵻�-1
	if (mSize == 0)
		return -1;

	// ��ȡdata�������е�����
	index = getIndex(data);
	if (index == -1)
		return -1;

	mHeap[index] = mHeap[--mSize];        // �����Ԫ���
	filterdown(index, mSize - 1);    // ��index��λ�ÿ�ʼ�������µ���Ϊ��С��

	return 0;
}

/*
* ��С�ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
*
* ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
*
* ����˵����
*     start -- ���ϵ��ڵ����ʼλ��(һ��Ϊ���������һ��Ԫ�ص�����)
*/
void MinHeap::filterup(int start)
{
	int c = start;            // ��ǰ�ڵ�(current)��λ��
	int p = (c - 1) / 2;        // ��(parent)����λ�� 
	lou tmp = mHeap[c];        // ��ǰ�ڵ�(current)�Ĵ�С

	while (c > 0)
	{
		if (mHeap[p].excuted_time< tmp.excuted_time)
			break;
		if (mHeap[p].excuted_time == tmp.excuted_time)
		{
			if (mHeap[p].buildingNum < tmp.buildingNum)
				break;
			else
			{
				mHeap[c] = mHeap[p];
				c = p;
				p = (p - 1) / 2;
			}
		}
		else
		{
			mHeap[c] = mHeap[p];
			c = p;
			p = (p - 1) / 2;
		}
	}
	mHeap[c] = tmp;
}

/*
* ��data���뵽�������
*
* ����ֵ��
*     0����ʾ�ɹ�
*    -1����ʾʧ��
*/
int MinHeap::insert(lou data)
{
	// ���"��"�������򷵻�
	if (mSize == mCapacity)
		return -1;

	mHeap[mSize] = data;        // ��"����"���ڱ�β
	filterup(mSize);            // ���ϵ�����
	mSize++;                    // �ѵ�ʵ������+1

	return 0;
}

/*
* ��ӡ�����
*
* ����ֵ��
*     0����ʾ�ɹ�
*    -1����ʾʧ��
*/
void MinHeap::print()
{
	for (int i = 0; i<mSize; i++)
		cout << " ( " << mHeap[i].getbuildingNum() << " , " << mHeap[i].getexcuted_time() << " , " << mHeap[i].gettotal_time() << " ) " << endl;
}
