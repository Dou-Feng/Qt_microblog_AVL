#pragma once
#include "ADT.h"
#include <vector>

enum KINDS{
	FRIEND,
	FAN,
	FOLLOWED
};

class User
{
public:
	User(int id, char *name); //初始化
	User(int id, char *name, char *passwd);//初始化
	User(int id, char *name, char *passwd, char *des);//初始化
	~User(); //析构函数
	bool add(KINDS a, Member m); //添加操作
	bool remove(KINDS a, Member m); //删除操作
	bool modify(KINDS a, int key, Member new_m); //修改操作
	Member find(KINDS a, Member m); //查找操作
	ADT getFriends(); //得到好友的集合
	ADT getFans(); //得到粉丝集合
	ADT getFollowed(); //得到关注人集合
    char *getPasswd(); //
	char *getName(); //得到名字
	int getId(); //得到ID
	bool read(); //文件读取
	bool save(); //文件保存

	static void InterFollowings(Member *coll, User *a, User *b); //共同关注
	static void InterFans(Member *coll, User *a, User *b); //共同粉丝
    static void InterHobby(Member *coll, User *a, vector<Member> m); //共同爱好
	static User *findUsers(vector<User> *users, int id); //查找用户
    static void InterFriends(Member *coll, User *a, vector<User> *users); //二度好友

public:
	int id;
	char name[25];
	char des[200];
	char passwd[17];
	ADT *friends;
	ADT *fans;
	ADT *followed;
};

