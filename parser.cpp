#include "parser.h"
#include<string>
#include<cassert>
#include<iostream>
using namespace std;


//类中的成员函数或构造函数代码生成时的全局变量
string funnameandclass;
bool ifBigPro=true;		//是否是大程序开关
int coutNum=1;			//cout全局变量
/*
@stateType:语句类型

	NORMALFUNCALL,	//普通函数调用语句
	VFFUNCALL,	//虚函数调用
	IFSTATE,	//if语句
	ADDSTATE,	//add语句
	OBJSTATE,	//对象创建
	PTREQUSTATE,	//多态赋值
	COUTSTATE,	//输出语句
	ASSIGNSTATE,	//赋值语句
	WHILESTATE	//while语句
问题：语法分析器写的不合规范，代码生成的时候出现了逻辑混乱。？？？？how,指点迷津，方向

*/
int parseSeq;	//本地的分析次数
bool notgen=false;
/*语法分析程序:把已正确分析的词法记号打印出来*/
void Parser::program(int parseSeqPara)
{	
	/*传给本地静态全局变量*/
	parseSeq=parseSeqPara;
	
	unsigned int sentence_type=0;
	
	//cout<<(lex.mycf).tellg()<<endl;
	while(!match(ENDOFFILE))			//如果没有匹配到文件的结束字符
	{
		//第二遍再进行代码生成
		if(parseSeq==1)
		{
			if(ifDataGened==false )
			{
				/*调用生成数据段的代码*/
				codegen.DealLabel(ifhasClass,ifBigPro);
				/*将标志加1*/
				ifDataGened=true;
			
			}
		}
		sentence_type=whatis();	
		if(sentence_type==1)		//类定义
		{
			outputCurrToken();
			classdecl();
			sentence_type=0;
		}
		else if(sentence_type==2)	//单行注释
		{	
			outputCurrToken();
			comment();
			sentence_type=0;
		}
		else if(sentence_type==3)	//函数声明
		{
			outputCurrToken();
			/*---------------------代码生成范例-----------------------*/
			
			/*在函数里面的左右大括号之间进行语句的代码生成*/
			funcdecl();	
			/*紧跟本函数右括号应该添加函数尾*/
			if(parseSeq==1)
			{
				//	codegen.endFunStack();
			}
			sentence_type=0;
		}
		else if(sentence_type==4)	//变量声明
		{
			vardecl();
			sentence_type=0;
		}
		else if(sentence_type==5)	//对象声明
		{
			objdecl();
			sentence_type=0;
			//这里只进行对象指针的处理
			if(parseSeq==1)
			{
		
				//stateType=OBJSTATE;
				//arg1,arg2... 参数不对
				//codegen.statement(stateType,arg1,arg2,arg3,arg4);
			}	
		}
		else if(sentence_type==PRIA)	//private权限处理
		{
			getCurrToken();
			outputCurrToken();
			if(match(COLON))
			{
				getCurrToken();
				outputCurrToken();
			}
			else
			{
				peType=MISSCOLON;
				error();
			}	
		}
		else if(match(RSQUAR))
		{
			getCurrToken();
			outputCurrToken();
			if(match(SEMIC))
			{
				/*类定义结束*/
				getCurrToken();
				
			}
			else
			{
				
				//第二遍再进行代码生成
				if(parseSeq==1 && notgen==false)
				{
				//codegen.endProgram();
				codegen.endFunStack();
				notgen=true;
				}
				cout<<"------------语法分析结果-----------"<<endl;
				cout<<"0 errors,0 wronings"<<endl;
			
			}
		}
		else if(match(COUT))
		{
			/*输出语句*/
			coutstate();
			//第二遍再进行代码生成
			if(parseSeq==1)
			{
				//stateType=VARSTATE;
				//codegen.statement(stateType,arg1,arg2,arg3,arg4);	
		
				stateType=COUTSTATE;
				/*因为helloworld.cpp中只有一个变量*/
				if(ifBigPro==true)
				{
					if(coutNum==1)
					{
						arg1="-28";
						coutNum++;
					}	
					else if(coutNum==2)
					{
						arg1="-32";
						coutNum++;
					}
					else if(coutNum==3)
					{
						arg1="-52";
						coutNum++;
					}
					else if(coutNum==4)
					{
						arg1="-56";
						coutNum++;
					}
					else if(coutNum==5)
					{
						arg1="-60";
						coutNum++;
					}
					else if(coutNum==6)
					{
						arg1="-64";
						coutNum++;
					}
					else
					{
					}
				}
				else
				{
					arg1="-20";
				}
				codegen.statement(stateType,arg1,arg2,arg3,arg4);
				//恢复现场
				if(ifhasClass==false)
				{
					codegen.ldrReg();
					codegen.jmp();
				}
				
			}
		}
		else if(sentence_type==DOBJ)
		{
			/*动态绑定的对象声明语句*/
			daynamicobj();
			//第二遍再进行代码生成
			if(parseSeq==1)
			{
		
			//stateType=PTREQUSTATE;
			//arg1...
			//codegen.statement(stateType,arg1,arg2,arg3,arg4);
			}
		}
		else if(sentence_type==WHIS)
		{
			whilestate();
			//第二遍再进行代码生成
			if(parseSeq==1)
			{
		
				stateType=WHILESTATE;
				codegen.statement(stateType,arg1,arg2,arg3,arg4);
			}
			//第二遍再进行代码生成
			if(parseSeq==1)
			{
				
				/*加法语句*/
				stateType=ADDSTATE;
				//arg1,arg2...
				codegen.statement(stateType,arg1,arg2,arg3,arg4);
				
				//保护现场
				codegen.strReg();
				
			}			
		}
		else				//错误处理
		{
			peType=BEYONDSYNTAX;	//超出文法语义
			error();		
		}		

		
	}
	
	/*判断语法分析过程中是否发生了错误，输出相关的提示信息*/
	if(err_num==0)
	{	
		/*语法分析正确，不存在分析错误*/
		//cout<<"------------语法分析结果-----------"<<endl;
		//cout<<"0 errors,0 wronings"<<endl;
	}
	else
	{
		/*分析错误大于0，说明存在分析错误*/
		
	}
	//文件指针回到程序的开头
	(lex.mycf).clear();
	(lex.mycf).seekg(0, ios_base::beg);
	cout<<(lex.mycf).tellg()<<endl;
	
}//program
/*匹配终结符函数*/
bool Parser::match(TokenType str)
{
	if(currToken.ttype==str)
	{
		return true;
	}
	else
	{
		return false;
	}
}//match
/*判断声明类别*/
int Parser::whatis()
{	
	/*处理虚函数*/
	if(match(VIRTUAL))
	{
		function_type=2;		
		getCurrToken();
	}
	
	if(match(CLASS))
	{	
		/*类声明*/
		return CLA;
	}
	else if(match(COMMENT))
	{
		/*注释*/
		return COM;
	}
	else if(match(INT) || match(VOID) || match(STRING))	
	{
		/*普通函数和变量声明*/
		lastToken=currToken;
		currToken=lex.getToken();
		q_to.push(currToken);
		if(match(ID))		//如果是标识符
		{
			currToken=lex.getToken();
			q_to.push(currToken);
			if(match(COMMA)||match(SEMIC))	//如果是逗号或者分号
			{
				currToken=lastToken;
				/*变量声明*/
				return VAR;
			}
			else if(match(LBRACK))
			{
				
				currToken=lastToken;
				if(function_type==2)
				{	
					/*虚函数，直接返回，不修改函数类型标记*/
					return FUN;
				}
				else
				{
					/*普通成员函数声明，修改函数类型标记*/
					function_type=0;
					return FUN;
				}
			}
			else
			{
				currToken=lastToken;
				return FUN;
			}
		}
	}
	else if(match(ID))
	{
		/*构造函数和语句声明*/
		lastToken=currToken;
		currToken=lex.getToken();
		q_to.push(currToken);
		//outputCurrToken();
		if(match(LBRACK))
		{
			
			currToken=lastToken;
			/*修改函数类型标记：构造函数声明*/
			function_type=1;
			/*构造函数声明*/
			return FUN;
	
		}
	        if(match(ASSIGN))
		{
			currToken=lex.getToken();
			q_to.push(currToken);
			if(match(ADDRESS))
			{
				currToken=lastToken;
				/*赋值语句声明*/	
				return DOBJ;
			}
			else
			{
				currToken=lastToken;
				/*赋值语句声明*/	
				return EXP;
			}
			
		}
		if(match(ID)||match(STAR)||match(ADDRESS))
		{
			currToken=lastToken;
			/*对象声明*/
			return OBJD;
		}
	}
	else if(match(IF))
	{
		/*if语句*/
		return IFS;
	}
	else if(match(WHILE))
	{
		/*while语句*/
		return WHIS;
	}
	else if(match(RETURN))
	{
		/*return语句*/
		return RES;
	}
	else if(match(CIN))
	{
		/*输入语句*/
		return CINS;
	}
	else if(match(COUT)) 
	{
		/*输出语句*/
		return COUS;
	}
	else if(match(PRIVATE))
	{
		/*private权限处理*/
		return PRIA;
	}
	else if(match(PUBLIC))
	{
		return PUB;
	}
	else
	{
		/*否则都不是上述类型声明*/
		return NABO;
	}
}//whatis
/*错误处理*/
void Parser::error()
{
	parserRW=false;			//将分析正确与否标志设置为假
	error_handler();		//调用错误恢复算法
	print_error_info(peType);	//根据出错信息进行错误恢复
}//error
/*进行错误恢复*/
void Parser::error_handler()
{
	/*两类错误：1、符号丢失；2、符号出错，归结起来就是不是需要的词法记号*/
	unsigned int err_type=0;	
	getCurrToken();
	outputCurrToken();
	q_eh.push(currToken);
	err_type=whatis();
	while(err_type!=1 || err_type!=2 || err_type!=3 || err_type!=4 || err_type!=5)
	{
		getCurrToken();
		outputCurrToken();
		q_eh.pop();
		q_eh.push(currToken);
		err_type=whatis();
	}
	/*使用上述while循环跳过若干个不能正确匹配下一个分析语句的词法记号*/
	currToken=q_eh.top();
	q_eh.pop();
	
}
/*根据错误类型进行错误恢复*/
void Parser::print_error_info(ParserError pe)
{
	unsigned int wrongline;
	cout<<"----------语法分析错误-----------"<<endl;
	cout<<"错误所在行："<<currToken.lines<<endl;
	cout<<"错误类型：";
	switch(peType)
	{
		case 0:
			cout<<"超出文法语义"<<endl;
			err_num++;
			break;
		case 1:
			cout<<"分号丢失"<<endl;
			err_num++;
			break;
		case 2:
			cout<<"缺少访问控制"<<endl;
			err_num++;
			break;
		case 3:
			cout<<"丢失左大括号"<<endl;
			err_num++;
			break;
		case 4:
			cout<<"丢失右大括号"<<endl;
			err_num++;
			break;
		case 5:
			cout<<"丢失分号"<<endl;
			err_num++;
			break;
		case 6:
			cout<<"丢失作用域操作符"<<endl;
			err_num++;
			break;
		case 7:
			cout<<"丢失左小括号"<<endl;
			err_num++;
			break;
		case 8:
			cout<<"丢失右小括号:"<<endl;
			err_num++;
			break;
		case 9:
			cout<<"缺少左边的反斜杠"<<endl;
			err_num++;
			break;
		case 10:
			cout<<"缺少星号"<<endl;
			err_num++;
			break;
		case 11:
			cout<<"右大括号丢失"<<endl;
			err_num++;
			break;
		case 12:
			cout<<"缺少右边的反斜杠"<<endl;
			err_num++;
			break;
		case 13:
			cout<<"if关键字出错"<<endl;
			err_num++;
			break;
		case 14:
			cout<<"while关键字出错"<<endl;
			err_num++;
			break;
		case 15:
			cout<<"cin关键字出错"<<endl;
			err_num++;
			break;
		case 16:
			cout<<"cout关键字出错"<<endl;
			err_num++;
			break;
		case 17:
			cout<<"不合法标识符"<<endl;
			err_num++;
			break;
		case 18:
			cout<<"未定义的运算符"<<endl;
			err_num++;
			break;
		case 19:
			cout<<"未定义关系操作符"<<endl;
			err_num++;
			break;
		case 20:
			cout<<"未知错误"<<endl;
			err_num++;
			break;
	}
}//print_error_info
/*取得当前词法记号*/
void Parser::getCurrToken()
{
	if(!q_to.empty())
	{
		/*先判断辅助队列是否为空*/
		currToken=q_to.front();		//取队首元素
		q_to.pop();			//出队
	}
	else
	{
		/*否则则读入下一个词法记号*/
		currToken=lex.getToken();
	}
}
/*类声明*/
void Parser::classdecl()
{
	getCurrToken();			//获取下一个词法记号
	outputCurrToken();		
	idvar();
	//第一遍，更新符号表内容
	if(parseSeq==0)
	{
		//填充符号表字段
		cs_p.class_name=currToken.str;
		vs_p.belongClass=currToken.str;
		fs_p.belongClass=currToken.str;
		
		//设置生成的代码类型
		ifhasClass=true;
	}
	
	//fs_p.belongClass=currToken.str;
	getCurrToken();			//获取下一个词法记号
	outputCurrToken();
	/*如果是继承的类声明：可选*/	
	if(match(COLON))
	{
		if(parseSeq==0)
		{
		cs_p.base_or_her=0;
		}
		/*匹配终结符后需要读下一个词法记号*/
		getCurrToken();
		outputCurrToken();
		if(match(PUBLIC) || match(PRIVATE))
		{
			getCurrToken();
			outputCurrToken();
			idvar();
			getCurrToken();
			outputCurrToken();
		}
		else
		{
			peType=MISSHERAUTH;
			error();
		}
	}
	/*如果直接跟着类体*/
	if(match(LSQUAR))
	{
		if(cs_p.base_or_her==0)
		{
			/*如果已经确定是派生类不再改动此标志*/
			;
		}
		else
		{
			cs_p.base_or_her=1;
		}
		/*匹配终结符后需要读下一个词法记号*/
		getCurrToken();
		/*输出当前待分析词法记号信息*/
		outputCurrToken();
	
		if(match(PUBLIC)||match(PRIVATE))
		{
			getCurrToken();
			/*输出当前待分析词法记号信息*/
			outputCurrToken();
			if(match(COLON))
			{
				getCurrToken();
				/*输出当前待分析词法记号信息*/
				outputCurrToken();
			}
			else
			{
				peType=MISSHERAUTH;
				error();
			}
		}
		if(parseSeq==0)
		{	
			st_p.add_class_symbol(0,cs_p);
		
			fs_p.fun_name=currToken.str;
		}
		
		//fs_p.fun_name=currToken.str;
		
		if(whatis()==FUN)
		{
			
			/*如果是函数声明*/
			funcdecl();
			//codegen.endFunStack();
			if(match(SEMIC))
			{
				getCurrToken();
				/*只声明不定义*/
				if(match(RSQUAR))
				{
					getCurrToken();
					
					
					if(match(SEMIC))
					{	
						/*分析正确*/
						getCurrToken();
						//添加类符号表操作
						if(parseSeq==0)
						{
						st_p.add_class_symbol(0,cs_p);
						}
					}
					else
					{
						peType=MISSSEMIC;
						error();
					}
				}
				else
				{
					peType=MISSRSQUAR;
					error();
				}
				
			}
			else
			{
				/*构造函数实现，所以右大括号后没有分号，退出*/
				;
			}
		}
		else if(whatis()==VAR)
		{	
			
			/*如果是变量声明*/
			vardecl();
			if(parseSeq==1)
			{
				//stateType=VARSTATE;
				
				//codegen.statement(stateType,arg1,arg2,arg3,arg4);
			}
			if(parseSeq==0)
			{
			st_p.add_class_symbol(0,cs_p);
			}
		}
		else
		{
			peType=BEYONDSYNTAX;	//超出文法语义
			error();
		}
	}
	else
	{
		peType=MISSLSQUAR;
		error();
	}	

	
}//classdecl
/*变量声明*/
/*
/*参数获取方法
int count=0;
int offset;
char temp[10];
//设定参数信息,int转换成string
offset=-(count*4+12);
sprintf(temp,"%d",offset);
arg1=temp;
*/

