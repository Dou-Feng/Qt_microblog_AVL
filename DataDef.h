#pragma once
#include <string>
using namespace std;
class Member
{
public:
	Member();
	Member(int id, char *, char *);

public:
	int id;
	//����Ҫ��������������Ϣ��
	char name[20];
	char description[150];
private:

};

