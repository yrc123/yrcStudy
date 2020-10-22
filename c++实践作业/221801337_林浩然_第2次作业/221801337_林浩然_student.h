#ifndef STU1
#define STU1
#include<iostream>
#include<map>
#include<ctime>
#include<string>
#include<vector>
#include<fstream>
#include<Windows.h>
#include<iomanip>
#include<cstdlib>
#include<ctype.h>
#include<conio.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
/*
	date:�洢����
	teacherInfo:�洢��ʦ��Ϣ
	majorInfo:�洢רҵ��Ϣ
	stuInfo:�洢ѧ����Ϣ
	STU:�洢ѧ��
	check:���ѧ����Ϣ��
*/
struct date;
struct teacherInfo;
struct majorInfo;
struct stuInfo;
struct Stu;
class check;

struct date{
	int year,mon,day;
	friend istream &operator>>(istream &is,date &a){
		is>>a.year>>a.mon>>a.day;
		return is;
	}
	friend ostream &operator<<(ostream &os,date &a){
		os<<a.year<<" "<<a.mon<<" "<<a.day;
		return os;
	}
};
struct teacherInfo{
	string name;
	int academy,major,grade,No;
	friend istream &operator>>(istream &is,teacherInfo &a){
		is>>a.academy>>a.major>>a.grade>>a.No>>a.name;
		return is;
	}
	friend ostream &operator<<(ostream &os,teacherInfo &a){
		os<<a.name;
		return os;
	}
};
struct majorInfo{
	string name;
	int academy,major;
	vector<pii > training_level;
	friend istream &operator>>(istream &is,majorInfo &a){
		char c;
		pii t;
		is>>a.academy>>a.major>>a.name;
		while((c=is.get())!='\n'&&c!=EOF){
			is>>t.first>>t.second;
			a.training_level.pb(t);
		}
		return is;
	}
	friend ostream &operator<<(ostream &os,majorInfo &a){
		os<<a.name;
		return os;
	}
};
struct stuInfo{
	string No="NA",name="NA",id="NA",country="NA";
	date birth,enrollment_year;
	int gender=0,nation=0,marital,political_status=0,student_type,enrollment_type;
	int academy=0,major=0,grade=0,length_of_schooling,training_level=0,student_class=0,teacher=0;
};
struct Stu{
	stuInfo info;
	friend istream &operator>>(istream &is,Stu &a){
		stuInfo &t=a.info;
		is>>t.No>>t.name>>t.gender>>t.country;
		is>>t.birth;
		if(t.country=="CN")is>>t.nation;
		is>>t.marital>>t.political_status;
		if(t.country=="CN")is>>t.id;
		is>>t.student_type>>t.enrollment_year>>t.enrollment_type>>t.academy>>t.major>>t.grade>>t.length_of_schooling>>t.training_level>>t.student_class>>t.teacher;
		return is;
	}
	friend ostream &operator<<(ostream &os,Stu &a){
		stuInfo &t=a.info;
		os<<t.No<<" "<<t.name<<" "<<t.gender<<" "<<t.country;
		os<<" "<<t.birth;
		if(t.country=="CN")os<<" "<<t.nation;
		os<<" "<<t.marital<<" "<<t.political_status;
		if(t.country=="CN")os<<" "<<t.id;
		os<<" "<<t.student_type<<" "<<t.enrollment_year<<" "<<t.enrollment_type<<" "<<t.academy<<" "<<t.major<<" "<<t.grade<<" "<<t.length_of_schooling<<" "<<t.training_level<<" "<<t.student_class<<" "<<t.teacher;
		return os;
	}
};


extern map<string,Stu>stu;
extern map<string,string>country,id;
extern map<int,string>nation,place,political_status,marital,training_level,student_type,enrollment_type,academy;
extern map<int,teacherInfo>teacher;
extern map<pii,majorInfo>major;


extern multimap<string,string>m_country,m_name;
extern multimap<int,string>m_teacher,m_student_class,m_nation,m_political_status,m_training_level,m_academy,m_gender,m_grade;
extern multimap<pii,string>m_major;


