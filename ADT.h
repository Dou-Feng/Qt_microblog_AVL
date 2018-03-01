#pragma once
#include "AVLTree.h"


class ADT
{
public:
	ADT(); //初始化
	void getAllElem(Member *coll); //得到所有元素
	int getSize(); //得到大小
	bool insert(Member coll);  //插入操作
	int insert(Member *coll, int size); //插入操作
	int insert(ADT *A); //插入操作
	bool remove(Member m); //删除操作
	int remove(Member *m, int size); //删除操作
	int remove(ADT *A); //删除操作
	bool modify(int key, Member m); //修改操作
	Member find(int key); //查找操作
	bool destroy(); //摧毁操作
	bool traverse(void (*f)(Member));   //遍历操作
	bool save(FILE *f); //储存到文件
	bool read(FILE *f); //从文件中读取

	static ADT *set_intersection(Member *coll, ADT *a, ADT *b); //求交集
	static ADT *set_different(Member *coll, ADT *a, ADT *b); //求差集
	static ADT *set_union(Member *coll, ADT *a, ADT *b); //求并集
	static bool set_subset(ADT *a, ADT *b); //子集判断
	static bool set_equal(ADT *a, ADT *b); //相等判断
	static Member set_member(ADT *a, Member m); //判断是否属于集合a

public:
	AVLTree *elems; //数据项

};

