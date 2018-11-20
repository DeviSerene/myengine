#include "BossScene.h"
#include "Character.h"
#include "Enemy.h"
#include "TestScene.h"
#include "ActionBar.h"
#include "TurnBar.h"
#include "Ability.h"
#include <myengine/Mesh.h>
#include <myengine/Resources.h>
#include <myengine/Sound.h>

BossScene::BossScene(std::shared_ptr<Core> _c)
	:Scene(_c)
{
	m_core = _c;

}

void BossScene::OnDeInit()
{
	if (!m_entities.empty())m_entities.clear();
	if (!m_environment.empty())m_environment.clear();
	if (!m_party.empty())m_party.clear();
	if (!m_enemies.empty())m_enemies.clear();
}

void BossScene::OnInit()
{
	std::shared_ptr<Entity> m_camera = AddEntity();
	m_camera->AddComponent<Camera>();
	m_core.lock()->AddCamera(m_camera);

	m_mesh = m_core.lock()->GetResources()->Load<Mesh>("assets/re_hall_bakedT.obj");
	m_grass = m_core.lock()->GetResources()->Load<Texture>("assets/mansion.bmp");
	std::shared_ptr<Entity> camera2 = AddEntity();
	camera2->AddComponent<Camera>();
	camera2->GetComponent<Camera>()->SetPos(glm::vec3(1, 1, 1));
	//_c->AddCamera(camera2);

	std::shared_ptr<Entity> enti = AddEntity();
	enti->AddComponent<Transform>(glm::vec3(3.55f, 0, -2.0f), glm::vec3(0, 20, 0), glm::vec3(1, 1, 1));
	enti->AddComponent<MeshRenderer>(m_mesh, m_grass);
	m_environment.push_back(enti);

	//------------------------------------------------------------------
		///Party and enemies
	//------------------------------------------------------------------

	std::shared_ptr<Entity> ophilia = AddEntity();
	ophilia->AddComponent<Character>();
	std::shared_ptr<ActionBar> oAB = ophilia->AddComponent<ActionBar>();
	m_party.push_back(ophilia);

	std::shared_ptr<Entity> enemy1 = AddEntity();
	enemy1->AddComponent<Enemy>(-0.915f, -0.55f, "assets/characters/enemy_03");
	enemy1->GetComponent<Enemy>()->SetStats(300, 1, 3);
	enemy1->GetComponent<Enemy>()->AddWeakness(BE_LIGHT);
	m_enemies.push_back(enemy1);



	std::shared_ptr<Entity> abilityEntity = AddEntity();
	std::vector<std::shared_ptr<Ability>> abilities;
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/staff", "Attack", BE_STAFF, 10, 0));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/cure", "Cure", BE_LIGHT, 25, 5));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/holy", "Holy Light", BE_LIGHT, 20, 5));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/bunny", "Attack", BE_SWORD, 20, 0));

	std::shared_ptr<Entity> TurnOrder = AddEntity();
	std::shared_ptr<TurnBar> to = TurnOrder->AddComponent<TurnBar>();
	to->SetCombatants(m_party, m_enemies);
	to->SetAB(oAB);
	to->SetAbilities(abilities);
	to->PlayMusic("assets/BossBattle.ogg");
	m_environment.push_back(TurnOrder);
}