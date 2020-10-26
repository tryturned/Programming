/*
 * @Author: taobo
 * @Date: 2020-10-26 16:50:57
 * @LastEditTime: 2020-10-26 16:59:10
 */
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        bool start=false;
        int sign=1;
        int ans=0;
        for(char& val:str){
            if(!start && val==' '){
                continue;
            }else if(!start && val=='-'){
                start=true;
                sign=-1;
            }else if(!start && val=='+'){
                start=true;
            }else if(val<='9'&&val>='0'){
                start=true;
                int tmp=ans*sign;
                int m=val-'0';
                if((tmp== INT_MAX/10 && m>=7) ||tmp>INT_MAX/10) return INT_MAX;
                if((tmp== INT_MIN/10 && m>=8) ||tmp<INT_MIN/10) return INT_MIN;
                ans=ans*10+m;
            }else{
                break;
            }
        }
        return sign*ans;
    }
};

int main() {
  Solution objs;
  string str = "-123888888845";
  cout << objs.myAtoi(str) << '\n';
  return 0;
}