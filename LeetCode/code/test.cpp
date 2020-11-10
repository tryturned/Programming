/*
 * @Author: taobo
 * @Date: 2020-10-29 08:25:12
 * @LastEditTime: 2020-11-10 12:21:41
 */
#include <bits/stdc++.h>
using namespace std;

void lcs(vector<int>& nums, vector<int>& res) {
    vector<int> dp, pos(nums.size(), 0);
    for (int i = 0; i < nums.size(); ++i) {
        int left = 0, right = dp.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (dp[mid] < nums[i]) left = mid + 1;
            else right = mid;
        }
        if (right >= dp.size()) {
            dp.push_back(nums[i]);
            pos[i] = dp.size();
        } else {
            dp[right] = nums[i];
            pos[i] = right+1;
        }
    }
    ///////////////////////
    int i, len = dp.size();
    res.resize(len, INT_MAX);
    for (i = nums.size()-1; i >= 0; i--) {
        if (pos[i] == len) {
            res[len-1] = min(res[len-1], nums[i]);
            len--;
        }
    }
}

vector<int> LIS(vector<int>& arr) {
    // write code here
    vector<int> res;
    lcs(arr, res);
    return res;
}





int main() {
    vector<int> arr = {2,1,5,3,6,4,8,9,7};
    vector<int> res = LIS(arr);
    for (int v: res) {
        cout << v << ' ';
    }
    return 0;
}