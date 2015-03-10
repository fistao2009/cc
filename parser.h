#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lex.h"
#include "symbols.h"
#include "codegenerator.h"
#include "errorhandler.h"
#include<queue>
#include<stack>
#include<string>
#include<vector>
#include<iostream>
#include<stdlib.h>
using namespace std;

/*常量定义区*/
#define CLA	1				//类定义
#define COM	2				//注释语句
#define FUN	3				//函数声明
#define VAR	4				//变量声明
#define OBJD	5				//对象声明
#define EXP	6				//赋值表达式
#define IFS	7				//if语句
#define WHIS	8				//while语句
#define RES	9				//return语句
#define CINS	10				//cin语句
#define COUS	11				//cout语句
#define NABO	12				//不是上述类型
#define PRIA	13				//private权限处理
#define EOFC	14				//类定义结束标记
#define DOBJ	15				//动态绑定对象定义
#define PUB	16
/*语法分析错误类型*/
enum ParserError
{
	BEYONDSYNTAX,			/*超出文法语义：0*/
	MISSCOLON,				/*丢失冒号：1*/
	MISSHERAUTH,			/*缺少访问控制:2*/
	MISSLSQUAR,				/*丢失左大括号:3*/
	MISSRSQUAR,				/*丢失右大括号：4*/
	MISSSEMIC,				/*丢失分号:5*/
	MISSAREA,				/*丢失作用域操作符：6*/
	MISSLBRACK,				/*丢失左小括号：7*/
	MISSRBRACK,				/*丢失右小括号:8*/
	MISSLSLASH,				/*缺少左边的反斜杠：9*/
	MISSSTAR,				/*缺少星号:10*/
	MISSRSLASH,				/*缺少右边的反斜杠：11*/
	UNDEFINEDTYPE,			/*未定义类型：12*/
	WRONGIF,				/*if关键字出错：13*/
	WRONGWHILE,				/*while关键字出错：13*/
	WRONGRETURN,			/*return关键字出错:14*/
	WRONGCIN,				/*cin关键字出错：15*/
	WRONGCOUT,				/*cout关键字出错：16*/
	NOTID,					/*不合法标识符:17*/
	UNDEFINEDCALC,			/*未定义的运算符:18*/
	UNDEFINEDRELOP,			/*未定义关系操作符：19*/
	UNKNOWNERROR			/*未知错误:20*/
};

/*
1.语法分析器中添加一个字段：
2.在对应的语句位置可以轻易的获取参数信息，传递给statement
3.在函数的语法分析过程中的语句位置调用，statement()

*/

/*语法分析器定义*/
class Parser
{
public:
	Parser()
	{
		currToken=lex.getToken();	//先读一个词法记号
		parserRW=true;
		function_type=0;		//默认是构造函数
		err_num=0;
		ifDataGened=false;

		/*初始化语句类型和参数信息*/
		stateType=999;	//不属于任何语句类型
		arg1="";
		arg2="";
		arg3="";
		arg4="";
		//arg5 arg6用做备份的参数传递器
		arg5="";
		arg6="";
		ifhasClass=false;
		count=0;

	}

	~Parser()
	{
	}
	/*解析程序*/
	void program(int parseSeq);

	void getFirstToken()
	{currToken=lex.getToken();}
	/*处理声明*/
	void classdecl();
	void vardecl();
	void funcdecl();
	void objdecl();
	void comment();


	void type();
	void paramalist();
	void chunkstatement();

	void statement();
	void ifstate();
	void whilestate();
	void returnstate();
	void cinstate();
	void coutstate();

	void expression();
	void compoundstate();
	void calacop();
	void relop();

	void operat();
	void funccall();
	void realparalist();
	void idvar();

	void daynamicobj();

	/*取得当前词法记号*/
	void getCurrToken();
	/*判断声明类别*/
	int whatis();
	/*匹配终结符*/
	bool match(TokenType str);
	/*打印出错信息*/
	void print_error_info(ParserError pe);
	/*进行错误恢复*/
	void error_handler();
	/*错误处理*/
	void error();
	/*输出当前词法记号*/
	void outputCurrToken()
	{
		cout<<currToken.lines<<" "<<currToken.ttype<<" "<<currToken.str<<endl;
	}
	//打印符号表内容
	void showTable()
	{
		st_p.show_symbol_content();
	}
	SymbolTable st_p;	//符号表对象
	/*不显示的初始化，系统会调用默认构造函数，所以这样写也是定义*/
	fun_symbol fs_p;	//函数符号表结构体
	class_symbol cs_p;	//类符号表结构体
	var_symbol vs_p;	//变量符号表结构体
	obj_symbol os_p;	//对象符号表结构体
	bool ifhasClass;	//是否有类声明
	int count;

private:



	unsigned int errorcount;//语法分析错误数量
	int	function_type;	//函数类型：0： 构造函数 1： 成员函数 2： 虚函数 3:main函数
	Token currToken;	//当前词法记号
	Token nextToken;	//下一个词法记号
	Token lastToken;	//上一个词法记号
	Lex lex;		//词法分析器接口
	queue<Token> q_to;	//辅助决策队列,这个队列要声明成类的成员，而不是函数的局部变量
	stack<Token> q_eh;	//错误恢复辅助栈
	unsigned int err_num;
	bool  parserRW;		//分析正确与否标志
	ParserError peType;	//用来在程序中表示语法分析的错误类型
	Code codegen;		//代码生成器接口
	bool ifDataGened;	//是否生成过数据段

	/*准备好代码生成语句的语句类型和参数信息*/
	int stateType;		//语句类型
	string arg1,arg2,arg3,arg4,arg5,arg6;//语句类型后的几个参数，在语法分析的语句处获得


};//class
#endif
