#include"221801337_林浩然_HugeInt.h"
/*
	姓名：林浩然		学号：221801337
	班级：软件3班		电话：18597701284
	邮箱：958480638@qq.com
	程序将4位数字存到一个int中，减少了空间复杂度
	本程序在windows下，用visual studio 2019中开发，在windows下
	运行

*/
int main(){
	HugeInt a(221801337),b,c("350103199910121553"),d(a);
	cout<<">HugeInt a(221801337),b,c(\"350103199910121553\"),d(a)<构造函数\\拷贝构造函数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	b=string("12345678901234567890123456789012345678901234567890123456789012345678901234567890");	
	cout<<"\n>b=string(\"12345678901234567890123456789012345678901234567890123456789012345678901234567890\")<重载=>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	d=0-b;
	cout<<"\n>d=0-b<重载=>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	a=a+b;
	cout<<"\n>a=a+b<正数+正数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	a=a+d;
	cout<<"\n>a=a+d<正数+负数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	a=-221801337;
	cout<<"\n>a=-221801337<重载=>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	a=a+d;
	cout<<"\n>a=a+d<负数+负数>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a=a+string("221801337");
	cout<<"\n>a=a+string(\"221801337\")<大数+string>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a=string("221801337")+a;
	cout<<"\n>a=string(\"221801337\")+a<string+大数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	c=b-c;
	cout<<"\n>c=b-c<正数-正数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	b=b-a;
	cout<<"\n>b=b-a<正数-负数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	a=a-d;
	cout<<"\n>a=a-d<负数-负数>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a=a-string("221801337");
	cout<<"\n>a=a-string(\"221801337\")<大数-string>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a=string("221801337")-a;
	cout<<"\n>a=string(\"221801337\")-a<string-大数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	a=0-a;
	cout<<"\n>a=0-a<int-大数>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	b=b*c;
	cout<<"\n>b=b*c<正数*正数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	c=c*d;
	cout<<"\n>c=c*d<正数*负数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	a=a*d;
	cout<<"\n>a=a*d<负数*负数>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a=a*string("221801337");
	cout<<"\n>a=a*string(\"221801337\")<大数*string>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a=string("221801337")*a;
	cout<<"\n>a=string(\"221801337\")*a<string*大数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	a=a*0;
	cout<<"\n>a=a*0<大整数*0>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	c=c/d;
	cout<<"\n>c=c/d<负数/负数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	b=b/d;
	cout<<"\n>b=b/d<正数/负数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	b=(0-b)/c;
	cout<<"\n>b=(0-b)/c<正数/正数>\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	d=d/string("221801337");
	cout<<"\n>d=d/string(\"221801337\")<大数/string>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	d=string("221801337221801337221801337221801337221801337221801337221801337221801337")/d;
	cout<<"\n>d=string(\"221801337221801337221801337221801337221801337221801337221801337221801337\")/d<string/大数>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	c=c%b;
	cout<<"\n>c=c%b<正数%正数>\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a+=d;
	cout<<"\n>a+=d\n";
	de(a);
	de(b);
	de(c);
	de(d);
	
	a-=b;
	cout<<"\n>a-=b\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a*=d;
	cout<<"\n>a*=d\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a/=b;
	cout<<"\n>a/=b\n";
	de(a);
	de(b);
	de(c);
	de(d);

	c%=d;
	cout<<"\n>c%=d\n";
	de(a);
	de(b);
	de(c);
	de(d);

	a=b;
	cout<<"\n>a=b\n";
	de(a);
	de(b);
	de(c);
	de(d);

	cout<<"\n>a>b\n";
	cout<<(a>b)<<endl;

	cout<<"\n>a>=b\n";
	cout<<(a>=b)<<endl;

	cout<<"\n>a<b\n";
	cout<<(a<b)<<endl;

	cout<<"\n>a<=b\n";
	cout<<(a<=b)<<endl;

	cout<<"\n>a>d\n";
	cout<<(a>d)<<endl;

	cout<<"\n>a<d\n";
	cout<<(a<d)<<endl;

	cout<<"\n>d>c\n";
	cout<<(d>c)<<endl;

	cout<<"\n>d<c\n";
	cout<<(d<c)<<endl;
	
	cout<<"\n>a==b\n";
	cout<<(a==b)<<endl;

	cout<<"\n>a!=b\n";
	cout<<(a!=b)<<endl;
	//
	cout<<"\n>a>1\n";
	cout<<(a>1)<<endl;

	cout<<"\n>1>=a\n";
	cout<<(1>=a)<<endl;

	cout<<"\n>a<1\n";
	cout<<(a<1)<<endl;

	cout<<"\n>a<=1\n";
	cout<<(a<=1)<<endl;

	cout<<"\n>a>-3\n";
	cout<<(a>-3)<<endl;

	cout<<"\n>a<-3\n";
	cout<<(a<-3)<<endl;

	cout<<"\n>-3>c\n";
	cout<<(-3>c)<<endl;

	cout<<"\n>-3<c\n";
	cout<<(-3<c)<<endl;
	
	cout<<"\n>1==a\n";
	cout<<(1==a)<<endl;

	cout<<"\n>a!=1\n";
	cout<<(a!=1)<<endl;

	cout<<"\n>cout<<a++\n";
	de(a++);

	cout<<"\n>cout<<a\n";
	de(a);

	cout<<"\n>cout<<a--\n";
	de(a--);

	cout<<"\n>cout<<a\n";
	de(a);

	cout<<"\n>cout<<++a\n";
	de(++a);

	cout<<"\n>cout<<a\n";
	de(a);

	cout<<"\n>cout<<--a\n";
	de(--a);

	cout<<"\n>cout<<a\n";
	de(a);

	cout<<"\n><8进制输出>\n";
	a.printOctal();cout<<"  ";
	b.printOctal();cout<<"  ";
	c.printOctal();cout<<"  ";
	d.printOctal();cout<<"\n";

	cout<<"\n><16进制输出>\n";
	a.printHex();cout<<"  ";
	b.printHex();cout<<"  ";
	c.printHex();cout<<"  ";
	d.printHex();cout<<"\n";

	HugeInt a1("0"),b1("-031310"),c1("045070"),d1("0106240");
	cout<<"\n>HugeInt a1(\"0\"),b1(\"-031310\"),c1(\"045070\"),d1(\"0106240\")<构造函数>\n";
	de(a1);
	de(b1);
	de(c1);
	de(d1);
	
	cout<<"\n><8进制输出>\n";
	a1.printOctal();cout<<"  ";
	b1.printOctal();cout<<"  ";
	c1.printOctal();cout<<"  ";
	d1.printOctal();cout<<"\n";

	HugeInt a2("-0"),b2("-0X32C8"),c2("0X4A38"),d2("0x8CA0");
	cout<<"\n>HugeInt a2(\"-0\"),b2(\"-0X32C8\"),c2(\"0X4A38\"),d2(\"0X8CA0\")<构造函数>\n";
	de(a2);
	de(b2);
	de(c2);
	de(d2);
	
	cout<<"\n><16进制输出>\n";
	a2.printHex();cout<<"  ";
	b2.printHex();cout<<"  ";
	c2.printHex();cout<<"  ";
	d2.printHex();cout<<"\n";

	cout<<"\n>对于除零抛出异常\n";
	try{
		cout<<"进行a/0\n";
		a/0;
	}catch(HugeInt::DivideByZero){
		cout<<"捕获到DivideByZero\n";
	}

	cout<<"\n>对于除零抛出异常\n";
	try{
		cout<<"进行a/string(\"0\")\n";
		a/string("0");
	}catch(HugeInt::DivideByZero){
		cout<<"捕获到DivideByZero\n";
	}

	cout<<"\n>对于非法字母出异常\n";
	try{
		cout<<"进行HugeInt test1(\"0XFFF\")\n";
		HugeInt test1("0XFFF");
		cout<<"构造成功\n";
		cout<<"进行HugeInt test2(\"0XSIX\")\n";
		HugeInt test2("0XSIX");
		cout<<"构造成功\n";
	}catch(HugeInt::WrongNum){
		cout<<"捕获到WrongNum\n";
	}

	cout<<"\n>对于非法字母异常\n";
	try{
		cout<<"进行HugeInt test3(\"0123\")\n";
		HugeInt test3("0123");
		cout<<"构造成功\n";
		cout<<"进行HugeInt test4(\"0129\")\n";
		HugeInt test4("0129");
		cout<<"构造成功\n";
	}catch(HugeInt::WrongNum){
		cout<<"捕获到WrongNum\n";
	}
	return 0;
}
