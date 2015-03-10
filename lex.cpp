#include "lex.h"

/*全局变量区*/
Token token;					//声明一个词法记号指针
char ch;					//用于接收每次返回的字符

/*扫描器*/
int Lex::scanner()
{
	if(mycf.is_open())
	{
		/*先读一个，解决判断文件结束多读一个字符问题*/
		mycf.getline(buffer,80,'\n');
		if(!mycf.eof())		//文件打开成功
		{

			linenumber++;		//行号加1
			readPos=0;		//将读写指针清0
		}
		else				//文件读写完毕
		{
			endOfFlag=0;
			token.str="END";
			token.ttype=ENDOFFILE;
			token.lines=linenumber;
			return -1;
		}
	}
	else
	{
		cout<<"文件打开失败"<<endl;
	}
}//scanner

/*返回当前位置的字符*/
char Lex::getCurrentChar()
{
	if(buffer[readPos+1]=='$')		//此行已分析完，读取下一行
	{

		/*刷新缓冲区,不然行缓冲区中仍然是上次存留的值*/
		for(int i=0;i<BUFFERSIZE;i++)
			buffer[i]='$';
		if(scanner())
			;
		else
			return -1;		//读取新的一行
	}

	/*每次判断是要先从输入行缓冲还是直接从现有未读完的行读取*/
	if(readPos<0 || readPos>80)		//当前位置小于0或者大于80
	{
		cout<<"readPos:"<<readPos<<endl;
		cout<<"出现了溢出"<<endl;
		return -1;
	}
	else					//读位置合法,隐含读指针自动加1
	{
		if(buffer[readPos]=='$')
			return -1;
		else
			return buffer[readPos++];
	}


}//getCurrentChar

/*返回当前位置的下一个位置的字符*/
char Lex::getNextChar()
{
	nextPos=readPos;
	if(nextPos<80)
		return buffer[nextPos];
	else
	{
		cout<<"已经读到行缓冲区的最后"<<endl;
		return -1;
	}
}//getNextChar

/*词法记号装配器*/
Token Lex::buildToken(string str,TokenType ttype,int lines)
{
	token.str=str;
	token.ttype=ttype;
	token.lines=lines;

	return token;
}//buildToken


