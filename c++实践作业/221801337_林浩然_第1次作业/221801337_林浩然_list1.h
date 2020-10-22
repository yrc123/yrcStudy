//�������ּ��㺯�� 
#ifndef LIST1_h 
#define LIST1_h
#define Lyear 2000
#define Ryear 2100
#define rep(i,a,b) for(int i=a;i<b;i++)
typedef long long ll;


int MON[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
char WEEK[7][10]={"����һ","���ڶ�","������","������","������","������","������"};


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Struct
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
	����Ľڵ� 
		dataspace:������node������
		year������� mon�����·�  day�������� 
	week�������� ttd����������ھ���2000��1��1�յ�����  
		node:����Ľڵ�
		t������ nextָ����
	nodeInfo:�������������β��Ϣ
		frontָ������ĵ�һ���ڵ� backָ����������һ���ڵ�
	���������<:���������ھ���2000��1��1�յ��������ٱȽϴ�С
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
		input:     ������
		function:  �����������ڵ���Ԫǰĳ��֮�������
		output:    long long���͵��������ڵ���Ԫǰĳ��֮�������
	ttday
		input:     ������
		function:  �����������ھ���2000��1��1�յ�����
		output:    long long���͵��������ھ���2000��1��1�յ�����
	calculateWeekDay
		input:     long long���͵��������ھ���2000��1��1�յ�����
		function:  ��������������Ӧ������
		output:    ָ�����ڵ�char���͵�ָ��
*/
ll calculateDays(ll,ll,ll); 
ll ttday(ll,ll,ll);
char *calculateWeekDay(ll y,ll m,ll d);

/*
	getTime
		input:      void
		function:   ��ȡϵͳʱ��
		output:     tm���͵�ָ��
	tmToNode
		input:     tm���͵�ָ��
		function:  ��tm����ת��Ϊnode����
		output:    node����
*/
tm *getTime();
node tmToNode(tm *);

/*
	addNode(node *)
		input:     һ���ڵ��ָ��
		function:  ������ڵ�<֮��>���һ���սڵ�
		output:    void
	addNode(node *,nodeInfo *,nodeInfo *)
		input:     Ҫ����λ�ýڵ��ָ��,��������������β��Ϣ<nodeInfo>,Ҫ������������β��Ϣ<nodeInfo>
		function:  ������ڵ�<֮��>����Ҫ���������
		output:    void
	addNode(node *,node *)
		input:     Ҫ����λ�ýڵ��ָ��,������Ľڵ��ָ��,�������β��Ϣ<nodeInfo>
		function:  ������ڵ�<֮��>���뱻����Ľڵ��<����>,�����������β��Ϣ<nodeInfo>
		output:    void
*/
void addNode(node *);
void addNode(node *,nodeInfo *,nodeInfo *);
void addNode(node *,node *,nodeInfo *);

/*
	delNode(node *)
		input:     ��ʼ�ڵ��ָ��
		function:  ɾ������ڵ�<֮��>�ĵ�һ���ڵ�
		output:    ɾ���Ľڵ���
	delNode(node *,int,nodeInfo *)
		input:     ��ʼ�ڵ��ָ��,ɾ���ڵ�ĸ���
		function:  ɾ������ڵ�<֮��>��n���ڵ�,�����������β��Ϣ<nodeInfo>
		output:    ɾ���Ľڵ���
	delNode(node *,node *cmd(node *),nodeInfo *)
		input:     ��ʼ�ڵ��ָ��,�Ҳ�ķ���,�������β��Ϣ<nodeInfo>
		function:  ɾ������ڵ�<֮��>�����а������ҵ��Ľڵ�,�����������β��Ϣ<nodeInfo>
		output:    ɾ���Ľڵ���
		����:
		showNode:        ɾ������ڵ�<֮��>�����нڵ�
		showWrongNode:   ɾ������ڵ�<֮��>�����в��ܹ��ɺϷ����ڵĽ��
		showPrimeNode:   ɾ������ڵ�<֮��>�����������Ľڵ�
*/
int delNode(node *);
int delNode(node *,int,nodeInfo *);
int delNode(node *,node *cmd(node *),nodeInfo *);

/*
	makeList
		input:     Ҫ������������ݽڵ���n
		function:  ����n��������ݽڵ㣬�����ڵ���λ���ݱ�����һ��nodeInfo��
		output:    nodeInfo���͵��´����ڵ����β����
*/
nodeInfo makeList(int);

/*
	rightData
		input:     ָ��һ���ڵ��ָ��
		function:  �жϸýڵ�������Ƿ�Ϸ�
		output:    bool����
*/
bool rightData(node *);

/*
	**���к��������ж������Ƿ�Ϊ����**
	prime
		input:     һ������������
		function:  �жϸ������Ƿ�Ϊ����
		output:    bool����
	isPrime
		input:     ָ��һ���ڵ��ָ��
		function:  �жϸýڵ�������Ƿ�Ϊ����
		output:    bool����
*/
bool prime(ll);
bool isPrime(node *);

/*
	**����������Ϊ�Ҳ�ָ������ڵĺ���**
	input:    ָ����ʼ�ڵ��ָ��
	function: �Ҳ�ָ���ڵ�
	output: 
		showNode:       ���ص�ǰ���ڵ��ָ��
		showWrongNode:  ������һ�����ܹ��ɺϷ����ڵĽ�����һ���ڵ��ָ��
		showPrimeNode:  ������һ�����ھ�Ϊ�����Ľڵ����һ���ڵ��ָ��
*/
node *showNode(node *);
node *showWrongNode(node *);
node *showPrimeNode(node *);

/*
	findKNode
		input:     �ڱ��ڵ�,����k
		function:  �ҵ���k���ڵ�
		output:    ���ص�k���ڵ��ָ��
*/
node *findKNode(node *,int);

/*
	**���ù鲢��������������**
	merge
		input:      ��Ҫ�鲢������a,��Ҫ�鲢������b
		function:  �鲢����ab
		output:    �鲢��ɺ�������ͷָ��
	mergeSort
		input:     ָ����Ҫ���������ĵ�һ���ڵ��ָ��
		function:  ���ù鲢��������������
		output:    �鲢�����������ͷָ��
*/
node *merge(node *a,node *b);
node *mergeSort(node *root);

/*
	turnList
		input:     �ڱ��ڵ�,����k
		function:  ��������������β��Ϣ<nodeInfo>
		output:    ���ط�ת���ͷ�ڵ�
*/
node *turnList(nodeInfo *);

/*
	findBiger
		input:     �ڱ��ڵ�,��ȽϵĽڵ�
		function:  Ѱ�ҵ�һ�����ڴ��ڸýڵ�Ľڵ�
		output:    ����ָ���һ�����ڴ��ڸýڵ��ǰһ���ڵ��ָ��
	turnList
		input:     �ڱ��ڵ�,��ȽϵĽڵ�
		function:  Ѱ�ҵ�һ������С�ڸýڵ�Ľڵ�
		output:    ����ָ���һ������С�ڸýڵ��ǰһ���ڵ��ָ��
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