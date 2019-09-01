# Bottleneck Interval Tree

This data structure represents a bottleneck interval tree, being a modification of the AVL tree. The tree is used to calculate the minimum capacity in a given interval. The tree can be used in many areas that are needed to represent 2D graphs, in Y-axis, you have the used capacity and in the X-axis the time, for example. All the code is built without recursion.

### Prerequisites

To execute the code is needed only a C++ compiler.

## Running the tests

To run the tests execute:

```
    sh run_tests.sh
```

The tests execute in two parts, first checking for memory leaks with Valgrind and later checking the correctness of the code.

### Examples

The tree has the same principles as a pure AVL tree. So, The tests explore the following cases (described by Griffin in [here](https://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct)) and other ones.

```
Consider the following AVL balanced binary trees for an insert operation:

  20+       20+           __20+__
 /         /  \          /       \
4         4    26       4         26
         / \           / \       /  \
        3   9         3+  9    21    30
                     /   / \
                    2   7   11

Inserting either an 8 or a 15 (for example) into any of these trees will trigger essentially the same Left/Right re-balancing, but the results are significantly different for each tree and insert value. To wit, the final landing place of the inserted value and the final balance factors of the node(4) and node(20) are entirely dependent on the relative value of the right child under node(4) - if any. A test solely off any one of these cases does not necessarily prove the correctness of any others. Note: node(4) must initially be balanced for these cases; an initial imbalance in the node(4) ultimately does not affect the node(20).

Case 1a: Insert 15

  20+        20        15
 /          /         /  \
4     =>   15   =>   4    20
  \       /
   15    4

Case 2a: Insert 15

    20+          20++           20++         9
   /  \         /  \           /  \         / \
  4    26 =>   4-   26 =>     9+   26 =>   4+  20
 / \          / \            / \          /   /  \
3   9        3   9-         4+  15       3  15    26
 \       /
  15    3

Case 3a: Insert 15
    __20+__          _20++_           _20++_          ___9___
   /       \        /      \         /      \        /       \
   4       26 =>   4-       26 =>   9+      26 =>   4+      __20__
  / \     /  \    / \      /  \    / \     /  \     / \     /      \
 3+  9   21  30  3+ 9-   21   30   4+ 11- 21   30  3+  7  11-       26
/   / \          /  / \           / \   \         /        \       / \
2  7  11        2  7   11-       3+  7  15       2         15     21 30
                        \       /
                        15     2

Case 1b: Insert 8

  20+      8
 /        / \
4     => 4   20
 \
  8

Case 2b: Insert 8

    20+          20++           20++         9
   /  \         /  \           /  \         / \
  4    26 =>   4-   26 =>     9++  26 =>   4   20-
 / \          / \            /            / \    \
3   9        3   9+         4            3   8    26
                /          / \
               8          3   8

Case 3b: Insert 8

    __20+__             _20++_              __20++_               ___9___
   /       \           /      \            /       \             /       \
  4         26         4-       26         9+        26         4        20-
 / \       /  \       / \      /  \       / \       /  \       / \      /  \
3+  9    21    30 => 3+  9+  21    30 => 4   11   21    30 => 3+  7-  11    26
/  / \              /   / \             / \                  /     \       /  \
2 7  11            2   7- 11           3+  7-               2       8     21  30
                        \             /     \
                         8           2       8

Delete - Double Rebalancing

Now consider these trees for a delete operation:

  2            ___6___               ___5___
 / \          /       \             /       \
1   4        2         9           2         8
   / \      / \       / \         / \       / \
  3   5    1   4     8   B       1   3     7   A
              / \   /   / \           \   /   / \
             3   5 7   A   C           4 6   9   B
                            \                     \
                             D                     C

Delete node(1) from each of these trees. Note that Case 1 conclusively proves Case 2, but not at all Case 3.

Case 4

  2          2            4
 / \          \          / \
1   4    =>    4    =>  2   5
   / \        / \        \
  3   5      3   5        3

Case 5

    ___6___                ___6___                 ___6___
   /       \              /       \               /       \
  2         9            2         9             4         9
 / \       / \            \       / \           / \       / \
1   4     8   B     =>     4     8   B      => 2   5     8   B
   / \   /   / \          / \   /   / \         \       /   / \
  3   5 7   A   C        3   5 7   A   C         3     7   A   C
                 \                      \                       \
                  D                      D                       D

Case 6

    ___5__         _5__            __5__             __8__
   /      \       /    \          /     \           /     \
  2        8     2      8        3       8        _5_      A
 / \      / \    \     / \      / \     / \      /   \    / \
1  3    7   A =>  3   7   A  => 2   4  7   A =>  3    7  9   B
    \  /   / \    \  /   / \          /   / \   / \   /       \
    4 6   9   B    4 6  9   B        6   9   B  2  4 6        C
               \              \                \
                C               C               C
```

## Deployment

To use this data structure into your code, import the header file (interval_tree.hpp).

To construct the tree declare an object as:

```
Interval_Tree::Interval_Tree *interval_tree = new Interval_Tree::Interval_Tree (capacity);
```

You can choose not to insert a capacity for the tree, and then this capacity is set to 0.

To insert a new interval in the tree, call the insert function with the low and high limits and the corresponding capacity. If you try to insert a new interval that already exists in the tree, the algorithm will only sum the capacities.

```
interval_tree->insert(low_interval, high_interval, capacity);
```

To remove an existing interval, call the remove function with the limits and the corresponding capacity. If the capacity to remove from the interval is lower than the current capacity from the node, the algorithm will only reduce the capacity. However, if the capacity to remove and the current node capacity are equals, then the node will be removed.

```
interval_tree->remove(low_interval, high_interval, capacity);
```

The getInterval function returns an object of the Interval_Tree::interval_t type. This function returns an array with all the nodes that overlap the given interval.

```
interval_tree->getInterval(low_interval, high_interval);
```

The getMinValueAvailable function returns a float variable that represents the minimum capacity that exists in the tree that overlaps the given interval.

```
interval_tree->getMinCapacityInterval(low_interval, high_interval);
```

## Built With

* This software built purely in C++.

## Authors

* **Leonardo Rosa Rodrigues** - *Initial work* - [Git](https://github.com/leorrodrigues)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
