#pragma once
#include "AVLTree.h"


class ADT
{
public:
	ADT(); //��ʼ��
	void getAllElem(Member *coll); //�õ�����Ԫ��
	int getSize(); //�õ���С
	bool insert(Member coll);  //�������
	int insert(Member *coll, int size); //�������
	int insert(ADT *A); //�������
	bool remove(Member m); //ɾ������
	int remove(Member *m, int size); //ɾ������
	int remove(ADT *A); //ɾ������
	bool modify(int key, Member m); //�޸Ĳ���
	Member find(int key); //���Ҳ���
	bool destroy(); //�ݻٲ���
	bool traverse(void (*f)(Member));   //��������
	bool save(FILE *f); //���浽�ļ�
	bool read(FILE *f); //���ļ��ж�ȡ

	static ADT *set_intersection(Member *coll, ADT *a, ADT *b); //�󽻼�
	static ADT *set_different(Member *coll, ADT *a, ADT *b); //��
	static ADT *set_union(Member *coll, ADT *a, ADT *b); //�󲢼�
	static bool set_subset(ADT *a, ADT *b); //�Ӽ��ж�
	static bool set_equal(ADT *a, ADT *b); //����ж�
	static Member set_member(ADT *a, Member m); //�ж��Ƿ����ڼ���a

public:
	AVLTree *elems; //������

};

