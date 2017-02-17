# **function语义学**

> _**Author:邱雨波**_
>
> _**2017年2月16日更新**_

> 本节讨论函数语义问题  

## **1.Member的各种调用方式**

### **1.1Nonstatic Member Functions**

C++的设计准则之一就是：nonstatic member function至少必须和一般的nonmember function相同的效率。也就是说，如果我们要在以下两个函数之间作选择：

```c++
void func(){};
void A::func(){};
```

那么选择member function不应该带来什么额外负担。这是因为编译器内部将“member函数实体”转换成对等的“nonmember函数实体”。