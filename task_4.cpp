#include <iostream>
#include <sstream>
#include <cassert>
#include <string>


void run(std::istream&, std::ostream&);
void testSolution();

template<class T>
class gVector {
    private:
        T* data_;
        int size_;
        int capacity_;

        void grow() {
            if (capacity_ == 0) {
                capacity_ = 1;
            } else {
                capacity_ *= 2;
            }

            T* new_arr = new T[capacity_];

            for (int i = 0; i < size_; ++i) {
                new_arr[i] = data_[i];
            }

            delete[] data_;
            data_ = new_arr;
        }

    public:
        gVector(): size_(0), capacity_(1), data_(new T[capacity_]) {}
        
        gVector(int size): size_(size), capacity_(size) {
            data_ = new T[size];
        }

        gVector(int size, const T& data): capacity_(size), size_(size) {
            data_ = new T[size];
            for (int i = 0; i < size_; ++i) {
                data_[i] = data;
            }
        }

        gVector(const gVector<T>& vector):
            data_(new T[vector.capacity_]),
            capacity_(vector.capacity_),
            size_(vector.size_) {
                for (int i = 0; i < size_; ++i) {
                    data_[i] = vector.data_[i];
                }
        }

        ~gVector() {
            delete[] data_;
        }

        gVector<T>& operator= (const gVector<T>& vector) {
            if (this != &vector) {
                delete[] this->data_;
                capacity_ = vector.capacity_;
                size_ = vector.size_;

                for (int i = 0; i < size_; ++i) {
                    data_[i] = vector.data_[i];
                }
            }
            return *this;
        }

        T& operator[] (int index) const {
            if (index < 0 || index >= size_)
                throw std::out_of_range("index out of range");
            return data_[index];
        }

        bool empty() const {
            return size_ == 0;
        }

        int size() const {
            return size_;
        }

        int get_capacity() const {
            return capacity_;
        }

        void push_back(const T& el) {
            if (size_ == capacity_) {
                this->grow();
            }
            data_[size_++] = el;
        }

        void pop_back() {
            size_--;
        }

        T get_last() const {
            return data_[size_ - 1];
        }

        T get_first() const {
            return data_[0];
        }

        void clear() {
            size_ = 0;
        }

        void reserve(int capacity) {
            if (capacity > this->capacity_) {
                T* new_arr = new T[capacity];
                for (int i = 0; i < size_; ++i) {
                    new_arr[i] = data_[i];
                }
                delete[] data_;
                data_ = new_arr;
                capacity_ = capacity;
            }
        }

        void resize(int size) {
            if (size_ == 0)
                return;
            if (size > size_) {
                this->reserve(size);
                for (int i = size_; i < size; ++i) {
                    data_[i] = T();
                }
                size_ = size;
            } else if (size_ > size) {
                size_ = size;
            }
        }

        void print() {
            if (size_ == 0) {
                std::cerr << "not initalisated vector" << std::endl;
                return;
            }

            std::cout << "[ ";
            for (int i = 0; i < size_ - 1; ++i) {
                std::cout << data_[i] << ", ";
            }
            std::cout << data_[size_ - 1] << " ]" << std::endl;
        }
};

struct element {
    int value;
    size_t value_id;
    size_t array_id;

    element() = default;
    element(int value_, size_t value_id_, size_t array_id_):value(value_), value_id(value_id_), array_id(array_id_) {}
};



template<class T>
class IsLessDefaultCmp {
    public:
    bool operator()(const T& l, const T& r) { return l < r; }
};

bool operator<(const element& l, const element& r) {
    return l.value < r.value;
}

template <class T, class Compare = IsLessDefaultCmp<T>>
class binHeap {
    public:
        binHeap(Compare cmp = IsLessDefaultCmp<T>()): cmp_(cmp) {}
        binHeap(T* arr, int size, Compare cmp = IsLessDefaultCmp<T>()) {
            data_.reserve(size);

            for (int i = 0; i < size; ++i) 
                this->insert(arr[i]);
            buildHeap();
        }

        void insert(const T& el) {
            data_.push_back(el);
            shiftUp(data_.size() - 1);
        }

        T extractMin() {
            if (data_.size() == 1) {
                T root = data_[0];
                data_.resize(0);
                return root;
            }

            T root = data_[0];
            data_[0] = data_[data_.size() - 1];
            data_.resize(data_.size() - 1);

            shiftDown(0);
            return root;
        }


