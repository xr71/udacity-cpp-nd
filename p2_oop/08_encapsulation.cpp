#include <iostream>
#include <string>
#include <cassert>

/*
 * Encapsulation is the grouping together of data and logic into a single unit.
 * In object-oriented programming, classes encapsulate data and functions that
 * operate on that data.
 *
 * This can be a delicate balance, because on the one hand we want to group
 * together relevant data and functions, but on the hand we want to limit
 * member functions to only those functions that need direct access to the
 * representation of a class.
 *
*/

class Date {
public:
  Date(int day, int month, int year);
  int Day() const { return day_; }
  void Day(int day);
  int Month() const { return month_; }
  void Month(int month);
  int Year() const { return year_; }
  void Year(int year);

private:
  int day_{1};
  int month_{1};
  int year_{0};
};

Date::Date(int day, int month, int year) {
  Year(year);
  Month(month);
  Day(day);
}

void Date::Day(int day) {
  if (day >= 1 && day <= 31)
    day_ = day;
}

void Date::Month(int month) {
  if (month >= 1 && month <= 12)
    month_ = month;
}

void Date::Year(int year) { year_ = year; }

// Test
int main() {
  Date date(29, 8, 1981);
  assert(date.Day() == 29);
  assert(date.Month() == 8);
  assert(date.Year() == 1981);
}


