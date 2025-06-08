/***************************************************
# File Name:    1.两数之和.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年04月06日 星期日 16时57分39秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


int* twoSum(int* nums, int numsSize, int target, int* returnSize) ;

int main(int argc, char *argv[]) {
	int nums1[] = {2,7,11,15};
	int nums2[] = {3,2,4};
	int nums3[] = {3,3};
	int numsSize1 = sizeof(nums1)/sizeof(nums1[0]);
	int numsSize2 = sizeof(nums2)/sizeof(nums2[0]);
	int numsSize3 = sizeof(nums3)/sizeof(nums3[0]);
	int returnSize;
	int *rp = twoSum(nums1,numsSize1,9, &returnSize);
	for(int i = 0; i < returnSize; i++)
	{	
		printf("%d\t",rp[i]);
	}
	printf("\n");
	free(rp);
	return 0;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    if ( numsSize < 2) {
        return NULL;
    }
    int returnNum[2] = {0};
    int *p = returnNum;
    p = malloc(sizeof(returnSize));
    for (int i = 0; i < numsSize; i++) {
        for (int j = numsSize-1; j > 0; j--) {
            if (nums[i] + nums[j] == target) {
                p[0] = i;
                p[1] = j;
                *returnSize = 2;
                return p;
            }
        }
    }
    free(p);
    return NULL;
}
