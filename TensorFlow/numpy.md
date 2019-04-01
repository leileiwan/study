# dot
numpy 的dot代表的是两个举证的点积运算（矩阵相乘）。

eg
```
In : a = np.arange(1,5).reshape(2,2)
Out:
array([[1, 2],
       [3, 4]])
In : b = np.arange(5,9).reshape(2,2)

Out:
array([[5, 6],
            [7, 8]])


In : np.dot(a,b)
Out:
array([[19, 22],
       [43, 50]])
```