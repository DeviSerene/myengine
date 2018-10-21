#include <iostream>
#include <fstream>
#include <memory>
#include <myengine/Transform.h>
#include <myengine/MeshRenderer.h>
#include <myengine/Component.h>
#include <myengine/Entity.h>
#include <myengine/Core.h>
#include <myengine/MyEngineException.h>
#include <Windows.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void safe_main()
{
	std::cout << "Hello world" << std::endl;
	std::vector<std::shared_ptr<Entity>> m_entities;

	std::shared_ptr<Core> core = Core::init();

	std::shared_ptr<Entity> enti = core->AddEntity();

	std::shared_ptr<Transform> tran = enti->AddComponent<Transform>(glm::vec3(0,0,0), glm::vec3(50, 50, 50), glm::vec3(1, 1, 1));
	std::shared_ptr<MeshRenderer> com = enti->AddComponent<MeshRenderer>();

	std::shared_ptr<Entity> enti2 = core->AddEntity();
	std::shared_ptr<Transform> tran2 = enti2->AddComponent<Transform>(glm::vec3(1, 1, -1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	std::shared_ptr<MeshRenderer> com2 = enti2->AddComponent<MeshRenderer>();
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		m_entities.push_back(core->AddEntity());
		m_entities[i]->AddComponent<Transform>(glm::vec3(rand() % 10, rand() % 10, -(rand() % 10)), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		m_entities[i]->AddComponent<MeshRenderer>();
	}

	if (enti->GetComponent<MeshRenderer>())
		std::cout << "Has a MESH";

	core->Start();
}

int main()
{
	try
	{
		safe_main();
	}
	catch (MyEngineException e)
	{
		MessageBox(0, e.what(), "Error Box", 0);
	}
	catch (std::exception e)
	{
		MessageBox(0, e.what(), "Error Box",0);
	}
	catch (...)
	{
		MessageBox(0, "Something has been thrown.", "Error Box", 0);
	}

return 0;
}