extern const char sex[3][3];
extern const char WEEK[7][10];
extern const int MON[13];
extern date now; 


//���������showListģ�庯��
string to_string(string);
string to_string(pii a);

/*	
	showList��
		input:		Ҫ������б��Ӧ��multimap,Ҫ������������ʼָ
					��,Ҫ���������Ľ���ָ��,��������ĸ���(Ĭ��Ϊ
					2),��ҳ���������(Ĭ��Ϊ24),��ŵ������,value
					�������
		function:	��ָ����ʽ���
		output:		�Ƿ������˳�
*/
template<class T>
bool showList(T &t,typename T::iterator it,typename T::iterator ed,int l=2,int r=24,int wkey=10,int wvul=10){
	int cnt=0;
	char quit;
	string c;
	while(it!=ed){
		c="["+to_string(it->fi)+"]";
		cout<<right<<setw(wkey)<<c;
		cout<<" "<<left<<setw(wvul)<<it->se;
		cnt++;
		it++;
		if(cnt!=0&&((cnt%l)==0))cout<<"\n";
		if(cnt!=0&&(cnt%(l*r)==0)){
			cout<<"\n�����������������<p\\P>��ͣ��ѡ�����ѡ��:";
			if(((quit=_getche())=='p'||quit=='P')){cout<<endl;return 0;}
			cout<<endl;
		}
	}
	cout<<"\n������������ʾ\n";
}


/*
	checkDate��
		input:		һ��������
		function:	�жϸ������Ƿ�Ϸ�
		output:		�������Ƿ�Ϸ�
*/
bool checkDate(const date &,const date &);

