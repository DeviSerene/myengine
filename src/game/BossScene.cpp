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
{
	m_core = _c;

	m_scene = std::shared_ptr<Scene>(new Scene(_c));
	_c->GetResources()->Load<Sound>("assets/Battle.ogg")->PlayLoop();
	_c->SetScene(m_scene);
	m_mesh = _c->GetResources()->Load<Mesh>("assets/re_hall_bakedT.obj");
	m_grass = _c->GetResources()->Load<Texture>("assets/mansion.bmp");
	std::shared_ptr<Entity> camera2 = m_scene->AddEntity();
	camera2->AddComponent<Camera>();
	camera2->GetComponent<Camera>()->SetPos(glm::vec3(1, 1, 1));
	//_c->AddCamera(camera2);
	
	std::shared_ptr<Entity> enti = m_scene->AddEntity();
	enti->AddComponent<Transform>(glm::vec3(3.55f, 0, -2.0f), glm::vec3(0, 20, 0), glm::vec3(1, 1, 1));
	enti->AddComponent<MeshRenderer>(m_mesh, m_grass);
	m_environment.push_back(enti);

	//------------------------------------------------------------------
		///Party and enemies
	//------------------------------------------------------------------

	std::shared_ptr<Entity> ophilia = m_scene->AddEntity();
	ophilia->AddComponent<Character>(); 
	std::shared_ptr<ActionBar> oAB = ophilia->AddComponent<ActionBar>();
	m_party.push_back(ophilia);

	std::shared_ptr<Entity> enemy1 = m_scene->AddEntity();
	enemy1->AddComponent<Enemy>(-0.5f, -0.35f, "assets/characters/enemy_01");
	enemy1->GetComponent<Enemy>()->AddWeakness(BE_LIGHT);
	m_enemies.push_back(enemy1);

	std::shared_ptr<Entity> enemy2 = m_scene->AddEntity();
	enemy2->AddComponent<Enemy>(-0.95f, -0.55f, "assets/characters/enemy_02");
	enemy2->GetComponent<Enemy>()->AddWeakness(BE_STAFF);
	m_enemies.push_back(enemy2);


	std::shared_ptr<Entity> abilityEntity = m_scene->AddEntity();
	std::vector<std::shared_ptr<Ability>> abilities;
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/hit.png", "Attack", BE_STAFF,10,0));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/cure.png", "Cure", BE_LIGHT,20,5));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/holy.png", "Holy Light", BE_LIGHT,20,5));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/hit.png", "Attack", BE_SWORD, 10, 0));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/hit.png", "Attack", BE_AXE, 9, 0));

	std::shared_ptr<Entity> TurnOrder = m_scene->AddEntity();
	std::shared_ptr<TurnBar> to = TurnOrder->AddComponent<TurnBar>();
	to->SetCombatants(m_party, m_enemies);
	to->SetAB(oAB);
	to->SetAbilities(abilities);
	m_environment.push_back(TurnOrder);


}