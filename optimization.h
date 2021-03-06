#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H


/*代码优化*/

class Optimization
{
public:
	Optimization()
	{
		/*默认禁用代码优化*/
		ifOptimiza=false;
	}
	~Optimization()
	{}

	void OptiProgramCall();			//优化子程序调用
	void OptiLoop();			//循环优化
	void VectorOpti();			//标量优化
private:
	bool ifOptimiza;			//是否进行代码优化

};

#endif
