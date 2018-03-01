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
	User(int id, char *name); //��ʼ��
	User(int id, char *name, char *passwd);//��ʼ��
	User(int id, char *name, char *passwd, char *des);//��ʼ��
	~User(); //��������
	bool add(KINDS a, Member m); //��Ӳ���
	bool remove(KINDS a, Member m); //ɾ������
	bool modify(KINDS a, int key, Member new_m); //�޸Ĳ���
	Member find(KINDS a, Member m); //���Ҳ���
	ADT getFriends(); //�õ����ѵļ���
	ADT getFans(); //�õ���˿����
	ADT getFollowed(); //�õ���ע�˼���
    char *getPasswd(); //
	char *getName(); //�õ�����
	int getId(); //�õ�ID
	bool read(); //�ļ���ȡ
	bool save(); //�ļ�����

	static void InterFollowings(Member *coll, User *a, User *b); //��ͬ��ע
	static void InterFans(Member *coll, User *a, User *b); //��ͬ��˿
    static void InterHobby(Member *coll, User *a, vector<Member> m); //��ͬ����
	static User *findUsers(vector<User> *users, int id); //�����û�
    static void InterFriends(Member *coll, User *a, vector<User> *users); //���Ⱥ���

public:
	int id;
	char name[25];
	char des[200];
	char passwd[17];
	ADT *friends;
	ADT *fans;
	ADT *followed;
};

