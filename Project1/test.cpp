
#include <iostream>
#include <vector>
#include<string>
#include<fstream>
#include "RBTree.h"
#include "MinHeap.h"

using namespace std;


//using two tree's link pointer to insert new building to red_black_tree and minheap 
//input:hp=insert building; rbtree=red black tree; mhtree=min heap
void myinsert(lou hp, RBTree* rbtree, MHeap* mhtree)
{
	hp.link = rbtree->insert(hp.buildingNum, hp.excuted_time, hp.total_time);//creat rbtnode
	mhtree->insert(hp);//creat mhnode
}


//remove minnode from minheap and red_black_tree correspondly
//input:the red_black_tree and minheap
void myremovemin(RBTree* rbtree,MHeap* mhtree)
{
	rbtree->deletenode(mhtree->hp[0].buildingNum);
	mhtree->removemin();
	
}


//using two tree's link pointer to update building by add 1 to excuted time of two trees
//input:min heap
void update_building(MHeap* mhtree) {
	mhtree->hp[0].excuted_time += 1;
	mhtree->hp[0].link->executed_time += 1;
//	rbtree->lookfor(mhtree->hp[0].buildingNum)->executed_time += 1;
}

//building a city under rules
void buildingCity(string s)
{
	ifstream inFile;
	ofstream outFile;

	string data;//save the current command
	inFile.open(s);
	outFile.open("output_file.txt");

	MHeap* mhtree = new MHeap(2000);
	RBTree* rbtree = new RBTree;
	//parameter
	bool jud = 0;//0:there is no building is under construction  1:there is building under construction
	int i = 0; //point to the last lou in a[] waiting for insert
	lou a[5] = {};//the buildings waiting for insert to trees
	int begin_time = 0; //the time of this building begins
	int global_timer = -1;// global time counter
	
	getline(inFile, data);// pick up one command from file to data,data:current command line
	while (mhtree->hsize || data.size() != 0)
	{
		string aaa = data;
		global_timer++;
		//read file command
		if (aaa.size() != 0) {
			unsigned maohao = aaa.find(':');
			string time = aaa.substr(0, maohao);
			int now = stoi(time);
			if (global_timer == now) {
				//insert operation
				if (aaa[maohao + 2] == 'I')
				{
					unsigned qkuohao = aaa.find('(');
					unsigned comma = aaa.find(',');
					unsigned hkuohao = aaa.find(')');
					string no1 = aaa.substr(qkuohao + 1, comma - qkuohao - 1);
					string no2 = aaa.substr(comma + 1, hkuohao - comma - 1);
					int num1 = stoi(no1);
					int num2 = stoi(no2);
					lou new_lou(num1, 0, num2);
					//no building is under construction, so insert new building and 
					//the buildings waiting in a[] to trees
					if (jud == 0) {
						myinsert(new_lou, rbtree, mhtree);
						if (a[0].buildingNum != 0) {
							for (int k = 0; k < i; k++)
							{
								myinsert(a[k], rbtree, mhtree);
							}
						}
						//set begin_time to building
						jud = 1;
						begin_time = global_timer;
						i = 0;
				
					}

					//if there is building under construction, so save new building to a[] to wait.
					else {
						a[i].buildingNum = num1;
						a[i].excuted_time = 0;
						a[i].total_time = num2;
						i++;
					}
					//read next command and save to data
					getline(inFile, data);
				}
			}
			
		}
		//today building
			if (mhtree->hsize != 0)//min heap is not empty
			{
				//there is no building under construction, insert all buildings to 
				//trees include in the waiting list and new comer
				if (jud == 0)
				{
					if (a[0].buildingNum != 0) {
						for (int k = 0; k < i; k++)
						{
							myinsert(a[k], rbtree, mhtree);
						}
					}
					//set begin building time
					jud = 1;
					begin_time = global_timer;
					i = 0;
				}
				//read "print" command
				if (aaa.size() != 0) {
					unsigned maohao = aaa.find(':');
					string strkey = aaa.substr(0, maohao);
					int now = stoi(strkey);
					if (global_timer == now) {
						string str = aaa;


						if (str[maohao + 2] == 'P')
						{
							unsigned qkuohao = str.find('(');
							unsigned comma = str.find(',');
							unsigned hkuohao = str.find(')');
							//buildingnum(num1, num2) operation
							if (comma != -1)
							{
								string no1 = str.substr(qkuohao + 1, comma - qkuohao - 1);
								string no2 = str.substr(comma + 1, hkuohao - comma - 1);
								int num1 = stoi(no1);
								int num2 = stoi(no2);
								if (rbtree->buildingnum(num1, num2) == "????")
								{
									;
								}
								else
									outFile << rbtree->buildingnum(num1, num2) << endl;
							}
							//printbuilding(num1) operation
							else
							{
								string no1 = str.substr(qkuohao + 1, hkuohao - qkuohao - 1);
								int num1 = stoi(no1);
								outFile << rbtree->buildingnum(num1) << endl;
							}
							getline(inFile, data);
						}
					}

				}
				//using two tree's link pointer to update building by add 1 to excuted time of two trees
				update_building(mhtree);

				//if this building is completed,print and remove
				if (mhtree->hp[0].excuted_time == mhtree->hp[0].total_time)
				{
					outFile << "(" << mhtree->hp[0].buildingNum << "," << global_timer + 1 << ")" << endl;
					myremovemin(rbtree, mhtree);
					jud = 0;
				}
				//if this building is constructed 5 days, end and fix up minheap.
				else if (global_timer == begin_time + 4) {
					mhtree->mhdown(0, mhtree->hsize - 1);
					jud = 0;
				}

			}
			//the minheap is empty but there is still command in file waiting for operation
			else
			{
				if (aaa.size() != 0) {
					//read command number before ":"
					unsigned maohao = aaa.find(':');
					string strkey = aaa.substr(0, maohao);
					int now = stoi(strkey);
					if (global_timer == now) {
						string str = aaa;

						//insert operation
						if (str[maohao + 2] == 'I')
						{
							unsigned qkuohao = str.find('(');
							unsigned comma = str.find(',');
							unsigned hkuohao = str.find(')');
							string no1 = str.substr(qkuohao + 1, comma - qkuohao - 1);
							string no2 = str.substr(comma + 1, hkuohao - comma - 1);
							int num1 = stoi(no1);
							int num2 = stoi(no2);
							lou new_lou(num1, 0, num2);
							if (jud==0){
							myinsert(new_lou, rbtree, mhtree);
							if (a[0].buildingNum != 0) {
								for (int k = 0; k < i; k++)
								{
									myinsert(a[k], rbtree, mhtree);
								}
								jud = 1;
								begin_time = global_timer;
								i = 0;

								update_building(mhtree);
								//****
								begin_time = global_timer;
								jud = 1;
							}
						}
							//save this new building to a[] waiting list
							else {
								a[i].buildingNum = num1;
								a[i].excuted_time = 0;
								a[i].total_time = num2;
								i++;
							}
						}
						//command=printbuilding
						if (str[maohao + 2] == 'P')
						{
							unsigned qkuohao = str.find('(');
							unsigned comma = str.find(',');
							unsigned hkuohao = str.find(')');
							if (comma != -1)
							{
								string no1 = str.substr(qkuohao + 1, comma - qkuohao - 1);
								string no2 = str.substr(comma + 1, hkuohao - comma - 1);
								int num1 = stoi(no1);
								int num2 = stoi(no2);
								if (rbtree->buildingnum(num1, num2) == "????")
								{
									;
								}
								else
									outFile << rbtree->buildingnum(num1, num2) << endl;
							}
							else
							{
								string no1 = str.substr(qkuohao + 1, hkuohao - qkuohao - 1);
								int num1 = stoi(no1);
								outFile << rbtree->buildingnum(num1) << endl;
							}
							getline(inFile, data);
						}
					}

				}
			}
		}
	inFile.close();
	outFile.close();
}
/*
int main(int argc, const char * argv[]) {
	buildingCity(argv[1]);
	return 0;
}*/
int main(int argc, const char * argv[]) {
	buildingCity("inp1.txt");
	return 0;
}