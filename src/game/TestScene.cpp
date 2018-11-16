#include "TestScene.h"
#include "myengine/Core.h"
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include "myengine/TextTexture.h"


void TestScene::OnGui()
{
	glm::vec4 pos;
	GetCore()->GetGui()->SetTexture(GetCore()->GetResources()->Load<Texture>("Card.bmp")->GetTexture());
	GetCore()->GetGui()->SetHighlight(GetCore()->GetResources()->Load<Texture>("Card_normal.bmp")->GetTexture());
	GetCore()->GetGui()->SetPressed(GetCore()->GetResources()->Load<Texture>("Card_height.bmp")->GetTexture());

	pos.x = -0.7;
	pos.y = -0.7;
	pos.z = 1.00;
	pos.w = 0.50;
	if (GetCore()->GetGui()->Button(pos, "Hello"))
	{
		std::cout << "Hit! ";
	}
}