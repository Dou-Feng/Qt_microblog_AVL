#include "ADT.h"

//��ʼ��
ADT::ADT()
{
	bool taller = false;
	elems = new AVLTree();
	elems->DeleteAVL(&elems, UNINIT, taller);
}

/*���ڼ�¼Member�����ݣ�getallElem���м亯��*/
void record(Member *p, int &index, Member *data) {
	p[index++] = *data;
}

/*�õ��������е�Ԫ�ص����ݣ����Ҽ�¼��coll��*/
void ADT::getAllElem(Member *coll)
{
	int index = 0;
	elems->TraverseAVL_n(this->elems, coll, index, record);
}

/*getSize���м亯����ͳ�Ʊ�������*/
void size(int &index) {
	index++;
}

/*�õ����ϴ�С*/
int ADT::getSize()
{
	int index = 0;
	elems->TraverseAVL_n(elems, index, size);
	return index;
}

/*����һ��Ԫ��*/
bool ADT::insert(Member m) {
	bool taller = false;
	if (AVLTree::InsertAVL(&elems, m, taller)) {
		return true;
	}
	else {
		return false;
	}
	
}

/*����insert�������������������*/
int ADT::insert(Member *m, int size) {
	int finish_time = 0;
	bool taller = false;
	for (int i = 0; i < size; i++) {
		try {
			if (AVLTree::InsertAVL(&elems, m[i], taller)) //����Ҫ������ķǷ��ж�
				finish_time++;
		}
		catch (exception) {
			throw "Memory fulled";
		}
	}
	return finish_time;
}

/*����insert�����������ü��ϲ���*/
int ADT::insert(ADT *A) {
	int A_size = A->getSize();
	Member *ms = (Member *)malloc(sizeof(Member) * A_size);
	A->getAllElem(ms);
	bool taller = false;
	int finish_time = 0;
	for (int i = 0; i < A_size; i++) {
		if (AVLTree::InsertAVL(&elems, ms[i], taller)) 
			finish_time++;
	}
	free(ms);
	return finish_time;
}

/*Ԫ�ص�ɾ����ɾ������Ԫ��.ɾ���ɹ�����true��ʧ�ܷ���false*/
bool ADT::remove(Member m) {
	bool shorter = false;
	if (AVLTree::DeleteAVL(&elems, m.id, shorter))
		return true;
	else
		return false;
}

/*�޸�Ԫ�ص�ֵ*/
bool ADT::modify(int key, Member m)
{
	if (AVLTree::modifyAVL(&elems, key, m))
		return true;
	else
		return false;
}

/*Ԫ��ɾ�������أ�ɾ�����Ԫ�أ�����ɾ���ɹ��ĸ���*/
int ADT::remove(Member *m, int size) {
	bool shorter = false;
	int delete_time = 0;
	for (int i = 0; i < size; ++i) {
		try {
			if (AVLTree::DeleteAVL(&elems, m[i].id, shorter))
				delete_time++;
		}
		catch (exception) {
			throw "Memory fulled";
		}
	}
	return delete_time;
}

/*Ԫ��ɾ�������أ�ɾ��һ���Ӽ�������ɾ���ĸ���*/
int ADT::remove(ADT *A) {
	int delete_time = 0;
	int A_size = A->getSize();
	Member *ms = (Member *)malloc(sizeof(Member) * A_size);
	memset(ms, 0, sizeof(Member *) * A_size);
	A->getAllElem(ms);
	bool  shorter = false;
	for (int i = 0; i < A_size; ++i) {
		if (this->remove(ms[i]))
			delete_time++;
	}
	free(ms);
	return delete_time;
}

/*���Һ���*/
Member ADT::find(int key)
{
	return AVLTree::SearchAVL(elems, key);
}

/*���ôݻ�AVL�ĺ������ݻ�ADT*/
bool ADT::destroy()
{
	if (AVLTree::DestroyAVL(&elems)) { //�ݻ���
		this->~ADT(); //���� ��������
		return true;
	}
	else {
		this->~ADT(); //���� ��������
		return false;
	}
}

/*��������*/
bool ADT::traverse(void (*f)(Member))
{
	if (getSize() != 0) {
		AVLTree::TraverseAVL(elems, f);
		return true;
	}
	else {
		return false;
	}
}

/*�ļ�����*/
bool ADT::save(FILE * f)
{
	if (AVLTree::file_save(elems, f))
		return true;
	else
		return false;
}

/*�ļ���ȡ*/
bool ADT::read(FILE * f)
{
	if (AVLTree::file_read(&elems, f))
		return true;
	else 
		return false;
}

/*�м亯�����������Ԫ�ص�������*/
void fullColl(Member *coll, int index, Member m) {
	
	try { //�п��ܻ����ڴ����
		coll[index] = m;
	}
	catch (exception) {
		throw "Memory fulled";
	}
}

