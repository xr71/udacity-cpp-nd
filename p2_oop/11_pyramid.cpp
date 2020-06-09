#include <cassert>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>



class Pyramid
{
    public:
        Pyramid(int l, int w, int h);
        int Length();
        void Length(int);

        int Width();
        void Width(int);

        int Height();
        void Height(int);

        float Volume();

    private:
        int length_;
        int width_;
        int height_;
};

// constructor
Pyramid::Pyramid(int l, int w, int h) : length_(l), width_(w), height_(h) {}

// accessors
int Pyramid::Length() { return length_; }
int Pyramid::Width() { return width_; }
int Pyramid::Height() { return height_; }
float Pyramid::Volume() { return length_ * width_ * height_ / 3.0; }

// mutators
void Pyramid::Length(int l)
{
    length_ = l;
}

void Pyramid::Width(int w)
{
    width_ = w;
}

void Pyramid::Height(int h)
{
    height_ = h;
}



// Test
int main()
{
  Pyramid pyramid(4, 5, 6);
  assert(pyramid.Length() == 4);
  assert(pyramid.Width() == 5);
  assert(pyramid.Height() == 6);
  assert(pyramid.Volume() == 40);
//
//  bool caught{false};
//  try {
//    Pyramid invalid(-1, 2, 3);
//  } catch (...) {
//    caught = true;
//  }
//  assert(caught);
}


