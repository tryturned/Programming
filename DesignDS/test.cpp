/*
 * @Author: taobo
 * @Date: 2020-10-28 11:41:11
 * @LastEditTime: 2020-11-06 18:01:25
 */
#include <bits/stdc++.h>
using namespace std;

template<class T>
class Shared_Ptr {
private:
  T* _data;
  int* _refCount;
  mutex* _mtx;
public:
  // 构造函数
  Shared_Ptr(T* ptr = nullptr);
  // 拷贝构造
  Shared_Ptr(const Shared_Ptr<T>& sp);
  // 拷贝赋值运算符函数
  Shared_Ptr<T>& operator= (const Shared_Ptr<T>& sp);
  // 析构函数
  ~Shared_Ptr();
  // 增加引用计数
  void addRefCount() {
    unique_lock<mutex> mtx(*_mtx);
    ++(*_refCount);
  }
  // 释放资源
  void release() {
    unique_lock<mutex> mtx(*_mtx);
    if (--(*_refCount) == 0) {
      delete _data;
      delete _refCount;
      delete _mtx;
    }
  }
  // operator*
  T& operator*() {
    return *_data;
  }
  // operator->
  T* operator->() {
    return _data;
  }
  // refcount
  int useCount() {
    return *_refCount;
  }
  // get
  T* get() {
    return _data;
  }
};

template<class T>
Shared_Ptr<T>::Shared_Ptr(T* ptr)
  : _data(ptr),
    _refCount(new int(1)),
    _mtx(new mutex)
    {}

template<class T>
Shared_Ptr<T>::~Shared_Ptr()
{
  release();
}

template<class T>
Shared_Ptr<T>::Shared_Ptr(const Shared_Ptr<T>& sp)
  : _data(sp._data),
    _refCount(sp._refCount),
    _mtx(sp._mtx)
{
  addRefCount();
}

template<class T>
Shared_Ptr<T>& Shared_Ptr<T>::operator= (const Shared_Ptr<T>& sp) {
  if (_data != sp._data) {
    release();
    _data = sp._data;
    _refCount = sp._refCount;
    _mtx = sp._mtx;
    addRefCount();
  }
  return *this;
}

int main() {
  Shared_Ptr<int> sp(new int(10));
  Shared_Ptr<int> copy_sp(sp);
  Shared_Ptr<int> operator_cp(new int(1));
  operator_cp = sp;
  cout << sp.useCount() << ' ' << copy_sp.useCount() << '\n';
  cout << *sp << ' ' << *sp.get() << '\n';
  cout << *operator_cp << '\n';
  return 0;
}