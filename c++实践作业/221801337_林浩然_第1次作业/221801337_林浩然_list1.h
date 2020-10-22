//包含各种计算函数 
#ifndef LIST1_h 
#define LIST1_h
#define Lyear 2000
#define Ryear 2100
#define rep(i,a,b) for(int i=a;i<b;i++)
typedef long long ll;


int MON[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
char WEEK[7][10]={"星期一","星期二","星期三","星期四","星期五","星期六","星期天"};


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Struct
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
	链表的节点 
		dataspace:包含了node的数据
		year储存年份 mon储存月份  day储存日期 
	week储存星期 ttd储存结点的日期距离2000年1月1日的天数  
		node:链表的节点
		t数据域 next指针域
	nodeInfo:包含了链表的首尾信息
		front指向链表的第一个节点 back指向链表的最后一个节点
	重载运算符<:按结点的日期距离2000年1月1日的天数多少比较大小
*/
struct dataspace{
	int year,mon,day;
	ll ttd;
};
struct node{
	dataspace t;
	node *next;
};
struct nodeInfo{
	node *front=NULL,*back=NULL;
};


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Function
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
	calculateDays
		input:     年月日
		function:  计算输入日期到公元前某天之间的天数
		output:    long long类型的输入日期到公元前某天之间的天数
	ttday
		input:     年月日
		function:  计算输入日期距离2000年1月1日的天数
		output:    long long类型的输入日期距离2000年1月1日的天数
	calculateWeekDay
		input:     long long类型的输入日期距离2000年1月1日的天数
		function:  计算输入天数对应的星期
		output:    指向星期的char类型的指针
*/
ll calculateDays(ll,ll,ll); 
ll ttday(ll,ll,ll);
char *calculateWeekDay(ll y,ll m,ll d);

/*
	getTime
		input:      void
		function:   获取系统时间
		output:     tm类型的指针
	tmToNode
		input:     tm类型的指针
		function:  将tm类型转换为node类型
		output:    node类型
*/
tm *getTime();
node tmToNode(tm *);

/*
	addNode(node *)
		input:     一个节点的指针
		function:  在输入节点<之后>添加一个空节点
		output:    void
	addNode(node *,nodeInfo *,nodeInfo *)
		input:     要插入位置节点的指针,被插入的链表的首尾信息<nodeInfo>,要插入的链表的首尾信息<nodeInfo>
		function:  在输入节点<之后>插入要插入的链表
		output:    void
	addNode(node *,node *)
		input:     要插入位置节点的指针,被插入的节点的指针,链表的首尾信息<nodeInfo>
		function:  在输入节点<之后>插入被插入的节点的<副本>,并更新链表的尾信息<nodeInfo>
		output:    void
*/
void addNode(node *);
void addNode(node *,nodeInfo *,nodeInfo *);
void addNode(node *,node *,nodeInfo *);

/*
	delNode(node *)
		input:     起始节点的指针
		function:  删除输入节点<之后>的第一个节点
		output:    删除的节点数
	delNode(node *,int,nodeInfo *)
		input:     起始节点的指针,删除节点的个数
		function:  删除输入节点<之后>的n个节点,并更新链表的尾信息<nodeInfo>
		output:    删除的节点数
	delNode(node *,node *cmd(node *),nodeInfo *)
		input:     起始节点的指针,找查的方法,链表的首尾信息<nodeInfo>
		function:  删除输入节点<之后>的所有按方法找到的节点,并更新链表的尾信息<nodeInfo>
		output:    删除的节点数
		方法:
		showNode:        删除输入节点<之后>的所有节点
		showWrongNode:   删除输入节点<之后>的所有不能构成合法日期的结点
		showPrimeNode:   删除输入节点<之后>的所有素数的节点
*/
int delNode(node *);
int delNode(node *,int,nodeInfo *);
int delNode(node *,node *cmd(node *),nodeInfo *);

/*
	makeList
		input:     要创建的随机数据节点数n
		function:  创建n个随机数据节点，并将节点首位数据保存在一个nodeInfo中
		output:    nodeInfo类型的新创建节点的首尾数据
*/
nodeInfo makeList(int);

/*
	rightData
		input:     指向一个节点的指针
		function:  判断该节点的日期是否合法
		output:    bool类型
*/
bool rightData(node *);

/*
	**下列函数用来判断日期是否为素数**
	prime
		input:     一个长整型数字
		function:  判断该数字是否为素数
		output:    bool类型
	isPrime
		input:     指向一个节点的指针
		function:  判断该节点的日期是否都为素数
		output:    bool类型
*/
bool prime(ll);
bool isPrime(node *);

/*
	**下面三个均为找查指点的日期的函数**
	input:    指向起始节点的指针
	function: 找查指定节点
	output: 
		showNode:       返回当前个节点的指针
		showWrongNode:  返回下一个不能构成合法日期的结点的上一个节点的指针
		showPrimeNode:  返回下一个日期均为素数的节点的上一个节点的指针
*/
node *showNode(node *);
node *showWrongNode(node *);
node *showPrimeNode(node *);

/*
	findKNode
		input:     哨兵节点,整数k
		function:  找到第k个节点
		output:    返回第k个节点的指针
*/
node *findKNode(node *,int);

/*
	**利用归并排序来排序链表**
	merge
		input:      需要归并的链表a,需要归并的链表b
		function:  归并链表ab
		output:    归并完成后的链表的头指针
	mergeSort
		input:     指向需要排序的链表的第一个节点的指针
		function:  利用归并排序来排序链表
		output:    归并排序后的链表的头指针
*/
node *merge(node *a,node *b);
node *mergeSort(node *root);

/*
	turnList
		input:     哨兵节点,整数k
		function:  被插入的链表的首尾信息<nodeInfo>
		output:    返回翻转后的头节点
*/
node *turnList(nodeInfo *);

/*
	findBiger
		input:     哨兵节点,别比较的节点
		function:  寻找第一个日期大于该节点的节点
		output:    返回指向第一个日期大于该节点的前一个节点的指针
	turnList
		input:     哨兵节点,别比较的节点
		function:  寻找第一个日期小于该节点的节点
		output:    返回指向第一个日期小于该节点的前一个节点的指针
*/
node *findBiger(node *,node *);
node *findSmaller(node *,node *);

ll calculateDays(ll y,ll m,ll d){
	if((m-=2)<=0){
		y--;
		m+=12;
	}
	return y/4-y/100+y/400+367*m/12+d+y*365; 
}
ll ttday(ll y,ll m,ll d){
	return calculateDays(y,m,d)-calculateDays(2000,1,1);
} 
char *calculateWeekDay(ll y,ll m,ll d){
	return WEEK[(ttday(y,m,d)+5)%7];
}

tm *getTime(){
	time_t tt=time(0);
	tm *t=localtime(&tt);
	return t;
}
node tmToNode(tm* t){
	node tm;
	tm.t.year=t->tm_year+1900;
	tm.t.mon=t->tm_mon+1;
	tm.t.day=t->tm_mday;
	tm.t.ttd=ttday(tm.t.year,tm.t.mon,tm.t.day);
	return tm;
}

void addNode(node *a){
	node *p=new node;
	p->next=a->next;
	a->next=p;
}
void addNode(node *insert,nodeInfo *a,nodeInfo *b){
	node *p;
	p=insert->next;
	insert->next=b->front;
	b->back->next=p;
	if(insert==a->back)a->back=b->back;
}
void addNode(node *a,node *add,nodeInfo *list){
	node *p=new node; 
	p->t.year=add->t.year;
	p->t.mon=add->t.mon;
	p->t.day=add->t.day;
	p->t.ttd=add->t.ttd;
	p->next=a->next;
	a->next=p;
	if(a==list->back)list->back=p;
}

int delNode(node *a){
	node *p;
	p=a->next;
	a->next=p->next;
	delete  p;
	return 1;
}
int delNode(node *a,int n,nodeInfo *list){
	int cnt=0;
	while(a->next!=NULL&&cnt<n){
		cnt+=delNode(a);
	}
	if(a->next==NULL)list->back=a;
	return cnt;
}
int delNode(node *a,node *cmd(node *),nodeInfo *list){
	int n=0;
	a=cmd(a);
	while(a->next!=NULL){
		if(a->next==list->back)list->back=a;
		n+=delNode(a);
		a=cmd(a);
	}
	return n;
}

nodeInfo makeList(int n){
	srand((unsigned)time(NULL));
	node root,*p;
	nodeInfo list;
	root.next=NULL;;
	p=&root;
	rep(i,0,n){
		addNode(p);
		p=p->next;
		p->t.year=rand()%(Ryear-Lyear)+2000;
		p->t.mon=rand()%(12-1+1)+1;
		p->t.day=rand()%(31-1+1)+1;
		p->t.ttd=ttday(p->t.year,p->t.mon,p->t.day);
	}
	list.front=root.next;
	list.back=p;
	return list;
}

bool rightData(node *a){
	if(a==NULL)return 0;
	if(a->t.year<=0||a->t.mon<=0||a->t.day<=0)return 0;
	if(a->t.year>=Lyear&&a->t.year<Ryear&&a->t.day<=MON[a->t.mon]){
		if(a->t.mon!=2)return 1;
		if(!((a->t.year%4==0&&a->t.year%100!=0)||a->t.year%400==0)&&a->t.day==29)return 0;
		else return 1;
	}
	return 0;
}

bool prime(ll n){
	for(int i=2;i*i<n;i++){
		if(n%i==0)return 0;
	}
	return 1;
}
bool isPrime(node *a){
	if(a==NULL)return 0;
	if(prime(a->t.year)&&prime(a->t.mon)&&prime(a->t.day))return 1;
	return 0;
}

node *showNode(node *a){
	return a;
}
node *showWrongNode(node *a){
	while(a->next!=NULL&&rightData(a->next)){
		a=a->next;
	}
	return a;
}
node *showPrimeNode(node *a){
	while(a->next!=NULL&&!isPrime(a->next)){
		a=a->next;
	}
	return a;
}

node *findKNode(node *a,int k){
	int n=0;
	while(a->next!=NULL&&n<k){
		a=a->next;
		n++;
	}
	return a;
}

node *merge(node *a,node *b){
	node root,*p;
	p=&root;
	while(a!=NULL&&b!=NULL){
		if(a->t.ttd<b->t.ttd){
			p->next=a;
			a=a->next;
			p=p->next;
		}else{
			p->next=b;
			b=b->next;
			p=p->next;
		}
	}
	p->next=(a==NULL)?b:a;
	return root.next;
}
node *mergeSort(node *root){
	if(root==NULL||root->next==NULL)return root;
	node *fast,*slow;
	fast=root->next;
	slow=root;
	while(fast!=NULL&&fast->next!=NULL){
		slow=slow->next;
		fast=fast->next->next;
	}
	fast=slow->next;
	slow->next=NULL;
	return merge(mergeSort(root),mergeSort(fast));
}

node *turnList(nodeInfo *list){
	node *p,*f,*b,*head;
	head=f=list->front->next;
	b=list->front->next->next;
	while(b!=NULL){
		f->next=b->next;
		b->next=head;
		head=b;
		b=f->next;
	}
	list->back=f;
	return head;
}

node *findBiger(node *root,node *flag){
	while(root->next!=NULL){
		if(root->next->t.ttd>flag->t.ttd)return root;
		root=root->next;
	}
	return root;
}
node *findSmaller(node *root,node *flag){
	while(root->next!=NULL){
		if(root->next->t.ttd<flag->t.ttd)return root->next;
		root=root->next;
	}
	return root;
}
#endif