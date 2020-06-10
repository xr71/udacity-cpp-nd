#include <iostream>

// friend class makes a private member of a different class accessible


class Heart {
    private:
        int rate{80};
        friend class Human;
};

class Human {
    public:
        Heart heart;
        void Exercise() { heart.rate = 150; }
        int HeartRate() { return heart.rate; }
};


// rectangle and square

class Square
{
    public:
        Square(int);
    private:
        friend class Rectangle;
        int side;
};

class Rectangle
{
    public:
        int Area() const { return width * height; }
        Rectangle(Square s);
    private:
        int width;
        int height;
};

// constructors
Rectangle::Rectangle(Square s) : width(s.side), height(s.side) {}
Square::Square(int s) : side(s) {}

int main(void)
{
    Human h1;
    h1.Exercise();
    std::cout << h1.HeartRate() << std::endl;

    Square sq{4};
    Rectangle rect(sq);
    std::cout << rect.Area() << std::endl;
}
