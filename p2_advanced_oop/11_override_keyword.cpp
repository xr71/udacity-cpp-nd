#include <iostream>
#include <cmath>

/*
 * "Overriding" a function occurs when a derived class defines the
 * implementation of a virtual function that it inherits from a base class.
 *
 * It is possible, but not required, to specify a function declaration as override.
 *
*/


// example
//

#define PI 3.14159

class Shape {
    public:
          virtual double Area() const = 0;
            virtual double Perimeter() const = 0;

};

class Circle : public Shape {
    public:
        Circle(double radius) : radius_(radius) {}
        double Area() const override { return pow(radius_, 2) * PI;  } // specified as an override function
        double Perimeter() const override { return 2 * radius_ * PI;  } // specified as an override function

    private:
        double radius_;
};


// more examples

class VehicleModel {
  // TODO: Declare virtual function Move()
  virtual void Move(double v, double phi) = 0;
};

class ParticleModel : public VehicleModel {
public:
  // TODO: Override the Move() function
  void Move(double v, double phi) override {
    theta += phi;
    x += v * cos(theta);
    y += v * sin(theta);
  }

  double x = 0;
  double y = 0;
  double theta = 0;
};

class BicycleModel : public ParticleModel {
public:
  // TODO: Override the Move() function
  void Move(double v, double phi) override {
    theta += v / L * tan(phi);
    x += v * cos(theta);
    y += v * sin(theta);
  }
  // TODO: Define L
  double L = 1;
};


int main(void)
{
    Circle c{5};
    std::cout << c.Area() << std::endl;

    BicycleModel bm;
    bm.Move(10, 0.3);

    std::cout << "x=" << bm.x << " y=" << bm.y << std::endl;
}

