// рабочий код
#include <iostream>
#include <climits>
#include <sstream>
#include <cassert>

class Soulution {
    public:
    size_t countBit(int input) {
        size_t count = 0;

        while (input > 0) {

            count += input&1;
            input >>= 2;
            
        }

        return count;
    }
};

void run(std::istream& input, std::ostream& output) {

    int num; 
    Soulution soulution;

    input >> num;
    output << soulution.countBit(num);

}

void testSoultion();

int main() {
    run(std::cin, std::cout);
}

void testSoultion() {
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "Test 1 start" << std::endl;

        input << "25";
        run(input, output);
        assert(output.str() == "2");

        std::cout << "Test 1 ended" << std::endl;
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "Test 2 start" << std::endl;

        input << "0";
        run(input, output);
        assert(output.str() == "0");

        std::cout << "Test 2 ended" << std::endl;
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "Test 3 start" << std::endl;

        input << "1";
        run(input, output);
        assert(output.str() == "1");

        std::cout << "Test 3 ended" << std::endl;
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "Test 4 start" << std::endl;

        input << "10";
        run(input, output);
        assert(output.str() == "0");

        std::cout << "Test 4 ended" << std::endl;
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "Test 5 start" << std::endl;

        
        input << "100";
        run(input, output);
        assert(output.str() == "2");

        std::cout << "Test 5 ended" << std::endl;
    }
    {
        std::stringstream input;
        std::stringstream output;

        std::cout << "Test 6 start" << std::endl;

        input << "4294967295";
        run(input, output);
        assert(output.str() == "16");

        std::cout << "Test 6 ended" << std::endl;
    }
}

