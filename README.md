# General Information
## HTree
This is, more or less, the same library as implemented in Homework #6,
but implemented using classes instead of structs.
It was written by Tucker R. Twomey and Julian Jacklin.

The authoritative specification of the HTree class and its methods is contained
in the `htree.hh` file.
The accessor, constructor, and destructor functions are fairly trivial.
The `path_to()` function is written recursively.
The `node_at()` function is not present in this version because the effort to
rewrite it encountered difficulties.

## HForest
The HForest class stores HTrees in a heap.
The class stores the trees in a vector,
and uses `std::make_heap()` and associated functions to turn said vector into a
heap,
allowing logarithmic-time removal of the lowest element.

The authoritative specification of the HForest class and its methods can once
again be found in `hforest.hh`.
There are two noted deviations from the assignment:
first, the constructor can be called with a `std::vector<HTree::tree_ptr_t` to
turn a pre-existing vector of trees into an HForest.
Second, the `pop_tree()` method returns `nullptr` if the forest contains zero
trees.

# Compiling and Testing
The compilation process for this library is fairly standard;
use the included `Makefile` directly.
```
% make -j4 test_htree test_hforest # if your machine has 4 CPU cores
% ./test_htree
% ./test_forest
```
