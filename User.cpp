#include "User.h"
#define MAXMEMBER 500

/*初始化*/
User::User(int id, char *name)
{
	this->id = id;
	strcpy_s(this->name, name);
	friends = new ADT();
	fans = new ADT();
	followed = new ADT();
}

User::User(int id, char * name, char * passwd)
{
	this->id = id;
	strcpy_s(this->name, name);
	strcpy_s(this->passwd, passwd);
	friends = new ADT();
	fans = new ADT();
	followed = new ADT();
}

User::User(int id, char * name, char * passwd, char *des)
{
	this->id = id;
	strcpy_s(this->name, name);
	strcpy_s(this->passwd, passwd);
	strcpy_s(this->des, des);
	friends = new ADT();
	fans = new ADT();
	followed = new ADT();
}

/*析构函数*/
User::~User()
{
	friends->destroy();
	fans->destroy();
	followed->destroy();
}

/*添加好友、粉丝、关注人*/
bool User::add(KINDS a, Member m)
{
	ADT *operatingObj = nullptr;
	switch (a)
	{
	case FRIEND:
		operatingObj = friends;
		break;
	case FAN:
		operatingObj = fans;
		break;
	case FOLLOWED:
		operatingObj = followed;
		break;
	default:
		break;
	}
	if (operatingObj->insert(m))
		return true;
	else
		return false;
}

/*删除好友、粉丝、关注人*/
bool User::remove(KINDS a, Member m)
{
	ADT *operatingObj = nullptr;
	switch (a)
	{
	case FRIEND:
		operatingObj = friends;
		break;
	case FAN:
		operatingObj = fans;
		break;
	case FOLLOWED:
		operatingObj = followed;
		break;
	default:
		break;
	}
	if (operatingObj->remove(m))
		return true;
	else
		return false;
}

/*修改好友、粉丝、关注人*/
bool User::modify(KINDS a, int key, Member new_m)
{
	ADT *operatingObj = nullptr;
	switch (a)
	{
	case FRIEND:
		operatingObj = friends;
		break;
	case FAN:
		operatingObj = fans;
		break;
	case FOLLOWED:
		operatingObj = followed;
		break;
	default:

		break;
	}
	if (operatingObj->modify(key, new_m))
		return true;
	else
		return false;
}

/*查找好友、粉丝、关注人*/
Member User::find(KINDS a, Member m)
{
	ADT *operatingObj = nullptr;
	Member find_s;
	switch (a)
	{
	case FRIEND:
		operatingObj = friends;
		break;
	case FAN:
		operatingObj = fans;
		break;
	case FOLLOWED:
		operatingObj = followed;
		break;
	default:
		break;
	}
	if ((find_s = operatingObj->find(m.id)).id != UNINIT)
		return find_s;
	else
		return find_s;
}

/*得到好友集*/
ADT User::getFriends()
{
	return *this->friends;
}

/*得到粉丝*/
ADT User::getFans()
{
	return *this->fans;
}

/*得到关注*/
ADT User::getFollowed()
{
    return *this->followed;
}

/*得到密码*/
char *User::getPasswd()
{
    return passwd;
}

char * User::getName()
{
	return this->name;
}

/*得到id*/
int User::getId()
{
	return this->id;
}



#pragma warning(disable:4996)
/*读取文件*/
bool User::read()
{
	// int to char*
	string id_s = to_string(id);
	const char *id_c = id_s.c_str();
	//处理文件名
	char file_name_friends[30] = "./";
	char file_name_fans[30] = "./";
	char file_name_followed[30] = "./";
	strcat_s(file_name_friends, id_c);
	strcat_s(file_name_friends, "friends.json");
	strcat_s(file_name_fans, id_c);
	strcat_s(file_name_fans, "fans.json");
	strcat_s(file_name_followed, id_c);
	strcat_s(file_name_followed, "followed.json");

	//打开文件
	FILE *f_friends = fopen(file_name_friends, "r");
	FILE *f_fans = fopen(file_name_fans, "r");
	FILE *f_followed = fopen(file_name_followed, "r");

	//调用储存函数
	bool b1 = friends->read(f_friends);
	bool b2 = fans->read(f_fans);
	bool b3 = followed->read(f_followed);
	if (b1 || b2 || b3) {
		fclose(f_friends);
		fclose(f_fans);
		fclose(f_followed);
		return true;
	}
	else if (f_friends && f_fans && f_followed) {
		fclose(f_friends);
		fclose(f_fans);
		fclose(f_followed);
		return false;
	}
	else
		return false;
}