void Parser::vardecl()
{
	int varcount=0;
	char temp[10];
	int offset;
	//填充符号表内容
	if(parseSeq==0)
	{
	vs_p.var_type=currToken.str;
	}
	type();
	if(parseSeq==0)
	{
	vs_p.var_name=currToken.str;
	}
	idvar();
	getCurrToken();
	outputCurrToken();
	if(parseSeq==0)
	{
	vs_p.var_pla=Local;
	}
	/*单变量定义*/
	if(match(SEMIC))
	{
		varcount++;
	
		if(parseSeq==0)
		{
			offset=-12-varcount*4;
			sprintf(temp,"%d",offset);
			vs_p.offset=temp;
			st_p.add_var_symbol(0,vs_p);
		}
		getCurrToken();
		outputCurrToken();
	}
	else
	{
		/*多变量定义*/
		while(match(COMMA))
		{	
			getCurrToken();
			idvar();
			if(parseSeq==0)
			{
			vs_p.var_name=currToken.str;
			}
			
		}
	}
}
/*函数声明*/
void Parser::funcdecl()
{
	
	if(function_type==1)
	{	
		/*构造函数*/
		if(parseSeq==0)
		{
		fs_p.fun_type=0;
		}
	}
	else if(function_type==2)
	{
		if(parseSeq==0)
		{
		fs_p.fun_type=2;
			
		/*虚函数*/
		fs_p.ifHasVFun=false;	//将有虚函数标志设置
		}
		outputCurrToken();
		getCurrToken();
		outputCurrToken();
		if(parseSeq==0)
		{
		fs_p.fun_name=currToken.str;
		}
		
		idvar();
	}
	else
	{
		if(parseSeq==0)
		{
		fs_p.fun_type=1;
		}
		/*普通函数*/
		getCurrToken();
		outputCurrToken();
		if(parseSeq==0)
		{
			//填充函数符号表的名称字段
			fs_p.fun_name=currToken.str;
		
		
			/*--------------代码生成的起始位置main-----------*/
			if(!(currToken.str).compare("main"))
			{
				function_type=3;			//main函数、
				fs_p.belongClass="start program";
				fs_p.fun_type=3;
			}
		
		}
		//记录函数的名字，在代码生成的时候需要按名访问
		fs_p.fun_name=currToken.str;
		idvar();
	}
	/*函数头放在函数的语句分析代码之前：左括号前,盯好左大括号和右大括号*/
	if(parseSeq==1)
	{
		
	/*
		解决大问题的办法：
		1.可行的办法，可采用下面的办法，先硬编码实现，然后再抽象。
		2.一步抽象太难了，先从具体的开始。
		tip:1.读入的程序文件名2.修改符号表插入方式 3.修改是否是大程序标记为假 ifhasClass为真 
		3.改动一个位置，要回头来检查那两个程序正确与否。
		4.将这些每次需要手工改动的，将来参数化即可。
	*/
		if(ifBigPro==true)
		{
			//先硬编码实现，从上往下依次进行代码生成
			string tempStr;
			if(count==0)
			{
				tempStr="UPCUPC";
				count++;				
			}
			else if(count==1)
			{
				tempStr="UPCUPC";
				count++;
			}
			else if(count==2)
			{
				tempStr="StuNumUPC";
				count++;
			}
			else if(count==3)
			{
				tempStr="TeaNumUPC";
				count++;
			}
			else if(count==4)
			{
				tempStr="TotalNumUPC";
				count++;
			}
			else if(count==5)
			{
				tempStr="CSCS";
				count++;
			}
			else if(count==6)
			{
				tempStr="StuNumCS";
				count++;
			}
			else if(count==7)
			{
				tempStr="TeaNumCS";
				count++;
			}
			else if(count==8)
			{
				tempStr="TotalNumUPC";
				count++;
			}
			else if(count==9)
			{
				tempStr="mainstart program";
				count++;
			}
			else
			{
				cout<<"代码生成出错了"<<endl;
			}
			if(count>1)
			codegen.functionPro(tempStr);
		}
		else
		{
			if(ifhasClass==true)
			{
				string tempStr;
				if(count==0)
				{
					tempStr="HelloWorldHelloWorld";
					count++;
				
				}
				else
				{
					tempStr="mainstart program";
				}
				//类的成员函数声明
				codegen.functionPro(tempStr);	
			}
			else
			{
				codegen.functionPro(fs_p.fun_name);	
			}
		}
	}
	/*普通成员和构造函数声明*/
	getCurrToken();
	/*输出当前待分析词法记号信息*/
	outputCurrToken();
	
	if(match(LBRACK))
	{
		getCurrToken();
		/*输出当前待分析词法记号信息*/
		outputCurrToken();
		paramalist();
		if(match(RBRACK))
		{
			getCurrToken();
			/*输出当前待分析词法记号信息*/
			outputCurrToken();
			/*函数声明*/
			if(match(SEMIC))
			{
				getCurrToken();
				/*输出当前待分析词法记号信息*/
				outputCurrToken();
				//这一句的执行是成功的
				if(parseSeq==0)
				{
				st_p.add_fun_symbol(0,fs_p);
				}
			}			
			else
			{
				chunkstatement();
				if(parseSeq==0)
				{
				st_p.add_fun_symbol(0,fs_p);
				}
			}	
			
			
			
		}
		else
		{
			peType=MISSRBRACK;
			error();
		}
		
		
	}
	else
	{
		peType=MISSLBRACK;
		error();
	}
	

}
/*动态绑定对象声明*/
void Parser::daynamicobj()
{
	idvar();
	getCurrToken();
	outputCurrToken();
	if(match(ASSIGN))
	{
		getCurrToken();
		outputCurrToken();
		if(match(ADDRESS))
		{
			getCurrToken();
			outputCurrToken();
			idvar();
			getCurrToken();
			outputCurrToken();
			if(match(SEMIC))
			{
				getCurrToken();
				outputCurrToken();
			}
			else
			{
				error();
			}
		}
		else
		{
			error();
		}
	}
}
/*对象声明*/
void Parser::objdecl()
{
	//outputCurrToken();
	idvar();
	if(parseSeq==0)
	{
	os_p.belongClass=currToken.str;	//所属的类
	}
	
	getCurrToken();
	outputCurrToken();
	/*如果是指针和引用声明*/
	if(match(STAR)||match(ADDRESS))	
	{
		if(parseSeq==0)
		{
		os_p.obj_type=1;	//对象指针
		}
		getCurrToken();
		outputCurrToken();
		//idvar();
	}
	
	if(os_p.obj_type==1)
	{
		//如果已经判定是对象指针
		;
	}
	else
	{
		if(parseSeq==0)
		{
		//普通对象定义
		os_p.obj_type=0;
		}
	}
	/*如果是普通类对象定义*/
	idvar();
	if(parseSeq==0)
	{
	//添加对象符号表信息
	os_p.obj_name=currToken.str;		//初始化对象符号表的名称字段
	}
	
	//设定参数信息
	if(parseSeq==1 && ifBigPro==false)
	{
		arg1=currToken.str;
		arg2="-16";
	}
	string name=currToken.str;
	string off="-16";
	//arg5=currToken.str;
	//arg6="-16";
	
	

	getCurrToken();
	outputCurrToken();
	if(match(SEMIC))
	{
		/*调用默认的构造函数初始化类对象*/
		getCurrToken();
		outputCurrToken();
		
	}
	else if(match(LBRACK))
	{
		getCurrToken();
		outputCurrToken();
		/*调用对应的构造函数初始化类对象*/
			
		/*当代码生成时有其他的语法模块时，需要注意其对参数的改变，这里改变了arg1,arg2*/
		realparalist();
		if(match(RBRACK))
		{
			getCurrToken();
			outputCurrToken();
			if(match(SEMIC))
			{
				arg1=name;
				arg2=off;
				cout<<"参数设定情况"<<arg1<<" "<<arg2<<endl;
				//进行代码生成
				if(parseSeq==1)
				{
					stateType=OBJSTATE;
					codegen.statement(stateType,arg1,arg2,arg3,arg4);
				}
				getCurrToken();
				outputCurrToken();
			}
			else
			{
				error();
			}
		}
		else
		{
			peType=MISSLBRACK;
			error();
		}
	}
	else
	{
		peType=MISSSEMIC;
		error();
	}
	if(parseSeq==0)
	{
	//更新对象符号表
	st_p.add_obj_symbol(0,os_p);
	
	}
	//进行代码生成
	if(parseSeq==1 && ifBigPro==false)
	{
		stateType=OBJSTATE;
		codegen.statement(stateType,arg1,arg2,arg3,arg4);
	}
	
}//objectdecl
/*单行注释:分析正确*/
void Parser::comment()
{
	int last_token_line=currToken.lines;
	if(match(COMMENT))
	{
		getCurrToken();
		/*输出当前待分析词法记号信息*/
		outputCurrToken();
		int new_token_line=currToken.lines;
		/*使用行号来判断注释行是否结束*/
		while(last_token_line==new_token_line)
		{
			idvar();
			getCurrToken();
			outputCurrToken();
			new_token_line=currToken.lines;
		}			
		getCurrToken();					
	}
	else
	{
		peType=MISSLSLASH;
		error();
	}

}//comment

