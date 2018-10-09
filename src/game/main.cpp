#include <iostream>
#include <memory>
#include <myengine/MeshRenderer.h>
#include <myengine/Component.h>
#include <myengine/Entity.h>
#include <myengine/Core.h>

int main()
{
std::cout << "Hello world" << std::endl;

std::shared_ptr<Core> core = Core::init();

std::shared_ptr<Entity> enti = core->AddEntity();

std::shared_ptr<MeshRenderer> com = enti->AddComponent<MeshRenderer>();

core->Start();

return 0;
}
