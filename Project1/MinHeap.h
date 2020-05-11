
#include <iomanip>
#include <iostream>
using namespace std;

class lou {
public:
	int buildingNum;
	int excuted_time;
	int total_time;
	RBTNode* link;//rbtnode address
public:
	lou();
	lou(int a, int b,int c);
	
};
/*
* constructor function
*/
lou::lou()
{
	new (this)lou(0,0,0);
}

lou::lou(int aa, int bb,int cc)
{
	buildingNum = aa;
	excuted_time = bb;
	total_time = cc;
}





class MHeap {
public:
	lou *hp;        // hp
	int longs;    // total capacity
	int hsize;        // actual capacity



public:
	// The downward adjustment algorithm for the mini heap
	void mhdown(int ss, int ee);
	// The upscaling algorithm for the mini heap (start up to 0, adjust the heap)
	void mhup(int ss);

	MHeap();
	MHeap(int longs);
	~MHeap();

	// Remove the HP from the min heap
	int removemin();
	// Insert the HP into the min heap
	lou* insert(lou data);
};

/*
*constructor function
*/
MHeap::MHeap()
{
	new (this)MHeap(30);
}

MHeap::MHeap(int capacity)
{
	hsize = 0;
	longs = capacity;
	hp = new lou[longs];
}
/*
* Îö¹¹º¯Êý
*/
MHeap::~MHeap()
{
	hsize = 0;
	longs = 0;
	delete[] hp;
}

/*
* The downward adjustment algorithm for the mini heap
*
* Note: the index value of the left child of the NTH node in the array implementation heap is (2N+1), and the index value of the right child is (2N+2).
*
* parameter description:
* start -- the starting position of the node being lowered (usually 0, indicating that it starts from the first node)
* end -- the end range (usually the index of the last element in an array)
*/
void MHeap::mhdown(int ss, int ee)
{
	int cc = ss;          // current node location
	int ll = 2 * cc + 1;     // the position of the left child
	lou now = hp[cc];    // the size of current location

	while (ll <= ee)
	{
		// "ll"is left child£¬"ll+1"is right child
		if (ll < ee && hp[ll].excuted_time > hp[ll + 1].excuted_time)
			ll++;        // The smaller of the two children, HP [l+1]
		if (ll < ee && hp[ll].excuted_time == hp[ll + 1].excuted_time)
		{
			if (hp[ll].buildingNum > hp[ll + 1].buildingNum)
				ll++;
		}
		if (now.excuted_time < hp[ll].excuted_time)
			break;        //end
		if (now.excuted_time == hp[ll].excuted_time)
		{
			if (now.buildingNum< hp[ll].buildingNum)
				break;//end
			else
			{
				hp[cc] = hp[ll];
				cc = ll;
				ll = 2 * ll + 1;
			}
		}
		else
		{
			hp[cc] = hp[ll];
			cc = ll;
			ll = 2 * ll + 1;
		}
	}
	hp[cc] = now;
}

/*
* Remove the min from the mini heap
*
* return value:
* 0, success
* -1, failed
*/
int MHeap::removemin()
{
	int index;
	// If the heap is empty, -1 is returned
	if (hsize == 0)
		return -1;

	hp[0] = hp[--hsize];        // Fill in with the last element
	mhdown(0, hsize - 1);    // Adjust from 0 down to the mini heap
	return 0;
}

/*
* The upscaling algorithm for the mini heap (start up to 0, adjust the heap)
*
* note: in the heap implemented by the array, the index value of the left child of the NTH node is (2N+1) and the index value of the right child is (2N+2).
*
* parameter description:
* start -- the starting position of the node being upregded (usually the index of the last element in the array)
*/
void MHeap::mhup(int start)
{
	int cu = start;            // The location of the current node
	int pa = (cu - 1) / 2;        // the location of the parent node 
	lou node = hp[cu];        //size of current node

	while (cu > 0)
	{
		if (hp[pa].excuted_time< node.excuted_time)
			break;
		if (hp[pa].excuted_time == node.excuted_time)
		{
			if (hp[pa].buildingNum < node.buildingNum)
				break;
			else
			{
				hp[cu] = hp[pa];
				cu = pa;
				pa = (pa - 1) / 2;
			}
		}
		else
		{
			hp[cu] = hp[pa];
			cu = pa;
			pa = (pa - 1) / 2;
		}
	}
	hp[cu] = node;
}

/*
* Insert the HP into the binary heap
*
* return value:
* the new node's address
*/
lou* MHeap::insert(lou data)
{
	// If the heap is full, return null
	if (hsize == longs)
		return NULL;

	hp[hsize] = data;        //Insert "array" at the end of the table
	mhup(hsize);            // adjust the heap upwards
	hsize++;                    //  the actual capacity of the heap is +1

	return &hp[hsize];
}


