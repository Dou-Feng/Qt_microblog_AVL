#include "ADT.h"

//初始化
ADT::ADT()
{
	bool taller = false;
	elems = new AVLTree();
	elems->DeleteAVL(&elems, UNINIT, taller);
}

/*用于记录Member的数据，getallElem的中间函数*/
void record(Member *p, int &index, Member *data) {
	p[index++] = *data;
}

/*得到集合所有的元素的数据，并且记录在coll中*/
void ADT::getAllElem(Member *coll)
{
	int index = 0;
	elems->TraverseAVL_n(this->elems, coll, index, record);
}

/*getSize的中间函数，统计遍历次数*/
void size(int &index) {
	index++;
}

/*得到集合大小*/
int ADT::getSize()
{
	int index = 0;
	elems->TraverseAVL_n(elems, index, size);
	return index;
}

/*插入一个元素*/
bool ADT::insert(Member m) {
	bool taller = false;
	if (AVLTree::InsertAVL(&elems, m, taller)) {
		return true;
	}
	else {
		return false;
	}
	
}

/*重载insert方法，可以用数组插入*/
int ADT::insert(Member *m, int size) {
	int finish_time = 0;
	bool taller = false;
	for (int i = 0; i < size; i++) {
		try {
			if (AVLTree::InsertAVL(&elems, m[i], taller)) //这里要做数组的非法判断
				finish_time++;
		}
		catch (exception) {
			throw "Memory fulled";
		}
	}
	return finish_time;
}

/*重载insert方法，可以用集合插入*/
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

/*元素的删除，删除单个元素.删除成功返回true，失败返回false*/
bool ADT::remove(Member m) {
	bool shorter = false;
	if (AVLTree::DeleteAVL(&elems, m.id, shorter))
		return true;
	else
		return false;
}

/*修改元素的值*/
bool ADT::modify(int key, Member m)
{
	if (AVLTree::modifyAVL(&elems, key, m))
		return true;
	else
		return false;
}

/*元素删除的重载，删除多个元素，返回删除成功的个数*/
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

/*元素删除的重载，删除一个子集，返回删除的个数*/
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

/*查找函数*/
Member ADT::find(int key)
{
	return AVLTree::SearchAVL(elems, key);
}

/*调用摧毁AVL的函数，摧毁ADT*/
bool ADT::destroy()
{
	if (AVLTree::DestroyAVL(&elems)) { //摧毁树
		this->~ADT(); //调用 析构函数
		return true;
	}
	else {
		this->~ADT(); //调用 析构函数
		return false;
	}
}

/*遍历函数*/
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

/*文件保存*/
bool ADT::save(FILE * f)
{
	if (AVLTree::file_save(elems, f))
		return true;
	else
		return false;
}

/*文件读取*/
bool ADT::read(FILE * f)
{
	if (AVLTree::file_read(&elems, f))
		return true;
	else 
		return false;
}

/*中间函数，用于添加元素到数组中*/
void fullColl(Member *coll, int index, Member m) {
	
	try { //有可能会有内存溢出
		coll[index] = m;
	}
	catch (exception) {
		throw "Memory fulled";
	}
}

