# 项目：生日攻击

## 哈希碰撞

所谓哈希（hash），就是将不同的输入映射成独一无二的、固定长度的值（又称"哈希值"）。它是最常见的软件运算之一。

如果不同的输入得到了同一个哈希值，就发生了"哈希碰撞"（collision）。

![](https://github.com/yuuu218/Innovation-pioneering/blob/main/image/z1.png?raw=true)

举例来说，很多网络服务会使用哈希函数，产生一个 token，标识用户的身份和权限。

```python
AFGG2piXh0ht6dmXUxqv4nA1PU120r0yMAQhuc13i8
```

上面这个字符串就是一个哈希值。如果两个不同的用户，得到了同样的 token，就发生了哈希碰撞。服务器将把这两个用户视为同一个人，这意味着，用户 B 可以读取和更改用户 A 的信息，这无疑带来了很大的安全隐患。

黑客攻击的一种方法，就是设法制造"哈希碰撞"，然后入侵系统，窃取信息。

## 防止哈希碰撞

防止哈希碰撞的最有效方法，就是扩大哈希值的取值空间。

16个二进制位的哈希值，产生碰撞的可能性是 65536 分之一。也就是说，如果有65537个用户，就一定会产生碰撞。哈希值的长度扩大到32个二进制位，碰撞的可能性就会下降到 4,294,967,296 分之一。

更长的哈希值意味着更大的存储空间、更多的计算，将影响性能和成本。开发者必须做出抉择，在安全与成本之间找到平衡。

下面就介绍，如何在满足安全要求的前提下，找出哈希值的最短长度。

## 生日攻击

哈希碰撞的概率取决于两个因素（假设哈希函数是可靠的，每个值的生成概率都相同）。

- 取值空间的大小（即哈希值的长度）
- 整个生命周期中，哈希值的计算次数

这个问题在数学上早有原型，叫做"生日问题"（birthday problem）：一个班级需要有多少人，才能保证每个同学的生日都不一样？

答案很出人意料。如果至少两个同学生日相同的概率不超过5%，那么这个班只能有7个人。事实上，一个23人的班级有50%的概率，至少两个同学生日相同；50人班级有97%的概率，70人的班级则是99.9%的概率（计算方法见后文）。

这意味着，如果哈希值的取值空间是365，只要计算23个哈希值，就有50%的可能产生碰撞。也就是说，哈希碰撞的可能性，远比想象的高。实际上，有一个近似的公式。
$$
\sqrt{\dfrac{\pi}{2}N}
$$
上面公式可以算出，50% 的哈希碰撞概率所需要的计算次数，N 表示哈希的取值空间。生日问题的 N 就是365，算出来是 23.9。这个公式告诉我们，哈希碰撞所需耗费的计算次数，跟取值空间的平方根是一个数量级。

这种利用哈希空间不足够大，而制造碰撞的攻击方法，就被称为生日攻击（birthday attack）。

## 数学推导

这一节给出生日攻击的数学推导。

至少两个人生日相同的概率，可以先算出所有人生日互不相同的概率，再用 1 减去这个概率。

我们把这个问题设想成，每个人排队依次进入一个房间。第一个进入房间的人，与房间里已有的人（0人），生日都不相同的概率是365/365；第二个进入房间的人，生日独一无二的概率是364/365；第三个人是363/365，以此类推。

因此，所有人的生日都不相同的概率，就是下面的公式。
$$
\bar{p}(n)=1\cdot(1-\dfrac{1}{365})\cdot(1-\dfrac{2}{365})\ldots(1-\dfrac{n-1}{365})
$$
上面公式的 n 表示进入房间的人数。可以看出，进入房间的人越多，生日互不相同的概率就越小。

这个公式可以推导成下面的形式。
$$
\dfrac{365!}{365^{n}(365-n)!}
$$
那么，至少有两个人生日相同的概率，就是 1 减去上面的公式。
$$
p(n)=1-\bar{p}(n)=1-\dfrac{365!}{365^{n}(365-n)!}
$$

## 哈希碰撞的公式

上面的公式，可以进一步推导成一般性的、便于计算的形式。

根据泰勒公式，指数函数 ex 可以用多项式展开。
$$
exp(x)=\sum_{k=0}^{\infty}\frac{x^{k}}{k!}=1+x+\frac{x^{2}}{2}+\frac{x^{3}}{6}+\frac{x^{4}}{24}+\ldots
$$
如果 x 是一个极小的值，那么上面的公式近似等于下面的形式。
$$
e^{x}\approx1+x
$$
现在把生日问题的`1/365`代入。
$$
e^{-\frac{1}{365}}\approx1-\frac{1}{365}
$$
因此，生日问题的概率公式，变成下面这样。
$$
\bar{p}(n)\approx1 \cdot e^{-\frac{1}{365}}\cdot e^{-\frac{2}{365}}\ldots e^{-\frac{n-1}{365}}\\
=e^{-\frac{1+2+\ldots+(n-1)}{365}}\\
=e^{-\frac{n(n-1)/2}{365}}=e^{-\frac{n(n-1)}{730}}
$$
假设 d 为取值空间（生日问题里是 365），就得到了一般化公式。
$$
p(n,d)\approx1-e^{-\frac{n(n-1)}{2d}}
$$
上面就是哈希碰撞概率的公式。

## 应用

由此我们可以将它用在碰撞，得到不同Message有着相同tag。

假设：取样次数为$N，M：M_{1}\ldots M_{n}$，取值在 tag:1~B 中，并且假设分布随机均匀相互独立。

取样次数n与B的关系，$n=1.2*B^{0.5}$（这是生日悖论中最坏的情况。）

证明：$M_{2}$不等于$M_{1}$的概率为$\frac{(B-1)}{B}$，同理可得$M_{3}$为$\frac{(B-2)}{B}$，$M_{4}$为$\frac{(B-2)}{B}$...$M_{n}$为$\frac{(B-n+1)}{B}$。

因此，其中有碰撞的概率为：$1-(1-\frac{1}{B})(1-\frac{2}{B})\ldots(1-\frac{k-1}{B})>= (1-e)^{\frac{-n^2}{2B}}$

因为$n=1.2*B^{0.5}$，因此$(1-e)^{\frac{-n^2}{2B}}=1-e^{-0.72}=0.53>50\%$

结论，因此使用生日攻击，我们只需2^(n/2)次寻找，就有50%概率能找到相同tag的两个不同Message。

1. 随机在2^(n/2)信息空间中寻找一个M
2. 求出相应的tag
3. 寻找是否有碰撞，没有则返回步骤1

## 运行指导

直接在C++编译器和pyhton环境运行

## python 运行结果

8 bit:

![](https://github.com/yuuu218/Innovation-pioneering/blob/main/image/z3.png?raw=true)

12 bit:

![](https://github.com/yuuu218/Innovation-pioneering/blob/main/image/z4.png?raw=true)

16 bit:

![](https://github.com/yuuu218/Innovation-pioneering/blob/main/image/z5.png?raw=true)

20 bit:

![](https://github.com/yuuu218/Innovation-pioneering/blob/main/image/z6.png?raw=true)

cpp文件运行结果不成功

## 完成人

李金源

## 参考文献

[抗碰撞性、生日攻击及安全散列函数结构解析](https://blog.csdn.net/Metal1/article/details/79887252?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165874988216782390592038%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&amp;request_id=165874988216782390592038&amp;biz_id=0&amp;utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~pc_rank_34-15-79887252-null-null.142^v33^pc_rank_34,185^v2^control&amp;utm_term=%E7%94%9F%E6%97%A5%E6%94%BB%E5%87%BB&amp;spm=1018.2226.3001.4187)

[哈希碰撞与生日攻击](https://blog.csdn.net/yyyggyy/article/details/108880247)