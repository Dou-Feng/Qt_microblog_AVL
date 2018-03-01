#include "AVLTree.h"
#include <stack>
#include <queue>

/*创建时的初始化函数*/
AVLTree::AVLTree()
{
	this->bf = 0;
	this->lchild = nullptr;
	this->rchild = nullptr;
}
/*创建时的初始化函数*/
AVLTree::AVLTree(int id) 
{
	this->bf = 0;
	this->lchild = nullptr;
	this->rchild = nullptr;
	this->data.id = id;
	strcpy_s(this->data.name, "");
	strcpy_s(this->data.description, "");
}
/*创建时的初始化函数*/
AVLTree::AVLTree(Member e) {
	this->bf = 0;
	this->lchild = nullptr;
	this->rchild = nullptr;
	this->data = e;
}


/*对以当前结点为根的二叉排序树作左旋处理*/
void AVLTree::l_Rotate(AVLTree **p) {

	AVLTree *rc = (*p)->rchild;
	(*p)->rchild = rc->lchild;
	rc->lchild = *p;
	*p = rc;
}

/*对以当前结点为根的二叉排序树作右旋处理*/
void AVLTree::r_Rotate(AVLTree **p) {

	AVLTree *rc = (*p)->lchild;
	(*p)->lchild = rc->rchild;
	rc->rchild = *p;
	*p = rc;
}

/*对以指针T所指结点为根的二叉树作左平衡旋转处理
算法结束时，指针T指向新的根结点*/
void AVLTree::leftBalance(AVLTree **T) {
	AVLTree *lc = (*T)->lchild;  //lc指向*T的左子树根结点
	if (lc == nullptr) return;
	AVLTree *rd = nullptr;
	switch (lc->bf) {  //检查*T的左子树的平衡度，并作相应的平衡处理
	case LH:  //新结点插入在*T的左孩子的左子树上，要做单右旋处理
		(*T)->bf = lc->bf = EH;
		r_Rotate(T);
		break;
	case EH:  //deleteAVL需要，insertAVL用不着  
		(*T)->bf = LH;
		lc->bf = RH;
		r_Rotate(T);
		break;
	case RH:  //新结点插入在*T的左孩子的右子树上，要做双旋处理
		rd = lc->rchild;  //指向*T的左孩子的右子树的根结点
		switch (rd->bf)
		{
		case LH:
			(*T)->bf = RH;
			lc->bf = EH;
			break;
		case EH:
			(*T)->bf = lc->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			lc->bf = LH;
			break;
		default:
			break;
		} //end switch(rd->bf)
		rd->bf = EH;
		l_Rotate(&(*T)->lchild);
		r_Rotate(T);
	} //end switch(lc->bf)
}

/*对以指针T所指结点为根的二叉树作左平衡旋转处理
算法结束时，指针T指向新的根结点*/
void AVLTree::rightBalance(AVLTree **T) {
	AVLTree *rc = (*T)->rchild;  //lc指向*T的右子树根结点
	AVLTree *ld = nullptr;
	switch (rc->bf) {  //检查*T的右子树的平衡度，并作相应的平衡处理
	case RH:  //新结点插入在*T的右孩子的右子树上，要做单左旋处理
		(*T)->bf = rc->bf = EH;
		l_Rotate(T);
		break;
	case EH:  //deleteAVL需要，insertAVL用不着  
		(*T)->bf = RH;
		rc->bf = LH;
		l_Rotate(T);
		break;
	case LH:  //新结点插入在*T的右孩子的左子树上，要做双旋处理
		ld = rc->lchild;  //指向*T的右孩子的左子树的根结点
		switch (ld->bf)
		{
		case RH:
			(*T)->bf = LH;
			rc->bf = EH;
			break;
		case EH:
			(*T)->bf = rc->bf = EH;
			break;
		case LH:
			(*T)->bf = EH;
			rc->bf = RH;
			break;
		default:
			break;
		} //end switch(ld->bf)
		ld->bf = EH;
		r_Rotate(&(*T)->rchild);
		l_Rotate(T);
	} //end switch(rc->bf)
}

/*层序遍历函数，能够按层遍历树，遍历成功返回1，遍历失败返回0*/
Status AVLTree::levelOrderTraverse(AVLTree * T, void(*visit)(Member))
{
	int time = 0;  //记录次数
	long number = 1;
	if (T) {
		//用于存储结点指针的队列
		queue<AVLTree *> q;
		//用于遍历的Node指针
		AVLTree *p;

		q.push(T);
		while (!q.empty()) {
			p = q.front();
			q.pop();
			visit(p->data);
			time++;
			if (time == number) {
				time -= number;
				printf("\n");
				number *= 2;
			}
			if (p->lchild != nullptr) {
				q.push(p->lchild);
			}
			if (p->rchild != nullptr) {
				q.push(p->rchild);
			}
		}
		return 1;
	}
	else {
		return -1;
	}
}

