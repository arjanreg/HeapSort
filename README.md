# HeapSort
A C++ program that implements build_heap and heap-sort functions to construct a max-heap and sort the items in a heap respectively. The values used in implementing these functions are random sets of integers from the input file.

For both methods, the value for n is taken to be the input size, that is, number of elements in the
array. We use the same input for both methods as we are trying to analyse the two algorithms.

For the empirical analysis we measure the number of basic operations performed to construct a
heap (build heap) for a given input size. To analyze the build_heap function, we chose another function, percolate_down, on line 153 as our basic operation. To analyze the heap_sort fucntion, we chose the two functions, build_heap, and percolate_down
in lines 108 and 115 as our basic operations.


