//包含用来与用户进行交互的函数
#ifndef LIST2_h 
#define LIST2_h
#include"林浩然_221801337_list1.h"


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Function
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
	printLine
		input:     void
		function:  用来输出一条分割线 
		output:    void
	error
		input:     int类型的错误代码
		function:  用来输出错误信息
		output:    void
	menu
		input:     void
		function:   用来输出主菜单 
		output:    void
*/
void printLine();
void error(int);
void menu(); 

/*
	printTtday
		input:     起始节点的指针
		function:  用来分页输出结点的日期距离2000年1月1日的天数  
		output:    输出节点的个数
	printfNode
		input:     起始节点的指针,找查的方法,链表中的节点数,输出的节点个数默认<n=0>
		function:  用来分页输出日期数据
		output:    输出节点的个数
		方法:
		showNode:        显示输入节点<之后>的所有节点
		showWrongNode:   显示输入节点<之后>的所有不能构成合法日期的结点
		showPrimeNode:   显示输入节点<之后>的所有素数的节点
*/
int printTtday(node *);
int printfNode(node *,node *cmd(node *),int,int);

/*
	haveList
		input:     指向哨兵节点的指针
		function:  判断该链表是否为空
		output:    bool类型
*/
bool haveList(node *a);

/*
	**下面均为主菜单调用的函数**
		input:     链表的长度,哨兵节点,链表的首尾信息<nodeInfo>**并非都用到,都调用为格式统一**
		function:  执行用户选择的功能
		output:	   int
*/
int que1(int &,node &,nodeInfo &);
int que2(int &,node &,nodeInfo &);
int que3(int &,node &,nodeInfo &);
int que4(int &,node &,nodeInfo &);
int que5(int &,node &,nodeInfo &);
int que6(int &,node &,nodeInfo &);
int que7(int &,node &,nodeInfo &);
int que8(int &,node &,nodeInfo &);
int que9(int &,node &,nodeInfo &);
int que10(int &,node &,nodeInfo &);


void printLine(){
	printf("****************************************************************\n");
}
void error(int code){
	switch (code){
		case 1:printf("选择错误，重新选择。。。。\n"); system("pause"); break;
		case 2:printf("链表为空!\n"); system("pause"); break;
		case 3:printf("请输入不小于1的数字\n"); system("pause"); break;
		case 4:printf("链表创建失败!\n"); system("pause"); break;
		case 5:printf("打开文件失败!\n"); system("pause"); break;
		case 6:printf("输入非法数据!\n"); system("pause"); break;
		default:printf("出现未知错误!\n"); system("pause"); break;
	}
}
void menu(){
	tm *t = getTime();
	printf("Copyright <c> 2019-2019 林浩然<221801337>. All Rights Reserved.\n\n");
	printf("当前日期、时间 : %d.%d.%d", t->tm_year+1900,t->tm_mon+1,t->tm_mday);
	printf(" <%s> %02d:%02d:%02d\n",calculateWeekDay(t->tm_year+1900,t->tm_mon+1,t->tm_mday),t->tm_hour,t->tm_min,t->tm_sec);
	printLine();
	printf("*	1:  创建一段新的存放日期数据的<无序>链表               *\n");
	printf("*	2:  显示链表前n个节点的日期数据                        *\n");
	printf("*	3:  将链表存入文件或从文件读取链表                     *\n");
	printf("*	4:  显示不能构成合法日期的<所有>节点                   *\n");
	printf("*	5:  删除节点                                           *\n");
	printf("*	6:  插入节点                                           *\n");
	printf("*	7:  显示节点的日期对应天数                             *\n");
	printf("*	8:  链表按日期大小从小到大排序                         *\n");
	printf("*	9:  找查链表中\"年月日\"都是素数的节点                   *\n");
	printf("*	10: 翻转链表                                           *\n");
	printf("*	11: 退出系统                                           *\n");
	printLine();
	printf("请选择<1-11>:");
}

