class HelloWorld
{
private:
	HelloWorld()
	{
		str="hello world";
	}
private:
	string str;
};
int main()
{
	HelloWorld hw;
	cout<<"my first program is"<<hw.str<<endl;
}
