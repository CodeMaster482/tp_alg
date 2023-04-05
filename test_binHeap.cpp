#include <cassert>
#include <iostream>
#include "binHeap.hpp"

void test_binHeap() {
    std::cout << "Testing binHeap...\n";
    binHeap<int> heap1;
    heap1.insert(10);
    heap1.insert(20);
    heap1.insert(15);
    assert(heap1.getMax() == 20);
    assert(heap1.peekMax() == 15);

    

    std::cout << "All binHeap tests passed!\n";
}

int main() {
    test_binHeap();
    return 0;
}
