#include <iostream>
#include <cassert>
#include <stdexcept>

template <class T>
class Stack {
public:
    Stack() : buffer_size(10), top_index(-1) {
        data_ = new T[buffer_size];
    }
    ~Stack() {
        delete[] data_;
    }
    void push(const T& data) {
        if (top_index == buffer_size - 1)
            this->grow();
        data_[++top_index] = data;
    }
    void pop() {
        if (top_index >= 0) {
            top_index--;
            if (top_index < buffer_size / 4)
                this->cut();
        }
    }
    T& top() {
        assert(top_index >= 0);
        return data_[top_index];
    }
    bool empty() const {
        return top_index == -1;
    }
    size_t size() const {
        return top_index + 1;
    }
    void print() const {
        for (int i = 0; i <= top_index; ++i) {
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    T* data_;
    int buffer_size;
    int top_index;

    void grow() {
        buffer_size *= 2;
        T* new_data = new T[buffer_size];
        for (size_t i = 0; i < buffer_size / 2; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }

    void cut() {
        buffer_size /= 2;
        T* new_data = new T[buffer_size];
        for (size_t i = 0; i < buffer_size; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
};

template <class T>
class stackQueue {
public:
    void enqueue(const T& data) {
        istack.push(data);
    }
    T dequeue() {
        if (ostack.empty()) {
            if (istack.empty())
                return -1;
            while (!istack.empty()) {
                ostack.push(istack.top());
                istack.pop();
            }
        }
        T x = ostack.top();
        ostack.pop();
        return x;
    }
    bool empty() const {
        return (istack.empty() && ostack.empty());
    }
    size_t size() const {
        return istack.size() + ostack.size();
    }
    void print() const {
        std::cout << "input stack" << std::endl;
        istack.print();
        std::cout << std::endl;

        std::cout << "output stack" << std::endl;
        ostack.print();
        std::cout << std::endl;
    }

private:
    Stack<T> istack;
    Stack<T> ostack;
};

int main() {
    stackQueue<int> q;
    int n, a, b;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a >> b;
        if (a == 2) {
            if (q.dequeue() != b) {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }
        else if (a == 3) {
            q.enqueue(b);
        }
    }
    std::cout << "YES" << std::endl;
    return 0;
}