/*写入文件*/
bool User::save()
{
	// int to char*
	string id_s = to_string(id);
	const char *id_c = id_s.c_str();
	//处理文件名
	char file_name_friends[30] = "./";
	char file_name_fans[30] = "./";
	char file_name_followed[30] = "./";
	strcat_s(file_name_friends, id_c);
	strcat_s(file_name_friends, "friends.json");
	strcat_s(file_name_fans, id_c);
	strcat_s(file_name_fans, "fans.json");
	strcat_s(file_name_followed, id_c);
	strcat_s(file_name_followed, "followed.json");
	//打开文件
	FILE *f_friends = fopen(file_name_friends, "w");
	FILE *f_fans = fopen(file_name_fans, "w");
	FILE *f_followed = fopen(file_name_followed, "w");
	//调用储存函数
	bool b1 = friends->save(f_friends);
	bool b2 = fans->save(f_fans);
	bool b3 = followed->save(f_followed);
	if (b1 || b2 || b3) {
		fclose(f_friends);
		fclose(f_fans);
		fclose(f_followed);
		return true;
	}
	else if (f_friends && f_fans && f_followed) {
		fclose(f_friends);
		fclose(f_fans);
		fclose(f_followed);
		return false;
	}
	else
		return false;
}


/*找到共同关注的人，并且填充在coll中*/
void User::InterFollowings(Member * coll, User * a, User * b)
{
	ADT::set_intersection(coll, a->followed, b->followed);
}

/*找到共同粉丝，并且填充在coll中*/
void User::InterFans(Member * coll, User * a, User * b)
{
	ADT::set_intersection(coll, a->fans, b->fans);
}

/*共同爱好，有相同爱好的用户信息填充在coll中*/
void User::InterHobby(Member * coll, User *a, vector<Member> m)
{
	int index = 0; //记录保存在coll中的位置
    for (int i = 0; i < m.size(); i++) {
        Member u = m[i];
        if (u.id == a->id)
			continue;
        if (strstr(a->des, u.description) || strstr(u.description, a->des)) {
            coll[index++] = u;
		}
	}
}

/*查找用户，返回查找到的用户的指针*/
User * User::findUsers(vector<User> *users, int id)
{
    User *user;
    for (int i = 0; i < users->size(); i++) {
        user = &(users->at(i));
        if (user->id == id)
            return user;
    }
    return nullptr;
}


/*找到二度好友，并且填充在coll中*/
void User::InterFriends(Member * coll, User * a, vector<User> *users)
{
	Member friends_a[MAXMEMBER];
	memset(friends_a, 0, sizeof(Member) * MAXMEMBER);
	a->getFriends().getAllElem(friends_a);
	ADT *f_friends;
	ADT f_friends_e;
	if (friends_a[0].id == 0)
		return;
	User *find_1 = findUsers(users, friends_a[0].id);
	if (find_1) {
		f_friends_e = find_1->getFriends();
		f_friends = &f_friends_e;
	}
	else
		return;
	User *find_user;
	for (int i = 1; friends_a[i].id != 0; i++) {
		find_user = findUsers(users, friends_a[i].id); //找到的用户是a的朋友，然后得到a的朋友的朋友
        if (!find_user)
            continue;
		ADT a_a_friends = find_user->getFriends();
		f_friends = ADT::set_union(coll, f_friends, &a_a_friends);
	}
}




