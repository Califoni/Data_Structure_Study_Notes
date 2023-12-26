//定义哈希表元素，每个元素都是一个键值对
typedef struct hashtable{
	int key;
	int value;
	UT_hash_handle hh;
}

hashtable* a;//初始化

hashtable* find(int ikey){
	hashtable*tmp;
	HASH_FIND_INT(a,&ikey,tmp);//从哈希表a中查找key对应的节点，并把指向该节点的指针赋值给tmp
	return tmp;
}

void insert(int ikey,int ival){
	hashtable*item=find(ikey);//判断哈希表中是否已经存在该关键字对应节点
	if(item==NULL){//若不存在则插入
		hashtable*tmp=(hashtable*)malloc(sizeof(hashtable));
		tmp->key=ikey;
		tmp->value=ival;
		HASH_ADD_INT(a,key,tmp);
	}
	else
		item->value=ival;//若已存在则修改对应键值对的值即可
	
}

int* twoSum(int* nums,int numsSize,int target,int *returnSize){
	a=NULL;//初始哈希表置空
	for(int i=0;i<nums;++i){
		hashtable*item=find(target-nums[i]);//判断哈希表是否存在对应节点
		if(item!=NULL){
			int*ret=(int *)malloc(sizeof(int)*2);
			ret[0]=item->value;ret[1]=i;
			*returnSize=2;
			return ret;
		}
		insert(nums[i],i);//以当前元素为关键字，以其在数组中的索引为值，插入哈希表中
	}
	*returnSize=0;
	return NULL;
}

