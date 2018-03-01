#include <stdio.h>
#include <string>
#include <iostream>
#include "User.h"

#define COLLSIZE 600
#define MAXSIZE 200

using namespace std;
#pragma warning(disable:4996)

void visit(Member e) {
	cout << "id:" << e.id
		<< ", name:" << e.name << "\ndescription:" << e.description << endl;
}

int main() {
	User *users[MAXSIZE];
	int cindex = -1, size = 0;
	int id1, id2;
	enum KINDS kind = FRIEND;
	Member m;
	int int_s;
	int id_index = 1;
	char name[20];

	char str_coll[3][150];
	int op = 0;
	Member coll[COLLSIZE];
	memset(coll, 0, sizeof(Member) * COLLSIZE);

	while (op >= 0) {
		system("cls");
		printf("\n\n");
		cout << "\tTest for the ADT" << endl;
		cout << "---------------------------------" << endl;
		cout << "1. user init  \t2. user destroy\n"
			<< "3. insert  \t4. remove\n"
			<< "5. modify\t6. find\n"
			<< "7. interfriends\t8. interfans\n"
			<< "9. interfolloweds\t10. read\n"
			<< "11. save\t12. switch users\n"
			<< "13. traverse\n";
		cout << "---------------------------------" << endl;
		cout << "input your choice :";
		cin >> op;
		switch (op) {
		case 1:
			if (size < MAXSIZE) {
				strcpy(name, "A");
				users[size] = new User(id_index++, name);
				cindex = size++;
				cout << "init finished" << endl;
				cout << "Current user's id:" << users[cindex]->getId() << ", name:" 
					<< users[cindex]->getName() << endl;;
			}
			getchar(); getchar();
			break;
		case 2:
			if (cindex >= 0) {
				users[cindex]->~User();
				size--;
				if (size == 0)
					cindex = -1; 
				else {
					for (int i = cindex; i < size; i++) {
						users[i] = users[i + 1];
					}
				}
				cout << "finished!" << endl;
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 3:
			if (cindex >= 0) {
				cout << "input your choice : (1. friends 2. fans 3. followed)";
				cin >> int_s;
				if (int_s == 1) {
					kind = FRIEND;
				}
				else if (int_s == 2) {
					kind = FAN;
				}
				else if (int_s == 3) {
					kind = FOLLOWED;
				}
				else {
					cout << "failed!" << endl;
					break;
				}
				cout << "input the id :";
				cin >> m.id;
				getchar();
				cout << "input the name :";
				fgets(m.name, 20, stdin);
				AVLTree::split(str_coll, m.name, "\n"); //去掉尾部\n
				strcpy(m.name, str_coll[0]);
				cout << "input the description :";
				fgets(m.description, 150, stdin);
				AVLTree::split(str_coll, m.description, "\n"); //去掉尾部\n
				strcpy(m.description, str_coll[0]);
				if (users[cindex]->add(kind, m))
					cout << "finished!" << endl;
				else
					cout << "failed!" << endl;
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			break;
		case 4:
			if (cindex >= 0) {
				cout << "input your choice : (1. friends 2. fans 3. followed)";
				cin >> int_s;
				if (int_s == 1) {
					kind = FRIEND;
				}
				else if (int_s == 2) {
					kind = FAN;
				}
				else if (int_s == 3) {
					kind = FOLLOWED;
				}
				else {
					cout << "failed!" << endl;
					break;
				}
				cout << "input the id :";
				cin >> m.id;
				if (users[cindex]->remove(kind, m))
					cout << "finished!" << endl;
				else
					cout << "failed!" << endl;
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 5:
			if (cindex >= 0) {
				cout << "input your choice : (1. friends 2. fans 3. followed)";
				cin >> int_s;
				if (int_s == 1) {
					kind = FRIEND;
				}
				else if (int_s == 2) {
					kind = FAN;
				}
				else if (int_s == 3) {
					kind = FOLLOWED;
				}
				else {
					cout << "failed!" << endl;
					break;
				}
				cout << "input the id :";
				cin >> m.id;
				getchar();
				cout << "input the name :";
				fgets(m.name, 20, stdin);
				AVLTree::split(str_coll, m.name, "\n"); //去掉尾部\n
				strcpy(m.name, str_coll[0]);
				cout << "input the description :";
				fgets(m.description, 150, stdin);
				AVLTree::split(str_coll, m.description, "\n"); //去掉尾部\n
				strcpy(m.description, str_coll[0]);
				if (users[cindex]->modify(kind, m.id, m))
					cout << "finished!" << endl;
				else
					cout << "failed!" << endl;
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			break;
		case 6:
			if (cindex >= 0) {
				cout << "input your choice : (1. friends 2. fans 3. followed)";
				cin >> int_s;
				if (int_s == 1) {
					kind = FRIEND;
				}
				else if (int_s == 2) {
					kind = FAN;
				}
				else if (int_s == 3) {
					kind = FOLLOWED;
				}
				else {
					cout << "failed!" << endl;
					break;
				}
				cout << "input the id :";
				cin >> m.id;
				if ((m = users[cindex]->find(kind, m)).id != UNINIT) {
					visit(m);
					cout << "finished!" << endl;
				}
				else
					cout << "failed!" << endl;
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 7:
			if (size > 1) {
				cout << "input two user's id :";
				cin >> id1;
				cin >> id2;
				if (id1 > size || id2 > size) {
					cout << "failed" << endl;
					break;
				}
				else {
					User::InterFriends(coll, users[id1 - 1], users[id2 - 1]);
					cout << "list of inter friends:" << endl;
					for (int i = 0; coll[i].id != 0; i++) {
						visit(coll[i]);
					}
					if (coll[0].id == 0) {
						cout << "No inter friends" << endl;
					}
				}
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 8:
			if (size > 1) {
				cout << "input two user's id :";
				cin >> id1;
				cin >> id2;
				if (id1 > size || id2 > size) {
					cout << "failed" << endl;
					break;
				}
				else {
					User::InterFans(coll, users[id1 - 1], users[id2 - 1]);
					cout << "list of inter fans:" << endl;
					for (int i = 0; coll[i].id != 0; i++) {
						visit(coll[i]);
					}
					if (coll[0].id == 0) {
						cout << "No inter fans" << endl;
					}
				}
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 9:
			if (size > 1) {
				cout << "input two user's id :";
				cin >> id1;
				cin >> id2;
				if (id1 > size || id2 > size) {
					cout << "failed" << endl;
					break;
				}
				else {
					User::InterFollowings(coll, users[id1 - 1], users[id2 - 1]);
					cout << "list of inter followeds:" << endl;
					for (int i = 0; coll[i].id != 0; i++) {
						visit(coll[i]);
					}
					if (coll[0].id == 0) {
						cout << "No inter followeds" << endl;
					}
				}
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 10:
			if (cindex >= 0) {
				if (users[cindex]->read()) {
					cout << "read finished!" << endl;
				}
				else {
					cout << "read failed!" << endl;
				}
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 11:
			if (cindex >= 0) {
				if (users[cindex]->save()) {
					cout << "save finished!" << endl;
				}
				else {
					cout << "save failed!" << endl;
				}
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 12:
			if (cindex >= 0) {
				cout << "input the id :(<=" << size << ")" << endl;
				cin >> id1;
				if (id1 > size) {
					cout << "fail!" << endl;
					break;
				}
				cindex = id1 - 1;
				cout << "Current user's id:" << users[cindex]->getId() << ", name:"
					<< users[cindex]->getName() << endl;
			}
			else {
				cout << "failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 13:
			if (cindex >= 0) {
				cout << "Current user's id:" << users[cindex]->getId() << ", name:"
					<< users[cindex]->getName() << endl;
				cout << "Friend:" << endl;
				users[cindex]->getFriends().traverse(visit);
				cout << endl;
				cout << "Fans:" << endl;
				users[cindex]->getFans().traverse(visit);
				cout << endl;
				cout << "Followed:" << endl;
				users[cindex]->getFollowed().traverse(visit);
				cout << endl;
			}
			else {
				cout << "failed!" << endl;
			}
			getchar(); getchar();
		default:
			break;
		}
	}
	return 0;
}