/*集合交集，填充coll，并且返回他们的交集*/
ADT *ADT::set_intersection(Member *coll, ADT * a, ADT * b)
{
	int index = 0; //用于记录coll下标
	bool taller = false; //用于插入元素
	Member result_s;
	ADT *interSet = new ADT(); //用于返回值
	int a_size = a->getSize(); //得到a集合大小
	int b_size = b->getSize(); //得到b集合大小
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size); 
	memset(a_ms, 0, sizeof(Member) * a_size);
	Member *b_ms = (Member *)malloc(sizeof(Member) * b_size); 
	memset(b_ms, 0, sizeof(Member) * b_size);
	a->getAllElem(a_ms);//得到a集合所有元素，且从小到大排列
	b->getAllElem(b_ms);//得到b集合所有元素，且从小到大排列
	
	if (a_size > b_size) { //用a作库，用b中的各个元素查找
		for (int i = 0; i < b_size; i++) {
			result_s = AVLTree::SearchAVL(a->elems, b_ms[i].id);
			if (result_s.id != UNINIT)
				fullColl(coll, index++, result_s);
		}
	}
	else {
		for (int i = 0; i < a_size; i++) { //用b作库，用a中的各个元素查找
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

/*集合差集（a - b)，填充coll，并且返回a - b 之后的集合指针*/
ADT * ADT::set_different(Member * coll, ADT * a, ADT * b)
{
	int index = 0; //用于记录coll下标
	bool taller = false; //用于插入元素
	ADT *diffSet = new ADT(); //用于返回值
	int a_size = a->getSize(); //得到a集合大小
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size);
	memset(a_ms, 0, sizeof(Member) * a_size);

	a->getAllElem(a_ms);//得到a集合所有元素，且从小到大排列

	for (int i = 0; i < a_size; i++) { //用b作库，用a中的各个元素查找
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

/*求a,b的并集，返回并集指针，并且填充coll*/
ADT * ADT::set_union(Member * coll, ADT * a, ADT * b)
{
	int index = 0; //用于记录coll下标
	bool taller = false; //用于插入元素
	ADT *unionSet = new ADT(); //用于返回值
	int a_size = a->getSize(); //得到a集合大小
	int b_size = b->getSize(); //得到b集合大小
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size);
	memset(a_ms, 0, sizeof(Member) * a_size);
	Member *b_ms = (Member *)malloc(sizeof(Member) * b_size);
	memset(b_ms, 0, sizeof(Member) * b_size);
	a->getAllElem(a_ms);//得到a集合所有元素，且从小到大排列
	b->getAllElem(b_ms);//得到b集合所有元素，且从小到大排列
	for (int i = 0; i < a_size; i++) { //首先把a中所有元素加入到coll中
		fullColl(coll, index++, a_ms[i]);
	}

	for (int i = 0; i < b_size; i++) { //然后把a中没有，b中有的元素加入到coll中
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

/*判断a是否为b的子集，是返回true，不是，返回false*/
bool ADT::set_subset(ADT * a, ADT * b)
{
	int a_size = a->getSize(); //得到a集合大小
	int b_size = b->getSize(); //得到b集合大小
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size);
	memset(a_ms, 0, sizeof(Member) * a_size);
	Member search_result;
	a->getAllElem(a_ms);//得到a集合所有元素，且从小到大排列
	if (a_size > b_size) //当a的长度大于b时，直接返回false
		return false;
	for (int i = 0; i < a_size; i++) {
		search_result = AVLTree::SearchAVL(b->elems, a_ms[i].id);
		if (search_result.id == UNINIT) //只要有一个元素找不到，那么就不是子集
			return false;
	}
	free(a_ms);
	return true;
}

/*集合相等，相等返回true，不相等返回false*/
bool ADT::set_equal(ADT * a, ADT * b)
{
	int a_size = a->getSize(); //得到a集合大小
	int b_size = b->getSize(); //得到b集合大小
	if (a_size != b_size)
		return false;
	Member *a_ms = (Member *)malloc(sizeof(Member) * a_size);
	memset(a_ms, 0, sizeof(Member) * a_size);
	Member search_result;
	a->getAllElem(a_ms);//得到a集合所有元素，且从小到大排列
	for (int i = 0; i < a_size; i++) {
		search_result = AVLTree::SearchAVL(b->elems, a_ms[i].id);
		if (search_result.id == UNINIT) //只要有一个元素找不到，那么就不相等
			return false;
	}
	free(a_ms);
	return true;
}

//判断是否在集合中，并且返回查找到的数据，如果没有找到返回数据的id为UNINIT
Member ADT::set_member(ADT * a, Member m)
{
	return AVLTree::SearchAVL(a->elems, m.id);
}

 
