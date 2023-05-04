#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>

void run(std::istream&, std::ostream&);
void test();

enum state {
    EMPTY,
    FULL,
    DELTE
};


template<class T, class H>
class HashTable {
public:
    HashTable(H hasher): hasher_(hasher) {}
    HashTable(const size_t size, H hasher): size_(size){}

    ~HashTable() = default;

    bool Has(const T& el);

    bool Add(const T& el) {
        for (int i = 0; i < size_; ++i) {
            int j = h
        }
    }

    bool Pop(const T& el);
private:
    struct HashTableNode {
        T data_;
        state has_data {EMPTY};

        HashTableNode() = default;
        HashTableNode(const T& data, unsigned int hash): data_(data), abs_hash_(hash), has_data(FULL) {}
    };

    size_t size_;
    size_t capacity_;
    std::vector<HashTableNode> table_;
    H hasher_;

    double grow_default_ = 2.0;
    double load_factor_ = 0.75;

    [[nodiscard]] unsigned int hash(const unsigned int abs_hash) const {
        return abs_hash % capacity_;
    }

    void growTable() {
        size_t new_capacity = capacity_ * grow_default_;
        std::vector<HashTableNode> new_tabele(new_capacity, this->size_, hasher_);


    }
};

int main (const int argc, const char* argv[]) {
    run(std::cin, std::cout);
    // test();
    return 0;
}

void run(std::istream& in, std::ostream& out) {
    return;
}


void test() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "+ hello\n + bye\n ? bye\n + bye\n - bye\n ? bye\n ? hello\n";

        run(in, out);

        assert(out.str() == "OK\n OK\n OK\n FAIL\n OK\n FAIL\n OK");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "+ hello\n + bye\n ? bye\n + bye\n - bye\n ? bye\n ? hello\n";

        run(in, out);

        assert(out.str() == "OK\n OK\n OK\n FAIL\n OK\n FAIL\n OK");
    }
}