int printfTtday(node *root){
	int printnum=0,row=0,i=0;
	while(root->next!=NULL){
		row++;
		while(i++<10&&root->next!=NULL){
			printf("%6I64d   ",root->next->t.ttd);
			printnum++;
			root=root->next;
		}
		i=0;
		printf("\n");
		if(row%24==0)system("pause");
	}
	return printnum;
}
int printfNode(node *root,node *cmd(node *),int cnt,int n=0){
	int printnum=0,row=0,i=0;
	char quit;
	root=cmd(root);
	getchar();
	if(n==0)n=cnt;
	while(root->next!=NULL&&printnum<n){
		row++;
		printf("%4d:",row);
		while(i++<6&&root->next!=NULL&&printnum<n){
			printf("  %d.%02d.%02d",root->next->t.year,root->next->t.mon,root->next->t.day);
			printnum++;
			root=cmd(root->next);
		}
		i=0;
		printf("\n");
		if(row%24==0){
			cout<<"链表中共有"<<cnt<<"个节点,已显示"<<printnum<<"个节点\n输入<q\\Q>退出或按任意键继续。。。";
			if((quit=getchar())=='q'||quit=='Q'&&(quit=getchar())=='\n')return printnum;
			else while(quit!='\n')quit=getchar();
		}
	}
	return printnum;
}

bool haveList(node *a){
	if(a->next==NULL){
		error(2);
		return 0;
	}
	return 1;
}

