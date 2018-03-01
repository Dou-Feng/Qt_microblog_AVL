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
	//还需要添加姓名、相关信息等
	char name[20];
	char description[150];
private:

};