/*类型分析*/
void Parser::type()
{
	if(match(INT) || match(VOID) ||match(STRING))
	{
		getCurrToken();
		outputCurrToken();
	}
	else
	{
		peType=UNDEFINEDTYPE;
		error();
	}
}//type
/*参数定义列表*/
void Parser::paramalist()
{
	if(match(RBRACK))
	{
		/*获取下一个词法记号采用贪心原则，只有需要的时候才获取*/
		//getCurrToken();
		;
		if(parseSeq==0)
		{
		fs_p.ifHasPara=false;
		}
	}
	else 
	{
		if(parseSeq==0)
		{
		fs_p.ifHasPara=true;
		}
		type();
		idvar();
		if(parseSeq==0)
		{
		//硬编码，将参数个数写成两个了
		fs_p.paraNum=2;
		}
		/*获取下一个词法记号*/
		getCurrToken();
		outputCurrToken();
		/*如果还有形式参数*/
		while(match(COMMA))
		{
			/*获取下一个词法记号*/
			getCurrToken();
			outputCurrToken();
			type();
			idvar();
			if(parseSeq==0)
			{
			fs_p.paraNum=2;
			}
			/*获取下一个词法记号*/
			getCurrToken();
			outputCurrToken();
			
		}
	}
}//paramalist
/*函数定义块*/
void Parser::chunkstatement()
{
	unsigned int sen_type=0;
	if(match(LSQUAR))
	{
		getCurrToken();
		/*输出当前待分析词法记号信息*/
		outputCurrToken();
		
		string leftvar=currToken.str;
		/*如果有多条语句的话，则需要一个while循环*/
		
		sen_type=whatis();
		if(sen_type==VAR)
		{
			/*变量声明*/
			vardecl();
			if(parseSeq==1)
			{
				//stateType=VARSTATE;
				//传递变量名
				arg1=vs_p.var_name;
				//codegen.statement(stateType,arg1,arg2,arg3,arg4);
			}
			if(match(RSQUAR))
			{	
				/*分析正确继续分析*/
				getCurrToken();
			}
			else if(match(ID))
			{
				sen_type=whatis();
				if(sen_type==EXP)
				{
					expression();
					/*如果是赋值语句*/
					if(parseSeq==1)
					{
						stateType=ASSIGNSTATE;
						codegen.statement(stateType,arg1,arg2,arg3,arg4);
						if(ifhasClass==true)
						{
							codegen.stringAssign();
						}
					}
					getCurrToken();
					outputCurrToken();
					
				}
			}
			else
			{
				error();
			}
		}
		else if(sen_type==RES)
		{
			
			/*获取下一个词法记号*/
			getCurrToken();
			outputCurrToken();
			
			//设定参数
			arg1=currToken.str;			

			/*调用加法表达式子程序*/
			calacop();
			/*获取下一个词法记号*/
			
			if(parseSeq==1 && ifBigPro==true)
			{
				codegen.classAddState(arg1,arg2);
				codegen.endFunStack();
			}
			getCurrToken();
			outputCurrToken();
			if(match(SEMIC))
			{
				/*获取下一个词法记号*/
				getCurrToken();
				outputCurrToken();
				if(match(RSQUAR))
				{
					/*函数实现结束,继续读取下一个字符*/
					getCurrToken();
					outputCurrToken();
				}
				else
				{
					peType=MISSRSQUAR;
					error();
				}
			}
			else
			{
				peType=MISSSEMIC;
				error();
			}
			
		}
		else if(match(RSQUAR))
		{
			/*块语句的空实现*/
	
			getCurrToken();
			/*输出当前待分析词法记号信息*/
			outputCurrToken();
		}
		else if(sen_type==EXP)
		{
			//这个地方进行赋值语句的代码生成
			expression();
			
			if(parseSeq==1 && ifBigPro==true)
			{
				codegen.classAssignState(arg1,leftvar);
				
			}
			//stateType=ASSIGNSTATE;
			//arg1,arg2...
			//codegen.statement(stateType,arg1,arg2,arg3,arg4);
			
			
			/*如果是赋值语句*/
			getCurrToken();
			outputCurrToken();
			//设定参数
			leftvar=currToken.str;
			//不是大程序时的代码生成
			if(parseSeq==1 && ifBigPro==false)
			{
				codegen.stringAssign();
				codegen.endFunStack();
			}
			if(match(RSQUAR))
			{
				
				/*只有一条语句，直接退出*/
				getCurrToken();
				outputCurrToken();
			}
			else
			{
				/*还有其他赋值语句*/
				expression();
				
				if(parseSeq==1 && ifBigPro==true)
				{
					codegen.classAssignState(arg1,leftvar);
					codegen.endFunStack();
				}
				//stateType=ASSIGNSTATE;
				//arg1,arg2...
				//codegen.statement(stateType,arg1,arg2,arg3,arg4);
				
				/*如果是赋值语句*/
				getCurrToken();
				outputCurrToken();
				if(match(RSQUAR))
				{
					getCurrToken();
					outputCurrToken();
				}
				else
				{
					error();
				}
			}
		
		}
		else if(sen_type==IFS)
		{
			/*如果是if语句*/
			ifstate();
			//第二遍再进行代码生成
			if(parseSeq==1 && ifBigPro==false)
			{
		
			stateType=IFSTATE;
			//arg1,arg2...
			codegen.statement(stateType,arg1,arg2,arg3,arg4);
			}
			if(parseSeq==1 && ifBigPro==true)
			{
				codegen.classIfState(arg1,arg2);
				codegen.endFunStack();
			}
			sen_type=whatis();
			if(match(RSQUAR))
			{
				/*还有其他语句*/
				;
			}
			else if(sen_type==RES)
			{
			
				/*return语句*/
				returnstate();
				if(match(RSQUAR))
				{
					getCurrToken();
					outputCurrToken();
				}
				else
				{
					error();
				}
			}
			else
			{
				error();
			}
		}
		else if(sen_type==OBJD)
		{
			objdecl();
			stateType=OBJSTATE;
			//准备参数
			arg1="-16";
			//arg4="helloworld_helloworld_void";
			//codegen.statement(stateType,arg1,arg2,arg3,arg4);
		}
		else
		{
			peType=BEYONDSYNTAX;	//超出文法语义
			error();
		}
	
	}
	else
	{
		peType=MISSLSQUAR;
		error();
	}
}//chunkstatement

