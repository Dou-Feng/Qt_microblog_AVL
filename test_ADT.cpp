#include <stdio.h>
#include <string>
#include <iostream>
#include "ADT.h"

#define COLLSIZE 600

using namespace std;
#pragma warning(disable:4996)
void visit(Member e) {
	cout << "id:" << e.id
		<< ", name:" << e.name << endl;
}

int main() {
	ADT *set = nullptr;
	FILE *f;
	Member m;
	char name[15];
	int id_t;
	int op = 0;
	ADT *setB = new ADT();
	ADT *setC;
	Member coll[COLLSIZE];
	memset(coll, 0, sizeof(Member) * COLLSIZE);
	f = fopen("friends.txt", "r");

	for (int i = 0; i < 484; i++)
	{
		fscanf(f, "%d%s", &m.id, name);
		if (1) {
			strcpy(m.name, name);
			setB->insert(m);
		}
	}
	strcpy(m.name, name);
	fclose(f);

	while (op >= 0)
	{
		system("cls");	printf("\n\n");
		cout << "\tTest for the ADT" << endl;
		cout << "---------------------------------" << endl;
		cout << "1. set_init  \t2. set_destroy\n"
			<< "3. set_insert  \t4. set_remove\n"
			<< "5. set_intersection\t6. set_union\n"
			<< "7. set_diffrence     \t8. set_size\n"
			<< "9. set_member     \t10. set_subset\n"
			<< "11. set_equal\t12. readDataFromFiles\t\n"
			<< "13. set_modify\t 14.set_find\n";
		cout << "---------------------------------" << endl;
		cout << "input your choice :" << endl;
		cin >> op;
		switch (op)
		{
		case 1:
			if (!set) {
				set = new ADT();
				cout << "Init finished!" << endl;
			}
			else {
				cout << "Init failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 2:
			if (set) {
				set->destroy();
				cout << "destroy finished!" << endl;
				set = nullptr;
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 3:
			if (set) {
				cout << "input id :";
				cin >> m.id;
				cout << "input name :";
				cin >> m.name;
				set->insert(m);
				cout << "insert finished!" << endl;
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 4:
			if (set) {
				cout << "input id :";
				cin >> m.id;
				set->remove(m);
				cout << "remove finished!" << endl;
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 5:
			if (set) {
				setC = ADT::set_intersection(coll, set, setB);
				AVLTree::TraverseAVL(setC->elems, visit);
				cout << endl;
				visit(coll[0]);
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 6:
			if (set) {
				setC = ADT::set_union(coll, set, setB);
				AVLTree::TraverseAVL(setC->elems, visit);
				cout << endl;
				visit(coll[0]);
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 7:
			if (set) {
				setC = ADT::set_different(coll, set, setB);
				AVLTree::TraverseAVL(setC->elems, visit);
				cout << endl;
				visit(coll[0]);
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 8:
			if (set) {
				cout << "Set size :" << set->getSize() << endl;
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 9:
			if (set) {
				cout << "The list of members:" << endl;
				AVLTree::TraverseAVL(set->elems, visit);
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 10:
			if (set) {
				if (set->set_subset(setB, set)) {
					cout << "It is Subset" << endl;
				}
				else {
					cout << "Not Subset!" << endl;
				}
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 11:
			if (set) {
				if (ADT::set_equal(set, setB))
					cout << "set equal!" << endl;
				else
					cout << "set Not equal!" << endl;
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 12:
			if (set) {
				f = fopen("friends.txt", "r");
				while (fscanf(f, "%d%s", &m.id, name) > 0)
				{
					strcpy(m.name, name);
					set->insert(m);
				}
				cout << "read finished!" << endl;
				strcpy(m.name, "");
				fclose(f);
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 13:
			if (set) {
				cout << "input modify id :";
				cin >> id_t;
				cout << "input member's id :";
				cin >> m.id;
				cout << "input member's name :";
				cin >> m.name;
				if (set->modify(id_t, m)) {
					cout << "modify finished!" << endl;
				}
				else {
					cout << "modify failed!" << endl;
				}
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		case 14:
			if (set) {
				cout << "input modify id :";
				cin >> id_t;

				if ((m = set->find(id_t)).id != UNINIT) {
					cout << "Find result is :" << endl;
					cout << "id :" << m.id << " ,name :" << m.name << endl;
				}
				else {
					cout << "find failed!" << endl;
				}
			}
			else {
				cout << "Not Init";
			}
			getchar();
			getchar();
			break;
		default:
			break;
		}
	}
	return 0;
}