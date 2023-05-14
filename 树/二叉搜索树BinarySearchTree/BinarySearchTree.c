//给定一串数字，利用这串数字从头开始构建一棵二叉搜索树
#include<stdio.h>
#include<stdlib.h>
/*
构建二叉搜索树，其性质是左子树必定小于父节点，右子树必定大于父节点
这个优秀的性质使得对上述数组进行搜索操作的时间复杂度为O(logN)，
	即对于一个要搜索的值val，每次判断val与当前节点的值data的大小
		若val==data,返回即可
		若val>data,进入右子树继续搜索(因为右子树的数都比当前节点大)
		若val<data,进入左子树继续搜索(因为左子树的数都比当前节点小)
上述方法也是二分法的思想
*/
typedef struct Node{
    int data;
    struct Node*left;
    struct Node*right;
}node;

//树结构指向一个节点的指针，相当于二重指针的效果，因而能实现在首节点为空的情况下可以在函数中更改指针变量的值
typedef struct Tree{
    node*root;
}tree;

void insert(tree*t,int val){
    node*tmp=malloc(sizeof(node));
    tmp->data=val;
    tmp->left=NULL;
    tmp->right=NULL;
    
    if(t->root==NULL){
        t->root=tmp;return;
    }
    
    node*p=t->root;
    while(p!=NULL){
        //父节点的值小于插入值，往右子树走
        if(val>p->data){
            if(p->right==NULL){p->right=tmp;return;}
            else p=p->right;
        }
        else{
            if(p->left==NULL){p->left=tmp;return;}
            else p=p->left;
        }    
    }
    return;
}

//二叉树的先序中序后序三个遍历，用于测试构建的二叉搜索树是否正确
void Preorder(node*root){
    if(root!=NULL){
        printf("%d  ",root->data);
        Preorder(root->left);
        Preorder(root->right);
    }
    return;
}

void Midorder(node*root){
    if(root!=NULL){
        Midorder(root->left);
        printf("%d  ",root->data);
        Midorder(root->right);
    }
    return;
}

void Postorder(node*root){
    if(root!=NULL){
        Postorder(root->left);
        Postorder(root->right);
        printf("%d  ",root->data);
    }
    return;
}


int main(){
    int *nums=malloc(sizeof(nums)*6);
    tree t;
    t.root=NULL;
    for(int i=0;i<6;i++){
        scanf("%d",&nums[i]);
        insert(&t,nums[i]);
    }
    
    Preorder(t.root);
    printf("\n");
    Midorder(t.root);
    return 0;
}