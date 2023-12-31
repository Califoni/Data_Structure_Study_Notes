class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int>hash;    //哈希表记录待加入元素最后出现的位置
        int ans=0,left=0;
        int i;
        for(i=0;i<s.length();++i){
            char c=s[i];
            if(hash.count(c)){  //如果哈希表中已有该字符
                ans=max(ans,i-left);
                left=max(left,hash[c]+1);//重新确定该字串的起点，若hash[c]+1<left说明此处遇到的重复字符不在不重复字串的范围内
            }
            hash[c]=i;
        }
        return max(ans,i-left);//针对最长不重复字串出现在字符串结尾的情况
    }
};
