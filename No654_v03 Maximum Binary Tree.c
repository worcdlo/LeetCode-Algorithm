/**
 * 給一個整數陣列
 * 建立Maximum Binary Tree
 * 「對任意子樹」滿足下列規則：
 * 1.根必然為最大值
 * 2.根的左子樹就是數列中在根左邊的數字
 * 3.根的右子樹就是數列中在根右邊的數字
 * [L~~~ root R~~~~]
 */


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * version3, 56ms, 61%
 * 這是看別人寫法的，在舊版的leetcode是跑16ms
 * 新版的leetcode竟然變成56，到今天才發現新版的遞迴成本非常高
 * 不過這依然是相當值得學習的一種寫法
 * 先說我的方法慢在樹的搜尋因為要在節點間跳來跳去很花時間，當然Order也是n(log n)
 * 
 * 這版的寫法如下：
 * 我們都知道根就是當前陣列的最大值
 * 左子樹的根也是左子陣列的最大值
 * 右子樹的根也是右子陣列的最大值
 * 因此寫一個遞迴不斷的往下找子陣列最大值就可以建立整棵樹
 * 遞迴方式有點像quicksort找pivot，不過找pivot的規則不同，也不用做交換，相對單純很多
 */

struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
    if(numsSize == 0){
        return NULL;
    }
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    int maxIdx = 0;
    int maxNum = nums[0];
    
    for(int i = 1; i < numsSize; ++i){
        if(maxNum < nums[i]){
            maxIdx = i;
            maxNum = nums[i];
        }
    }

    node->val = maxNum;
    node->left = constructMaximumBinaryTree(nums, maxIdx);
    node->right = constructMaximumBinaryTree(&nums[maxIdx + 1], numsSize - maxIdx - 1);
    return node;
}


/**
 * version2, 48ms, 62%
 * 減少while回圈內的判斷式 (就是把執行後會break的判斷式拿出來)
 * 不過速度沒變
 */

struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
    int newNum;
    struct TreeNode* root = NULL, *preNode, *crtNode, *newNode;
    root = NewNode(nums[0]);
    
    for(int i = 1; i < numsSize; ++i){
        newNum = nums[i];
        
        preNode = NULL;
        crtNode = root;
        newNode = NewNode(newNum);
        while(crtNode && newNum < crtNode->val){
            preNode = crtNode;
            crtNode = crtNode->right;
        }
        
        if(crtNode == NULL){
            preNode->right = newNode;
        }else{
            if(preNode == NULL){
                root = newNode;
            }else{
                preNode->right = newNode;
            }
            newNode->left = crtNode;
        }
        
    }
    return root;
    
}

/**
 * version1, 48ms, 62%
 * 中規中矩的作法
 * 總之就是從root開始，用新的點往右比node
 * 若新的點一直都比較小，則插入到最右邊
 * 若新的變比某些node大，則將新的點插入，並將那個node接在新點的左邊
 */
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
    int newNum;
    struct TreeNode* root = NULL, *preNode, *crtNode, *newNode;
    root = NewNode(nums[0]);
    
    for(int i = 1; i < numsSize; ++i){
        newNum = nums[i];
        
        preNode = NULL;
        crtNode = root;
        newNode = NewNode(newNum);
        while(1){
            
            if(crtNode == NULL){
                preNode->right = newNode;
                break;
            }else if(crtNode->val < newNum){
                if(preNode == NULL){
                    root = newNode;
                }else{
                    preNode->right = newNode;
                }
                newNode->left = crtNode;
                break;
            }else if(crtNode->val > newNum){
                preNode = crtNode;
                crtNode = crtNode->right;
            }
        }
    }
    return root;   
}


struct TreeNode* NewNode(int num){
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->left = NULL;
    node->right = NULL;
    node->val = num;
    return node;
}

