#ifndef TOKEN_H
#define TOKEN_H
#include<string>
using namespace std;

/*单词分类枚举*/
enum TokenType
{
	/*关键字*/
	IF,ELSE,WHILE,RETURN,VOID,INT,INCLUDE,VIRTUAL,CLASS,PUBLIC,PRIVATE,CIN,COUT,ENDL,STRING,
	/*运算符*/
	DOT,STAR,ADD,SUB,LT,LTEQ,GT,GTEQ,EQ,NEQ,ASSIGN,POINTER,
	/*界符*/
	SEMIC,COMMA,COLON,LBRACK,RBRACK,LSQUAR,RSQUAR,COMMENT,SLASH,SHARP,DOLLAR,AREA,OUTPUT,INPUT,TAB,
	DQUOTATION,ADDRESS,
	/*标识符:42*/
	ID,
	/*数字常量*/
	NUMBERIC,
	/*其他类型*/
	NONTOKEN,ERROR,ENDOFFILE
};

/*单词符号数据结构*/
class Token
{
public:
	Token(){};
	Token(string str,TokenType tt,int lines)
	{
		this->str=str;
		this->ttype=tt;
		this->lines=lines;
	}
	string str;	        	//单词字符串
	TokenType ttype;		//单词类型
	int 	lines;			//行号
};
#endif
