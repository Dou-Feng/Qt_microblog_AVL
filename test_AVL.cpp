#include <stdio.h>
#include <string>
#include <iostream>
#include "AVLTree.h"

using namespace std;

void visit(Member e) {
	cout << "id:" <<e.id
		<< ", name:" << e.name << endl;
}

#pragma warning(disable:4996)
int main() {
	int op = 0;
	AVLTree *T = nullptr;
	Member e;
	int id; bool taller = false, shorter = false;
	string des;
	char name[100];
	FILE *file;
	char file_name[20];
	int read_time = 0;
	while (op >= 0)
	{
		system("cls");	printf("\n\n");
		cout << "\tTest for the AVL" << endl;
		cout << "---------------------------------" << endl;
		cout << "1. Init AVL\t2. Destroy AVL\n"
			<< "3. Search AVL\t4. Insert AVL\n"
			<< "5. Delete AVL\t6. Traverse AVL" << endl
			<< "7. input data from files\t 8. save data into file" << endl;
		cout << "---------------------------------" << endl;
		cout << "input your choice :" << endl;
		cin >> op;
		switch (op)
		{
		case 1:
			cout << "input the id: ";
			cin >> e.id;
			T = AVLTree::InitAVL(e);
			cout << "init finish!" << endl;
			getchar();
			getchar();
			break;
		case 2:
			if (AVLTree::DestroyAVL(&T)) {
				T = nullptr;
				cout << "destroy finished!" << endl;
			}
			else {
				cout << "destroy failed!" << endl;
			} 
			getchar(); getchar();
			break;
		case 3:
			cout << "input the id :";
			cin >> e.id;
			e = AVLTree::SearchAVL(T, e.id);
			if (e.id == UNINIT) {
				cout << "Not found!" << endl;
			}
			else {
				cout << "find it!\nID:" << e.id << endl;
			}
			getchar();
			getchar();
			break;
		case 4:
			cout << "input the id: ";
			cin >> e.id;
			AVLTree::InsertAVL(&T, e, taller);
			cout << "insert finish!" << endl;
			getchar();
			getchar();
			break;
		case 5:
			cout << "input the delete id:";
			cin >> id;
			if (AVLTree::DeleteAVL(&T, id, shorter)) {
				cout << "delete finished!" << endl;
			}
			else {
				cout << "delete failed!" << endl;
			}
			getchar();
			getchar();
			break;
		case 6:
			if (AVLTree::TraverseAVL(T, visit)) {
				cout << "Traverse finished!" << endl;
			} else {
				cout << "Traverse failed!" << endl;
			}
			getchar(); getchar();
			break;
		case 7:
			file = fopen("friends.txt", "r");
			if ((read_time = AVLTree::file_read(&T, file)) > 0)
			cout << "read finished!" << ", time:" << read_time << endl;
			strcpy(e.name, "");
			fclose(file);
			getchar(); getchar();
			break;
		case 8:
			cout << "input file name: ";
			cin >> file_name;
			file = fopen(file_name, "w");
			if (AVLTree::file_save(T, file)) {
				cout << "save finished!" << endl;
			}
			else {
				cout << "save failed!" << endl;
			}
			fclose(file);
			getchar();
			getchar();
			break;
		default:
			break;
		}
	}
	return 0;
}