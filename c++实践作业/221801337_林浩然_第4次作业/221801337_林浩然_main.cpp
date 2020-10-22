#include<fstream>
#include"221801337_�ֺ�Ȼ_Levenshtein.h"
#define max(a,b) ((a)>(b)?(a):(b))
int main(){
	string fsource,ftarget,source,target,t;
	cout<<"����ԭ���ļ�·��(Ĭ��Ϊfsource.txt):";
	getline(cin,fsource);
	cout<<"����Ա��ļ�·��(Ĭ��Ϊftarget.txt):";
	getline(cin,ftarget);
	if(fsource.size()==0){
		fsource=".\\fsource.txt";
	}
	if(ftarget.size()==0){
		ftarget=".\\ftarget.txt";
	}
	ifstream fp;
	fp.open(fsource);
	if(!fp.is_open()){
		cout<<"ԭ���ļ��޷��򿪻򲻴���\n";
		return 0;
	}
	getline(fp,source,char(-1));
	source+=EOF;
	fp.clear();
	fp.close();
	fp.open(ftarget);
	if(!fp.is_open()){
		cout<<"�Ա��ļ��޷��򿪻򲻴���\n";
		return 0;
	}
	getline(fp,target,char(-1));
	target+=EOF;
	fp.clear();
	fp.close();
	Levenshtein Le(source,target);
	Le.check();
	cout<<"�����ļ������ƶ�Ϊ:"<<Le.same*100<<"%\n";
	if(Le.same>0.65){
		cout<<"���ݴ������ƶȹ���,���п���Ϊ��Ϯ��";
	}else if(Le.same>0.35){
		cout<<"���ݴ������ƶȽϸ�,�п���Ϊ��Ϯ��";
	}else{
		cout<<"���ݴ������ƶȽϵ�,��Ϯ�Ŀ��ܺܵ͡�";
	}
}