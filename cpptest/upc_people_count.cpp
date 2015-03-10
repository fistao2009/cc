//base
class UPC
{
public:
	UPC()
	{
		
	}
	UPC(int sn,int tn)
	{
		stuNum=sn;
		teaNum=tn;
	}
	int StuNum()
	{
		if(stuNum>0)
		return stuNum;
	}
	int TeaNum()
	{
		if(teaNum>0)
		return teaNum;
	}
	virtual int TotalNum()
	{
		return stuNum+teaNum;
	}
private:
	int stuNum;
	int teaNum;
	
};
class CS:public UPC		
{
public:
	CS(int i,int j)
	{
		csStuNum=i;
		csTeaNum=j;
	}
	int StuNum()
	{
		if(csStuNum>0)
		return csStuNum;
	}
	int TeaNum()
	{
		if(csTeaNum>0)
		return csTeaNum;
	}
	int TotalNum()
	{
		return csStuNum+csTeaNum;
	}
private:
	int csStuNum;
	int csTeaNum;
};
//main process
int main()
{
	UPC upc_t(20000,3000);
	cout<<"The stunumber is "<<upc_t.StuNum()<<endl;
	cout<<"The teanumber is "<<upc_t.TeaNum()<<endl;
	CS  cs_t(2000,300);
	cout<<"The stunumber is "<<cs_t.StuNum()<<endl;
	cout<<"The teanumber is "<<cs_t.TeaNum()<<endl;
	UPC *upc;
	cout<<"The total number of UPC is "<<upc_t.TotalNum()<<endl;
	upc=&cs_t;
	cout<<"The total number of CS is "<<upc->TotalNum()<<endl;
}
