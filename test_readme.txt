The tests were made in two types
test_case refers to only insertion and rotation tests
test2_case refers to deletion tests

Consider the following AVL balanced binary trees for an insert operation:

  20+       20+           __20+__
 /         /  \          /       \
4         4    26       4         26
         / \           / \       /  \
        3   9         3+  9    21    30
                     /   / \
                    2   7   11

Inserting either an 8 or a 15 (for example) into any of these trees will trigger essentially the same Left/Right re-balancing, but the end results are significantly different for each tree and insert value. To wit, the final landing place of the inserted value and the final balance factors of node(4) and node(20) are entirely dependent on the relative value of the right child under node(4) - if any. A test solely off any one of these cases does not necessarily prove the correctness of any others. Note: node(4) must initially be balanced for these cases; an initial imbalance in node(4) ultimately has no effect on node(20).

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

Delete node(1) from each of these trees. Note that Case 1 effectively proves Case 2, but not at all Case 3.

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
