//�����������û����н����ĺ���
#ifndef LIST2_h 
#define LIST2_h
#include"�ֺ�Ȼ_221801337_list1.h"


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Function
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
	printLine
		input:     void
		function:  �������һ���ָ��� 
		output:    void
	error
		input:     int���͵Ĵ������
		function:  �������������Ϣ
		output:    void
	menu
		input:     void
		function:   ����������˵� 
		output:    void
*/
void printLine();
void error(int);
void menu(); 

/*
	printTtday
		input:     ��ʼ�ڵ��ָ��
		function:  ������ҳ����������ھ���2000��1��1�յ�����  
		output:    ����ڵ�ĸ���
	printfNode
		input:     ��ʼ�ڵ��ָ��,�Ҳ�ķ���,�����еĽڵ���,����Ľڵ����Ĭ��<n=0>
		function:  ������ҳ�����������
		output:    ����ڵ�ĸ���
		����:
		showNode:        ��ʾ����ڵ�<֮��>�����нڵ�
		showWrongNode:   ��ʾ����ڵ�<֮��>�����в��ܹ��ɺϷ����ڵĽ��
		showPrimeNode:   ��ʾ����ڵ�<֮��>�����������Ľڵ�
*/
int printTtday(node *);
int printfNode(node *,node *cmd(node *),int,int);

/*
	haveList
		input:     ָ���ڱ��ڵ��ָ��
		function:  �жϸ������Ƿ�Ϊ��
		output:    bool����
*/
bool haveList(node *a);

