#include "lex.h"
#include "parser.h"
#include "codegenerator.h"
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

enum ParseSeq
{
	FIRST,	//第一遍，填充符号表，不进行代码生成
	SECOND	//第二遍，不填充符号表，只进行代码生成
};

/*外部变量引用区*/
extern bool ifBigPro;
extern bool ifHelloWorld;

/*----------------------------主程序----------------------------------------------*/
int main()
{	
	/*选择测试程序代码
	
	cout<<"********************测试程序集合***********************"<<endl;
	cout<<"-----------1.helloWorld.cpp---------------"<<endl;
	//cout<<"-----------2.hanoi.cpp--------------------"<<endl;
	cout<<"-----------2.sum.cpp----------------------"<<endl;
	cout<<"-----------3.upc_people_count.cpp---------"<<endl;	
	cout<<"-----------4.whiletest.cpp----------------"<<endl;	
	
	cout<<"请选择需要测试的程序："<<endl;
	cin>>selectTest;
	/*根据输入的数字选择需要进行翻译的程序
	if(selectTest<0 || selectTest>5)
	{
		cout<<"输入了不合法的程序编号"<<endl;
	}
	switch(selectTest)
	{
		case 1:
			lexFileName="cpptest/helloworld.cpp";
			break;
		case 2:
			lexFileName="cpptest/sum.cpp";
			break;
		case 3:
			lexFileName="cpptest/upc_people_count.cpp";
			break;
		case 4:
			lexFileName="cpptest/whiletest.cpp";
			break;
		default:
			cout<<"请输入规定范围内的程序编号"<<endl;
			break;
	}
	
	
	//词法分析
	Lex lex(lexFileName);	
	Token l_token;
	cout<<"**************************词法分析程序:******************************"<<endl;
	//词法记号总数：392
	while(lex.endOfFlag==1)
	{
		l_token=lex.getToken();		//用一个临时对象来接受返回的token值
		cout<<"词法记号："<<setw(10)<<l_token.str<<" "<<"词法类型:"<<setw(10)<<l_token.ttype<<" "<<"行号:"<<setw(10)<<l_token.lines<<endl;
	}
	cout<<"*********************恭喜，源程序的词法分析已经完成！*******************"<<endl;*/
	
	//语法分析
	//cout<<"**************************语法分析程序:******************************"<<endl;
	//Parser parser;
	//parser.program();
	//cout<<"*********************恭喜，源程序的语法分析已经完成！*******************"<<endl;
		

	//cout<<"C++源程序执行结果"<<endl;
	//...	
	//cout<<"是否对程序进行优化:yes no"<<endl;
	//cin>>str;
	/*if(!str.compare("yes"))
	{
		isOptimize=true;
		cout<<"优化后的汇编代码:1.指令占用空间 2.运行时间"<<endl;
		//...
	}
	else
	{
		isOptimize=false;
		cout<<"未优化的ARM汇编代码"<<endl;
		//...
	}
	*/	
	//cout<<"ARM汇编代码在qemu上的执行结果:"<<endl;
	//...
	//cout<<"错误恢复技术"<<endl;
	//...
	
	
	/*预期输出：三列的单词分类表
	Lex lex;	
	Token l_token;
	cout<<"**************************词法分析程序:******************************"<<endl;
	//词法记号总数：392
	while(lex.endOfFlag==1)
	{
		l_token=lex.getToken();		//用一个临时对象来接受返回的token值
		cout<<"词法记号："<<setw(10)<<l_token.str<<" "<<"词法类型:"<<setw(10)<<l_token.ttype<<" "<<"行号:"<<setw(10)<<l_token.lines<<endl;
	}
	cout<<"*********************恭喜，源程序的词法分析已经完成！*******************"<<endl;
	cout<<"**************************语法分析程序:******************************"<<endl;
	Parser parser;
	parser.program();
	cout<<"*********************恭喜，源程序的语法分析已经完成！*******************"<<endl;*/
	//打印符号表内容
	//SymbolTable st;		//在主函数中这样写是无法打印符号表中的数据的
	/*fun_symbol  fs;
	fs.fun_name="test";
	fs.ret_type="int";
	fs.entry_addr=1;
	fs.para_size=1;
	fs.local_size=1;
	fs.fun_type=1;
	st.add_fun_symbol(0,fs);
	var_symbol  vs;
	vs.var_name="test";
	st.add_var_symbol(0,vs);
	class_symbol  cs;
	cs.class_name="test";
	st.add_class_symbol(0,cs);
	obj_symbol  os;
	os.obj_name="test";
	//用局部对象调用会产生空结果
	st.add_obj_symbol(0,os);*/
	/*
	int selectTest;
	
	char *lexFileName;

	

	
	cout<<"********************测试程序集合***********************"<<endl;
	cout<<"-----------1.helloWorld.cpp---------------"<<endl;
	cout<<"-----------2.upc_people_count.cpp---------"<<endl;	
	cout<<"-----------3.whiletest.cpp----------------"<<endl;	
	
	cout<<"请选择需要测试的程序："<<endl;
	cin>>selectTest;
	/*根据输入的数字选择需要进行翻译的程序
	if(selectTest<0 || selectTest>3)
	{
		cout<<"输入了不合法的程序编号"<<endl;
	}
	switch(selectTest)
	{
		case 1:
			cout<<"you choice is: helloWorld.cpp"<<endl;
			lexFileName="cpptest/helloworld.cpp";
			/*设定这两个标记
			ifHelloWorld=true;
			ifBigPro=false;
			break;
		case 2:
			cout<<"you choice is: upc_people_count.cpp"<<endl;
			lexFileName="cpptest/upc_people_count.cpp";
			ifHelloWorld=false;
			ifBigPro=true;
			break;
		case 3:
			cout<<"you choice is: whiletest.cpp"<<endl;
			lexFileName="cpptest/whiletest.cpp";
			ifHelloWorld=true;
			ifBigPro=false;
			break;
		default:
			cout<<"请输入规定范围内的程序编号"<<endl;
			break;
	}

	string yes;
	cin>>yes;
	 
	*/	
	Parser parser;
	/*第一遍遍历，填充符号表*/
	parser.program(FIRST);
	parser.showTable();
	/*第二遍遍历，代码生成*/
	parser.getFirstToken();
	parser.program(SECOND);
	parser.showTable();


	/*去执行生成的汇编文件*/
	
	
	return 0;
}































