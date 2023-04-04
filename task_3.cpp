// Copyright 2023 CodeMaster482
#include <iostream>
#include <cassert>
#include <sstream>
#include <cstring>

void test_solution();

template <class T>
class Stack {
    public:
        Stack(): buffer_size(10), top_index(-1) {
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
                top_index --;
                if (top_index < buffer_size/4)
                    this->cut();
            }
        }

        T& top() {
            assert (top_index >= 0);
            return data_[top_index];
        }

        bool empty() const {
            return top_index == -1;
        }

        size_t size() const {
            return top_index + 1;
        }

        void print() const{
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
            for (size_t i = 0; i < buffer_size/2; ++i) {
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

        bool empty() const{
            return (istack.empty() && ostack.empty());
        }

        size_t size() const{
            return istack.size() + ostack.size();
        }

        void print() const{
            std::cout << "input stack" << std::endl;
            istack.print();
            std::cout << std::endl;

            std::cout << "output stack" << std::endl;
            ostack.print();
            std::cout << std::endl;
        }


    private:
        Stack <T> istack;
        Stack <T> ostack;
};


class Soulution {
    public:
    bool solutionFunc(int n, std::istream& input) {
        bool result = true;
        stackQueue<int> q1;
        int a, b;
        for (int i = 0; i < n; ++i) {
            input >> a >> b;

            if (a == 2) {
                if (q1.dequeue() != b)
                    result = false;
            } else if (a == 3) {
                q1.enqueue(b);
            }
        }

        return result;
    }
};


void run(std::istream& input, std::ostream& output) {
    output << "-------- Task 3 compilation -------------" << std::endl;
    Soulution solution;
    int n;
    
    input >> n;
    if (solution.solutionFunc(n, input)) {
        output << "YES";
    } else {
        output << "NO";
    }
}

void test_run_Stack(std::istream& input, std::ostream& output) {
    output << "-------- Task 3 compilation -------------" << std::endl;
    Stack<int> q1;
    output << "status ok ....." << std::endl;
    Stack<char> q2;
    Stack<double> q3;

    q1.push(1);
    output << "status ok ....." << std::endl;
    q1.push(2);
    q1.push(3);
    q1.push(5);
    q1.push(7);
    q1.print();
    q1.pop();
    q1.pop();
    q1.print();

    q2.push('a');
    q2.push('b');
    q2.push('c');
    q2.push('d');
    q2.push('e');
    q2.print();
    q2.pop();
    q2.pop();
    q2.print();

    q3.push(3.14);
    q3.push(2.71);
    q3.print();
    q3.pop();
    q3.print();
}

void test_run_Queue(std::istream& input, std::ostream& output) {
    stackQueue<int> q1;
    stackQueue<char> q2;
    stackQueue<double> q3;

    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(5);
    q1.enqueue(7);
    q1.print();
    q1.dequeue();
    q1.dequeue();
    q1.print();

    q2.enqueue('a');
    q2.enqueue('b');
    q2.enqueue('c');
    q2.enqueue('d');
    q2.enqueue('e');
    q2.print();
    q2.dequeue();
    q2.dequeue();
    q2.print();

    q3.enqueue(3.14);
    q3.enqueue(2.71);
    q3.print();
    q3.dequeue();
    q3.print();
}

int main() {
    test_run_Queue(std::cin, std::cout);
    // test_solution();
    return 0;
}

void test_solution() {
    char yes[] = "YES\n";
    char no[] = "NO";
    {
        std::stringstream input;
        std::stringstream output;

        input << "3 3 44 3 50 2 44";
        run (input, output);
        // assert(strcmp(output.str(), yes));
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2 2 -1 3 10";
        run (input, output);
        assert(output.str() == "YES");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2 3 44 2 66";
        run (input, output);
        assert(output.str() == "NO");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "5 3 1 3 2 2 1 2 2 2 3";
        run (input, output);
        assert(output.str() == "NO");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "4 3 1 3 2 2 1 2 2";
        run (input, output);
        assert(output.str() == "YES");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "0";
        run (input, output);
        assert(output.str() == "YES");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "1 4 3";
        run (input, output);
        assert(output.str() == "NO");
    }
    
    
    
}