int que1(int &cnt,node &root,nodeInfo &rootInfo){
	int n;
	nodeInfo list;
	cout<<"*******新链表将填充随机数据,并且将会被插入在已有链表之后********\n当前链表内节点数为:"<<cnt<<endl;
	cout<<"请输入要新建的节点数:";
	cin>>n;
	if(n==0){
		error(3);
		return 0;
	}
	list=makeList(n);
	if(list.front==NULL){
		error(4);
	}else{
		addNode(rootInfo.back,&rootInfo,&list);
		cnt+=n;
		cout<<"新建链表成功!\n";
		cout<<"新增节点数:"<<n<<"     当前链表总长:"<<cnt<<endl;system("pause");
	}
	return 1;
}
int que2(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	cout<<"请输入要查询的节点数量(显示全部请输入0):";
	int printnum,que=-1;
	cin>>que;
	if(!cin.good()||que>cnt||que<0){error(6);return 0;}
	printnum=printfNode(&root,showNode,cnt,que);
	cout<<"共有"<<cnt<<"个节点需显示,已显示"<<printnum<<"个节点\n";
	system("pause");
}
int que3(int &cnt,node &root,nodeInfo &rootInfo){
	FILE *fp=NULL;
	char file[100],a;
	int n=0,que;
	node r,*p;
	p=&root;
	memset(file,0,sizeof(file));
	cout<<"输入路径,或将文件拖拽到程序框内<路径长度小于100个字节>(默认为当前文件夹下的list.out):";
	getchar();
	while((a=getchar())!='\n'){
		file[n++]=a;
	}
	if(n<=0)strcpy(file,".\\list.out");
	cout<<"1.从文件读取数据\n2.把数据存入文件\n输入要执行的操作:";
	cin>>que;
	if(que==1){
		fp=fopen(file,"r");
		if(fp==NULL){
			error(5);
			return 0;
		}
		while(fscanf(fp,"%d%d%d%I64d",&r.t.year,&r.t.mon,&r.t.day,&r.t.ttd)!=EOF){
			addNode(p,&r,&rootInfo);
			p=p->next;
			cnt++;
		}
		fclose(fp);
	}else if(que==2){
		if(!haveList(&root))return 0;
		cout<<"1.将数据追加在文件后面\n2.将数据覆盖\n输入要执行的操作:";
		cin>>que;
		if(que==1)fp=fopen(file,"a");
		else if(que==2)fp=fopen(file,"w");
		else{
			error(1);
			return 0;
		}
		while(p->next!=NULL){
			p=p->next;
			fprintf(fp,"%d %d %d %I64d\n",p->t.year,p->t.mon,p->t.day,p->t.ttd);
		}
		fclose(fp);
		return 1;
	}else {
		error(1);
		return 0;
	}
}
int que4(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	int n;
	n=printfNode(&root,showWrongNode,cnt);
	cout<<"当前链表总节点数:"<<cnt<<"     非法节点数:"<<n<<"     合法节点数:"<<cnt-n<<endl;
	system("pause");
	return 1;
}
int que5(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	int que,k,n;
	cout<<"当前链表总节点数:"<<cnt<<endl;
	cout<<"1.删除链表的第一个节点\n2.删除链表的最后一个节点\n";
	cout<<"3.删除链表的第k个节点后的n个节点\n4.所有不能构成合法日期的结点\n";
	cout<<"5.删除链表中\"年月日\"都是素数的节点\n6.清空链表\n";
	cout<<"输入要执行的操作:";
	cin>>que;
	switch (que){
		case 1:n=delNode(&root,1,&rootInfo);break;
		case 2:n=delNode(findKNode(&root,cnt-1),1,&rootInfo);break;
		case 3:
			cout<<"开始的节点k:";cin>>k;
			cout<<"删除的节点n:";cin>>n;
			if(k<=0||k>cnt||n+k-1>cnt||n<0){error(6);return 0;}
			delNode(findKNode(&root,k),n,&rootInfo);
			break;
		case 4:n=delNode(&root,showWrongNode,&rootInfo);break;
		case 5:n=delNode(&root,showPrimeNode,&rootInfo);break;
		case 6:n=delNode(&root,showNode,&rootInfo);break;
		default:error(1);return 0;
	}
	cnt-=n;
	cout<<"删除总节数:"<<n<<"     当前链表总节点数:"<<cnt<<endl;
	system("pause");
	return 1;
}
int que6(int &cnt,node &root,nodeInfo &rootInfo){
	int que,que1;
	node insert;
	insert.next=NULL;
	cout<<"当前链表总节点数:"<<cnt<<endl;
	cout<<"1.插入到链表头\n2.插入到链表尾插\n3.插入到第一个大于该结点日期的前面\n4.插入到第一个小于该结点日期的后面\n";
	cout<<"输入要执行的操作:";
	cin>>que;
	if(que!=1&&que!=2&&que!=3&&que!=4){
		error(1);
		return 0;
	}
	cout<<"1.当前日期\n2.手动输入一个日期\n";
	cout<<"输入要执行的操作:";
	cin>>que1;
	if(que1!=1&&que1!=2){
		error(1);
		return 0;
	}
	if(que1==1)insert=tmToNode(getTime());
	else if(que1==2){
		cout<<"输入要插入的日期<请输入的日期在2000-2100之间>(年月日以空格隔开,例如:2000 1 1):";
		cin>>insert.t.year>>insert.t.mon>>insert.t.day;
		if(!rightData(&insert)){
			error(6);
			return 0;
		}
		insert.t.ttd=ttday(insert.t.year,insert.t.mon,insert.t.day);
	}
	switch(que){
		case 1:addNode(rootInfo.front,&insert,&rootInfo);break;
		case 2:addNode(rootInfo.back,&insert,&rootInfo);break;
		case 3:addNode(findBiger(rootInfo.front,&insert),&insert,&rootInfo);break;
		case 4:addNode(findSmaller(rootInfo.front,&insert),&insert,&rootInfo);break;
	}
	cnt+=1;
	return 1;
}
int que7(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	int n;
	n=printfTtday(&root);
	cout<<"共有"<<cnt<<"个节点需显示,已显示"<<n<<"个节点\n";
	system("pause");
	return 1;
}
int que8(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	cout<<"当前链表总节点数:"<<cnt<<endl;
	cout<<"正在排序链表。。。";
	root.next=mergeSort(root.next);
	rootInfo.back=findKNode(&root,cnt);
	cout<<"\n排序成功\n";
	system("pause");
	return 1;
}
int que9(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	int n;
	n=printfNode(&root,showPrimeNode,cnt);
	cout<<"共有"<<cnt<<"个节点需显示,已显示"<<n<<"个节点\n";
	system("pause");
	return 1;
}
int que10(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	cout<<"当前链表总节点数:"<<cnt<<endl;
	cout<<"正在翻转链表。。。";
	if(cnt>=2)root.next=turnList(&rootInfo);
	cout<<"\n翻转完成\n";
	system("pause");
	return 1;
}
#endif