/*���Ͻ��������coll�����ҷ������ǵĽ���*/
ADT *ADT::set_intersection(Member *coll, ADT * a, ADT * b)
{
	int index = 0; //���ڼ�¼coll�±�
	bool taller = false; //���ڲ���Ԫ��
	Member result_s;
	ADT *interSet = new ADT(); //���ڷ���ֵ
	int a_size = a->getSize(); //�õ�a���ϴ�С
	int b_size = b->getSize(); //�õ�b���ϴ�С
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size); 
	memset(a_ms, 0, sizeof(Member) * a_size);
	Member *b_ms = (Member *)malloc(sizeof(Member) * b_size); 
	memset(b_ms, 0, sizeof(Member) * b_size);
	a->getAllElem(a_ms);//�õ�a��������Ԫ�أ��Ҵ�С��������
	b->getAllElem(b_ms);//�õ�b��������Ԫ�أ��Ҵ�С��������
	
	if (a_size > b_size) { //��a���⣬��b�еĸ���Ԫ�ز���
		for (int i = 0; i < b_size; i++) {
			result_s = AVLTree::SearchAVL(a->elems, b_ms[i].id);
			if (result_s.id != UNINIT)
				fullColl(coll, index++, result_s);
		}
	}
	else {
		for (int i = 0; i < a_size; i++) { //��b���⣬��a�еĸ���Ԫ�ز���
			result_s = AVLTree::SearchAVL(b->elems, a_ms[i].id);
			if (result_s.id != UNINIT)
				fullColl(coll, index++, result_s);
		}
	}

	for (int i = 0; i < index; i++) {
		AVLTree::InsertAVL(&interSet->elems, coll[i], taller);
	}
	free(a_ms);
	free(b_ms);
	return interSet;
}

/*���ϲ��a - b)�����coll�����ҷ���a - b ֮��ļ���ָ��*/
ADT * ADT::set_different(Member * coll, ADT * a, ADT * b)
{
	int index = 0; //���ڼ�¼coll�±�
	bool taller = false; //���ڲ���Ԫ��
	ADT *diffSet = new ADT(); //���ڷ���ֵ
	int a_size = a->getSize(); //�õ�a���ϴ�С
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size);
	memset(a_ms, 0, sizeof(Member) * a_size);

	a->getAllElem(a_ms);//�õ�a��������Ԫ�أ��Ҵ�С��������

	for (int i = 0; i < a_size; i++) { //��b���⣬��a�еĸ���Ԫ�ز���
		Member result_s = AVLTree::SearchAVL(b->elems, a_ms[i].id);
		if (result_s.id == UNINIT)
			fullColl(coll, index++, a_ms[i]);
	}
	for (int i = 0; i < index; i++) {
		AVLTree::InsertAVL(&diffSet->elems, coll[i], taller);
	}
	free(a_ms);
	return diffSet;
}

/*��a,b�Ĳ��������ز���ָ�룬�������coll*/
ADT * ADT::set_union(Member * coll, ADT * a, ADT * b)
{
	int index = 0; //���ڼ�¼coll�±�
	bool taller = false; //���ڲ���Ԫ��
	ADT *unionSet = new ADT(); //���ڷ���ֵ
	int a_size = a->getSize(); //�õ�a���ϴ�С
	int b_size = b->getSize(); //�õ�b���ϴ�С
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size);
	memset(a_ms, 0, sizeof(Member) * a_size);
	Member *b_ms = (Member *)malloc(sizeof(Member) * b_size);
	memset(b_ms, 0, sizeof(Member) * b_size);
	a->getAllElem(a_ms);//�õ�a��������Ԫ�أ��Ҵ�С��������
	b->getAllElem(b_ms);//�õ�b��������Ԫ�أ��Ҵ�С��������
	for (int i = 0; i < a_size; i++) { //���Ȱ�a������Ԫ�ؼ��뵽coll��
		fullColl(coll, index++, a_ms[i]);
	}

	for (int i = 0; i < b_size; i++) { //Ȼ���a��û�У�b���е�Ԫ�ؼ��뵽coll��
		Member result_s = AVLTree::SearchAVL(a->elems, b_ms[i].id);
		if (result_s.id == UNINIT)
			fullColl(coll, index++, b_ms[i]);
	}
	

	for (int i = 0; i < index; i++) {
		AVLTree::InsertAVL(&unionSet->elems, coll[i], taller);
	}
	free(a_ms);
	free(b_ms);
	return unionSet;
}

/*�ж�a�Ƿ�Ϊb���Ӽ����Ƿ���true�����ǣ�����false*/
bool ADT::set_subset(ADT * a, ADT * b)
{
	int a_size = a->getSize(); //�õ�a���ϴ�С
	int b_size = b->getSize(); //�õ�b���ϴ�С
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size);
	memset(a_ms, 0, sizeof(Member) * a_size);
	Member search_result;
	a->getAllElem(a_ms);//�õ�a��������Ԫ�أ��Ҵ�С��������
	if (a_size > b_size) //��a�ĳ��ȴ���bʱ��ֱ�ӷ���false
		return false;
	for (int i = 0; i < a_size; i++) {
		search_result = AVLTree::SearchAVL(b->elems, a_ms[i].id);
		if (search_result.id == UNINIT) //ֻҪ��һ��Ԫ���Ҳ�������ô�Ͳ����Ӽ�
			return false;
	}
	free(a_ms);
	return true;
}

/*������ȣ���ȷ���true������ȷ���false*/
bool ADT::set_equal(ADT * a, ADT * b)
{
	int a_size = a->getSize(); //�õ�a���ϴ�С
	int b_size = b->getSize(); //�õ�b���ϴ�С
	if (a_size != b_size)
		return false;
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size);
	memset(a_ms, 0, sizeof(Member) * a_size);
	Member search_result;
	a->getAllElem(a_ms);//�õ�a��������Ԫ�أ��Ҵ�С��������
	for (int i = 0; i < a_size; i++) {
		search_result = AVLTree::SearchAVL(b->elems, a_ms[i].id);
		if (search_result.id == UNINIT) //ֻҪ��һ��Ԫ���Ҳ�������ô�Ͳ����
			return false;
	}
	free(a_ms);
	return true;
}

//�ж��Ƿ��ڼ����У����ҷ��ز��ҵ������ݣ����û���ҵ��������ݵ�idΪUNINIT
Member ADT::set_member(ADT * a, Member m)
{
	return AVLTree::SearchAVL(a->elems, m.id);
}

 
