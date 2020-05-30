#include <iostream>
#include <string>
#include <vector>

int main() {

    int a = 0;
    std::vector<int> v = {1, 2, 3};
    std::string b = "hello, world!";

    std::cout << b << std::endl;
    std::cout << a << "\n";

    std::cout << v[1] << "\n\n\n";

    for (int i : v) {
        std::cout << i << "\n";
    }


    // we can also use auto keyword for automatic type inference;

    auto v1 = {6,7,8,9,10};
    std::cout << std::endl;

    for (int i : v1) {
        std::cout << i << "\n";
    }

    return 0;
}
