### Configuration & Run
--------
1. Install [VSCode](https://code.visualstudio.com/).
2. Follow the guide [CMake Tools for Visual Studio Code](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/README.md).
   1. Install C/C++ extension for VS Code. 
   2. Install CMake Tool extension for VS Code.
   3. Install **MinGW-w64** via [MSYS2](https://www.msys2.org/) follow this [guide](https://code.visualstudio.com/docs/cpp/config-mingw#_installing-the-mingww64-toolchain)
      1. Download MSYS2 and install.
      2. Open MSYS2 terminal and install MinGW-w64 toolchain by running
          
          ``` pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain ```
      3. Add the MinGW-w64 folder to System PATH.
   4. install [CMake](https://cmake.org/download/) and add CMake to System PATH.
3. Open project in VS Code. 
4. From the command palette in VS Code, run the **CMake: Configure command**.
5. From the command palette, run the **CMake: Select a Kit**.
6. From the command palette, run the **CMake: Run** or click **Run** button from the status bar.

### Project Structure
   --------
#### [线性表](https://github.com/Yunme/DataStructure/tree/master/LinearList) 
   包含顺序表和链表。
##### 顺序表 [SqList](https://github.com/Yunme/DataStructure/blob/master/LinearList/SqList.cpp)
   1. 插入元素
   2. 删除元素
   3. 查找元素：按索引查找，按值查找
   4. 遍历等。
##### 单链表 [LinkList](https://github.com/Yunme/DataStructure/blob/master/LinearList/LinkList.cpp)
   1. 插入元素：头插法，尾插法
   2. 删除元素
   3. 查找元素：按索引查找，按值查找
   4. 遍历等。
   
   -  双向链表（前驱指针）
   -  双向循环链表（头结点的前驱指向尾结点，尾结点后继指向头结点）

##### 线性表使用
   1. 线性表的合并 
      - [顺序表实现](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/LinearList/LinearList.cpp#L33)
      - [链表实现](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/LinearList/LinearList.cpp#L18)
   2. 有序线性表的合并
      - [顺序表实现](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/LinearList/LinearList.cpp#L118)
      - [链表实现](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/LinearList/LinearList.cpp#L140)

#### 栈和队列
##### 栈 
   后进新出
   - 栈顶插入元素：入栈
   - 栈顶删除元素：出栈
   1. 顺序栈（[顺序表实现](https://github.com/Yunme/DataStructure/blob/master/StackQueue/SqStack.cpp)）
   2. 链栈（[链表实现](https://github.com/Yunme/DataStructure/blob/master/StackQueue/LinkStack.cpp)）
      - push 元素入栈
      - pop 元素出栈
      - top 返回栈顶元素
   
使用：
- 数值转换
- 表达式求值
- 括号匹配检验
- 八皇后问题
- 函数调用
- 递归调用实现

**栈与递归**：
- 递归定义的数学函数（阶乘，斐波拉契数列）
- 具有递归特性的数据结构（**二叉树**）
- 可递归求解的问题（迷宫问题，汉诺塔问题）


##### 队列
   先进先出
   - 队尾插入元素：入队
   - 队头删除元素：出队
   1. 顺序队列（[顺序表实现](https://github.com/Yunme/DataStructure/blob/master/StackQueue/SqQueue.cpp)）
   2. 链队（[链表实现](https://github.com/Yunme/DataStructure/blob/master/StackQueue/LinkQueue.cpp)）
      - push 元素入队
      - pop 元素出队
      - front 返回队头元素

**循环队列**

使用：
- 脱机打印
- 多用户排队
- 不同优先级队列
- 接收先后处理问题


#### 字符串
   内容是字符的线性表
##### 顺序串
   1. 串比较
   2. 串赋值
   3. 串相连
   4. 求子串
   5. 子串替换
   6. 子串插入
   7. 子串查找
##### 链串
   操作方便，存储密度低

   子串、前缀
   匹配算法 [KMP](https://github.com/Yunme/DataStructure/blob/master/String/SearchString.cpp)

#### 二叉树

##### 概念定义：
- 根结点：无前驱结点的结点
- 结点的度：结点拥有的子树数。
- 叶子：终端结点，度= 0
- 分支结点：根结点以外的度 != 0 
- 双亲结点，孩子结点。
- 兄弟结点：共同的双亲
- 结点的祖先：从根到该结点所经分支的所有结点
- 结点的子孙：以某结点为根的子树中任一结点
- 树的深度：结点的最大层次。

##### 顺序存储 **堆**
##### [链存储](https://github.com/Yunme/DataStructure/blob/master/Tree/BiTree.cpp) 
   1. 深度遍历
      - 先序：根左右
      - 中序：左根右
      - 后序：左右根
   2. 层次遍历
   
遍历应用：
   - 建立二叉树
   - 复制二叉树
   - 计算二叉树深度
   - 计算二叉树结点总数
   - 计算二叉树叶子结点
  
##### 哈夫曼树、哈夫曼编码

#### 图
##### 概念定义：
   - **无向图**：每条边无方向
   - **有向图**：每条边有方向
   - **完全图**：任意两个点都有一条边相连
   - 网：边/弧带权的图
   - 邻接：有边/弧相连的两个顶点之间的关系
   - 顶点的度：与该顶点相关联的边的数目
   - 路径：持续的边构成的顶点序列
   - 简单路径：除路径起点和终点可以相同外，其余顶点均不相同的路径。
   - 连通图（强连通图）任意两顶点存在路径
   - 权与网 图中边或弧所具有的相关数称为**权**，表明一个顶点到另一个顶点的距离
   - 带权的图称为**网**
   - 子图
   - 连通分量 无向图 G 的极大连通子图称为G的连通分量。
    极大连通子图意思是：该子图是G连通子图，将G的任何不在孩子图中的顶点加入，子图不再连通。
   - 极小连通子图：该子图是G的连通子图，在该子图中删除任何一条边，该子图不再连通。
   - 生成树：包含无向图G所有顶点的极小连通子图。不存在回路

##### 邻接矩阵（[顺序表实现](https://github.com/Yunme/DataStructure/blob/master/Graph/AMGraph.cpp)）
#### 邻接表（[链表实现](https://github.com/Yunme/DataStructure/blob/master/Graph/ALGraph.cpp)）
   - 查找顶点是否存在
   - 查找边是否存在
   - 顶点的邻接顶点
   - 新增顶点
   - 删除顶点（及相关的边）
   - 新增边
   - 删除边
   - 深度优先遍历 DFS
   - 广度优先遍历 BFS

使用：
   1. Prim 算法构造最小生成树
      - [邻接矩阵表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L14)
   2. Kruskal 算法构造最小生成树
      - [邻接矩阵表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L120)
      - [邻接表表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L156)
   3. Dijkstra 算法 求有向网的单源点最短路径
      - [邻接矩阵表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L203)
      - [邻接表表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L250)
   5. Floyd 算法求有向网各个顶点间的最短路径
      - [邻接矩阵表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L297)
      - [邻接表表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L322)
   7. 拓扑排序判断有向图中是否有环
      - [邻接矩阵表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L388)
      - [邻接表表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L422)
   9. 关键路径
      - [邻接矩阵表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L454)
      - [邻接表表示](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Graph/GraphAlgorithm.cpp#L500)

#### 查找

##### 顺序表的查找
   有序表：二分查找
##### 树表的查找
- 二叉搜索树 [BST](https://github.com/Yunme/DataStructure/blob/master/Search/BiTreeSearch.cpp)
  
  定义：左子树小于根结点；根结点小于右子树；中序遍历有序。
  - [查找](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Search/BiTreeSearch.cpp#L118)时间复杂度 O(logN)，最坏 O(N);
  - [插入结点](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Search/BiTreeSearch.cpp#L59)
  - 生成 BST: 插入每个元素。
  - [删除结点](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Search/BiTreeSearch.cpp#L155)

- [AVL 平衡二叉树](https://github.com/Yunme/DataStructure/blob/master/Search/AVLSearch.cpp)
  
  为解决 BST 形态不均时查找效率O(N);
  定义：每个结点平衡因子（左右子树高度差）绝对值小于等于1。
  - [失衡调整](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Search/AVLSearch.cpp#L85)

- [红黑树](https://github.com/Yunme/DataStructure/blob/master/Search/RedBlackTree.cpp)
   
   自平衡二叉树，性质：

  1. 结点是红色或黑色；
  2. 根是黑色；
  3. 不能有连续的红色结点
  4. 从任一结点到每个叶子结点路径包含相同数量的黑色结点。
  5. 结论: 如果某结点只有一个子树，那么一定子树一定是红色的（如果是黑色的不满足4）
  6. 同5，红色结点不可能只有一个子树。
   

 - [插入及失衡调整](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Search/RedBlackTree.cpp#L147)
 - [删除及失衡调整](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Search/RedBlackTree.cpp#L233)

| 操作         | BST                | AVL 树         | 红黑树         |
|--------------|--------------------|----------------|----------------|
| 搜索         | 平均：O(log n)      | 平均：O(log n) | 平均：O(log n) |
|              | 最坏：O(n)         | 最坏：O(log n) | 最坏：O(log n) |
| 插入         | 平均：O(log n)      | 平均：O(log n) | 平均：O(log n) |
|              | 最坏：O(n)         | 最坏：O(log n) | 最坏：O(log n) |
| 删除         | 平均：O(log n)      | 平均：O(log n) | 平均：O(log n) |
|              | 最坏：O(n)         | 最坏：O(log n) | 最坏：O(log n) |
| 平衡维护     | 不适用             | 平均：O(log n) | 不适用         |
|              |                    | 最坏：O(log n) |                |
| 空间复杂度   | 平均：O(n)          | 平均：O(n)     | 平均：O(n)     |
|              | 最坏：O(n)         | 最坏：O(n)     | 最坏：O(n)     |

##### [哈希表](https://github.com/Yunme/DataStructure/blob/master/Search/HashTable.cpp)
   记录的存储位置与关键字之间存在对应关系，对应关系：hash 函数

   1. 散列函数构造（直接定址法，除留余数法等）
   2. 冲突解决 (开放定址法，拉链法)


#### 排序
- [插入排序](https://github.com/Yunme/DataStructure/blob/master/Sort/InsertSort.cpp)

   每步将一个待排序的对象，按其关键码大小，插入到前面已经排好序的一组对象的适当位置上，直到对象全部插入为止。
    - [直接插入排序](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Sort/InsertSort.cpp#L11) O(n^2)（采用顺序查找法查找插入位置）
    - [二分插入排序](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Sort/InsertSort.cpp#L68) O(n^2)（采用二分查找法查找插入位置）
    - 希尔排序
- [交换排序](https://github.com/Yunme/DataStructure/blob/master/Sort/SwapSort.cpp)

   两两排序，如果发生逆序则交换，直到所有记录都排好序为止
    - [冒泡排序](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Sort/SwapSort.cpp#L10) O(n^2)（每趟不断将记录两两比较，并按“前小后大”规则交换。）
    - [快速排序](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Sort/SwapSort.cpp#L52) O(nlogN)
      -  任取一个元素为中心 pivot
      - 所有比它小的元素一律前放，比它大的元素一律后放，形成**左右两个子表**
      - 对各子表重新选择中心元素依此规则调整
      - 直到每个子表中剩**一个元素**

- [选择排序](https://github.com/Yunme/DataStructure/blob/master/Sort/SelectionSort.cpp)

   每一趟从待排序的记录中选出最小的记录，按顺序放在已排序的记录最后，直到排完。
    - [简单选择排序](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Sort/SelectionSort.cpp#L10) O(n^2)（在待排序的数据中选出最小的元素放在其最终位置。）
    - [堆排序](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Sort/SelectionSort.cpp#L46) O(nlogN)
      - **根大于左右孩子：大根堆**，**根小于左右孩子：小根堆**
      - 堆的调整
      - 堆的建立

- [归并排序](https://github.com/Yunme/DataStructure/blob/00e3fa086244b9ac8041a6d63a88f9c100bbca83/Sort/SelectionSort.cpp#L63C6-L63C16) O(nLogN)

   将两个或两个以上的有序子序列归并为一个有序序列。
    - 2路归并排序

- [基数排序](https://github.com/Yunme/DataStructure/blob/master/Sort/RadixSort.cpp) O(k*(n + m))

   分配 + 收集。设置若干个箱子，将关键字为k的记录放入第k个箱子，然后再按序号将非空的箱子连接。