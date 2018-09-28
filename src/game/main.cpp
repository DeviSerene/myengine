#include <iostream>
#include <memory>
#include <myengine/Core.h>

int main()
{
std::cout << "Hello world" << std::endl;

std::shared_ptr<Core> core = Core::init();



return 0;
}
