#include <iostream>
#include <vector>
#include "increment_and_sum.h"

using std::vector;
using std::cout;

int main(void)
{
    vector<int> v = {1, 2, 3, 4};
    int total = IncrementAndComputeVectorSum(v);

    cout << "The total is " << total << std::endl;
}
