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
	date:存储日期
	teacherInfo:存储教师信息
	majorInfo:存储专业信息
	stuInfo:存储学生信息
	STU:存储学生
	check:检查学生信息类
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


//重载以配合showList模板函数
string to_string(string);
string to_string(pii a);

/*	
	showList：
		input:		要输出的列表对应的multimap,要输出的区间的起始指
					针,要输出的区间的结束指针,单行输出的个数(默认为
					2),单页输出的行数(默认为24),序号的最长长度,value
					的最长长度
		function:	按指定格式输出
		output:		是否正常退出
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
			cout<<"\n按任意键继续或输入<p\\P>暂停以选择你的选项:";
			if(((quit=_getche())=='p'||quit=='P')){cout<<endl;return 0;}
			cout<<endl;
		}
	}
	cout<<"\n所有内容已显示\n";
}


/*
	checkDate：
		input:		一个日期类
		function:	判断该日期是否合法
		output:		该日期是否合法
*/
bool checkDate(const date &,const date &);

/*
	check类:
		public:
		成员函数:
			clear:清除类数据
			checkData:
				input:		学生信息stuInfo
				function:	判断学生信息是否有误
				output:		是否有错误、警告
			getErrorInfo:
				output:		错误的信息string类
			getErrorNum:
				output:		错误的个数
		private:
		成员变量:
			E:存储错误信息
			n:存储错误个数
		成员函数:
			checkNo
			checkName
			checkBirth
			checkEnrollmentYear
			checkTeather
			checkMajor
			checkID
				input:		学生信息stuInfo
				function:	判断学生信息是否有误，并把错误信息存到E
				output:		是否有错误、警告
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
		output: 1为无误，0为警告，-1为有误
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
		E+="E:学号为"+s.No+"的学生的学号无效\n";
		return -1;
	}
	if(stu.count(s.No)==1){
		n++;
		E+="E:学号为"+s.No+"的学生的学号已存在\n";
		return -1;
	}
	if((No/100)%10!=s.student_class){
		E+="W:学号为"+s.No+"的学生的学号所对应的班级不符，请确认是否无误\n";
		f=0;
	}
	No/=1000000;
	if(major.count(make_pair(No/10,No%10))==0){
		n++;
		E+="E:学号为"+s.No+"的学生的学号对应的专业为无效值\n";
		return -1;
	}
	if(No/10!=s.academy){
		E+="W:学号为"+s.No+"的学生的学号与学院不匹配，请确认是否无误\n";
		f=0;
	}
	if(No%10!=s.major){
		E+="W:学号为"+s.No+"的学生的学号与专业不匹配，请确认是否无误\n";
		f=0;
	}
	return f;
}
inline int check::checkName(stuInfo &s){
	if(s.country=="CN"){
		for(int i=0;i<s.name.size();i++){
			if(s.name[i]<='Z'&&s.name[i]>='A'||s.name[i]<='z'&&s.name[i]>='a'||s.name[i]==' '||s.name[i]<='9'&&s.name[i]>='0'){
				n++;
				E+="E:学号为"+s.No+"的学生的姓名应由汉字组成\n";
				return -1;
			}
		}
	}else{
		for(int i=0;i<s.name.size();i++){
			if(!(s.name[i]<='Z'&&s.name[i]>='A'||s.name[i]<='z'&&s.name[i]>='a'||s.name[i]==' '||s.name[i]<='9'&&s.name[i]>='0')){
				n++;
				E+="E:学号为"+s.No+"的学生的姓名应由英文组成\n";
				return -1;
			}
		}
	}
	return 1;
}
inline int check::checkBirth(stuInfo &s){
	if(!checkDate(s.birth,now)){
		n++;
		E+="E:学号为"+s.No+"的学生的出生日期应小于当前日期并且与当前日期之差在10~100年之间，且为合法日期\n";
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
		E+="E:学号为"+s.No+"的学生的入学日期应为合法日期\n";
		return -1;
	}
	if(t.year>=now.year&&t.mon>=now.mon&&t.day>now.day){
		n++;
		E+="E:学号为"+s.No+"的学生的入学日期应小于当前日期\n";
		return -1;
	}
	if(t.year<=s.birth.year+10){
		n++;
		E+="E:学号为"+s.No+"的学生的入学日期应大于出生日期+10年\n";
		return -1;
	}
	ll No=stoll(s.No);
	if(t.mon>10||t.mon<8){
		E+="W:学号为"+s.No+"的学生的入学日期应在8-10月之间，请确认是否无误\n";
		f=0;
	}
	if(t.year!=(No/100000)%100+2000){
		E+="W:学号为"+s.No+"的学生的入学年份与学号对应入学年份不一致，请确认是否无误\n";
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
			E+="E:学号为"+s.No+"的学生的辅导员与同班级的同学不同\n";
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
	E+="E:学号为"+s.No+"的学生的学制或培养层次不一致或该专业不含有对应的培养层次\n";
	return -1;
}
inline int check::checkID(stuInfo &s){
	if(id.count(s.id)!=0){
		n++;
		E+="E:学号为"+s.No+"的学生的身份证与学号为"+stu[id[s.id]].info.No+"的学生的身份证号相同\n";
		return -1;
	}
	if(s.id.size()!=18){
		n++;
		E+="E:学号为"+s.No+"的学生的身份证非18位\n";
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
		E+="E:学号为"+s.No+"的身份证校验位无效\n";
		return -1;
	}
	int c=(s.id[0]-'0')*100000+(s.id[1]-'0')*10000+(s.id[2]-'0')*1000+(s.id[3]-'0')*100+(s.id[4]-'0')*10+(s.id[5]-'0');
	if(place.count(c)==0){
		n++;
		E+="E:学号为"+s.No+"的身份证区域号无效\n";
		return -1;
	}
	if(((s.id[16]-'0')%2==1&&s.gender==2)||((s.id[16]-'0')%2==0&&s.gender==1)){
		n++;
		E+="E:学号为"+s.No+"的身份证号与性别不符\n";
		return -1;
	}
	int y,m,d;
	y=(s.id[6]-'0')*1000+(s.id[7]-'0')*100+(s.id[8]-'0')*10+(s.id[9]-'0');
	m=(s.id[10]-'0')*10+(s.id[11]-'0');
	d=(s.id[12]-'0')*10+(s.id[13]-'0');
	if(y!=s.birth.year||m!=s.birth.mon||d!=s.birth.day){
		n++;
		E+="E:学号为"+s.No+"的身份证号与出生日期不符\n";
		return -1;
	}
	return 1;
}
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
date tmToNode(tm *);
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
	getList：
		input:		输入流,要输入的map
		function:	输入对应列表信息
		output:		是否输入成功
*/
bool getList(ifstream &,map<int,string>);
/*
	 getCountryList
	 getTeacherList
	 getMajorList
		input:		输入流
		function:	输入对应列表信息
		output:		是否输入成功
*/
bool getCountryList(ifstream &);
bool getTeacherList(ifstream &);
bool getMajorList(ifstream &);

