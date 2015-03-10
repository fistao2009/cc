#ifndef SYMBOLS_H
#define SYMBOLS_H

#include<ext/hash_map>
#include<string>
#include<list>
#include<map>
#include<vector>
#include<iostream>
using namespace std;
using namespace __gnu_cxx;

/*变量的作用域*/
enum VarPlace{Global,Local,Para,Member};


/*类符号*/
struct class_symbol
{
	string class_name;		//类名
	int	*base;			//父类指针
	list<string> 	virtable;	//虚函数表
	int		*vptr;		//虚指针
	unsigned int    base_or_her;	//基类:0 派生类：1
	unsigned int 	pretermit_visited;	//默认访问属性
	list<string>	funList;	//成员函数列表
	list<string>	varList;	//成员变量列表
	unsigned int 	member_size;	//所需的空间大小
};
/*对象符号*/
struct obj_symbol
{
	string obj_name;		//对象名
	string para1;
	string para2;			//两个参数
	int obj_type;			//0：普通对象 1:对象指针
	string belongClass;
	list<string> para;
	unsigned int paranum;		//参数个数

};
/*变量符号*/
struct var_symbol
{
	string var_name;		//变量名
	string	belongClass;		//所属的类
	string var_type;		//变量类型
	VarPlace var_pla;		//变量的作用域
	unsigned int var_addr;		//变量的地址
	string offset;			//变量的偏移,根据变量先后加入符号表的顺序，设定不同的偏移
};
/*函数符号表结构体*/
struct fun_symbol
{
	string fun_name;		//函数名
	int	fun_type;		//函数类型 0：构造函数 1：成员函数2 虚函数 3 main函数
	string	belongClass;		//所属的类
	string	para1;
	string	para2;			//两个参数
	bool	ifHasPara;		//是否有参数
	bool	ifHasVFun;		//是否有虚函数
	int	paraNum;		//参数个数
	string	vfFunctionName;		//虚函数名字
	list<string>	parlist;	//参数列表
	int 	local_size;		//局部变量所占的大小
	string ret_type;		//函数返回类型
	int	entry_addr;		//函数的入口地址
	int	para_size;		//局部变量所占的大小
	list<string>	localvar;	//局部变量列表
	int	stmtNum;		//函数中语句的条数

};

//符号表管理
class SymbolTable
{
public:
	/*不带参数的构造函数*/
	SymbolTable()
	{

	}
	/*拷贝构造函数*/
	SymbolTable(SymbolTable &st)
	{

	}
	~SymbolTable()
	{
		/*
		不写良好的析构函数会导致内存泄漏
		*/

	}

	/*增加符号表*/

	void add_var_symbol(bool wornot,var_symbol vs);
	void add_fun_symbol(bool wornot,fun_symbol fs);
	void add_class_symbol(bool wornot,class_symbol cs);
	void add_obj_symbol(bool wornot,obj_symbol os);

	/*字符串处理*/
	void add_string_symbol(const char *str);

	/*语义处理模块*/
	bool checkVarRedefined(string varName);			//检查变量重定义
	bool checkFCallRW(fun_symbol fs,list<string> modapar);	//检查函数调用正确性：类型匹配，个数符合
	/*打印符号表内容*/
	void show_symbol_content();				//打印符号表内容
	int querySymbolTable(string name);			//按名查找符号表
public:

	vector<const char *>	strSpace;			//字符串处理
};
#endif


















