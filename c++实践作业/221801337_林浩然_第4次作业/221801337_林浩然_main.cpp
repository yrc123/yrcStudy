#include<fstream>
#include"221801337_林浩然_Levenshtein.h"
#define max(a,b) ((a)>(b)?(a):(b))
int main(){
	string fsource,ftarget,source,target,t;
	cout<<"输入原文文件路径(默认为fsource.txt):";
	getline(cin,fsource);
	cout<<"输入对比文件路径(默认为ftarget.txt):";
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
		cout<<"原文文件无法打开或不存在\n";
		return 0;
	}
	getline(fp,source,char(-1));
	source+=EOF;
	fp.clear();
	fp.close();
	fp.open(ftarget);
	if(!fp.is_open()){
		cout<<"对比文件无法打开或不存在\n";
		return 0;
	}
	getline(fp,target,char(-1));
	target+=EOF;
	fp.clear();
	fp.close();
	Levenshtein Le(source,target);
	Le.check();
	cout<<"两个文件的相似度为:"<<Le.same*100<<"%\n";
	if(Le.same>0.65){
		cout<<"两份代码相似度过高,很有可能为抄袭。";
	}else if(Le.same>0.35){
		cout<<"两份代码相似度较高,有可能为抄袭。";
	}else{
		cout<<"两份代码相似度较低,抄袭的可能很低。";
	}
}