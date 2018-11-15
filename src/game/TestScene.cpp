#include "TestScene.h"
#include "myengine/Core.h"
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include "myengine/TextTexture.h"


void TestScene::OnGui()
{
	glm::vec4 pos;

	pos.x = -1.0;
	pos.y = -1.0;
	pos.z = 2.00;
	pos.w = 2.00;

	std::shared_ptr<TextTexture> text = GetCore()->GetResources()->Load<TextTexture>("Hello World");
	text->SetText({ 255,255,255,255 }, 35);

	GetCore()->GetGui()->SetTexture(GetCore()->GetResources()->Load<Texture>("grass_background.png")->GetTexture());
	GetCore()->GetGui()->Sprite(pos);


	GetCore()->GetGui()->SetTexture(text->GetTexture()); //GetCore()->GetResources()->Load<Texture>("Card.bmp")
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
	glm::vec4 pos2;
	pos2.x = 20;
	pos2.y = 20;
	pos2.z = 80;
	pos2.w = 380;


	GetCore()->GetGui()->SetTexture(GetCore()->GetResources()->Load<Texture>("mat_gold.png")->GetTexture());
	GetCore()->GetGui()->Sprite(GetCore()->GetGui()->GetPos(pos2));
}