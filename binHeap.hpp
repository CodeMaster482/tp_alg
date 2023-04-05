#include <iostream>
#include <cassert>

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
        gVector(): size_(0), capacity_(0), data_(nullptr) {}
        
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
            if (index < 0 && index > size_)
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
            if (size > size_) {
                this->reserve(size);
                for (int i = size_; i < size; ++i) {
                    data_ = T();
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

template <class T>
class binHeap {
    public:
        binHeap() {
            data_ = gVector<T>();

            data_.push_back(T());
            data_.push_back(T());

            buildHeap();
        }
        explicit binHeap(const T& input_data) {
            data_.push_back(input_data);
            data_.push_back(T());

            buildHeap();
        }

        void insert(T el) {
            data_.push_back(el);
            shiftUp(data_.size() - 1);
        }

        T getMax() {
            assert( !data_.empty() );
            // Запоминаем значение корня.
            int result = data_[0];
            // Переносим последний элемент в корень.
            data_[0] = data_.Last();
            data_.DeleteLast();
            // Вызываем SiftDown для корня.
            if( !data_.IsEmpty() ) {
            siftDown( 0 );
            }
            return result;
        }

        T peekMax() const {
            return data_[0];
        }
    private:
        gVector<T> data_;

        void buildHeap() {
            for (int i = data_.size()/2 - 1; i >= 0; --i) {
                shiftDown(i);
            }
        }

        void shiftDown(int x) {
            int left = 2*x + 1;
            int right = 2*x + 2;

            int max = data_[x];
            if (left < data_.size() && data_[left] > data_[x]) {
                max = data_[left];
            }
            if (right < data_.size() && data_[right] > data_[max]) {
                max = data_[right];
            }

            if (max != x) {
                std::swap(data_[x], data_[max]);
                shiftDown(max);
            }
        }
        void shiftUp(int x) {
            while (x > 0) {
                int parent = (x - 1) / 2;
                
                if (data_[x] <= data_[parent])
                    continue;
                std::swap(data_[x], data_[parent]);
                x = parent;
            }
        }
};