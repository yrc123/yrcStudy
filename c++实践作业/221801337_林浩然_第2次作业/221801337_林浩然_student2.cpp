#define _CRT_SECURE_NO_DEPRECATE
#include "221801337_�ֺ�Ȼ_student.h"



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
	printf("Copyright <c> 2019-2019 �ֺ�Ȼ<221801337>. All Rights Reserved.\n\n");
	printf("��ǰ���ڡ�ʱ�� : %d.%d.%d", t->tm_year+1900,t->tm_mon+1,t->tm_mday);
	printf(" <%s> %02d:%02d:%02d\n",WEEK[t->tm_wday],t->tm_hour,t->tm_min,t->tm_sec);
	printLine();
	printf("*	1:  ���ѧ����Ϣ                                       *\n");
	printf("*	2:  ɾ��ѧ����Ϣ                                       *\n");
	printf("*	3:  �޸�ѧ����Ϣ                                       *\n");
	printf("*	4:  ��ѯѧ����Ϣ                                       *\n");
	printf("*	5:  ��ʾѧ����Ϣ                                       *\n");
	printf("*	6:  ��ѧ����Ϣ�����ļ�����ļ���ȡѧ����Ϣ             *\n");
	printf("*	7:  ͳ��ѧ����Ϣ                                       *\n");
	printf("*	8:  �˳�ϵͳ                                           *\n");
	printLine();
	printf("��ѡ��<1-8>:");
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
	if(!readFile("221801337_�ֺ�Ȼ_nation.dat",nation,getList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_marital.dat",marital,getList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_place.dat",place,getList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_political_status.dat",political_status,getList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_country.dat",getCountryList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_training_level.dat",training_level,getList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_student_type.dat",student_type,getList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_enrollment_type.dat",enrollment_type,getList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_academy.dat",academy,getList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_teacher.dat",getTeacherList))return 0;
	if(!readFile("221801337_�ֺ�Ȼ_major.dat",getMajorList))return 0;
	return 1;
}
bool noOpen(const string &a){
	cout<<"E:\""<<a<<"\"��ʧ�ܻ��ļ������ڣ�����֤�����ļ��������ԣ�"<<endl;
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
	cout<<"������9λѧ��ѧ��:";
	cin>>s.No;
	n=stoll(s.No);
	getchar();
	if(s.No.size()!=9){
		error(2);
		return 0;
	}
	if(stu.count(s.No)!=0){
		cout<<"E:ѧ��Ϊ"<<n<<"��ѧ����Ϣ�Ѵ��ڣ��޷��ظ����"<<endl;
		pause();
		return 0;
	}
	return 1;
}
bool getName(stuInfo &s){
	cout<<"������ѧ������:";
	getline(cin,s.name);
	if(s.name.size()==0){
		cout<<"��������Ϊ��\n";
		pause();
		return 0;
	}
	return 1;
}
bool getGender(stuInfo &s){
	cout<<"������ѧ���Ա�:\n[1]�� [2]Ů\n��ѡ���Ա�(Ĭ��Ϊ��):";
	s.gender=getNum(1);
	if(s.gender!=1&&s.gender!=2){
		error(2);
		return 0;
	}
	return 1;
}
bool getCountry(stuInfo &s){
	cout<<"����ѧ�������Ĺ��һ����:\n";
	showList(country,country.begin(),country.end(),2,24,5,34);
	cout<<"��ѡѧ�������Ĺ��һ����(Ĭ���й�):";
	getline(cin,s.country);
	if(s.country.size()==0)s.country="CN";
	if(country.count(s.country)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getBirth(stuInfo &s){
	cout<<"�������������(yyyy mm dd):";
	string a;
	date &t=s.birth;
	int pow=1,ans[3]={0},cnt=2;
	getline(cin,a);
	for(int i=a.size()-1;i>=0;i--){
		if(a[i]>'9'||a[i]<'0'){
			if(a[i]!=' '){
				cout<<"���ڸ�ʽ����\n";
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
		cout<<"ѧ���ĳ�������ӦС�ڵ�ǰ���ڲ����뵱ǰ����֮����10~100��֮�䣬��Ϊ�Ϸ�����\n";
		pause();
		return 0;
	}
	return 1;
}
bool getNation(stuInfo &s){
	cout<<"����������:\n";
	showList(nation,nation.begin(),nation.end(),3,24);
	cout<<"��ѡ������(Ĭ�Ϻ���):";
	s.nation=getNum(1);
	if(nation.count(s.nation)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getMarital(stuInfo &s){
	cout<<"���������״��:\n";
	showList(marital,marital.begin(),marital.end(),3,24);
	cout<<"��ѡ�����״��(Ĭ��δ��):";
	s.marital=getNum(1);
	if(marital.count(s.marital)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getPoliticalStatus(stuInfo &s){
	cout<<"������������ò:\n";
	showList(political_status,political_status.begin(),political_status.end(),2,24,10,24);
	cout<<"��ѡ��������ò(Ĭ�Ϲ�����Ա):";
	s.political_status=getNum(3);
	if(political_status.count(s.political_status)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getID(stuInfo &s){
	cout<<"���������֤��:";
	cin>>s.id;
	clear();
	if(s.id.size()!=18){
		cout<<"���֤��ӦΪ18λ"<<endl;
		pause();
		return 0;
	}
	return 1;
}
bool getStudentType(stuInfo &s){
	cout<<"������ѧ�����:\n";
	showList(student_type,student_type.begin(),student_type.end());
	cout<<"��ѡ��ѧ�����:";
	s.student_type=getNum(0);
	if(student_type.count(s.student_type)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getEnrollmentYear(stuInfo &s){
	cout<<"��������ѧ����(yyyy mm dd Ĭ��Ϊ��ǰѧ�Ŷ�Ӧ��ݵ�9��1��):";
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
				cout<<"���ڸ�ʽ����\n";
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
		cout<<"ѧ������ѧ����ӦΪ�Ϸ�����\n";
		pause();
		return 0;
	}
	if(t.year>=now.year&&t.mon>=now.mon&&t.day>now.day){
		cout<<"ѧ������ѧ����ӦС�ڵ�ǰ����\n";
		pause();
		return 0;
	}
	if(t.year<=s.birth.year+10){
		cout<<"ѧ������ѧ����Ӧ���ڳ�������+10��\n";
		pause();
		return 0;
	}
	return 1;
}
bool getEnrollmentType(stuInfo &s){
	cout<<"��������ѧ��ʽ:\n";
	showList(enrollment_type,enrollment_type.begin(),enrollment_type.end(),3);
	cout<<"��ѡ����ѧ��ʽ(Ĭ����ͨ��ѧ):";
	s.enrollment_type=getNum(1);
	if(enrollment_type.count(s.enrollment_type)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getAcademy(stuInfo &s){
	cout<<"������ѧԺ����:\n";
	showList(academy,academy.begin(),academy.end(),3,24,5,20);
	cout<<"��ѡ��ѧԺ����:";
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
	cout<<"������רҵ����:\n";
	showList(major,it,ed,3,24,10,16);
	cout<<"��ѡ��רҵ����:";
	s.major=getNum();
	if(major.count(make_pair(s.academy,s.major))==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getGrade(stuInfo &s){
	cout<<"�������꼶:";
	cin>>s.grade;
	if(s.grade<=0){
		error(2);
		return 0;
	}
	return 1;
}
bool getLengthOfSchooling(stuInfo &s){
	cout<<"������ѧ��:";
	cin>>s.length_of_schooling;
	clear();
	if(s.length_of_schooling<=0){
		error(2);
		return 0;
	}
	return 1;
}
bool getTrainingLevel(stuInfo &s){
	cout<<"�������������:\n";
	showList(training_level,training_level.begin(),training_level.end(),2,24,10,20);
	cout<<"��ѡ���������(Ĭ�ϱ���):";
	s.training_level=getNum(10);
	if(training_level.count(s.training_level)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool getStudentClass(stuInfo &s){
	cout<<"������༶<1-10>:";
	cin>>s.student_class;
	clear();
	if(s.student_class<=0||s.student_class>10){
		error(2);
		return 0;
	}
	return 1;
}
bool getTeacher(stuInfo &s){
	cout<<"�����븨��Ա:\n";
	showList(teacher,teacher.begin(),teacher.end(),3);
	cout<<"��ѡ�񸨵�Ա:";
	s.teacher=getNum(1);
	if(teacher.count(s.teacher)==0){
		error(2);
		return 0;
	}
	return 1;
}
bool printfStu(stuInfo &s){
	printLine();
	cout<<"ѧ��ѧ��:\t"<<s.No<<endl;
	cout<<"ѧ������:\t"<<s.name<<endl;
	cout<<"ѧ���Ա�:\t"<<sex[s.gender]<<endl;
	cout<<"ѧ������:\t"<<country[s.country]<<endl;
	if(s.country=="CN")cout<<"���֤��:\t"<<s.id<<endl;
	cout<<"ѧ��ѧԺ:\t"<<academy[s.academy]<<endl;
	cout<<"ѧ��רҵ:\t"<<major[make_pair(s.academy,s.major)].name<<endl;
	cout<<"��ѧ����:\t"<<enrollment_type[s.enrollment_type]<<endl;
	cout<<"������ò:\t"<<political_status[s.political_status]<<endl;
	cout<<"�����㼶:\t"<<training_level[s.training_level]<<endl;
	cout<<"ѧ���༶:\t"<<s.student_class<<endl;
	cout<<"ѧ���꼶:\t"<<s.grade<<endl;
	cout<<"ѧ����ѧ����:\t"<<s.enrollment_year.year<<"."<<s.enrollment_year.mon<<"."<<s.enrollment_year.day<<endl;
	cout<<"ѧ������Ա:\t"<<teacher[s.teacher]<<endl;
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
		cout<<"�����ѧ����Ϣ����"<<er<<"������:\n";
		cout<<ER;
		pause();
		return 0;
	}else if(f==0){
		cout<<"����:\n";
		cout<<ER;
		if(!YorN("�Ƿ�¼��(Y/N):")){
			pause();
			return 0;
		}
	}
	push(s);
	stu[s.No]=tmp;
	cout<<"ѧ����Ϣ¼��ɹ�\n";
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
	fp.open("221801337_�ֺ�Ȼ_student_list.dat");
	if(!fp.is_open()){
		noOpen("221801337_�ֺ�Ȼ_student_list.dat");
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
		cout<<"�����ѧ����Ϣ����"<<er<<"������:\n";
		cout<<ER;
		pause();
	}
	if(wstu.size()){
		cout<<"����:\n";
		cout<<WA;
		if(YorN("�Ƿ�¼��(Y/N):")){
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
	fp.open("221801337_�ֺ�Ȼ_student_list.dat");
	if(!fp.is_open()){
		noOpen("221801337_�ֺ�Ȼ_student_list.dat");
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
			cout<<"û��ƥ���ѧ��\n";
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
		cout<<"û��ƥ���ѧ��\n";
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
	if(YorN("�Ƿ�"+c+"(Y/N):")){
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
	case 1:printf("ѡ���������ѡ�񡣡�����\n"); pause(); break;
	case 2:printf("����Ƿ�����!\n"); pause(); break;
	default:printf("����δ֪����!\n"); pause(); break;
	}
}