/*递归调用摧毁函数，直到摧毁整棵树*/
Status AVLTree::DestroyAVL(AVLTree **p) {
	if (*p == nullptr)
		return 0;
	if ((*p)->lchild != nullptr) {
		DestroyAVL(&(*p)->lchild);
	}
	if ((*p)->rchild != nullptr) {
		DestroyAVL(&(*p)->rchild);
	}
	if (*p != nullptr) {
		free(*p);
		return 1;
	}
	else {
		return 0;
	}
}

/*搜索结点，AVL的搜索非常迅速，时间总是与log成正比
返回指向目标及结点的指针*/
AVLTree *SearchAVL_Node(AVLTree *T, int key)
{
	AVLTree *p = T; //遍历指针
	while (p != nullptr)
	{
		if (key < p->data.id) {
			p = p->lchild;
		}
		else if (key > p->data.id) {
			p = p->rchild;
		}
		else if (key == p->data.id) {
			return p;
		}
	}
	return nullptr;
}

/*搜索结点，AVL的搜索非常迅速，时间总是与log成正比*/
Member AVLTree::SearchAVL(AVLTree * T, int key)
{
	Member aT;
	AVLTree *p;
	if ((p = SearchAVL_Node(T, key))) {
		aT = p->data;
	}
	return aT;
}

/*若在平衡二叉树T中不存在和e有相同关键字的结点，则插入一个数据元素
为e的新结点，并返回1，否则返回0,。若因插入而使二叉排序树失去平衡，则作
平衡处理。布尔值taller反应T长高与否*/ 
Status AVLTree::InsertAVL(AVLTree **T, Member e, bool &taller) {
	if (!*T) { //当T没有被初始化时
		*T = new AVLTree();
		(*T)->data = e;
		(*T)->bf = EH;
		taller = true;
	}
	else {
        if (e.id == (*T)->data.id || e.id == UNINIT) {
			taller = false;
			return 0;
		} 
		if (e.id < (*T)->data.id) {
			if (!InsertAVL(&(*T)->lchild, e, taller)) return 0;
			if (taller) {
				switch ((*T)->bf) {
				case LH:
					leftBalance(T);
					taller = false;
					break;
				case RH:
					(*T)->bf = EH;
					taller = false;
					break;
				case EH:
					(*T)->bf = LH;
					taller = true;
					break;
				default:
					break;
				} //end switch
			} //end if (taller)
		} 
		else {
			if (!InsertAVL(&(*T)->rchild, e, taller)) return 0;
			if (taller) 
				switch ((*T)->bf) {
				case LH:
					(*T)->bf = EH;
					taller = false;
					break;
				case EH:
					(*T)->bf = RH;
					taller = true;
					break;
				case RH:
					rightBalance(T);
					taller = false;
					break;
				} //end switch
		} //end else
	} // end else
	return 1;
}

/*遍历AVL，使用函数指针*/
Status AVLTree::TraverseAVL(AVLTree *T, void (*f)(Member)) {
	if (T == nullptr)
		return 0;
	
	if (T->lchild != nullptr) {
		TraverseAVL(T->lchild, f);
	}
	if (T != nullptr)
		f(T->data);
	if (T->rchild != nullptr) {
		TraverseAVL(T->rchild, f);
	}
	return 1;
}

//用于后面ADT中得到所有元素，遍历每一个树结点，并且每次都执行f
Status AVLTree::TraverseAVL_n(AVLTree * T, Member *p, int & index, void(*f)(Member *p, int &index, Member *data))
{
	if (T == nullptr)
		return 0;
	if (T->lchild != nullptr) {
		TraverseAVL_n(T->lchild, p, index,  f);
	}
	if (T != nullptr)
		f(p, index, &T->data);
	if (T->rchild != nullptr) {
		TraverseAVL_n(T->rchild, p, index, f);
	}
	return 1;

}

//用于后面ADT的元素个数统计，遍历每一个树结点，并且每次都执行f
Status AVLTree::TraverseAVL_n(AVLTree * T, int & index, void(*f)(int &index))
{
	if (T == nullptr)
		return 0;
	if (T->lchild != nullptr) {
		TraverseAVL_n(T->lchild, index, f);
	}
	if (T != nullptr)
		f(index);
	if (T->rchild != nullptr) {
		TraverseAVL_n(T->rchild, index, f);
	}
	return 1;
}