/*
	check��:
		public:
		��Ա����:
			clear:���������
			checkData:
				input:		ѧ����ϢstuInfo
				function:	�ж�ѧ����Ϣ�Ƿ�����
				output:		�Ƿ��д��󡢾���
			getErrorInfo:
				output:		�������Ϣstring��
			getErrorNum:
				output:		����ĸ���
		private:
		��Ա����:
			E:�洢������Ϣ
			n:�洢�������
		��Ա����:
			checkNo
			checkName
			checkBirth
			checkEnrollmentYear
			checkTeather
			checkMajor
			checkID
				input:		ѧ����ϢstuInfo
				function:	�ж�ѧ����Ϣ�Ƿ����󣬲��Ѵ�����Ϣ�浽E
				output:		�Ƿ��д��󡢾���
*/
class check{
public:
	check(){
		n=0;
		E.clear();
	}
	void clear(){
		n=0;
		E.clear();
	}
	/*
		output: 1Ϊ����0Ϊ���棬-1Ϊ����
	*/
	int checkData(stuInfo &a){
		int f=1;
		f=minn(checkNo(a),f);
		f=minn(checkName(a),f);
		f=minn(checkBirth(a),f);
		f=minn(checkEnrollmentYear(a),f);
		f=minn(checkTeather(a),f);
		f=minn(checkMajor(a),f);
		if(a.country=="CN")f=min(checkID(a),f);
		return f;
	}
	string getErrorInfo(){
		return E;
	}
	int getErrorNum(){
		return n;
	}
private:
	string E;
	int n;
	int checkNo(stuInfo &);
	int checkName(stuInfo &);
	int checkBirth(stuInfo &);
	int checkEnrollmentYear(stuInfo &);
	int checkTeather(stuInfo &);
	int checkMajor(stuInfo &);
	int checkID(stuInfo &);
	int minn(int a,int b){
		return a>b?b:a;
	}
};
inline int check::checkNo(stuInfo &s){
	int f=1;
	ll No=stoll(s.No);
	if(s.No.size()!=9){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"��ѧ����ѧ����Ч\n";
		return -1;
	}
	if(stu.count(s.No)==1){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"��ѧ����ѧ���Ѵ���\n";
		return -1;
	}
	if((No/100)%10!=s.student_class){
		E+="W:ѧ��Ϊ"+s.No+"��ѧ����ѧ������Ӧ�İ༶��������ȷ���Ƿ�����\n";
		f=0;
	}
	No/=1000000;
	if(major.count(make_pair(No/10,No%10))==0){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"��ѧ����ѧ�Ŷ�Ӧ��רҵΪ��Чֵ\n";
		return -1;
	}
	if(No/10!=s.academy){
		E+="W:ѧ��Ϊ"+s.No+"��ѧ����ѧ����ѧԺ��ƥ�䣬��ȷ���Ƿ�����\n";
		f=0;
	}
	if(No%10!=s.major){
		E+="W:ѧ��Ϊ"+s.No+"��ѧ����ѧ����רҵ��ƥ�䣬��ȷ���Ƿ�����\n";
		f=0;
	}
	return f;
}
inline int check::checkName(stuInfo &s){
	if(s.country=="CN"){
		for(int i=0;i<s.name.size();i++){
			if(s.name[i]<='Z'&&s.name[i]>='A'||s.name[i]<='z'&&s.name[i]>='a'||s.name[i]==' '||s.name[i]<='9'&&s.name[i]>='0'){
				n++;
				E+="E:ѧ��Ϊ"+s.No+"��ѧ��������Ӧ�ɺ������\n";
				return -1;
			}
		}
	}else{
		for(int i=0;i<s.name.size();i++){
			if(!(s.name[i]<='Z'&&s.name[i]>='A'||s.name[i]<='z'&&s.name[i]>='a'||s.name[i]==' '||s.name[i]<='9'&&s.name[i]>='0')){
				n++;
				E+="E:ѧ��Ϊ"+s.No+"��ѧ��������Ӧ��Ӣ�����\n";
				return -1;
			}
		}
	}
	return 1;
}
inline int check::checkBirth(stuInfo &s){
	if(!checkDate(s.birth,now)){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"��ѧ���ĳ�������ӦС�ڵ�ǰ���ڲ����뵱ǰ����֮����10~100��֮�䣬��Ϊ�Ϸ�����\n";
		return -1;
	}
	return 1;
}
inline int check::checkEnrollmentYear(stuInfo &s){
	date &t=s.enrollment_year,d;
	d=t;
	d.year+=15;
	int f=1;
	if(!checkDate(t,d)){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"��ѧ������ѧ����ӦΪ�Ϸ�����\n";
		return -1;
	}
	if(t.year>=now.year&&t.mon>=now.mon&&t.day>now.day){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"��ѧ������ѧ����ӦС�ڵ�ǰ����\n";
		return -1;
	}
	if(t.year<=s.birth.year+10){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"��ѧ������ѧ����Ӧ���ڳ�������+10��\n";
		return -1;
	}
	ll No=stoll(s.No);
	if(t.mon>10||t.mon<8){
		E+="W:ѧ��Ϊ"+s.No+"��ѧ������ѧ����Ӧ��8-10��֮�䣬��ȷ���Ƿ�����\n";
		f=0;
	}
	if(t.year!=(No/100000)%100+2000){
		E+="W:ѧ��Ϊ"+s.No+"��ѧ������ѧ�����ѧ�Ŷ�Ӧ��ѧ��ݲ�һ�£���ȷ���Ƿ�����\n";
		f=0;
	}
	return f;
}
inline int check::checkTeather(stuInfo &s){
	pair<multimap<int,string>::iterator,multimap<int,string>::iterator> edge;
	edge=m_student_class.equal_range(s.student_class);
	for(multimap<int,string>::iterator it=edge.fi;it!=edge.se;it++){
		if(stu[it->se].info.academy==s.academy&&stu[it->se].info.major==s.major&&stu[it->se].info.grade==s.grade&&stu[it->se].info.teacher!=s.teacher){
			n++;
			E+="E:ѧ��Ϊ"+s.No+"��ѧ���ĸ���Ա��ͬ�༶��ͬѧ��ͬ\n";
			return -1;
		}
	}
	return 1;
}
inline int check::checkMajor(stuInfo &s){
	vector<pii > &t=major[make_pair(s.academy,s.major)].training_level;
	for(int i=0;i<t.size();i++){
		if(t[i].fi==s.length_of_schooling&&t[i].se==s.training_level){
			return 1;
		}
	}
	n++;
	E+="E:ѧ��Ϊ"+s.No+"��ѧ����ѧ�ƻ�������β�һ�»��רҵ�����ж�Ӧ���������\n";
	return -1;
}
inline int check::checkID(stuInfo &s){
	if(id.count(s.id)!=0){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"��ѧ�������֤��ѧ��Ϊ"+stu[id[s.id]].info.No+"��ѧ�������֤����ͬ\n";
		return -1;
	}
	if(s.id.size()!=18){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"��ѧ�������֤��18λ\n";
		return -1;
	}
	int weight[]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
	char validate[]={ '1','0','X','9','8','7','6','5','4','3','2'};  
	int sum=0;
	int mode=0;
	for(int i=0;i<s.id.size()-1;i++){
		sum=sum+(s.id[i]-'0')*weight[i];
	}
	mode=sum%11;
	if (validate[mode]!=s.id[17])
	{
		n++;
		E+="E:ѧ��Ϊ"+s.No+"�����֤У��λ��Ч\n";
		return -1;
	}
	int c=(s.id[0]-'0')*100000+(s.id[1]-'0')*10000+(s.id[2]-'0')*1000+(s.id[3]-'0')*100+(s.id[4]-'0')*10+(s.id[5]-'0');
	if(place.count(c)==0){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"�����֤�������Ч\n";
		return -1;
	}
	if(((s.id[16]-'0')%2==1&&s.gender==2)||((s.id[16]-'0')%2==0&&s.gender==1)){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"�����֤�����Ա𲻷�\n";
		return -1;
	}
	int y,m,d;
	y=(s.id[6]-'0')*1000+(s.id[7]-'0')*100+(s.id[8]-'0')*10+(s.id[9]-'0');
	m=(s.id[10]-'0')*10+(s.id[11]-'0');
	d=(s.id[12]-'0')*10+(s.id[13]-'0');
	if(y!=s.birth.year||m!=s.birth.mon||d!=s.birth.day){
		n++;
		E+="E:ѧ��Ϊ"+s.No+"�����֤����������ڲ���\n";
		return -1;
	}
	return 1;
}
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
date tmToNode(tm *);
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
	getList��
		input:		������,Ҫ�����map
		function:	�����Ӧ�б���Ϣ
		output:		�Ƿ�����ɹ�
*/
bool getList(ifstream &,map<int,string>);
/*
	 getCountryList
	 getTeacherList
	 getMajorList
		input:		������
		function:	�����Ӧ�б���Ϣ
		output:		�Ƿ�����ɹ�
*/
bool getCountryList(ifstream &);
bool getTeacherList(ifstream &);
bool getMajorList(ifstream &);

/*
	readFile��
		input:		�ļ�������ȡ����
		function:	�����Ӧ�б���Ϣ
		output:		�Ƿ�����ɹ�
*/
bool readFile(const char *,bool read(ifstream &fp));
bool readFile(const char *,map<int,string> &,bool read(ifstream &fp,map<int,string> &));

/*
	getData��
		function:	��ȡ�б���Ϣ
		output:		�Ƿ�����ɹ�
*/
bool getData();
/*
	getData��
		input:		������Ϣ
		function:	���������Ϣ
		output:		�Ƿ�����ɹ�
*/
bool noOpen(const string &);
/*
	getData��
		input:		�������
		function:	���������Ϣ
		output:		�Ƿ�����ɹ�
*/
void error(int);
/*
	getData��
		input:		ѧ��ѧ��<Ĭ��Ϊ����ѧ����Ϣ>
		function:	��ȡѧ����Ϣ
		output:		�Ƕ�ȡ�ɹ�
*/
bool getStuInfo();
/*
	push��
		input:		ѧ����Ϣ
		function:	��ѧ����Ϣ�����������
		output:		�Ǽ���ɹ�
*/
bool push(stuInfo &);
/*
	getStudentList��
		function:	���ļ���ȡѧ����Ϣ
		output:		�Ƿ��ȡ�ɹ�
*/
bool getStudentList();
/*
	saveStudentList��
		function:	��ѧ����Ϣ�����ļ�
		output:		�Ƿ����ɹ�
*/
bool saveStudentList();
/*
	getNum��
		input:		Ĭ��ֵ
		function:	��ȡ����
		output:		Ĭ��ֵ���ȡ������
*/
int getNum(int);
/*
	getName
	getGender
	getCountry
	getNation
	getPoliticalStatus
	getAcademy
	getMajor
	getGrade
	getTrainingLevel
	getStudentClass
	getTeacher
		input:		ѧ����ϢstuInfo
		function:	��ȡ��Ӧ��Ϣ
		output:		�Ƿ��ȡ�ɹ�
*/
bool getName(stuInfo &);
bool getGender(stuInfo &);
bool getCountry(stuInfo &);
bool getBirth(stuInfo &);
bool getNation(stuInfo &);
bool getMarital(stuInfo &);
bool getPoliticalStatus(stuInfo &);
bool getID(stuInfo &);
bool getStudentType(stuInfo &);
bool getEnrollmentYear(stuInfo &);
bool getEnrollmentType(stuInfo &);
bool getAcademy(stuInfo &);
bool getMajor(stuInfo &);
bool getGrade(stuInfo &);
bool getLengthOfSchooling(stuInfo &);
bool getTrainingLevel(stuInfo &);
bool getStudentClass(stuInfo &);
bool getTeacher(stuInfo &);
/*
	findStu��
		input:		ѧ����ϢstuInfo
		function:	ʵ��ѧ����Ϣ��ѯ
		output:		�Ƿ��ѯ�ɹ�
*/
bool findStu(stuInfo &s);
/*
	getfind��
		input:		��ѯ��Чֵ,ѧ����ϢstuInfo,��ѯ����
		function:	��ѯѧ����Ϣ
		output:		�Ƿ��ѯ�ɹ�
*/
bool getfind(string,stuInfo &,bool read(stuInfo &));
/*
	YorN��
		input:		��ʾ��Ϣ
		function:	��ȡ"Y"��"N"
		output:		����Ķ�Ӧ��true/false
*/
bool YorN(string a="������(Y/N):");
/*
	printfStu��
		input:		ѧ����Ϣ
		function:	���ѧ����Ϣ
		output:		�Ƿ�����ɹ�
*/
bool printfStu(stuInfo &s);
/*
	del��
		input:		Ҫɾ������Ϣ,��Ϣ��Ӧ��map,��ɾ����ֵ
		function:	ɾ��map�еĶ�Ӧֵ
		output:		�Ƿ�ɾ���ɹ�
*/
template<class T1,class T2>
bool del(T1 &a,T2 &m,string s){
	typename T2::iterator it=m.equal_range(a).fi,ed=m.equal_range(a).se;
	for(it;it!=ed;it++){
		if(it->se==s){
			m.erase(it);
			return 1;
		}
	}
	return 0;
}
/*
	delStudent��
		input:		ѧ����Ϣ
		function:	ɾ��ѧ����Ϣ
		output:		�Ƿ�ɾ���ɹ�
*/
bool delStudent(stuInfo &);
/*
	que1
	que2
	que3
	que4
	que5
	que6
		function:	ִ�в˵���Ӧ����	
		output:		�Ƿ�ִ�гɹ�
*/
bool que1();
bool que2();
bool que3();
bool que4();
bool que5();
bool que6();
bool que7();
/*
	pause��
		function:	��ͣ����
*/
inline void pause(){
	cout<<"�밴���������������";
	_getche();
	cout<<endl;
}
/*
	pause��
		function:	��ջ�����
*/
inline void clear(){
	if(!cin.good())
			cin.clear();
	while(getchar()!='\n');
}
#endif