    const T& peek() const {
            return data_[0];
        }

        size_t size() const {
            return data_.size();
        }
    private:
        Compare cmp_;
        gVector<T> data_;

        void buildHeap() {
            for (int i = data_.size()/2 - 1; i >= 0; --i) {
                shiftDown(i);
            }
        }

        void shiftDown(size_t i) {
            size_t parent = i;
            int child = 2 * i + 1;
            while (child < data_.size()) {
                if ((child + 1 < data_.size()) && cmp_(data_[child + 1], data_[child])) {
                    child++;
                }

                if (cmp_(data_[child], data_[parent])) {
                    std::swap(data_[parent], data_[child]);
                    parent = child;
                    child = 2 * parent + 1;
                } else {
                    break;
                }
            }
        }

        void shiftUp(size_t i) {
            while (i > 0) {
                size_t parent = (i - 1) / 2;
                
                if (cmp_(data_[i], data_[parent])) {
                    std::swap(data_[i], data_[parent]);
                    i = parent;
                } else {
                    return;
                }

            }
        }
};

template<class T>
gVector<T> mergeKArrays(const gVector<gVector<T>>& arr) {
    int count_el = 0, k = arr.size();

    gVector<int> length(k);

    for (size_t i = 0; i < k; ++i) {
        length[i] = arr[i].size();
        count_el += length[i];
    }

    gVector<int> result;
    result.reserve(count_el);


    binHeap<element, IsLessDefaultCmp<element>> heap;

    for (size_t i = 0; i < k; ++i) {
        if (length[i] > 0) {
            heap.insert({ arr[i][0], 0, i });
        }
    }

    for (size_t i = 0; i < count_el; ++i) {
        element min_element = heap.extractMin();

        result.push_back(min_element.value);
        
        if (min_element.value_id + 1 < length[min_element.array_id]) {
            int val = arr[min_element.array_id][min_element.value_id + 1];
            size_t index = min_element.value_id + 1;
            size_t array_index = min_element.array_id;
            heap.insert({val, index, array_index});
        }
    }
    return result;
}


void run(std::istream& input, std::ostream& output) {
    int k, n, el;
    input >> k;
    gVector<gVector<int>> arr(k);
    
    for (int i = 0; i < k; ++i) {
        input >> n;

        for (int j = 0; j < n; ++j) {
            input >> el;
            arr[i].push_back(el);
        }
    }

    gVector<int> sorted = mergeKArrays(arr);
    
    for (int i = 0; i < sorted.size(); ++i) {
        output << sorted[i] << " ";
    }

}

int main() {
    testSolution();
    // run(std::cin, std::cout);
    return 0;
}

void testSolution() {
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "<---------------------------------test-1 ------------------------------------->" << std::endl;

        input << '0';

        run(input, output);
        std::cout << output.str() << std::endl;
        assert(output.str() == "");
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "<---------------------------------test-2------------------------------------>" << std::endl;

        input << "2 3 100 200 300 4 10 20 30 40";

        run(input, output);
        std::cout << output.str() << std::endl;
        assert(output.str() == "10 20 30 40 100 200 300");
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "<---------------------------------test-3------------------------------------>" << std::endl;

        input << "3 2 1 3 3 2 4 6 1 5";

        run(input, output);
        assert(output.str() == "1 2 3 4 5 6 ");
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "<---------------------------------test-4------------------------------------>" << std::endl;

        input << "2 5 10 20 30 40 50 1 1000";

        run(input, output);

        assert(output.str() == "10 20 30 40 50 1000 ");
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "<---------------------------------test-5------------------------------------>" << std::endl;

        input << "3 2 1000 2000 3 500 1500 2500 4 10 20 30 40";

        run(input, output);

        assert(output.str() == "10 20 30 40 500 1000 1500 2000 2500 ");
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "<---------------------------------test-6------------------------------------>" << std::endl;

        input << "1 5 1 2 3 4 5";

        run(input, output);

        assert(output.str() == "1 2 3 4 5 ");
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "<---------------------------------test-7------------------------------------>" << std::endl;

        input << "2 4 -10 -5 -2 -1 3 0 1 5";

        run(input, output);

        assert(output.str() == "-10 -5 -2 -1 0 1 5 ");
    }
}