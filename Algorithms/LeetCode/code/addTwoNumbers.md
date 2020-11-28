<!--
 * @Author: taobo
 * @Date: 2020-11-28 20:33:01
 * @LastEditTime: 2020-11-28 20:41:54
-->
# 两数相加
[2. 两数相加](https://leetcode-cn.com/problems/add-two-numbers/)  
给出两个非空的链表用来表示两个非负的整数。其中，它们各自的位数是按照逆序的方式存储的，并且它们的每个节点只能存储一位数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。  
```bash
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
```
  
题目比较简单，直接模拟普通加法就好，比较有意思的点是考虑使用 C++ lambda 表达式简化代码逻辑, 学习下面 `invoke` 对象的写法：  
```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *dump = new ListNode(-1), *p = dump;
    int mod = 0;
    auto invoke = [](ListNode** node) {
        int res = (*node)->val;
        (*node) = (*node)->next;
        return res;
    };
    while (l1 || l2 || mod != 0) {
        int n1 = l1 ? invoke(&l1) : 0;
        int n2 = l2 ? invoke(&l2) : 0;
        int sum = n1 + n2 + mod;
        mod = sum / 10;
        p->next = new ListNode(sum % 10);
        p = p->next;
    }
    p = dump->next;
    delete dump;
    return p;
}
```  


## C++ 函数调用运算符 () 重载
函数调用运算符 () 可以被重载用于类的对象。当重载 () 时，您不是创造了一种新的调用函数的方式，相反地，这是创建一个可以传递任意数目参数的运算符函数。  

下面的实例演示了如何重载函数调用运算符 ():
```cpp
#include <iostream>
using namespace std;
 
class Distance
{
   private:
      int feet;             // 0 到无穷
      int inches;           // 0 到 12
   public:
      // 所需的构造函数
      Distance(){
         feet = 0;
         inches = 0;
      }
      Distance(int f, int i){
         feet = f;
         inches = i;
      }
      // 重载函数调用运算符
      Distance operator()(int a, int b, int c)
      {
         Distance D;
         // 进行随机计算
         D.feet = a + c + 10;
         D.inches = b + c + 100 ;
         return D;
      }
      // 显示距离的方法
      void displayDistance()
      {
         cout << "F: " << feet <<  " I:" <<  inches << endl;
      }
      
};

int main()
{
   Distance D1(11, 10), D2;

   cout << "First Distance : "; 
   D1.displayDistance();

   D2 = D1(10, 10, 10); // invoke operator()
   cout << "Second Distance :"; 
   D2.displayDistance();

   return 0;
}
```
当上面的代码被编译和执行时，它会产生下列结果：
```bash
First Distance : F: 11 I:10
Second Distance :F: 30 I:120
```