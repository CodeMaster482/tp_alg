/*
#include <iostream>
#include <cassert>
#include <sstream>


void testSoultion();
void run(std::istream& input, std::ostream& output);
int binSearch(int* arr, int l, int r, int aim);
int expSearch(int* right_arr, int length, int aim);

class Solution {
    public:
        int* idInsertion (int* a, int n, int* b, int m, int* result);
};


int main() {
    run(std::cin, std::cout);
    // testSoultion();
    return 0;
}


void run (std::istream& input, std::ostream& output) {
    Solution solution;
    int n, m;

    input >> n >> m;

    int* a = new int[n];
    int* b = new int[m];
    int* result = new int[m];

    for (int i = 0; i < n; ++i) {
        input >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        input >> b[i];
    }

    solution.idInsertion(a, n, b, m, result);
    
    for (int i = 0; i < m - 1; ++i) {
        output  << result[i] << " ";
    }

    output << result[m - 1] << std::endl;
    
    delete[] a;
    delete[] b;
    delete[] result;
}


int expSearch(int* right_arr, int length, int aim) {

    if (right_arr[0] == aim)
        return 0;
    
    int i = 1;

    while (i < length && right_arr[i] <= aim) {
        i *= 2;
    }
    
    return binSearch(right_arr, i/2, std::min(length - 1, i), aim); 
}


int binSearch(int* arr, int l, int r, int aim) {
    int mid;
    
    while (l <= r) {
        mid = (l + r) / 2;

        if (arr[mid] == aim)
            return mid;
        
        if (aim < arr[mid])
            r = mid - 1;
        
        if (aim > arr[mid])
            l = mid + 1;
    }
    return l;
}


int* Solution::idInsertion (int* a, int n, int* b, int m, int* result) {
    for (int i = 0; i < m; ++i) {
        int index = expSearch(a, n, b[i]);

        if (index < n && a[index] >= b[i]) {
            result[i] = index;
        } else {
            result[i] = n;
        }
    }
    return result;
}

void testSoultion() {
    std::stringstream input;
    std::stringstream output;

    input << "3 3\n1 3 4\n2 3 4\n";
    run(input, output);
    assert(output.str() == "0 2 2\n");

    input.str("");
    output.str("");
    input.clear();
    output.clear();

    input << "5 5\n0 5 5 5 5\n5 5 5 5 5\n";
    run(input, output);
    assert(output.str() == "1 4 4 4 4\n");

    input.str("");
    output.str("");
    input.clear();
    output.clear();

    input << "5 5\n0 5 5 5 5\n1 1 1 1 1\n";
    run(input, output);
    assert(output.str() == "0 0 0 0 0\n");
}
*/
#include <iostream>
#include <cassert>
#include <sstream>

// Binary Search
int binSearch(int* arr, int l, int r, int aim);

// Exponential Search
int expSearch(int* right_arr, int length, int aim);

// Insertion Helper
class Solution {
public:
    int* idInsertion (int* a, int n, int* b, int m, int* result);
};

void run(std::istream& input, std::ostream& output);

void testSoultion();

int main() {
    testSoultion();
    return 0;
}

void run (std::istream& input, std::ostream& output) {
    Solution solution;
    int n, m;

    input >> n >> m;

    int* a = new int[n];
    int* b = new int[m];
    int* result = new int[m];

    for (int i = 0; i < n; ++i) {
        input >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        input >> b[i];
    }

    solution.idInsertion(a, n, b, m, result);

    for (int i = 0; i < m - 1; ++i) {
        output  << result[i] << " ";
    }

    output << result[m - 1] << std::endl;

    delete[] a;
    delete[] b;
    delete[] result;
}

int expSearch(int* right_arr, int length, int aim) {

    if (right_arr[0] == aim)
        return 0;

    int i = 1;

    while (i < length && right_arr[i] <= aim) {
        i *= 2;
    }

    return binSearch(right_arr, i/2, std::min(length - 1, i), aim);
}

int binSearch(int* arr, int l, int r, int aim) {
    int mid;

    while (l <= r) {
        mid = (l + r) / 2;

        if (arr[mid] == aim)
            return mid;

        if (aim < arr[mid])
            r = mid - 1;

        if (aim > arr[mid])
            l = mid + 1;
    }
    return r;
}

int* Solution::idInsertion (int* a, int n, int* b, int m, int* result) {
    for (int i = 0; i < m; ++i) {
        int index = expSearch(a, n, b[i]);

        if (index < n && a[index] >= b[i]) {
            result[i] = index;
        } else {
            result[i] = n - 1;
        }
    }
    return result;
}

