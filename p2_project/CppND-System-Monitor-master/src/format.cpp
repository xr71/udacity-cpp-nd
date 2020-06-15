#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long second) {
    int minutes = second / 60;
    int min_remaining = minutes % 60;
    int hours = minutes / 60;
    int sec_remaining = second % 60;

    char output[9];
    std::sprintf(output, "%02i:%02i:%02i", hours, min_remaining, sec_remaining);

    return output;
}
