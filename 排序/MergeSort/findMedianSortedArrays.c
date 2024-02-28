double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if(nums1Size==0)    return ((double)nums2[nums2Size/2]+(double)nums2[(nums2Size-1)/2])/2;
    if(nums2Size==0)    return ((double)nums1[nums1Size/2]+(double)nums1[(nums1Size-1)/2])/2;
    int numsSize=nums1Size+nums2Size;printf("%d\n",numsSize);
    int* nums=(int*)malloc(sizeof(int)*(numsSize));
    int i=0,j=0,k=0;
    while(i<nums1Size&&j<nums2Size){
        if(nums1[i]>nums2[j]){nums[k]=nums2[j];++j;}
        else{nums[k]=nums1[i];++i;}
        ++k;
    }
    while(i<nums1Size){nums[k]=nums1[i];++i;++k;}
    while(j<nums2Size){nums[k]=nums2[j];++j;++k;}
    for(int l=0;l<numsSize;++l)printf("%d ",nums[l]);
    return ((double)nums[numsSize/2]+(double)nums[(numsSize-1)/2])/2;
}
