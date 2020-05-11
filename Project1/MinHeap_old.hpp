/**
* 二叉堆(最小堆)
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
* 构造函数
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
	lou *mHeap;        // 数据
	int mCapacity;    // 总的容量
	int mSize;        // 实际容量

public:
	// 最小堆的向下调整算法
	void filterdown(int start, int end);
	// 最小堆的向上调整算法(从start开始向上直到0，调整堆)
	void filterup(int start);
public:
	MinHeap();
	MinHeap(int capacity);
	~MinHeap();

	// 返回data在二叉堆中的索引
	int getIndex(lou data);
	// 删除最小堆中的data
	int remove(lou data);
	// 将data插入到二叉堆中
	int insert(lou data);
	// 打印二叉堆
	void print();
};

/*
* 构造函数
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
* 析构函数
*/
MinHeap::~MinHeap()
{
	mSize = 0;
	mCapacity = 0;
	delete[] mHeap;
}

/*
* 返回data在二叉堆中的索引
*
* 返回值：
*     存在 -- 返回data在数组中的索引
*     不存在 -- -1
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
* 最小堆的向下调整算法
*
* 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
*
* 参数说明：
*     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
*     end   -- 截至范围(一般为数组中最后一个元素的索引)
*/

void MinHeap::filterdown(int start, int end)
{
	int c = start;          // 当前(current)节点的位置
	int l = 2 * c + 1;     // 左(left)孩子的位置
	lou tmp = mHeap[c];    // 当前(current)节点的大小

	while (l <= end)
	{
		// "l"是左孩子，"l+1"是右孩子
		if (l < end && mHeap[l].excuted_time > mHeap[l + 1].excuted_time)
			l++;        // 左右两孩子中选择较小者，即mHeap[l+1]
		if (l < end && mHeap[l].excuted_time == mHeap[l + 1].excuted_time)
		{
			if (mHeap[l].buildingNum > mHeap[l + 1].buildingNum)
				l++;
		}
		if (tmp.excuted_time < mHeap[l].excuted_time)
			break;        //调整结束
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
* 删除最小堆中的data
*
* 返回值：
*      0，成功
*     -1，失败
*/
int MinHeap::remove(lou data)
{
	int index;
	// 如果"堆"已空，则返回-1
	if (mSize == 0)
		return -1;

	// 获取data在数组中的索引
	index = getIndex(data);
	if (index == -1)
		return -1;

	mHeap[index] = mHeap[--mSize];        // 用最后元素填补
	filterdown(index, mSize - 1);    // 从index号位置开始自上向下调整为最小堆

	return 0;
}

/*
* 最小堆的向上调整算法(从start开始向上直到0，调整堆)
*
* 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
*
* 参数说明：
*     start -- 被上调节点的起始位置(一般为数组中最后一个元素的索引)
*/
void MinHeap::filterup(int start)
{
	int c = start;            // 当前节点(current)的位置
	int p = (c - 1) / 2;        // 父(parent)结点的位置 
	lou tmp = mHeap[c];        // 当前节点(current)的大小

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
* 将data插入到二叉堆中
*
* 返回值：
*     0，表示成功
*    -1，表示失败
*/
int MinHeap::insert(lou data)
{
	// 如果"堆"已满，则返回
	if (mSize == mCapacity)
		return -1;

	mHeap[mSize] = data;        // 将"数组"插在表尾
	filterup(mSize);            // 向上调整堆
	mSize++;                    // 堆的实际容量+1

	return 0;
}

/*
* 打印二叉堆
*
* 返回值：
*     0，表示成功
*    -1，表示失败
*/
void MinHeap::print()
{
	for (int i = 0; i<mSize; i++)
		cout << " ( " << mHeap[i].getbuildingNum() << " , " << mHeap[i].getexcuted_time() << " , " << mHeap[i].gettotal_time() << " ) " << endl;
}
