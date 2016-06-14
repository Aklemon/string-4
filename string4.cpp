#define _CRT_SECURE_NO_WARNINGS
#include< iostream>
using namespace std;
class String
{
public :
	String(char* _str = "")
	{
		if (_str == NULL)
		{
			str = new char[1 + 4];
			*(int*)(str) = 1;
			str += 4;
			*str = '\0';
		}
		else
		{
			str = new char[strlen(_str) + 5];
			*(int*)str = 1;
			str += 4;
			strcpy(str, _str);
		}
	}
	String(const String& s)
		:str(s.str)
    {
 		++GetRef(); 
	}
	String &operator=(const String & s)
	{
		if (str != s.str)
		{
			--GetRef();
			ReduceRef();
		}
		else
		{
			str = s.str;
		}
		return *this;
	}
	~String()
	{
		--GetRef();
		ReduceRef();

	}
	//[]的重载 为了实现写时拷贝的数组[]下标形式的访问
	char &operator[](size_t index)
	{
		if (GetRef() > 1)
		{
			char*_str = new char(strlen(str) + 1 + 4);
			*(int*)str = 1;
			str += 4;
			strcpy(_str, str);
			--GetRef();
			str = _str;
		}
		return str[index];
	}

private:
	int &GetRef()
	{
		return *(int*)str;
 	}
	void ReduceRef()
	{
		if (0 == GetRef())
		{
			str += 4;
			delete[]str;
		}

	}

private:
	char* str;
};


int main()
{
	String s1("hello");
	String s2(s1);
	String s3(s2);
	s3 = s1;
	s3[0] = 'w';//提示不匹配,是因为[]没有重载
}