/*若在平衡的二叉排序树t中存在和e有相同关键字的结点，则删除之
并返回true，否则返回false。若因删除而使二叉排序树
失去平衡，则作平衡旋转处理，布尔变量shorter反映t变矮与否
*/
Status AVLTree::DeleteAVL(AVLTree ** T, int key, bool & shorter)
{
	if (*T == nullptr)
		return 0;
	if (key == (*T)->data.id) {
		AVLTree *q = nullptr;
		if ((*T)->lchild == nullptr) {
			q = *T;
			*T = (*T)->rchild;
			delete q;
			shorter = true;
		}
		else if ((*T)->rchild == nullptr) {
			q = (*T);
			*T = (*T)->lchild;
			delete q;
			shorter = true;
		}
		else {
			q = (*T)->lchild;
			while (q->rchild) {
				q = q->rchild;
			}
			(*T)->data = q->data;
			DeleteAVL(&(*T)->lchild, q->data.id, shorter);
			if (shorter) { //保持原点的平衡需要旋转
				switch ((*T)->bf) {
				case LH:
					(*T)->bf = EH;
					shorter = true;
					break;
				case EH:
					(*T)->bf = RH;
					shorter = false;
					break;
				case RH:
					if ((*T)->rchild->bf == EH) {
						shorter = false;
					}
					else
						shorter = true;
					rightBalance(T);
					break;
				}
			}
		}
	}
	else if (key < (*T)->data.id) {
		if (!DeleteAVL(&(*T)->lchild, key, shorter)) {
			return 0;
		}
		if (shorter) {
			switch ((*T)->bf) {
			case LH:
				(*T)->bf = EH;
				shorter = true;
				break;
			case EH:
				(*T)->bf = RH;
				shorter = false;
				break;
			case RH:
				if ((*T)->rchild->bf == EH) {
					shorter = false;
				}
				else
					shorter = true;		
				rightBalance(T);
				break;
			}
		}
	} 
	else {
		if (!DeleteAVL(&(*T)->rchild, key, shorter)) {
			return false;
		}
		if (shorter) {
			switch ((*T)->bf) {
			case LH:
				if ((*T)->lchild->bf == EH) {
					shorter = false;
				} else
					shorter = true;
				leftBalance(T);
				break;
			case EH:
				(*T)->bf = LH;
				shorter = false;
				break;
			case RH:
				(*T)->bf = EH;
				shorter = true;
				break;
			}
		}
	}
	return 1;
}

/*修改指定id的数据内容，修改成功返回1，没有成功返回0*/
Status AVLTree::modifyAVL(AVLTree ** T, int key, Member m)
{
	bool shorter = false;
	bool taller = false;
	AVLTree *p = SearchAVL_Node(*T, key); //找到目标结点
	if (p) { //能够找到
		//修改
		if (p->data.id == m.id) { //当id相等时
			p->data = m;
		}
		else {
			AVLTree::DeleteAVL(T, key, shorter); //先删除在添加
			AVLTree::InsertAVL(T, m, taller); //再添加
		}
		return 1;
	}
	else {
		return 0;
	}
}

#pragma warning(disable:4996)
/*字符串切割，把切割好的字符串数组存放在coll中，doc为原字符串
seg为切割标记*/
void AVLTree::split(char coll[][150], char * doc, const char * seg)
{
	int index = 0;
	char *str_s = strtok(doc, seg);
	while (str_s != NULL) {
		strcpy(coll[index++], str_s);
		str_s = strtok(NULL, seg);
	}
}


/*从文件中读取数据，读取失败返回0，读取成功返回读取条数*/
Status AVLTree::file_read(AVLTree **T,FILE * f)
{
	if (!f) //打开失败，直接返回false
		return 0;
	Member e;
	char str_gets[200];
	bool taller = false;
	int time = 0;
	while (fscanf(f, "%d", &e.id) &&fgets(str_gets, 200, f) != NULL)
	{
		char str_coll[3][150];
		AVLTree::split(str_coll, str_gets, "|*"); //以|*的分割符切割
		strcpy(e.name, str_coll[0]);
		char str_temp[150];
		strcpy(str_temp, str_coll[1]);
		AVLTree::split(str_coll, str_temp, "\n");  //去掉尾部的\n
		strcpy(e.description, str_coll[0]);
		if (AVLTree::InsertAVL(T, e, taller))
			time++;
	}
	return time;
}

/*储存数据到文件中，储存成功返回1，失败返回0*/
Status AVLTree::file_save(AVLTree * T, FILE * f)
{
	if (!f || !T)
		return 0;
	if (T->lchild != nullptr)
		file_save(T->lchild, f);
	if (T) {
		fprintf(f, "%d|*%s|*%s\n", T->data.id, T->data.name, T->data.description);
	}
	if (T->rchild != nullptr)
		file_save(T->rchild, f);
	return 1;
}



