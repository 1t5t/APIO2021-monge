这里记录了一些当时在做课件的时候翻阅的文献和当时的一些笔记，年代久远所以内容不保真。

## 1. Perspectives of Monge properties in optimization

介绍四边形不等式矩阵的基本性质与生成方式，以及在组合优化问题里的应用，包括二分图匹配与运输问题、行列最值查询、动态规划优化、旅行商问题，后面还有一系列类似四边形不等式的定义和运用，不过我没看。总结向文章，一些具体的内容还需要查询相应 reference。

## 2. Geometric Applications of A Matrix Searching Algorithm

介绍针对完全单调矩阵的 SMAWK 算法。同时给出了常见的分治求解单调矩阵的行最值问题的算法并使用 adversary argument 方式证明了单调矩阵上最值求解问题的复杂度下界。

## 3. Efficient Minimum Cost Matching Using Quadrangle Inequality

首先介绍了在环上和直线上的以距离为权的带权二分图匹配和运输问题的快速做法，然后介绍了边权为 **双调** monge 矩阵时求解带权二分图匹配和运输问题的高效做法。

- "Transportation problem on a line" 最后部分的算法流程是这样的：把拆开的蓝色点看作 +1，红色点看作 -1，那么每一条链的蓝点部分就是前缀和相同的位置连成的，然后对前缀和值扫描线可以发现 （当前点所在的 node、它的蓝色后继所在的 node）这个二元组的数量是 $O(m)$ 的。所以如果可以快速转移复杂度就可以接受。每个 node 的平衡树以前缀和作为下标，维护子树反转代价的最小值以进行删最小值，这样把转移的区间枚出来之后就可以用 FHQ Treap 的基础操作 $O(\log m)$ 转移代价，同时一起转移的部分代价的变化也一定是一样的。这样就可以做到 $O((m+n) \log (m+n))$。

## 4. Efficient Dynamic Programming Using Quadrangle Inequalities

介绍最优搜索树的 $O(n^3)$ 区间型动态规划通过四边形不等式进行优化得到 $O(n^2)$ 算法的流程，同时介绍了该算法在多叉树上的拓展，也得到了一个复杂度优秀的算法。

## 5. The D-Edge Shortest-Path Problem for a Monge Graph

介绍了决策单调性序列划分问题中给定序列长度的最短路对应的函数的凸性。

## 6. Finding a minimum-weight K-link path in graphs with Monge property and applications

决策单调性序列划分问题的与值域无关的强多项式算法，但复杂度相当高所以大部分情况下都不如斜率凸优化加二分栈 DP，所以没看。

## 7. Submatrix maximum queries in Monge matrices and partial Monge matrices, and their applications

满足四边形不等式的矩阵的子矩阵最大值查询，还介绍了在另外一类与四边形不等式相关的矩阵上的子矩阵最大值查询，不过与主题无关所以没看。

## 8. Improved Submatrix Maximum Queries in Monge Matrices

对论文 7 的算法进行改进，但在四边形不等式阵上要用 $O(n)-O(1)$ rmq 所以没看。

## 9. Well-Solved Special Cases of the Traveling Salesman Problem

介绍了若干旅行商问题的特殊情形。10 的前置结论“任意一个满足四边形不等式的矩阵均存在一个最短哈密顿回路是金字塔回路”的结论在 pyramidral tour 部分里。这给出了 $O(n^2)$ 的朴素做法。

## 10. A special case of the n-vertex traveling salesman problem that can be solved in O(n) time

利用 9 的前置结论给出金字塔回路的 dp 并转化为平行的决策单调性 dp 形式，使用 12 中的算法解决可以线性。

## 11. The Concave Least-Weight Subsequence Problem Revisited

介绍了形如 $f_i = \min_{j<i} f_j+w_{j,i}$ 这类与前面计算的值有关的决策单调性动态规划的线性算法。

## 12. Sequence Comparison with Mixed Convex and Concave Costs

对 11 的算法进行了简单的拓展，使得该算法仍然线性，且在 $f_{i+1}$ 求解前已知 $f_1 \sim f_i$ 的值。这可以在 11 的基础上解决多个决策单调性动态规划交错影响的例子，包括 10 和 12 中的例子。由于上下凸权值求解部分与本文无关所以没看，只看了交错求解部分。

## 13. The Knuth-Yao Quadrangle-Inequality Speedup is a Consequence of Total-Monotonicity

介绍了如何对 4 中的二叉树 dp 算法使用 SMAWK $O(n^2)$ 完成计算。同时介绍了动态在开头末尾加入键值并维护动态规划的单次 $O(n)$ 算法，但没看。