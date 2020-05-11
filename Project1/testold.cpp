/**
* C++ 语言: 二叉查找树
*
* @author skywang
* @date 2013/11/07
*/

#include <iostream>
#include <vector>
#include<string>
#include<fstream>
#include "RBTree.h"
#include "MinHeap_old.hpp"

using namespace std;

void myinsert(lou mHeap, RBTree* rbtree, MinHeap* mhtree)
{
	rbtree->insert(mHeap.buildingNum, mHeap.excuted_time, mHeap.total_time);//creat rbtnode
	mhtree->insert(mHeap);//creat mhnode
}
void myremovemin(RBTree* rbtree,MinHeap* mhtree)
{
	rbtree->remove(mhtree->mHeap[0].buildingNum);
	mhtree->remove(mhtree->mHeap[0]);
}
void update(MinHeap* mhtree, RBTree* rbtree) {
	mhtree->mHeap[0].excuted_time += 1;
//	mhtree->mHeap[0].link->executed_time += 1;
//	rbtree->iterativeSearch(mhtree->mHeap[0].buildingNum)->executed_time += 1;
	rbtree->remove(mhtree->mHeap[0].buildingNum);
	rbtree->insert(mhtree->mHeap[0].buildingNum, mhtree->mHeap[0].excuted_time, mhtree->mHeap[0].total_time);
}


void buildingCity2(string s)
{
	ifstream inFile;
	ofstream outFile;

	string data;
	inFile.open(s);
	outFile.open("output_file.txt");

	MinHeap* mhtree = new MinHeap(2000);
	RBTree* rbtree = new RBTree;
	//变量
	bool jud = 0;
	int i = 0;
	lou a[5] = {};
	int start_time = 0;
	int counter = -1;
	getline(inFile, data);

	while (mhtree->mSize || data.size() != 0)
	{
		string aaa = data;
		counter++;
		//读文件
		if (aaa.size() != 0) {
			unsigned start = aaa.find(':');
			string strkey = aaa.substr(0, start);
			int num = stoi(strkey);
			if (counter == num) {
				string str = aaa;
				//insert operation
				if (str[start + 2] == 'I')
				{
					//cout << str << endl;
					unsigned firstb = str.find('(');
					unsigned comma = str.find(',');
					unsigned secondb = str.find(')');
					string strkey1 = str.substr(firstb + 1, comma - firstb - 1);
					string strkey2 = str.substr(comma + 1, secondb - comma - 1);
					int num1 = stoi(strkey1);
					int num2 = stoi(strkey2);
					//cout << num1 << num2 << endl;
					lou new_building(num1, 0, num2);
					if (jud == 0) {
						//			mhtree->insert(new_building);
						myinsert(new_building, rbtree, mhtree);
						if (a[0].buildingNum != 0) {
							for (int k = 0; k < i; k++)
							{
								myinsert(a[k], rbtree, mhtree);
								//rbtree->preOrder();
							}
						}
						//update(mhtree, rbtree);
						//****
						start_time = counter;
						jud = 1;
					}
					else {
						//cout << num1 << num2 << endl;
						a[i].buildingNum = num1;
						a[i].excuted_time = 0;
						a[i].total_time = num2;
						i++;
					}
					getline(inFile, data);
				}
			}
			
		}

			if (mhtree->mSize != 0)
			{
				if (jud == 0)
				{
					if (a[0].buildingNum != 0) {
						for (int k = 0; k < i; k++)
						{
							myinsert(a[k], rbtree, mhtree);
							//rbtree->preOrder();
						}
					}
					jud = 1;
					start_time = counter;
					i = 0;
					//				memset(a, 0, sizeof(a));
				}
				//读print
				if (aaa.size() != 0) {
					unsigned start = aaa.find(':');
					string strkey = aaa.substr(0, start);
					int num = stoi(strkey);
					if (counter == num) {
						string str = aaa;


						if (str[start + 2] == 'P')
						{
							cout << str << endl;
							unsigned firstb = str.find('(');
							unsigned comma = str.find(',');
							unsigned secondb = str.find(')');
							if (comma != -1)
							{
								string strkey1 = str.substr(firstb + 1, comma - firstb - 1);
								string strkey2 = str.substr(comma + 1, secondb - comma - 1);
								int num1 = stoi(strkey1);
								int num2 = stoi(strkey2);
								cout << num1 << "," << num2 << endl; //在红黑树中进行搜索输出
								outFile << rbtree->get_triplet2(num1, num2) << endl;
							}
							else
							{
								string strkey1 = str.substr(firstb + 1, secondb - firstb - 1);
								int num1 = stoi(strkey1);
								cout << num1 << endl; //在红黑树中进行搜索输出
								outFile << rbtree->get_triplet(num1) << endl;
							}
							getline(inFile, data);
						}
					}

				}
				update(mhtree, rbtree);
				if (mhtree->mHeap[0].excuted_time == mhtree->mHeap[0].total_time)
				{
					outFile << "(" << mhtree->mHeap[0].buildingNum << "," << counter + 1 << ")" << endl;
					myremovemin(rbtree, mhtree);
					//				mhtree->removemin();
					jud = 0;
				}
				else if (counter == start_time + 4) {
					mhtree->filterdown(0, mhtree->mSize - 1);
					jud = 0;
				}

			}
			else if (aaa.size() != 0) {
					unsigned start = aaa.find(':');
					string strkey = aaa.substr(0, start);
					int num = stoi(strkey);
					if (counter == num) {
						string str = aaa;


						if (str[start + 2] == 'P')
						{
							cout << str << endl;
							unsigned firstb = str.find('(');
							unsigned comma = str.find(',');
							unsigned secondb = str.find(')');
							if (comma != -1)
							{
								string strkey1 = str.substr(firstb + 1, comma - firstb - 1);
								string strkey2 = str.substr(comma + 1, secondb - comma - 1);
								int num1 = stoi(strkey1);
								int num2 = stoi(strkey2);
								cout << num1 << "," << num2 << endl; //在红黑树中进行搜索输出
								outFile << rbtree->get_triplet2(num1, num2) << endl;
							}
							else
							{
								string strkey1 = str.substr(firstb + 1, secondb - firstb - 1);
								int num1 = stoi(strkey1);
								cout << num1 << endl; //在红黑树中进行搜索输出
								outFile << rbtree->get_triplet(num1) << endl;
							}
							getline(inFile, data);
						}
					}

				}
		
		}
	
	inFile.close();
	outFile.close();
}

int main(int argc, const char * argv[]) {
	buildingCity2("Sample_input1.txt");
	return 0;
}