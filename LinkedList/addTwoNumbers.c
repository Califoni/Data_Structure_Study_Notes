/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int c=0;//进位器
    int sum=0;
    struct ListNode*head=(struct ListNode*)malloc(sizeof(struct ListNode));//初始化结果链表头指针
    head->next=NULL;
    struct ListNode*p=head;
    while(l1!=NULL||l2!=NULL){
        if(l1!=NULL&&l2!=NULL){
            sum=(l1->val+l2->val+c);
            l1=l1->next;
            l2=l2->next;
        }        
        else if(l1!=NULL&&l2==NULL){
            sum=(l1->val+c);
            l1=l1->next;
        }
        else{
            sum=(l2->val+c);
            l2=l2->next;
        }
        c=sum/10;
        struct ListNode*node=(struct ListNode*)malloc(sizeof(struct ListNode));
        node->next=NULL;
        if(c==1)    node->val=sum-c*10;
        else        node->val=sum;
        p->next=node;
        p=p->next;
    }
    //遍历完全部节点后若有进位还需加上一位
    if(c==1){
        struct ListNode*node=(struct ListNode*)malloc(sizeof(struct ListNode));
        node->next=NULL;node->val=1;
        p->next=node;
        p=p->next;
    }
    head=head->next;
    return head;
}
