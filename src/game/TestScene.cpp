#include "TestScene.h"
#include "myengine/Core.h"


void TestScene::OnGui()
{
	glm::vec4 pos;
	pos.x = 5;
	pos.y = 5;
	pos.z = 50;
	pos.w = 50;
	GetCore()->GetGui()->Button(pos, "Hello");
}