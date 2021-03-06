#ifndef CODE_H
#define CODE_H

#include<ext/hash_map>
#include"symbols.h"
#include "common.h"
#include<string>
#include<list>
#include<vector>
#include<iostream>
#include<fstream>
#include <cctype>
#include <algorithm>
using namespace std;
using namespace __gnu_cxx;

/*函数类型枚举*/
enum FunType
{
	initfun,	//构造函数
	memberfun,	//成员函数
	virtualfun,	//虚函数
	mainfun		//主函数
};
/*目标代码格式*/
struct Opcode
{
	string op;
	string arg1;
	string arg2;
	string arg3;
	string arg4;
	Opcode()
	{
		op="";
		arg1="";
		arg2="";
		arg3="";
		arg4="";
	}

};
/*标号格式*/
struct Labelcode
{
	string label1;
	string label2;
	/*构造函数*/
	Labelcode()
	{
		label1="";
		label2="";
	}
};
/*分类型代码生成*/
enum StateTypeGen
{
	NORMALFUNCALL,	//普通函数调用语句
	VFFUNCALL,	//虚函数调用
	IFSTATE,	//if语句
	ADDSTATE,	//add语句
	OBJSTATE,	//对象创建
	PTREQUSTATE,	//多态赋值
	COUTSTATE,	//输出语句
	ASSIGNSTATE,	//赋值语句
	WHILESTATE,	//while语句
	VARSTATE	//变量定义

};
/*目标代码生成类*/
class Code
{
public:
	/*析构函数和构造函数*/
	Code()
	{
		c_file.open("target/targetcode.s",ios::trunc);	//新建一个文件
		ifHasVf=false;
		ifHasPara=false;
		paraNum=0;
		ifPolyIsOn="yes";
	}
	Code(Code &code)
	{

	}
	~Code()
	{
		c_file.close();					//关闭文件
	}
	/*代码生成接口*/
	void genNextCode(Opcode &tempCode);			//生成下一条指令，并加入到指令列表里
	void clearTempCode(Opcode &tempCode);			//清除上一条指令
	/*标号生成接口*/
	void genLabel(Labelcode &tempLabel);			//生成下一条指令，并加入到指令列表里
	void clearLabel(Labelcode &tempLabel);			//清除上一条指令

	void DealLabel(bool ifhasClass,bool ifBigPro);			//生成数据段



	void initFunStack();
	void functionPro(string fun_name_frsys);		//函数代码生成
	void endFunStack();

	void endProgram();					//程序结尾

	void initFunctionPro();					//构造函数代码生成
	void memberFunctionPro();				//成员函数代码
	void virtualFunctionPro();				//虚函数代码生成
	void mainFunctionPro();					//main函数代码生成

	void statement(int stateType,string arg1,string arg2,string arg3,string arg4);

	void funcall(string funName);
	void vfFunCall(string vffunname);
	void vfSet(string objname,bool ifPoly);
	void ifstate(string num);				//if语句
	void addstate(string num);	//表达式
	void objstate(string objname_frsys,string offset);
	void ptrequstate(string thisoffset,string ptroffset);	//赋值语句代码生成
	void coutstate(string offset);				//输出语句
	void assignstate(string num);		//赋值语句
	void whilestate(string cmpNum);				//while语句
	void retstate(string reg1,string reg2);			//retrun语句
	void varstate(string varname_frysys);			//变量处理语句
	void jmp();
	void strReg();
	void ldrReg();
	void stringAssign();					//字符串处理
	void classAssignState(string rvar,string lvar);	//类里的赋值语句处理
	void classIfState(string lvar,string num);	//类里的比较函数
	void classAddState(string ladd,string radd);	//类里的加法函数
	void classFuncCall(string objname,string funname);//类里的函数调用语句
private:

	/*文件操作*/
	ofstream c_file;					//声明一个创建文件指针
	bool ifHasVf;						//是否有虚函数
	bool ifHasPara;						//是否有参数
	string ifPolyIsOn;					//是否开启多态
	int paraNum;						//参数个数
};
#endif




















