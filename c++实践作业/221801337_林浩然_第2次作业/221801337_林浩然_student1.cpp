#define _CRT_SECURE_NO_DEPRECATE
/*
	姓名：林浩然		学号：221801337
	班级：软件3班		电话：18597701284
	邮箱：958480638@qq.com
	程序使用了STL库中的map和multimap，由于其底层是由红黑树实现
	所以对于每一次查询的时间复杂度从o(n)降到o(logn)
	本程序在windows下，用visual studio 2019中开发，在windows下
	运行

*/
#include "221801337_林浩然_student.h"

map<string,Stu>stu;
map<string,string>country,id;
map<int,string>nation,place,political_status,marital,training_level,student_type,enrollment_type,academy;
map<int,teacherInfo>teacher;
map<pii,majorInfo>major;

multimap<string,string>m_country,m_name;
multimap<int,string>m_teacher,m_student_class,m_nation,m_political_status,m_training_level,m_academy,m_gender,m_grade;
multimap<pii,string>m_major;


const char sex[3][3]={"NA","男","女"};
const char WEEK[7][10]={"星期天","星期一","星期二","星期三","星期四","星期五","星期六"};
const int MON[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
date now; 

int main(){
	cout<<"正在获取配置信息。。。"<<endl;
	if(!getData()){
		cout<<"E:程序初始化失败:配置文件缺失"<<endl;
		system("pause");
		return 0;
	}
	cout<<"程序初始化成功"<<endl;
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
		cout<<"请输入学号:";
		cin>>f;
		if(f.size()==9&&stu.count(f)==1)
			break;
		if(f.size()!=9){
			cout<<"输入的学号无效\n";
			pause();
			return 0;
		}else if(stu.count(f)==0){
			cout<<"没有学号为"<<f<<"的学生\n";
			pause();
			return 0;
		}
	}
	stuInfo &s=stu[f].info;
	printfStu(s);
	printLine();
	if(YorN("是否删除该学生(Y/N):"))delStudent(s);
	else{
		pause();
		return 0;
	}
	cout<<"学号为"<<f<<"学生信息已删除\n";
	pause();
	return 1;
}
bool que3(){
	string f;
	while(1){
		cout<<"请输入学号:";
		cin>>f;
		getchar();
		if(f.size()==9&&stu.count(f)==1)
			break;
		if(f.size()!=9){
			cout<<"输入的学号无效\n";
			pause();
			return 0;
		}else if(stu.count(f)==0){
			cout<<"没有学号为"<<f<<"的学生\n";
			pause();
			return 0;
		}
	}
	Stu tmp=stu[f];
	stuInfo &s=tmp.info;
	getfind("修改姓名",s,getName);
	getfind("修改性别",s,getGender);
	getfind("修改国家和地区",s,getCountry);
	getfind("修改出生日期",s,getBirth);
	if(s.country!=stu[f].info.country&&s.country=="CN")while(!getNation(s));
	else if(s.country=="CN")getfind("修改民族",s,getNation);
	getfind("修改婚姻状况",s,getMarital);
	getfind("修改政治面貌",s,getPoliticalStatus);
	if(s.country!=stu[f].info.country&&s.country=="CN")while(!getID(s));
	else if(s.country=="CN")getfind("修改身份证",s,getID);
	getfind("修改入学日期",s,getEnrollmentYear);
	getfind("修改学生类型",s,getStudentType);
	getfind("修改学院",s,getAcademy);
	if(s.academy==stu[f].info.academy)getfind("修改专业",s,getMajor);
	else while(!getMajor(s));
	getfind("修改年级",s,getGrade);
	getfind("修改学制",s,getLengthOfSchooling);
	getfind("修改培养层次",s,getTrainingLevel);
	getfind("修改班级",s,getStudentClass);
	getfind("修改辅导员",s,getTeacher);
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
		cout<<"输入的学生信息中有"<<er<<"个错误:\n";
		cout<<ER;
		cout<<"学生信息修改失败\n";
		stu[f]=t;
		push(t.info);
		pause();
		return 0;
	}else if(b==0){
		cout<<"警告:\n";
		cout<<ER;
		if(!YorN("是否录入(Y/N):")){
			stu[f]=t;
			push(t.info);
			pause();
			return 0;
		}
	}
	stu[f]=tmp;
	push(s);
	cout<<"学生信息修改成功\n";
	pause();
	return 1;
}
bool que4(){
	stuInfo f;
	if(YorN("是否按学号查询(Y/N):")){
		while(1){
			cout<<"请输入学号:";
			cin>>f.No;
			if(f.No.size()==9){
				findStu(f);
				printLine();
				pause();
				return 1;
			}else{
				cout<<"输入学号无效\n";
				pause();
			}
		}
	}
	getfind("查询姓名",f,getName);
	getfind("查询国家和地区",f,getCountry);
	getfind("查询辅导员",f,getTeacher);
	getfind("查询班级",f,getStudentClass);
	getfind("查询民族",f,getNation);
	getfind("查询政治面貌",f,getPoliticalStatus);
	getfind("查询培养层次",f,getTrainingLevel);
	getfind("查询学院",f,getAcademy);
	if(f.academy!=0)getfind("查询专业",f,getAcademy);
	getfind("查询性别",f,getGender);
	getfind("查询年级",f,getGrade);
	if(findStu(f))printLine();
	pause();
	return 1;
}
bool que5(){
	int cnt=0,c;
	char quit;
	cout<<"选择输出方式:\n1.按学号大小输出\n2.按入年级输出\n你的选择:";
	cin>>c;
	if(c==1){
		map<string,Stu>::iterator it=stu.begin(),ed=stu.end();
		while(it!=ed){
			printfStu(it->second.info);
			it++;
			cnt++;
			if(cnt!=0&&(cnt%2==0)){
				printLine();
				cout<<"\n按任意键继续或输入<p\\P>退出输出:";
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
				cout<<"\n按任意键继续或输入<p\\P>退出输出:";
				if(((quit=_getche())=='p'||quit=='P')){cout<<endl;return 0;}
				cout<<endl;
			}
		}
	}else{
		error(1);
		return 0;
	}
	if(cnt%2!=0)printLine();
	cout<<"\n所有内容已显示\n";
	pause();
	return 1;
}
bool que6(){
	int cmp;
	cout<<"请选择操作\n1.从文件读入学生信息221801337_林浩然_student_list.dat\n2.将学生信息存入221801337_林浩然_student_list.dat\n请输入你的选择:";
	cin>>cmp;
	if(cmp==1){
		if(getStudentList()){
			cout<<"学生信息读取成功\n";
			pause();
		}else{
			cout<<"学生信息读取失败\n";
			pause();
		}
	}else if(cmp==2){
		if(saveStudentList()){
			cout<<"学生信息保存成功\n";
			pause();
		}else{
			cout<<"学生信息保存失败\n";
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
	cout<<"当前学生信息数:"<<stu.size()<<endl;
	cout<<"当前学院数:"<<academy.size()<<endl;
	cout<<"当前专业数:"<<major.size()<<endl;
	cout<<"当前辅导员数:"<<teacher.size()<<endl;
	cout<<"当前党员数:"<<m_political_status.count(1)<<endl;
	cout<<"当前"<<now.year<<"级学生数:"<<m_grade.count(now.year%100)<<endl;
	cout<<"当前"<<now.year-1<<"级学生数:"<<m_grade.count(now.year%100-1)<<endl;
	cout<<"当前"<<now.year-2<<"级学生数:"<<m_grade.count(now.year%100-2)<<endl;
	cout<<"当前"<<now.year-3<<"级学生数:"<<m_grade.count(now.year%100-3)<<endl;
	cout<<"当前"<<now.year-4<<"级学生数:"<<m_grade.count(now.year%100-4)<<endl;
	pause();
	return 1;
}