/*
	**�����Ϊ���˵����õĺ���**
		input:     ����ĳ���,�ڱ��ڵ�,�������β��Ϣ<nodeInfo>**���Ƕ��õ�,������Ϊ��ʽͳһ**
		function:  ִ���û�ѡ��Ĺ���
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
		case 1:printf("ѡ���������ѡ�񡣡�����\n"); system("pause"); break;
		case 2:printf("����Ϊ��!\n"); system("pause"); break;
		case 3:printf("�����벻С��1������\n"); system("pause"); break;
		case 4:printf("������ʧ��!\n"); system("pause"); break;
		case 5:printf("���ļ�ʧ��!\n"); system("pause"); break;
		case 6:printf("����Ƿ�����!\n"); system("pause"); break;
		default:printf("����δ֪����!\n"); system("pause"); break;
	}
}
void menu(){
	tm *t = getTime();
	printf("Copyright <c> 2019-2019 �ֺ�Ȼ<221801337>. All Rights Reserved.\n\n");
	printf("��ǰ���ڡ�ʱ�� : %d.%d.%d", t->tm_year+1900,t->tm_mon+1,t->tm_mday);
	printf(" <%s> %02d:%02d:%02d\n",calculateWeekDay(t->tm_year+1900,t->tm_mon+1,t->tm_mday),t->tm_hour,t->tm_min,t->tm_sec);
	printLine();
	printf("*	1:  ����һ���µĴ���������ݵ�<����>����               *\n");
	printf("*	2:  ��ʾ����ǰn���ڵ����������                        *\n");
	printf("*	3:  ����������ļ�����ļ���ȡ����                     *\n");
	printf("*	4:  ��ʾ���ܹ��ɺϷ����ڵ�<����>�ڵ�                   *\n");
	printf("*	5:  ɾ���ڵ�                                           *\n");
	printf("*	6:  ����ڵ�                                           *\n");
	printf("*	7:  ��ʾ�ڵ�����ڶ�Ӧ����                             *\n");
	printf("*	8:  �������ڴ�С��С��������                         *\n");
	printf("*	9:  �Ҳ�������\"������\"���������Ľڵ�                   *\n");
	printf("*	10: ��ת����                                           *\n");
	printf("*	11: �˳�ϵͳ                                           *\n");
	printLine();
	printf("��ѡ��<1-11>:");
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
			cout<<"�����й���"<<cnt<<"���ڵ�,����ʾ"<<printnum<<"���ڵ�\n����<q\\Q>�˳������������������";
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
	cout<<"*******����������������,���ҽ��ᱻ��������������֮��********\n��ǰ�����ڽڵ���Ϊ:"<<cnt<<endl;
	cout<<"������Ҫ�½��Ľڵ���:";
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
		cout<<"�½�����ɹ�!\n";
		cout<<"�����ڵ���:"<<n<<"     ��ǰ�����ܳ�:"<<cnt<<endl;system("pause");
	}
	return 1;
}
int que2(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	cout<<"������Ҫ��ѯ�Ľڵ�����(��ʾȫ��������0):";
	int printnum,que=-1;
	cin>>que;
	if(!cin.good()||que>cnt||que<0){error(6);return 0;}
	printnum=printfNode(&root,showNode,cnt,que);
	cout<<"����"<<cnt<<"���ڵ�����ʾ,����ʾ"<<printnum<<"���ڵ�\n";
	system("pause");
}
int que3(int &cnt,node &root,nodeInfo &rootInfo){
	FILE *fp=NULL;
	char file[100],a;
	int n=0,que;
	node r,*p;
	p=&root;
	memset(file,0,sizeof(file));
	cout<<"����·��,���ļ���ק���������<·������С��100���ֽ�>(Ĭ��Ϊ��ǰ�ļ����µ�list.out):";
	getchar();
	while((a=getchar())!='\n'){
		file[n++]=a;
	}
	if(n<=0)strcpy(file,".\\list.out");
	cout<<"1.���ļ���ȡ����\n2.�����ݴ����ļ�\n����Ҫִ�еĲ���:";
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
		cout<<"1.������׷�����ļ�����\n2.�����ݸ���\n����Ҫִ�еĲ���:";
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
	cout<<"��ǰ�����ܽڵ���:"<<cnt<<"     �Ƿ��ڵ���:"<<n<<"     �Ϸ��ڵ���:"<<cnt-n<<endl;
	system("pause");
	return 1;
}
int que5(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	int que,k,n;
	cout<<"��ǰ�����ܽڵ���:"<<cnt<<endl;
	cout<<"1.ɾ������ĵ�һ���ڵ�\n2.ɾ����������һ���ڵ�\n";
	cout<<"3.ɾ������ĵ�k���ڵ���n���ڵ�\n4.���в��ܹ��ɺϷ����ڵĽ��\n";
	cout<<"5.ɾ��������\"������\"���������Ľڵ�\n6.�������\n";
	cout<<"����Ҫִ�еĲ���:";
	cin>>que;
	switch (que){
		case 1:n=delNode(&root,1,&rootInfo);break;
		case 2:n=delNode(findKNode(&root,cnt-1),1,&rootInfo);break;
		case 3:
			cout<<"��ʼ�Ľڵ�k:";cin>>k;
			cout<<"ɾ���Ľڵ�n:";cin>>n;
			if(k<=0||k>cnt||n+k-1>cnt||n<0){error(6);return 0;}
			delNode(findKNode(&root,k),n,&rootInfo);
			break;
		case 4:n=delNode(&root,showWrongNode,&rootInfo);break;
		case 5:n=delNode(&root,showPrimeNode,&rootInfo);break;
		case 6:n=delNode(&root,showNode,&rootInfo);break;
		default:error(1);return 0;
	}
	cnt-=n;
	cout<<"ɾ���ܽ���:"<<n<<"     ��ǰ�����ܽڵ���:"<<cnt<<endl;
	system("pause");
	return 1;
}
int que6(int &cnt,node &root,nodeInfo &rootInfo){
	int que,que1;
	node insert;
	insert.next=NULL;
	cout<<"��ǰ�����ܽڵ���:"<<cnt<<endl;
	cout<<"1.���뵽����ͷ\n2.���뵽����β��\n3.���뵽��һ�����ڸý�����ڵ�ǰ��\n4.���뵽��һ��С�ڸý�����ڵĺ���\n";
	cout<<"����Ҫִ�еĲ���:";
	cin>>que;
	if(que!=1&&que!=2&&que!=3&&que!=4){
		error(1);
		return 0;
	}
	cout<<"1.��ǰ����\n2.�ֶ�����һ������\n";
	cout<<"����Ҫִ�еĲ���:";
	cin>>que1;
	if(que1!=1&&que1!=2){
		error(1);
		return 0;
	}
	if(que1==1)insert=tmToNode(getTime());
	else if(que1==2){
		cout<<"����Ҫ���������<�������������2000-2100֮��>(�������Կո����,����:2000 1 1):";
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
	cout<<"����"<<cnt<<"���ڵ�����ʾ,����ʾ"<<n<<"���ڵ�\n";
	system("pause");
	return 1;
}
int que8(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	cout<<"��ǰ�����ܽڵ���:"<<cnt<<endl;
	cout<<"����������������";
	root.next=mergeSort(root.next);
	rootInfo.back=findKNode(&root,cnt);
	cout<<"\n����ɹ�\n";
	system("pause");
	return 1;
}
int que9(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	int n;
	n=printfNode(&root,showPrimeNode,cnt);
	cout<<"����"<<cnt<<"���ڵ�����ʾ,����ʾ"<<n<<"���ڵ�\n";
	system("pause");
	return 1;
}
int que10(int &cnt,node &root,nodeInfo &rootInfo){
	if(!haveList(&root))return 0;
	cout<<"��ǰ�����ܽڵ���:"<<cnt<<endl;
	cout<<"���ڷ�ת��������";
	if(cnt>=2)root.next=turnList(&rootInfo);
	cout<<"\n��ת���\n";
	system("pause");
	return 1;
}
#endif