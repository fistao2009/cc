#include "symbols.h"

//内部类用来辅助hash_map的使用
struct str_hash{
	size_t operator()(const string& str) const
	{
		return __stl_hash_string(str.c_str());
	}
};
hash_map<string,var_symbol,str_hash> var_map;		//变量的hash表索引
hash_map<string,fun_symbol,str_hash> fun_map;		//函数的hash表索引
hash_map<string,class_symbol,str_hash> class_map;	//类的hash表索引
hash_map<string,obj_symbol,str_hash> obj_map;		//对象的hash表索引

/*---------------------符号表内容管理------------------------------*/
/*添加变量符号表*/
void SymbolTable::add_var_symbol(bool wornot,var_symbol vs)
{
	//检测是否发生了语法错误,如果有语法错误，退出
	if(wornot==1)
	{
		cout<<"出现了语法错误，请改正语法错误后继续"<<endl;
		exit(-1);
	}
	if(var_map.find(vs.var_name)!=var_map.end())
	{
		cout<<"符号表中存该变量的条目内容"<<endl;
	}
	else
	{
		var_map[vs.var_name]=vs;
	}
}

/*添加类符号表*/
void SymbolTable::add_class_symbol(bool wornot,class_symbol cs)
{
	//检测是否发生了语法错误,如果有语法错误，退出
	if(wornot==1)
	{
		cout<<"出现了语法错误，请改正语法错误后继续"<<endl;
		exit(-1);
	}
	if(class_map.find(cs.class_name)!=class_map.end())
	{
		cout<<"符号表中存该类的条目内容"<<endl;
	}
	else
	{
		class_map[cs.class_name]=cs;
	}
}
/*添加对象符号表*/
void SymbolTable::add_obj_symbol(bool wornot,obj_symbol os)
{
	//检测是否发生了语法错误,如果有语法错误，退出
	if(wornot==1)
	{
		cout<<"出现了语法错误，请改正语法错误后继续"<<endl;
		exit(-1);
	}
	if(obj_map.find(os.obj_name)!=obj_map.end())
	{
		cout<<"符号表中存该函数的条目内容"<<endl;
	}
	else
	{
		obj_map[os.obj_name]=os;
	}
}
void SymbolTable::add_fun_symbol(bool wornot,fun_symbol fs)
{

	if(wornot==1)
	{
		cout<<"出现了语法错误，请改正语法错误后继续"<<endl;
		exit(-1);
	}
	//检查是否有重定义，如果有，则放弃插入，否则将该条目插入到符号表中
	//if(fun_map.find(fs.fun_name)!=fun_map.end() && fun_map.find(fs.belongClass)!=fun_map.end() )
	//{
	//	cout<<"符号表中存该函数的条目内容"<<endl;
	//}
	//else
	//{
		fun_map[fs.fun_name+fs.belongClass]=fs;	//有类的时候的插入符号表的语句
		//fun_map[fs.fun_name]=fs;			//木有类的时候的更新符号表的语句
	//}


}
/*打印符号表内容*/
void SymbolTable::show_symbol_content()
{
	cout<<"******************************代码生成需要用到的符号表内容**************"<<endl;
	cout<<"-------------函数符号表内容--------"<<endl;
	//声明一个该hash_map的迭代器，遍历该hash_map打印符号表内容
	hash_map<string,fun_symbol,str_hash>::iterator iter=fun_map.begin();
	for(;iter!=fun_map.end();iter++)
	{
		//依次打印函数的各个字段的符号表记录
		fun_symbol fs=iter->second;
		cout<<"函数名："<<fs.fun_name<<endl;
		cout<<"函数类型："<<fs.fun_type<<endl;
		cout<<"所属的类："<<fs.belongClass<<endl;
		if(fs.ifHasPara==true)
		{
			cout<<"参数1："<<fs.para1<<endl;
			cout<<"参数2："<<fs.para2<<endl;
			//cout<<"是否有参数:"<<fs.ifHasPara<<endl;
		}

		cout<<endl;

	}
	cout<<"-------------变量符号表内容---    -----"<<endl;
	hash_map<string,var_symbol,str_hash>::iterator iter1=var_map.begin();
	for(;iter1!=var_map.end();iter1++)
	{
		//依次打印变量的各个字段的符号表记录
		var_symbol vs=iter1->second;
		cout<<"变量名字："<<vs.var_name<<endl;
		//cout<<"变量类型:"<<vs.var_type<<endl;
		cout<<"变量所属的类:"<<vs.belongClass<<endl;
		cout<<endl;
	}
	cout<<"-------------类符号表内容--------"<<endl;
	hash_map<string,class_symbol,str_hash>::iterator iter2=class_map.begin();
	for(;iter2!=class_map.end();iter2++)
	{
		//依次打印类的各个字段的符号表记录
		class_symbol cs=iter2->second;
		cout<<"类名："<<cs.class_name<<endl;
		cout<<"基类还是派生类："<<cs.base_or_her<<endl;
		//cout<<"默认访问属性:"<<cs.pretermit_visited<<endl;
		cout<<endl;

	}
	cout<<"-------------对象符号表内容--------"<<endl;
	hash_map<string,obj_symbol,str_hash>::iterator iter3=obj_map.begin();
	for(;iter3!=obj_map.end();iter3++)
	{
		//依次打印函数的各个字段的符号表记录
		obj_symbol os=iter3->second;
		cout<<"对象名："<<os.obj_name<<endl;
		//cout<<"参数个数:"<<os.paranum<<endl;
		cout<<"对象类型:"<<os.obj_type<<endl;
		cout<<"参数1:"<<os.para1<<endl;
		cout<<"参数2:"<<os.para2<<endl;
		cout<<"所属的类"<<os.belongClass<<endl;
		cout<<"参数个数"<<os.paranum<<endl;
		cout<<endl;
	}

}


/*----------------------静态语义处理模块----------------------------*/
bool SymbolTable::checkVarRedefined(string varName)	//检查变量重定义
{
	if(var_map.find(varName)!=var_map.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*
检查函数调用正确性：类型匹配，个数符合
@参数fs:函数符号表中的参数列表；
@参数modapar:给定的函数调用中获取的实参列表。
*/
bool SymbolTable::checkFCallRW(fun_symbol fs,list<string> modapar)
{
	list<string> realpar=fs.parlist;	//取得函数表符号中的参数声明字段
	list<string>::iterator iter1,iter2;
	//检查参数的个数是否相同
	if(realpar.size()!=modapar.size())
	{
		cout<<"函数调用中的实参个数和形参个数不同"<<endl;
		//exit(-1);			//直接终止程序，不再向下执行
		return false;
	}
	else
	{
		for(iter1=realpar.begin();iter1!=realpar.end();iter1++)
		{
			for(iter2=modapar.begin();iter2!=modapar.end();iter2++)
			{
				//比较两个string是否相同
				if(!(*iter1).compare((*iter2)))
				{
					;
				}
				else
				{
					cout<<"实参类型和形参类型不匹配"<<endl;
					return false;
				}
			}
		}
		return true;
	}


}


/*-------------------------字符串处理--------------------------------*/
void SymbolTable::add_string_symbol(const char *str)
{
	if(str==NULL)
	{
		cout<<"字符串为空，出现了异常"<<endl;
		exit(-1);			//直接终止程序执行
	}
	else
	{
		//将该字符添加到vector中
		strSpace.push_back(str);
	}


}

/*按名查找符号表*/
int querySymbolTable(string name)
{

}






























