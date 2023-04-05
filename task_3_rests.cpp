#include <iostream>
#include <vector>

using namespace std;

class Stack {
private:
    vector<int> stack;

public:
    void push(int value) {
        stack.push_back(value);
    }

    int pop() {
        int value = stack.back();
        stack.pop_back();
        return value;
    }

    bool is_empty() {
        return stack.empty();
    }
};

class Queue {
private:
    Stack istack;
    Stack ostack;

public:
    void push_back(int value) {
        istack.push(value);
    }

    bool pop_front(int value) {
        if (ostack.empty()) {
            while (!istack.empty()) {
                ostack.push(istack.pop());
            }
        }

        if (ostack.empty()) {
            return value == -1;
        }

        return ostack.pop() == value;
    }
};

int main() {
    int n;
    cin >> n;

    Queue queue;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;

        if (a == 2) {
            if (!queue.pop_front(b)) {
                cout << "NO" << endl;
                return 0;
            }
        } else {
            queue.push_back(b);
        }
    }

    cout << "YES" << endl;

    return 0;
}