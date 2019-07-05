
/**
 * version2, 0ms, beats 100%
 * 將version1的dp降為1維，減少一些配置記憶體等時間
 */

int Min3(int a, int b, int c)
int minDistance(char* word1, char* word2){
    int n = 0, m = 0, tmpCrt, tmpNext;
    char crtWord;
    int* dp;
    while(word1[n++]);
    while(word2[m++]);
    
    dp = (int*)malloc(sizeof(int) * (m));
    for(int j = 0; j < m; ++j){
        dp[j] = j;
    }
    
    for(int i = 1; i < n; ++i){
        crtWord = word1[i - 1];
        tmpNext = dp[0];
        dp[0] = i;
        for(int j = 1; j < m; ++j){
            tmpCrt = tmpNext;
            tmpNext = dp[j];
            if(crtWord == word2[j - 1]){
                dp[j] = Min3(dp[j - 1] + 1, dp[j] + 1, tmpCrt);
            }else{
                dp[j] = Min3(dp[j - 1] + 1, dp[j] + 1, tmpCrt + 1);
            }
        }
    }
    return dp[m - 1];
}

int Min3(int a, int b, int c){
    if(a < b){
        if(a < c){
            return a;
        }else{
            return c;
        }
    }
    if(b < c){
        return b;
    }
    return c;
}
