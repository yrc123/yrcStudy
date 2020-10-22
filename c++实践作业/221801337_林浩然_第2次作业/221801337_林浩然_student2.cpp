#define _CRT_SECURE_NO_DEPRECATE
#include "221801337_林浩然_student.h"



string to_string(string a){
	return a;
}
string to_string(pii a){
	return to_string(a.se);
}


void printLine(){
	printf("****************************************************************\n");
}
void menu(){
	tm *t = getTime();
	now=tmToNode(t);
	printf("Copyright <c> 2019-2019 林浩然<221801337>. All Rights Reserved.\n\n");
	printf("当前日期、时间 : %d.%d.%d", t->tm_year+1900,t->tm_mon+1,t->tm_mday);
	printf(" <%s> %02d:%02d:%02d\n",WEEK[t->tm_wday],t->tm_hour,t->tm_min,t->tm_sec);
	printLine();
	printf("*	1:  添加学生信息                                       *\n");
	printf("*	2:  删除学生信息                                       *\n");
	printf("*	3:  修改学生信息                                       *\n");
	printf("*	4:  查询学生信息                                       *\n");
	printf("*	5:  显示学生信息                                       *\n");
	printf("*	6:  将学生信息存入文件或从文件读取学生信息             *\n");
	printf("*	7:  统计学生信息                                       *\n");
	printf("*	8:  退出系统                                           *\n");
	printLine();
	printf("请选择<1-8>:");
}
tm *getTime(){
	time_t tt=time(0);
	tm *t=localtime(&tt);
	return t;
}
date tmToNode(tm* t){
	date tm;
	tm.year=t->tm_year+1900;
	tm.mon=t->tm_mon+1;
	tm.day=t->tm_mday;
	return tm;
}
bool getList(ifstream &fp,map<int,string> &a){
	int n;
	string s;
	while(fp>>n>>s){
		a[n]=s;
	}
	return 1;
}
bool getCountryList(ifstream &fp){
	string s1,s2;
	while(fp>>s1>>s2){
		country[s1]=s2;
	}
	return 1;
}
bool getTeacherList(ifstream &fp){
	teacherInfo inf;
	while(fp>>inf){
		teacher[inf.No]=inf;
	}
	return 1;
}
bool getMajorList(ifstream &fp){
	majorInfo inf;
	while(fp>>inf){
		major[make_pair(inf.academy,inf.major)]=inf;
	}
	return 1;
}
bool readFile(const char *f,map<int,string> &a,bool read(ifstream &fp,map<int,string> &)){
	ifstream fp;
	string file(f);
	fp.open(file);
	if(!fp.is_open()){
		noOpen(file);
		return 0;
	}
	read(fp,a);
	fp.close();
	return 1;
}
bool readFile(const char *f,bool read(ifstream &fp)){
	ifstream fp;
	string file(f);
	fp.open(file);
	if(!fp.is_open()){
		noOpen(file);
		return 0;
	}
	read(fp);
	fp.close();
	return 1;
}
bool getData(){
	if(!readFile("221801337_林浩然_nation.dat",nation,getList))return 0;
	if(!readFile("221801337_林浩然_marital.dat",marital,getList))return 0;
	if(!readFile("221801337_林浩然_place.dat",place,getList))return 0;
	if(!readFile("221801337_林浩然_political_status.dat",political_status,getList))return 0;
	if(!readFile("221801337_林浩然_country.dat",getCountryList))return 0;
	if(!readFile("221801337_林浩然_training_level.dat",training_level,getList))return 0;
	if(!readFile("221801337_林浩然_student_type.dat",student_type,getList))return 0;
	if(!readFile("221801337_林浩然_enrollment_type.dat",enrollment_type,getList))return 0;
	if(!readFile("221801337_林浩然_academy.dat",academy,getList))return 0;
	if(!readFile("221801337_林浩然_teacher.dat",getTeacherList))return 0;
	if(!readFile("221801337_林浩然_major.dat",getMajorList))return 0;
	return 1;
}
bool noOpen(const string &a){
	cout<<"E:\""<<a<<"\"打开失败或文件不存在！请验证配置文件的完整性！"<<endl;
	return 1;
}
bool checkDate(const date &a,const date &now){
	if(a.year<=now.year-100||a.year>=now.year-10)return 0;
	if(a.year<=0||a.mon<=0||a.mon>12||a.day<=0)return 0;
	if(a.day<=MON[a.mon]){
		if(a.mon!=2)return 1;
		if(!((a.year%4==0&&a.year%100!=0)||a.year%400==0)&&a.day==29)return 0;
		else return 1;
	}
	return 0;
}
int getNum(int def=0){
	string a;
	int pow=1,ans=0;
	getline(cin,a);
	if(a.size()==0)return def;
	for(int i=a.size()-1;i>=0;i--){
		if(a[i]<'0'||a[i]>'9'){
			return -1;
		}
		ans+=(a[i]-'0')*pow;
		pow*=10;
	}
	return ans;
}
bool getNo(stuInfo &s,ll &n){
	cout<<"请输入9位学生学号:";
	cin>>s.No;
	n=stoll(s.No);
	getchar();
	if(s.No.size()!=9){
		error(2);
		return 0;
	}
	if(stu.count(s.No)!=0){
		cout<<"E:学号为"<<n<<"的学生信息已存在，无法重复添加"<<endl;
		pause();
		return 0;
	}
	return 1;
}
bool getName(stuInfo &s){
	cout<<"请输入学生姓名:";
	getline(cin,s.name);
	if(s.name.size()==0){
		cout<<"姓名不得为空\n";
		pause();
		return 0;
	}
	return 1;
}
bool getGender(stuInfo &s){
	cout<<"请输入学生性别:\n[1]男 [2]女\n请选择性别(默认为男):";
	s.gender=getNum(1);
	if(s.gender!=1&&s.gender!=2){
		error(2);
		return 0;
	}
	return 1;
}
bool getCountry(stuInfo &s){
	cout<<"请输学生所属的国家或地区:\n";
	showList(country,country.begin(),country.end(),2,24,5,34);
	cout<<"请选学生所属的国家或地区(默认中国):";
	getline(cin,s.country);
	if(s.country.size()==0)s.country="CN";
	if(country.count(s.country)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getBirth(stuInfo &s){
	cout<<"请输入出生日期(yyyy mm dd):";
	string a;
	date &t=s.birth;
	int pow=1,ans[3]={0},cnt=2;
	getline(cin,a);
	for(int i=a.size()-1;i>=0;i--){
		if(a[i]>'9'||a[i]<'0'){
			if(a[i]!=' '){
				cout<<"日期格式错误\n";
				pause();
				return 0;
			}
			pow=1;
			cnt--;
			continue;
		}
		ans[cnt]+=pow*(a[i]-'0');
		pow*=10;
	}
	t.year=ans[0];
	t.mon=ans[1];
	t.day=ans[2];
	if(!checkDate(s.birth,now)){
		cout<<"学生的出生日期应小于当前日期并且与当前日期之差在10~100年之间，且为合法日期\n";
		pause();
		return 0;
	}
	return 1;
}
bool getNation(stuInfo &s){
	cout<<"请输入民族:\n";
	showList(nation,nation.begin(),nation.end(),3,24);
	cout<<"请选择民族(默认汉族):";
	s.nation=getNum(1);
	if(nation.count(s.nation)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getMarital(stuInfo &s){
	cout<<"请输入婚姻状况:\n";
	showList(marital,marital.begin(),marital.end(),3,24);
	cout<<"请选择婚姻状况(默认未婚):";
	s.marital=getNum(1);
	if(marital.count(s.marital)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getPoliticalStatus(stuInfo &s){
	cout<<"请输入政治面貌:\n";
	showList(political_status,political_status.begin(),political_status.end(),2,24,10,24);
	cout<<"请选择政治面貌(默认共青团员):";
	s.political_status=getNum(3);
	if(political_status.count(s.political_status)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getID(stuInfo &s){
	cout<<"请输入身份证号:";
	cin>>s.id;
	clear();
	if(s.id.size()!=18){
		cout<<"身份证号应为18位"<<endl;
		pause();
		return 0;
	}
	return 1;
}
bool getStudentType(stuInfo &s){
	cout<<"请输入学生类别:\n";
	showList(student_type,student_type.begin(),student_type.end());
	cout<<"请选择学生类别:";
	s.student_type=getNum(0);
	if(student_type.count(s.student_type)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getEnrollmentYear(stuInfo &s){
	cout<<"请输入入学日期(yyyy mm dd 默认为当前学号对应年份的9月1日):";
	string a;
	date &t=s.enrollment_year,d;
	ll n=stoll(s.No);
	int pow=1,ans[3]={0},cnt=2;
	getline(cin,a);
	if(a.size()==0){
		t.year=(n/100000)%100+2000;
		t.mon=9;
		t.day=1;
		return 1;
	}
	for(int i=a.size()-1;i>=0;i--){
		if(a[i]>'9'||a[i]<'0'){
			if(a[i]!=' '){
				cout<<"日期格式错误\n";
				pause();
				return 0;
			}
			pow=1;
			cnt--;
			continue;
		}
		ans[cnt]+=pow*(a[i]-'0');
		pow*=10;
	}
	t.year=ans[0];
	t.mon=ans[1];
	t.day=ans[2];
	d=t;
	d.year+=15;
	int f=1;
	if(!checkDate(t,d)){
		cout<<"学生的入学日期应为合法日期\n";
		pause();
		return 0;
	}
	if(t.year>=now.year&&t.mon>=now.mon&&t.day>now.day){
		cout<<"学生的入学日期应小于当前日期\n";
		pause();
		return 0;
	}
	if(t.year<=s.birth.year+10){
		cout<<"学生的入学日期应大于出生日期+10年\n";
		pause();
		return 0;
	}
	return 1;
}
bool getEnrollmentType(stuInfo &s){
	cout<<"请输入入学方式:\n";
	showList(enrollment_type,enrollment_type.begin(),enrollment_type.end(),3);
	cout<<"请选择入学方式(默认普通入学):";
	s.enrollment_type=getNum(1);
	if(enrollment_type.count(s.enrollment_type)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getAcademy(stuInfo &s){
	cout<<"请输入学院名称:\n";
	showList(academy,academy.begin(),academy.end(),3,24,5,20);
	cout<<"请选择学院名称:";
	s.academy=getNum();
	if(academy.count(s.academy)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getMajor(stuInfo &s){
	pii cmp=make_pair(s.academy,1);
	map<pii,majorInfo>::iterator it=major.find(cmp),ed=it,tmp;
	while(ed!=major.end()){
		if(cmp.fi==ed->fi.fi)ed++;else break;
	}
	cout<<"请输入专业名称:\n";
	showList(major,it,ed,3,24,10,16);
	cout<<"请选择专业名称:";
	s.major=getNum();
	if(major.count(make_pair(s.academy,s.major))==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getGrade(stuInfo &s){
	cout<<"请输入年级:";
	cin>>s.grade;
	if(s.grade<=0){
		error(2);
		return 0;
	}
	return 1;
}
bool getLengthOfSchooling(stuInfo &s){
	cout<<"请输入学制:";
	cin>>s.length_of_schooling;
	clear();
	if(s.length_of_schooling<=0){
		error(2);
		return 0;
	}
	return 1;
}
bool getTrainingLevel(stuInfo &s){
	cout<<"请输入培养层次:\n";
	showList(training_level,training_level.begin(),training_level.end(),2,24,10,20);
	cout<<"请选择培养层次(默认本科):";
	s.training_level=getNum(10);
	if(training_level.count(s.training_level)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getStudentClass(stuInfo &s){
	cout<<"请输入班级<1-10>:";
	cin>>s.student_class;
	clear();
	if(s.student_class<=0||s.student_class>10){
		error(2);
		return 0;
	}
	return 1;
}
bool getTeacher(stuInfo &s){
	cout<<"请输入辅导员:\n";
	showList(teacher,teacher.begin(),teacher.end(),3);
	cout<<"请选择辅导员:";
	s.teacher=getNum(1);
	if(teacher.count(s.teacher)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool printfStu(stuInfo &s){
	printLine();
	cout<<"学生学号:\t"<<s.No<<endl;
	cout<<"学生姓名:\t"<<s.name<<endl;
	cout<<"学生性别:\t"<<sex[s.gender]<<endl;
	cout<<"学生国别:\t"<<country[s.country]<<endl;
	if(s.country=="CN")cout<<"身份证号:\t"<<s.id<<endl;
	cout<<"学生学院:\t"<<academy[s.academy]<<endl;
	cout<<"学生专业:\t"<<major[make_pair(s.academy,s.major)].name<<endl;
	cout<<"入学类型:\t"<<enrollment_type[s.enrollment_type]<<endl;
	cout<<"政治面貌:\t"<<political_status[s.political_status]<<endl;
	cout<<"培养层级:\t"<<training_level[s.training_level]<<endl;
	cout<<"学生班级:\t"<<s.student_class<<endl;
	cout<<"学生年级:\t"<<s.grade<<endl;
	cout<<"学生入学日期:\t"<<s.enrollment_year.year<<"."<<s.enrollment_year.mon<<"."<<s.enrollment_year.day<<endl;
	cout<<"学生辅导员:\t"<<teacher[s.teacher]<<endl;
	return 1;
}
bool getStuInfo(){
	ll n;
	Stu tmp;
	char c;
	stuInfo &s=tmp.info;
	while(!getNo(s,n));
	while(!getName(s));
	while(!getGender(s));
	while(!getCountry(s));
	while(!getBirth(s));
	if(s.country=="CN")while(!getNation(s));
	while(!getMarital(s));
	while(!getPoliticalStatus(s));
	if(s.country=="CN")while(!getID(s));
	while(!getStudentType(s));
	while(!getEnrollmentYear(s));
	while(!getEnrollmentType(s));
	while(!getAcademy(s));
	while(!getMajor(s));
	while(!getGrade(s));
	while(!getLengthOfSchooling(s));
	while(!getTrainingLevel(s));
	while(!getStudentClass(s));
	while(!getTeacher(s));
	printfStu(s);
	printLine();
	check e;
	int er,f;
	f=e.checkData(s);
	er=e.getErrorNum();
	string ER=e.getErrorInfo();
	if(f==-1){
		cout<<"输入的学生信息中有"<<er<<"个错误:\n";
		cout<<ER;
		pause();
		return 0;
	}else if(f==0){
		cout<<"警告:\n";
		cout<<ER;
		if(!YorN("是否录入(Y/N):")){
			pause();
			return 0;
		}
	}
	push(s);
	stu[s.No]=tmp;
	cout<<"学生信息录入成功\n";
	pause();
	return 1;
}
bool push(stuInfo &s){
	m_academy.insert(make_pair(s.academy,s.No));
	m_country.insert(make_pair(s.country,s.No));
	m_gender.insert(make_pair(s.gender,s.No));
	m_grade.insert(make_pair(s.grade,s.No));
	m_major.insert(make_pair(make_pair(s.academy,s.major),s.No));
	m_name.insert(make_pair(s.name,s.No));
	m_nation.insert(make_pair(s.nation,s.No));
	m_teacher.insert(make_pair(s.teacher,s.No));
	m_training_level.insert(make_pair(s.training_level,s.No));
	m_student_class.insert(make_pair(s.student_class,s.No));
	if(s.country=="CN")id.insert(make_pair(s.id,s.No));
	return 1;
}
bool getStudentList(){
	char cmp;
	ifstream fp;
	Stu tmp;
	vector<Stu>wstu;
	string ER,WA;
	int er=0,f;
	check c;
	fp.open("221801337_林浩然_student_list.dat");
	if(!fp.is_open()){
		noOpen("221801337_林浩然_student_list.dat");
		return 0;
	}
	while(fp>>tmp){
		f=1;
		f=c.checkData(tmp.info);
		if(f==-1){
			er+=c.getErrorNum();
			ER+=c.getErrorInfo();
		}else if(f==0){
			wstu.pb(tmp);
			WA+=c.getErrorInfo();
		}else if(f==1){
			stu[tmp.info.No]=tmp;
			push(tmp.info);
		}
		c.clear();
	}
	if(er!=0){
		cout<<"输入的学生信息中有"<<er<<"个错误:\n";
		cout<<ER;
		pause();
	}
	if(wstu.size()){
		cout<<"警告:\n";
		cout<<WA;
		if(YorN("是否录入(Y/N):")){
			for(int i=0;i<wstu.size();i++){
				stu[wstu[i].info.No]=wstu[i];
				push(wstu[i].info);
			}
		}
	}
	fp.close();
	return 1;
}
bool saveStudentList(){
	ofstream fp;
	fp.open("221801337_林浩然_student_list.dat");
	if(!fp.is_open()){
		noOpen("221801337_林浩然_student_list.dat");
		return 0;
	}
	map<string,Stu>::iterator it;
	for(it=stu.begin();it!=stu.end();it++){
		fp<<it->se<<endl;
	}
	fp.close();
	return 1;
}
template<class T1,class T2,class T3>
bool jionFind(T1 &a,T2 def,T3 &m,map<string,int> &q,int &cnt){
	if(a!=def){
		cnt++;
		typename T3::iterator it=m.equal_range(a).fi,ed=m.equal_range(a).se;
		for(it;it!=ed;it++){
			if(q.count(it->se)!=1){
				q[it->se]=1;
			}else{
				q[it->se]++;
			}
		}
		return 1;
	}
	return 0;
}
bool findStu(stuInfo &s){
	map<string,int> q;
	int cnt=0;
	if(s.No!="NA"){
		if(stu.count(s.No)!=0)
			printfStu(stu[s.No].info);
		else
			cout<<"没有匹配的学生\n";
		return 0;
	}
    jionFind(s.name,"NA",m_name,q,cnt);
	jionFind(s.country,"NA",m_country,q,cnt);
	jionFind(s.teacher,0,m_teacher,q,cnt);
	jionFind(s.student_class,0,m_student_class,q,cnt);
	jionFind(s.nation,0,m_nation,q,cnt);
	jionFind(s.political_status,0,m_political_status,q,cnt);
	jionFind(s.training_level,0,m_training_level,q,cnt);
	jionFind(s.academy,0,m_academy,q,cnt);
	jionFind(s.gender,0,m_gender,q,cnt);
	jionFind(s.grade,0,m_grade,q,cnt);
	if(s.major!=0){
		pair<int,int> a(s.academy,s.major);
		jionFind(a,make_pair(0,0),m_major,q,cnt);
	}
	map<string,int>::iterator it=q.begin(),ed=q.end();
	int n=0;
	for(it;it!=ed;it++){
		if(it->se==cnt){
			printfStu(stu[it->fi].info);
			n++;
		}
	}
	if(n==0){
		cout<<"没有匹配的学生\n";
		return 0;
	}
	return 1;
}
bool YorN(string a){
	char cmp;
	while(1){
		cout<<a;
		if((cmp=_getche())=='y'||cmp=='Y'){cout<<endl;return 1;}
		else if(cmp=='n'||cmp=='N'){cout<<endl;return 0;}
		cout<<endl;
	}
}
bool getfind(string c,stuInfo &a,bool read(stuInfo &)){
	if(YorN("是否"+c+"(Y/N):")){
		while(!read(a));
		return 1;
	}
	return 0;
}
bool delStudent(stuInfo &s){
	string f=s.No;
	del(s.country,m_country,f);
	del(s.name,m_name,f);
	del(s.teacher,m_teacher,f);
	del(s.student_class,m_student_class,f);
	del(s.nation,m_nation,f);
	del(s.political_status,m_political_status,f);
	del(s.training_level,m_training_level,f);
	del(s.academy,m_academy,f);
	del(s.gender,m_gender,f);
	del(s.grade,m_grade,f);
	pair<int,int> a(s.academy,s.major);
	del(a,m_major,f);
	if(s.country=="CN")id.erase(id.find(s.id));
	stu.erase(stu.find(f));
	return 1;
}
void error(int code){
	cout<<"E:";
	switch (code){
	case 1:printf("选择错误，重新选择。。。。\n"); pause(); break;
	case 2:printf("输入非法数据!\n"); pause(); break;
	default:printf("出现未知错误!\n"); pause(); break;
	}
}