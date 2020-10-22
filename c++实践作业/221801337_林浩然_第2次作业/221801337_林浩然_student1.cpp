#define _CRT_SECURE_NO_DEPRECATE
/*
	�������ֺ�Ȼ		ѧ�ţ�221801337
	�༶�����3��		�绰��18597701284
	���䣺958480638@qq.com
	����ʹ����STL���е�map��multimap��������ײ����ɺ����ʵ��
	���Զ���ÿһ�β�ѯ��ʱ�临�Ӷȴ�o(n)����o(logn)
	��������windows�£���visual studio 2019�п�������windows��
	����

*/
#include "221801337_�ֺ�Ȼ_student.h"

map<string,Stu>stu;
map<string,string>country,id;
map<int,string>nation,place,political_status,marital,training_level,student_type,enrollment_type,academy;
map<int,teacherInfo>teacher;
map<pii,majorInfo>major;

multimap<string,string>m_country,m_name;
multimap<int,string>m_teacher,m_student_class,m_nation,m_political_status,m_training_level,m_academy,m_gender,m_grade;
multimap<pii,string>m_major;


const char sex[3][3]={"NA","��","Ů"};
const char WEEK[7][10]={"������","����һ","���ڶ�","������","������","������","������"};
const int MON[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
date now; 

int main(){
	cout<<"���ڻ�ȡ������Ϣ������"<<endl;
	if(!getData()){
		cout<<"E:�����ʼ��ʧ��:�����ļ�ȱʧ"<<endl;
		system("pause");
		return 0;
	}
	cout<<"�����ʼ���ɹ�"<<endl;
	int cmp=0;
	while(1){
		menu();
		//showList(country,2,24,5,34);
		cin>>cmp;
		clear();
		switch(cmp){
			case 1:que1();break;
			case 2:que2();break;
			case 3:que3();break;
			case 4:que4();break;
			case 5:que5();break;
			case 6:que6();break;
			case 7:que7();break;
			case 8:return 0;
			default:error(1);break;
		}
		cmp=0;
		if(!cin.good()){
			cin.clear();
			while(getchar()!='\n');
		}
		system("CLS");
	}
}
bool que1(){
	getStuInfo();
	return 1;
}
bool que2(){
	string f;
	while(1){
		cout<<"������ѧ��:";
		cin>>f;
		if(f.size()==9&&stu.count(f)==1)
			break;
		if(f.size()!=9){
			cout<<"�����ѧ����Ч\n";
			pause();
			return 0;
		}else if(stu.count(f)==0){
			cout<<"û��ѧ��Ϊ"<<f<<"��ѧ��\n";
			pause();
			return 0;
		}
	}
	stuInfo &s=stu[f].info;
	printfStu(s);
	printLine();
	if(YorN("�Ƿ�ɾ����ѧ��(Y/N):"))delStudent(s);
	else{
		pause();
		return 0;
	}
	cout<<"ѧ��Ϊ"<<f<<"ѧ����Ϣ��ɾ��\n";
	pause();
	return 1;
}
bool que3(){
	string f;
	while(1){
		cout<<"������ѧ��:";
		cin>>f;
		getchar();
		if(f.size()==9&&stu.count(f)==1)
			break;
		if(f.size()!=9){
			cout<<"�����ѧ����Ч\n";
			pause();
			return 0;
		}else if(stu.count(f)==0){
			cout<<"û��ѧ��Ϊ"<<f<<"��ѧ��\n";
			pause();
			return 0;
		}
	}
	Stu tmp=stu[f];
	stuInfo &s=tmp.info;
	getfind("�޸�����",s,getName);
	getfind("�޸��Ա�",s,getGender);
	getfind("�޸Ĺ��Һ͵���",s,getCountry);
	getfind("�޸ĳ�������",s,getBirth);
	if(s.country!=stu[f].info.country&&s.country=="CN")while(!getNation(s));
	else if(s.country=="CN")getfind("�޸�����",s,getNation);
	getfind("�޸Ļ���״��",s,getMarital);
	getfind("�޸�������ò",s,getPoliticalStatus);
	if(s.country!=stu[f].info.country&&s.country=="CN")while(!getID(s));
	else if(s.country=="CN")getfind("�޸����֤",s,getID);
	getfind("�޸���ѧ����",s,getEnrollmentYear);
	getfind("�޸�ѧ������",s,getStudentType);
	getfind("�޸�ѧԺ",s,getAcademy);
	if(s.academy==stu[f].info.academy)getfind("�޸�רҵ",s,getMajor);
	else while(!getMajor(s));
	getfind("�޸��꼶",s,getGrade);
	getfind("�޸�ѧ��",s,getLengthOfSchooling);
	getfind("�޸��������",s,getTrainingLevel);
	getfind("�޸İ༶",s,getStudentClass);
	getfind("�޸ĸ���Ա",s,getTeacher);
	printfStu(s);
	printLine();
	Stu t=stu[f];
	delStudent(stu[f].info);
	check e;
	int er,b;
	b=e.checkData(s);
	er=e.getErrorNum();
	string ER=e.getErrorInfo();
	if(b==-1){
		cout<<"�����ѧ����Ϣ����"<<er<<"������:\n";
		cout<<ER;
		cout<<"ѧ����Ϣ�޸�ʧ��\n";
		stu[f]=t;
		push(t.info);
		pause();
		return 0;
	}else if(b==0){
		cout<<"����:\n";
		cout<<ER;
		if(!YorN("�Ƿ�¼��(Y/N):")){
			stu[f]=t;
			push(t.info);
			pause();
			return 0;
		}
	}
	stu[f]=tmp;
	push(s);
	cout<<"ѧ����Ϣ�޸ĳɹ�\n";
	pause();
	return 1;
}
bool que4(){
	stuInfo f;
	if(YorN("�Ƿ�ѧ�Ų�ѯ(Y/N):")){
		while(1){
			cout<<"������ѧ��:";
			cin>>f.No;
			if(f.No.size()==9){
				findStu(f);
				printLine();
				pause();
				return 1;
			}else{
				cout<<"����ѧ����Ч\n";
				pause();
			}
		}
	}
	getfind("��ѯ����",f,getName);
	getfind("��ѯ���Һ͵���",f,getCountry);
	getfind("��ѯ����Ա",f,getTeacher);
	getfind("��ѯ�༶",f,getStudentClass);
	getfind("��ѯ����",f,getNation);
	getfind("��ѯ������ò",f,getPoliticalStatus);
	getfind("��ѯ�������",f,getTrainingLevel);
	getfind("��ѯѧԺ",f,getAcademy);
	if(f.academy!=0)getfind("��ѯרҵ",f,getAcademy);
	getfind("��ѯ�Ա�",f,getGender);
	getfind("��ѯ�꼶",f,getGrade);
	if(findStu(f))printLine();
	pause();
	return 1;
}
bool que5(){
	int cnt=0,c;
	char quit;
	cout<<"ѡ�������ʽ:\n1.��ѧ�Ŵ�С���\n2.�����꼶���\n���ѡ��:";
	cin>>c;
	if(c==1){
		map<string,Stu>::iterator it=stu.begin(),ed=stu.end();
		while(it!=ed){
			printfStu(it->second.info);
			it++;
			cnt++;
			if(cnt!=0&&(cnt%2==0)){
				printLine();
				cout<<"\n�����������������<p\\P>�˳����:";
				if(((quit=_getche())=='p'||quit=='P')){cout<<endl;return 0;}
				cout<<endl;
			}
		}
	}else if(c==2){
		map<int,string>::iterator it=m_grade.begin(),ed=m_grade.end();
		while(it!=ed){
			printfStu(stu[it->se].info);
			it++;
			cnt++;
			if(cnt!=0&&(cnt%2==0)){
				printLine();
				cout<<"\n�����������������<p\\P>�˳����:";
				if(((quit=_getche())=='p'||quit=='P')){cout<<endl;return 0;}
				cout<<endl;
			}
		}
	}else{
		error(1);
		return 0;
	}
	if(cnt%2!=0)printLine();
	cout<<"\n������������ʾ\n";
	pause();
	return 1;
}
bool que6(){
	int cmp;
	cout<<"��ѡ�����\n1.���ļ�����ѧ����Ϣ221801337_�ֺ�Ȼ_student_list.dat\n2.��ѧ����Ϣ����221801337_�ֺ�Ȼ_student_list.dat\n���������ѡ��:";
	cin>>cmp;
	if(cmp==1){
		if(getStudentList()){
			cout<<"ѧ����Ϣ��ȡ�ɹ�\n";
			pause();
		}else{
			cout<<"ѧ����Ϣ��ȡʧ��\n";
			pause();
		}
	}else if(cmp==2){
		if(saveStudentList()){
			cout<<"ѧ����Ϣ����ɹ�\n";
			pause();
		}else{
			cout<<"ѧ����Ϣ����ʧ��\n";
			pause();
		}
	}else{
		error(1);
		return 0;
	}
	return 1;
}

/*

multimap<int,string>m_political_status,m_training_level,m_academy,m_gender,m_grade;
multimap<pii,string>m_major;
*/
bool que7(){
	cout<<"��ǰѧ����Ϣ��:"<<stu.size()<<endl;
	cout<<"��ǰѧԺ��:"<<academy.size()<<endl;
	cout<<"��ǰרҵ��:"<<major.size()<<endl;
	cout<<"��ǰ����Ա��:"<<teacher.size()<<endl;
	cout<<"��ǰ��Ա��:"<<m_political_status.count(1)<<endl;
	cout<<"��ǰ"<<now.year<<"��ѧ����:"<<m_grade.count(now.year%100)<<endl;
	cout<<"��ǰ"<<now.year-1<<"��ѧ����:"<<m_grade.count(now.year%100-1)<<endl;
	cout<<"��ǰ"<<now.year-2<<"��ѧ����:"<<m_grade.count(now.year%100-2)<<endl;
	cout<<"��ǰ"<<now.year-3<<"��ѧ����:"<<m_grade.count(now.year%100-3)<<endl;
	cout<<"��ǰ"<<now.year-4<<"��ѧ����:"<<m_grade.count(now.year%100-4)<<endl;
	pause();
	return 1;
}
