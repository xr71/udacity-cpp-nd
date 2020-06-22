#include <iostream>
#include <memory>

class Entity
{

public:
    Entity()
    {
        std::cout << "Created" << std::endl;
    }

    ~Entity()
    {
        std::cout << "Destroyed" << std::endl;
    }
};

int main(void)
{

    // we are allowed to create empty scopes
    {
        // here we can properly create and destroy if we do so on stack
        Entity e1 = Entity();

        // the moment we leave these braces e1 will be destroyed
    }

    // this is on the heap
    Entity *e = new Entity;

    // we fail to delete e;
    // delete e;

    // if we use smart pointers, we can avoid using new and delete
    std::unique_ptr<Entity> e2(new Entity());

    /*
    The smart pointer destructor contains the call to delete, 
    and because the smart pointer is declared on the stack,
    its destructor is invoked when the smart pointer goes out of 
    scope, even if an exception is thrown.
    */
}