/*
	readFile：
		input:		文件名，读取函数
		function:	输入对应列表信息
		output:		是否输入成功
*/
bool readFile(const char *,bool read(ifstream &fp));
bool readFile(const char *,map<int,string> &,bool read(ifstream &fp,map<int,string> &));

/*
	getData：
		function:	获取列表信息
		output:		是否输入成功
*/
bool getData();
/*
	getData：
		input:		错误信息
		function:	输出错误信息
		output:		是否输出成功
*/
bool noOpen(const string &);
/*
	getData：
		input:		错误代码
		function:	输出错误信息
		output:		是否输出成功
*/
void error(int);
/*
	getData：
		input:		学生学号<默认为输入学生信息>
		function:	读取学生信息
		output:		是读取成功
*/
bool getStuInfo();
/*
	push：
		input:		学生信息
		function:	把学生信息加入查找索引
		output:		是加入成功
*/
bool push(stuInfo &);
/*
	getStudentList：
		function:	从文件读取学生信息
		output:		是否读取成功
*/
bool getStudentList();
/*
	saveStudentList：
		function:	把学生信息存入文件
		output:		是否存入成功
*/
bool saveStudentList();
/*
	getNum：
		input:		默认值
		function:	获取数字
		output:		默认值或获取的数字
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
		input:		学生信息stuInfo
		function:	获取对应信息
		output:		是否获取成功
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
	findStu：
		input:		学生信息stuInfo
		function:	实现学生信息查询
		output:		是否查询成功
*/
bool findStu(stuInfo &s);
/*
	getfind：
		input:		查询无效值,学生信息stuInfo,查询函数
		function:	查询学生信息
		output:		是否查询成功
*/
bool getfind(string,stuInfo &,bool read(stuInfo &));
/*
	YorN：
		input:		提示信息
		function:	获取"Y"或"N"
		output:		输入的对应的true/false
*/
bool YorN(string a="请输入(Y/N):");
/*
	printfStu：
		input:		学生信息
		function:	输出学生信息
		output:		是否输出成功
*/
bool printfStu(stuInfo &s);
/*
	del：
		input:		要删除的信息,信息对应的map,不删除的值
		function:	删除map中的对应值
		output:		是否删除成功
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
	delStudent：
		input:		学生信息
		function:	删除学生信息
		output:		是否删除成功
*/
bool delStudent(stuInfo &);
/*
	que1
	que2
	que3
	que4
	que5
	que6
		function:	执行菜单对应功能	
		output:		是否执行成功
*/
bool que1();
bool que2();
bool que3();
bool que4();
bool que5();
bool que6();
bool que7();
/*
	pause：
		function:	暂停程序
*/
inline void pause(){
	cout<<"请按任意键继续。。。";
	_getche();
	cout<<endl;
}
/*
	pause：
		function:	清空缓冲区
*/
inline void clear(){
	if(!cin.good())
			cin.clear();
	while(getchar()!='\n');
}
#endif