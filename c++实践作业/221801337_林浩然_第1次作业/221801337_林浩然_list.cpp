#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<time.h>
#include<windows.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
#include"林浩然_221801337_list1.h"
#include"林浩然_221801337_list2.h"
int main(int argc, char** argv){
	int cmp,cnt=0;
	node root;//哨兵节点
	nodeInfo rootInfo;//包含了链表的首尾信息,避免在表尾插入数据时遍历链表
	root.next=NULL;
	rootInfo.front=rootInfo.back=&root;
	while (1) {
		system("CLS");
		menu();
		cin>>cmp;
		switch(cmp){
			case 1:que1(cnt,root,rootInfo);break;
			case 2:que2(cnt,root,rootInfo);break;
			case 3:que3(cnt,root,rootInfo);break;
			case 4:que4(cnt,root,rootInfo);break;
			case 5:que5(cnt,root,rootInfo);break;
			case 6:que6(cnt,root,rootInfo);break;
			case 7:que7(cnt,root,rootInfo);break;
			case 8:que8(cnt,root,rootInfo);break;
			case 9:que9(cnt,root,rootInfo);break;
			case 10:que10(cnt,root,rootInfo);break;
			case 11:return 0;
			default:error(1);break;
		}
		cmp=0;
		if(!cin.good()){
			cin.clear();
			cin.ignore(1024,'\n');
		}
	}
	return 0;
}