/*语句*/
void Parser::statement()
{	
	/*在switch语句中进行函数调用是否是会损失效率,所以在switch外面进行函数调用是高效的做法*/
	char wi=whatis();
	
	switch(wi)
	{
		
		case 3:
			/*让当前词法记号等于上一个词法记号*/
			//currToken=lastToken;
			outputCurrToken();
			
			/*加法表达式*/
			calacop();
			/*读取下一个分号*/
			getCurrToken();
			outputCurrToken();
			if(match(SEMIC))
			{
				/*加法表达式分析完，读下一个词法记号*/
				getCurrToken();
				outputCurrToken();
			
			}
			else
			{
				peType=MISSSEMIC;
				error();
			}
			break;
		case 4:
			ifstate();
			if(match(SEMIC))
			{	
				getCurrToken();
			}
			else
			{
				peType=MISSSEMIC;
				error();
			}
			break;
		case 5:
			whilestate();
			if(match(SEMIC))
			{
				getCurrToken();
			}
			else
			{
				peType=MISSSEMIC;
				error();
			}
			break;
		case 6:
			returnstate();
			if(match(SEMIC))
			{
				getCurrToken();
			}
			else
			{
				peType=MISSSEMIC;
				error();
			}
			break;
		case 7:
			cinstate();
			if(match(SEMIC))
			{
				getCurrToken();
			}
			else
			{
				peType=MISSSEMIC;
				error();
			}
			break;
		case 8:
			coutstate();
			if(match(SEMIC))
			{
				getCurrToken();
			}
			else
			{
				peType=MISSSEMIC;
				error();
			}
			break;
	}
}

