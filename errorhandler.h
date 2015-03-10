#ifndef ERROR_H
#define ERROR_H
#include<iostream>
using namespace std;

/*错误类型枚举*/
enum ErrorType
{
	lackSemic,lackComma,paserErrorRecovery	
};


/*错误处理和恢复*/
class ErrorHandler
{
public:
	ErrorHandler()
	{
		ifHandlerError=true;
	}
	~ErrorHandler()
	{}

	ErrorType errorType();
	void dealError();
	void wrongRecovery();			//语法分析错误恢复算法

	
private:
	bool ifHandlerError;
};

#endif
