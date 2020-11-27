<!--
 * @Author: taobo
 * @Date: 2020-10-28 11:40:57
 * @LastEditTime: 2020-11-06 18:11:21
-->
**C++ 的一个常见面试题是让你实现一个 String 类，限于时间，不可能要求具备 std::string 的功能，但至少要求能正确管理资源。具体来说：**
- 1. 能像 int 类型那样定义变量，并且支持赋值、复制。
- 2. 能用作函数的参数类型及返回类型。
- 3. 能用作标准库容器的元素类型，即 vector/list/deque 的 value_type。（用作 std::map 的 key_type 是更进一步的要求，本文从略）。  

首先选择数据成员，最简单的 String 只有一个 char* 成员变量。好处是容易实现，坏处是某些操作的复杂度较高（例如 size() 会是线性时间）。为了面试时写代码不出错，本文设计的 String 只有一个 char* data_成员。而且规定 invariant 如下：一个 valid 的 string 对象的 data_ 保证不为 NULL，data_ 以 '\0' 结尾，以方便配合 C 语言的 str*() 系列函数。  

其次决定支持哪些操作，构造、析构、拷贝构造、赋值这几样是肯定要有的（以前合称 big three，现在叫 copy control）。如果钻得深一点，C++11的移动构造和移动赋值也可以有。为了突出重点，本文就不考虑 operator[] 之类的重载了。  

这样代码基本上就定型了：  
```cpp
#include <utility>
#include <string.h>

class String
{
 public:
  String()
    : data_(new char[1])
  {
    *data_ = '\0';
  }

  String(const char* str)
    : data_(new char[strlen(str) + 1])
  {
    strcpy(data_, str);
  }

  String(const String& rhs)
    : data_(new char[rhs.size() + 1])
  {
    strcpy(data_, rhs.c_str());
  }
  /* Delegate constructor in C++11
  String(const String& rhs)
    : String(rhs.data_)
  {
  }
  */

  ~String()
  {
    delete[] data_;
  }

  /* Traditional:
  String& operator=(const String& rhs)
  {
    String tmp(rhs);
    swap(tmp);
    return *this;
  }
  */
  String& operator=(String rhs) // yes, pass-by-value
  {
    swap(rhs);
    return *this;
  }

  // C++ 11
  String(String&& rhs)
    : data_(rhs.data_)
  {
    rhs.data_ = nullptr;
  }

  String& operator=(String&& rhs)
  {
    swap(rhs);
    return *this;
  }

  // Accessors

  size_t size() const
  {
    return strlen(data_);
  }

  const char* c_str() const
  {
    return data_;
  }

  void swap(String& rhs)
  {
    std::swap(data_, rhs.data_);
  }

 private:
  char* data_;
};
```

注意代码的几个要点：

- 1. 只在构造函数里调用 new char[]，只在析构函数里调用 delete[]。
- 2. 赋值操作符采用了《C++编程规范》推荐的现代写法。
- 3. 每个函数都只有一两行代码，没有条件判断。
- 4. 析构函数不必检查 data_ 是否为 NULL。
- 5. 构造函数 String(const char* str) 没有检查 str 的合法性，这是一个永无止境的争论话题。这里在初始化列表里就用到了 str，因此在函数体内用 assert() 是无意义的。  

原文：https://coolshell.cn/articles/10478.html