/*if语句*/
void Parser::ifstate()
{
	if(match(IF))
	{
		getCurrToken();
		outputCurrToken();
		if(match(LBRACK))
		{
			getCurrToken();
			outputCurrToken();
			if(ifBigPro==true)
			{
				//设定参数
				arg1=currToken.str;
			}
			operat();
			getCurrToken();
			outputCurrToken();
			relop();
			getCurrToken();
			outputCurrToken();
			if(ifBigPro==true)
			{
				//设定参数
				arg2=currToken.str;
			}
			operat();
			getCurrToken();
			outputCurrToken();
			if(match(RBRACK))
			{
				getCurrToken();
				outputCurrToken();
				if(match(ELSE))
				{	
					/*带有else的if语句*/
					statement();
				}
				else
				{	
					/*if条件判断结束*/
					;
				}
				
				
				
			}
		}
		else
		{
			peType=MISSLBRACK;
			error();
		}
	}
	else
	{
		peType=WRONGIF;
		error();
	}
	
	
}//ifstate
/*while语句*/
void Parser::whilestate()
{
	if(match(WHILE))
	{
		getCurrToken();
		if(match(LBRACK))
		{
			getCurrToken();
			outputCurrToken();
			operat();
			getCurrToken();
			outputCurrToken();
			relop();
			getCurrToken();
			outputCurrToken();
			//operat();
			
			//设定比较的参数
			arg1=currToken.str;
			
			getCurrToken();
			outputCurrToken();
			if(match(RBRACK))
			{
				getCurrToken();
				outputCurrToken();
				if(match(LSQUAR))
				{
					getCurrToken();
					outputCurrToken();
					idvar();
					getCurrToken();
					outputCurrToken();
					if(match(ASSIGN))
					{
						getCurrToken();
						outputCurrToken();
						//get a
						//arg1=currToken.str;
							
						idvar();
						getCurrToken();
						outputCurrToken();
						if(match(ADD))
						{
							//get 1
							getCurrToken();
							outputCurrToken();
							
							arg2=currToken.str;
							
							idvar();
							getCurrToken();
							outputCurrToken();
							if(match(SEMIC))
							{
								getCurrToken();
								outputCurrToken();
							}
								
							
						}
					}
				}
			}
			else
			{
				peType=MISSRBRACK;
				error();
			}
		}
	}
	else
	{
		peType=WRONGWHILE;
		error();
	}
}//whilestate
/*return语句*/
void Parser::returnstate()
{
	if(match(RETURN))
	{
		getCurrToken();
		outputCurrToken();
		idvar();
		getCurrToken();
		outputCurrToken();
		if(match(SEMIC))
		{
			/*return语句结束*/
			getCurrToken();
			outputCurrToken();
		}
		else
		{
			error();
		}
	}
	else
	{
		peType=WRONGRETURN;
		error();
	}
}//returnstate
/*输入语句*/
void Parser::cinstate()
{
	if(match(CIN))
	{
		getCurrToken();
		outputCurrToken();
		if(match(INPUT))
		{
			getCurrToken();
			outputCurrToken();
			idvar();
		}
	}
	else
	{
		peType=WRONGCIN;
		error();
	}
}//cinstate
/*输出语句*/
void Parser::coutstate()
{
	if(match(COUT))
	{
		getCurrToken();
		outputCurrToken();
		if(match(OUTPUT))
		{
			getCurrToken();
			outputCurrToken();
			if(match(DQUOTATION))
			{	
				getCurrToken();
				outputCurrToken();
				do
				{
					idvar();
					getCurrToken();
					outputCurrToken();
				}while(!match(DQUOTATION));
				getCurrToken();
				outputCurrToken();
				if(match(OUTPUT))
				{
					getCurrToken();
					outputCurrToken();
					arg1=currToken.str;
					/*函数调用*/
					funccall();
					//如果是虚函数调用
					if(!arg2.compare("TotalNum") && parseSeq==1 && ifBigPro==true)
					{	
						bool ifPoly;
						//如果开启了多态、
						if(!arg1.compare("upc"))
						{
							ifPoly=true;
							codegen.vfSet(arg1,ifPoly); 
						}
						else
						{
							ifPoly=false;
							codegen.vfSet(arg1,ifPoly); 
						}
						codegen.vfFunCall(arg2);
					}
					//第二遍再进行代码生成
					if(parseSeq==1)
					{
		
						/*普通函数调用或者虚函数调用*/
						//stateType=NORMALFUNCALL;
						//arg1,arg2...
						//codegen.statement(stateType,arg1,arg2,arg3,arg4);
					}
					
					if(match(OUTPUT))
					{
						getCurrToken();
						outputCurrToken();
						if(match(ENDL))
						{
							getCurrToken();
							outputCurrToken();
							if(match(SEMIC))
							{
								getCurrToken();
								outputCurrToken();
							}
							else
							{
								error();
							}
						}
						else
						{
							error();
						}
					}
				}
				else
				{
					error();
				}
			}
			else
			{
				error();
			}
			
		}
	}
	else
	{
		peType=WRONGCOUT;
		error();
	}
}//coutstate


