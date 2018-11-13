#include "TestScene.h"
#include "myengine/Core.h"


void TestScene::OnGui()
{
	glm::vec4 pos;
	pos.x = -0.7;
	pos.y = -0.7;
	pos.z = 1.00;
	pos.w = 0.50;
	if (GetCore()->GetGui()->Button(pos, "Hello"))
	{
		std::cout << "Hit! ";
	}
}