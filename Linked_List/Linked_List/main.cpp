#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct LNode{
	ElemType data;
	LNode *next;
}LNode,*LinkList;

void CreateLinkList(LinkList &L,int n,ElemType arr[]);

void PrintLinkList(LinkList L);

void ReverseLinkList(LinkList L);

int LinkListLength(LinkList L);

//increase ch before n-th 
bool IncreaseLNode(LinkList &L,int n,ElemType ch);

// delete n-th Node
bool DeleteLNode(LinkList &L,int n);

void DestroyLinkList(LinkList L);

int main(){
	ElemType arr1[10]={'A','A','B','C','D','E','F','G','G','G'};
	LinkList L1=NULL;
	CreateLinkList(L1,10,arr1);
	PrintLinkList(L1);
	printf("%d\n",LinkListLength(L1));

	IncreaseLNode(L1,11,'H');
	PrintLinkList(L1);
	printf("%d\n",LinkListLength(L1));

	DeleteLNode(L1,1);
	PrintLinkList(L1);
	printf("%d\n",LinkListLength(L1));

	ReverseLinkList(L1);
	PrintLinkList(L1);
	ReverseLinkList(L1);
	PrintLinkList(L1);
	return 0;
}

void CreateLinkList(LinkList &L,int n,ElemType arr[]){
	if(L=(LinkList)malloc(sizeof(LNode))){
		L->data=NULL;
		L->next=NULL;
	}
	else{
		exit(0);
	}
	LinkList p=NULL;
	if(n>0){
		if(p=(LinkList)malloc(sizeof(LNode))){
			L->next=p;
			p->data=arr[0];
			p->next=NULL;
		}
		else{
			exit(0);
		}
	}
	if(n>1){
		for(int i=1;i<n;i++){
			if((p->next)=(LinkList)malloc(sizeof(LNode))){
				p=p->next;
				p->data=arr[i];
				p->next=NULL;
			}
			else{
				exit(0);
			}
		}
	}
}//CreateLinkList

void PrintLinkList(LinkList L){
	LinkList p=L->next;
	for(int i=0;p;p=p->next,i++){
		if(i%4==0){
			printf("\n");
		}
		printf("%c  ",p->data);
	}
	free(p);
	printf("\n");
}//PrintLinkList

void ReverseLinkList(LinkList L){
	LinkList p=NULL,q=NULL,s=NULL;
	p=L->next;
	q=p->next;
	s=q->next;
	p->next=NULL;
	while(s->next){
		q->next=p;
		p=q;
		q=s;
		s=s->next;
	}
	q->next=p;
	s->next=q;
	L->next=s;
}//ReverseLinkList

int LinkListLength(LinkList L){
	int len=0;
	for(LinkList p=L->next;p;p=p->next,len++);
	return len;
}//LinkListLength

bool IncreaseLNode(LinkList &L,int n,ElemType ch){
	if(n<1||n>(LinkListLength(L)+1)){
		return false;
	}
	else{
		LinkList p=L,q=NULL;
		if(!(q=(LinkList)malloc(sizeof(LNode)))){
			exit(0);
		}
		for(int i=1;i<n;i++,p=p->next);
		q->next=p->next;
		q->data=ch;
		p->next=q;
		return true;
	}
}//IncreaseLNode

bool DeleteLNode(LinkList &L,int n){
	if(n<1||n>(LinkListLength(L)+1)){
		return false;
	}
	else{
		LinkList p=L;
		for(int i=1;i<n;i++,p=p->next);
		LinkList q=p->next;
		p->next=p->next->next;
		free(q);
		return true;
	}
}//DeteleLNode

void DestroyLinkList(LinkList L){

}