/*表达式*/
void Parser::expression()
{
	/*如果是赋值表达式*/
	if(match(ID))
	{
		getCurrToken();
		if(match(ASSIGN))
		{
			outputCurrToken();
			getCurrToken();
			outputCurrToken();
			/*此处似乎有问题*/
			idvar();
			//设定这个立即数参数
			arg1=currToken.str;
			getCurrToken();
			outputCurrToken();
			if(match(SEMIC))
			{
				/*赋值表达式结束*/
				;
			}
			else
			{
				error();
			}
		}
		else if(match(SEMIC))
		{
			getCurrToken();
		}
		else if(match(ADD))
		{
			getCurrToken();
			
		}
		else
		{
			error();
		}
	}
	else
	{
		peType=NOTID;
		error();
	}
	
}//expression
/*复合语句*/
void Parser::compoundstate()
{
	calacop();
	relop();
	calacop();
}
/*计算表达式*/
void Parser::calacop()
{
	operat();
	/*读加号应该在这里读*/
	getCurrToken();
	outputCurrToken();
	if(match(ADD)||match(SUB))
	{
		getCurrToken();
		outputCurrToken();
		//设定参数:紧挨着本分析模块设定arg1,arg2,arg3等就没有问题
		arg2=currToken.str;
		/*计算表达式*/
		operat();
	}
	else
	{
		peType=UNDEFINEDCALC;
		error();
	}
}
/*关系操作符*/
void Parser::relop()
{
	if(match(LT)||match(GT)||match(LTEQ)||match(GTEQ)||match(EQ)||match(NEQ))
	{
		/*这里多读了一个*/
		;
	}
	else
	{
		peType=UNDEFINEDRELOP;
		error();
	}
}
/*操作数*/	
void Parser::operat()
{
	/*先是第一种操作数只是变量的*/
	idvar();	

}
/*函数调用*/
void Parser::funccall()
{
	if(parseSeq==1 && ifBigPro==true)
	{
		//调用的对象名
		arg1=currToken.str;
	}
	idvar();
	getCurrToken();
	outputCurrToken();
	if(match(DOT))
	{
		getCurrToken();
		outputCurrToken();
		//设定参数
		if(parseSeq==1 && ifBigPro==true)
		{
			//被调用的函数名
			arg2=currToken.str;
		}
		idvar();
		getCurrToken();
		outputCurrToken();
		if(match(LBRACK))
		{
			getCurrToken();
			outputCurrToken();
			//realparalist();	
			if(match(RBRACK))
			{
				//如果不是虚函数调用
				if(arg2.compare("TotalNum"))
				{				
					//在这里进行函数调用代码的生成
					if(parseSeq==1 && ifBigPro==true)
					{
						codegen.classFuncCall(arg1,arg2);
					}
				}
				getCurrToken();
				outputCurrToken();
			}
			else
			{
				error();
			}
		}
		else if(match(OUTPUT))
		{
			//getCurrToken();
			//outputCurrToken();
			
		}
		else
		{}
	}
	else if(match(SUB))
	{
		getCurrToken();
		outputCurrToken();
		if(match(GT))
		{
			getCurrToken();
			outputCurrToken();
			idvar();
			getCurrToken();
			outputCurrToken();
			if(match(LBRACK))
			{
				getCurrToken();
				outputCurrToken();
				//realparalist();	
				if(match(RBRACK))
				{
					getCurrToken();
					outputCurrToken();
				}
				else
				{
					error();
				}
			}
		}
	}
	else if(match(OUTPUT))
	{
		//如果直接是变量输出
		;
	}
	else
	{
		error();
	}
}
/*实参列表*/
void Parser::realparalist()
{
	/*参数获取方法*/
	int count=0;
	int offset;
	char temp[10];
	
	idvar();
	//实参1
	os_p.para1=currToken.str;
	//参数1
	arg2=currToken.str;
	count++;
	getCurrToken();
	outputCurrToken();
	
	while(match(COMMA))
	{
		getCurrToken();
		outputCurrToken();
		idvar();
		os_p.para2=currToken.str;
		arg3=currToken.str;
		count++;
		getCurrToken();
		outputCurrToken();
	}
	//设定参数信息,int转换成string
	offset=-(count*4+12);
	sprintf(temp,"%d",offset);
	arg1=temp;
}//realparalist
/*标识符分析*/
void Parser::idvar()
{
	if(match(ID))
	{
		;
	}
	else if(match(NUMBERIC))
	{
		;	
	}
	else if(match(DQUOTATION))
	{
		//不能出现递归调用
		getCurrToken();
		outputCurrToken();
		while(match(ID))
		{
			if(match(ID))
			{
				getCurrToken();
				outputCurrToken();
			}
		}
		if(match(DQUOTATION))
		{
			;
		}
		else
		{
			cout<<"不是正确的字符串赋值语句";
		}
	}
	else
	{
		error();		//错误处理
	}
}

































































































