#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode{
	char data;
	BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void CreateBiTree(BiTree &T);

void PostOrderTraverse(BiTree T,void (* Visit)(char));

void PrintData(char ch);

void (* Visit)(char);

int main(){
	BiTree T1;

	printf("Input a Tree:");
	CreateBiTree(T1);

	Visit=&PrintData;
	PostOrderTraverse(T1,Visit);

	return 0;
}

void CreateBiTree(BiTree &T){
	char ch=' ';
	scanf("%c",&ch);
	if(ch!='.'){
		if(T=(BiTree)malloc(sizeof(BiTNode))){
			T->data=ch;
			CreateBiTree(T->lchild);
			CreateBiTree(T->rchild);
		}
	}
	else{
		T=NULL;
	}
}//CreateBiTree

void PostOrderTraverse(BiTree T,void (* Visit)(char)){
	if(T){
		PostOrderTraverse(T->lchild,Visit);
		PostOrderTraverse(T->rchild,Visit);
		Visit(T->data);
	}
}//PostOrderTraverse

void PrintData(char ch){
	printf("%c\n",ch);
}//PrintData