/*词法分析主程序*/
Token Lex::getToken()				//词法分析器和语法分析器的接口,识别单词类型
{
	char nextCh;				//下一个位置的字符
	string str="";				//声明一个空串用来存储这个标识符
	ch=getCurrentChar();			//先读取一个字符
	int lastline;
	lastline=linenumber;			//处理两行标识符相连的情况

	/*过滤掉空白字符，空格，制表符,由于每次读取一行，所以不存在换行符*/
	while(ch==' '|| ch=='\t'||ch=='\n')
	{
		ch=getCurrentChar();		//继续读取下一个字符
	}

	/*如果是以字母或者下划线开头，则表示是标识符（关键字） a~z、A~Z、_*/
	if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch=='_')
	{
		/*标识符*/
		do
		{
			if(linenumber>lastline)
				break;
			str.push_back(ch);	//将这个字符添加到str中
			ch=getCurrentChar();	//继续返回下一个字符


		}while(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch=='_');

		/*do-while循环会多取一个非ID或关键字的字符，所以读写指针应该回退1,好隐蔽*/
		readPos=readPos-1;

		//处理关键字compare函数，相等时返回0
		if(!str.compare("if"))		//if
		{
			token.str=str;
			token.ttype=IF;
			token.lines=linenumber;
		}
		else if(!str.compare("else"))	//else
		{
			token.str=str;
			token.ttype=ELSE;
			token.lines=linenumber;
		}
		else if(!str.compare("while"))	//while
		{
			token.str=str;
			token.ttype=WHILE;
			token.lines=linenumber;
		}
		else if(!str.compare("return"))	//return
		{
			token.str=str;
			token.ttype=RETURN;
			token.lines=linenumber;
		}
		else if(!str.compare("void"))	//void
		{
			token.str=str;
			token.ttype=VOID;
			token.lines=linenumber;
		}
		else if(!str.compare("int"))	//int
		{
			token.str=str;
			token.ttype=INT;
			token.lines=linenumber;
		}
		else if(!str.compare("include"))
		{
			buildToken(str,INCLUDE,linenumber);
		}
		else if(!str.compare("virtual"))
		{
			token.str=str;
			token.ttype=VIRTUAL;
			token.lines=linenumber;
		}
		else if(!str.compare("class"))
		{
			token.str=str;
			token.ttype=CLASS;
			token.lines=lastline;
		}
		else if(!str.compare("public"))
		{
			token.str=str;
			token.ttype=PUBLIC;
			token.lines=lastline;
		}
		else if(!str.compare("private"))
		{
			token.str=str;
			token.ttype=PRIVATE;
			token.lines=lastline;
		}
		else if(!str.compare("cout"))
		{
			token.str=str;
			token.ttype=COUT;
			token.lines=lastline;
		}
		else if(!str.compare("string"))
		{
			token.str=str;
			token.ttype=STRING;
			token.lines=lastline;
		}
		else if(!str.compare("cin"))
		{
			token.str=str;
			token.ttype=CIN;
			token.lines=lastline;
		}
		else if(!str.compare("endl"))
		{
			token.str=str;
			token.ttype=ENDL;
			token.lines=lastline;
		}
		else				//一般标识符
		{
			token.str=str;
			token.ttype=ID;
			token.lines=linenumber;
		}

		return token;			//返回这个词法记号

	}
	else if(ch>='0' && ch<='9')		//数字
	{
		/*只考虑10进制，需要把字符转换成数字 -48 ，暂时不转换*/
		do
		{
			str.push_back(ch);
			ch=getCurrentChar();

		}while(ch>='0' && ch<='9');

		/*do-while循环都会使得读写指针超前一个位置*/
		readPos=readPos-1;

		/*构造词法记号*/
		buildToken(str,NUMBERIC,linenumber);

		return token;			//返回这个词法记号

	}
	else 					//运算符
	{
		switch(ch)
		{

			case '\t':
				str.push_back(ch);
				buildToken(str,TAB,linenumber);
				break;
			case '$':
				str.push_back(ch);
				buildToken(str,DOLLAR,linenumber);
				break;
			case ':':
				nextCh=getNextChar();
				if(nextCh==':')	//域操作符
				{
					str.push_back(ch);
					ch=getCurrentChar();
					str.push_back(ch);
					buildToken(str,AREA,linenumber);
				}
				else
				{
					str.push_back(ch);
					buildToken(str,COLON,linenumber);
				}
				break;
			case '#':
				str.push_back(ch);
				buildToken(str,SHARP,linenumber);
				break;

			case '+':		//加号,ch是char，不能作为string类型的参数
				str.push_back(ch);
				buildToken(str,ADD,linenumber);
				break;
			case '-':		//减号
				str.push_back(ch);
				buildToken(str,SUB,linenumber);
				break;
			case '*':		//指针
				str.push_back(ch);
				buildToken(str,STAR,linenumber);
				break;
			case '/':		//除号和单行注释
				nextCh=getNextChar();
				if(nextCh=='/')	//单行注释
				{
					str.push_back(ch);
					ch=getCurrentChar();
					str.push_back(ch);
					buildToken(str,COMMENT,linenumber);
				}
				else		//除号
				{
					str.push_back(ch);
					buildToken(str,SLASH,linenumber);
				}
				break;
			case '>':		//大于和大于等于
				nextCh=getNextChar();
				if(nextCh=='>')	//小于等于
				{
					str.push_back(ch);
					ch=getCurrentChar();
					str.push_back(ch);
					buildToken(str,INPUT,linenumber);
				}
				else if(nextCh=='=')
				{
					str.push_back(ch);
					ch=getCurrentChar();
					str.push_back(ch);
					buildToken(str,GTEQ,linenumber);
				}
				else
				{
					str.push_back(ch);
					token.str=str;
					token.ttype=GT;
					token.lines=linenumber;
				}
				break;
			case '<':		//小于和小于等于
				nextCh=getNextChar();
				if(nextCh=='<')	//小于等于
				{
					str.push_back(ch);
					ch=getCurrentChar();
					str.push_back(ch);
					buildToken(str,OUTPUT,linenumber);
				}
				else if(nextCh=='=')
				{
					str.push_back(ch);
					ch=getCurrentChar();
					str.push_back(ch);
					buildToken(str,LTEQ,linenumber);
				}
				else
				{
					str.push_back(ch);
					token.str=str;
					token.ttype=LT;
					token.lines=linenumber;
				}
				break;
			case '=':		//赋值
				str.push_back(ch);
				buildToken(str,ASSIGN,linenumber);
				break;
			case '!':		//不等于
				ch=getCurrentChar();
				if(ch=='=')
				{
					str.push_back(ch);
					buildToken(str,NEQ,linenumber);
				}
				break;
			case ',':		//逗号
				str.push_back(ch);
				buildToken(str,COMMA,linenumber);
				break;
			case ';':		//分号
				str.push_back(ch);
				buildToken(str,SEMIC,linenumber);
				break;
			case '(':		//左括号
				str.push_back(ch);
				buildToken(str,LBRACK,linenumber);
				break;
			case ')':		//右括号
				str.push_back(ch);
				buildToken(str,RBRACK,linenumber);
				break;
			case '{':		//左大括号
				str.push_back(ch);
				buildToken(str,LSQUAR,linenumber);
				break;
			case '}':		//右大括号
				str.push_back(ch);
				buildToken(str,RSQUAR,linenumber);
				break;
			case '.':		//点运算符
				str.push_back(ch);
				buildToken(str,DOT,linenumber);
				break;
			case '"':
				str.push_back(ch);
				buildToken(str,DQUOTATION,linenumber);
				break;
			case '&':
				str.push_back(ch);
				buildToken(str,ADDRESS,linenumber);
				break;

		}
		/*返回词法记号*/
		return token;
	}
}//getToken





























