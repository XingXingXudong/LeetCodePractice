/**
 * 使用vector实现最大堆的关键算法
 * 最大堆可以在O(1)的时间内获取最大值，可以在O(logN)的时间内取出最大值或者插入任意值
 **/

#include <vector>
#include <gtest/gtest.h>

class MaxHeap {
    private:
    std::vector<int> heap;
    public:
    int top() {
        return heap[0];
    }
    void push(int k) {
        heap.push_back(k);
        swim(heap.size() - 1);
    }
    void pop() {
        heap[0] = heap.back();
        heap.pop_back();
        sink(0);
    }
    void swim(int pos) {
        while(pos >= 1 && heap[pos/2] < heap[pos]) {
            std::swap(heap[pos/2], heap[pos]);
            pos /= 2;
        }
    }
    void sink(int pos) {
        while(2 * pos < (int)heap.size()) {
            int i = 2 * pos;
            if (i < (int)heap.size() && heap[i] < heap[i + 1]) {
                ++i;
            }
            if (heap[pos] >= heap[i]) {
                break;
            }
            std::swap(heap[pos], heap[i]);
            pos = i;
        }
    }
};

TEST(maxHeap, a) {
    MaxHeap* max_heap = new MaxHeap();
    max_heap->push(2);
    EXPECT_EQ(max_heap->top(), 2);
    max_heap->push(3);
    EXPECT_EQ(max_heap->top(), 3);
    max_heap->push(1);
    EXPECT_EQ(max_heap->top(), 3);
    max_heap->push(4);
    EXPECT_EQ(max_heap->top(), 4);
    max_heap->pop();
    EXPECT_EQ(max_heap->top(), 3);
    max_heap->pop();
    EXPECT_EQ(max_heap->top(), 2);
    max_heap->pop();
    EXPECT_EQ(max_heap->top(), 1);
    max_heap->pop();
    EXPECT_EQ(max_heap->top(), 1);

    delete max_heap;
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}