#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

int main()
{
    // we have seen container data structures: array, vector
    // these are fantastic for ordered data structures
    //
    // but we need something more powerful for associated data
    //
    // we can use a hash-map - or dictionary
    // these use key value pairs to make retrieval more efficient
    // the c++ standard implementation of map is the unordered_map
    //


    string key = "word";
    string def_1 = "a unit of language";
    string def_2 = "speech or talk: to express one's emotion in words";
    string def_3 = "a short talk or conversation";
    string def_4 = "an expression or utterance";

    unordered_map <string, vector<string>> my_dict;

    // check if the key is in the map
    if (my_dict.find(key) == my_dict.end())
    {
        std::cout << "the key is not in the dictionary" << std::endl;
        std::cout << "we will insert the key-value pair into the hash map now"
            << std::endl;

        my_dict[key] = vector<string> {def_1, def_2, def_3, def_4};
    }

    std::cout << std::endl;
    std::cout << "now fetching the value of the key" << std::endl;
    std::cout << key << std::endl;
    auto definitions = my_dict[key];

    for (string definition : definitions)
    {
        std::cout << definition << std::endl;
    }
}
