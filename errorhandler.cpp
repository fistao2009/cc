#include "errorhandler.h"
#include<stdlib.h>

/*返回错误类型*/
ErrorType ErrorHandler::errorType()
{
	return lackSemic;
}

/*根据错误类型调用相应的错误处理函数进行处理*/
void ErrorHandler::dealError()
{
	int errType=errorType();
	switch(errType)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			exit(-1);
			break;
	}
}
/*语法分析错误恢复算法*/
void ErrorHandler::wrongRecovery()
{
	
}			
