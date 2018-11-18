#include "BattleScene.h"
#include "Character.h"
#include "Enemy.h"
#include "TestScene.h"
#include "ActionBar.h"
#include "TurnBar.h"
#include "Ability.h"
#include <myengine/Mesh.h>
#include <myengine/Resources.h>
#include <myengine/Sound.h>

BattleScene::BattleScene(std::shared_ptr<Core> _c)
{
	m_core = _c;

	m_scene = std::shared_ptr<Scene>(new Scene(_c));
	_c->GetResources()->Load<Sound>("assets/Battle.ogg")->PlayLoop();
	_c->SetScene(m_scene);
	m_mesh = _c->GetResources()->Load<Mesh>("assets/Cube.obj");
	m_grass = _c->GetResources()->Load<Texture>("assets/grass.bmp");
	std::shared_ptr<Entity> enti = m_scene->AddEntity();
	enti->AddComponent<Transform>(glm::vec3(3.55f, 0, 0), glm::vec3(0, 30, 0), glm::vec3(1, 1, 1));
	enti->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	enti->AddComponent<BattleBackground>(); //this shouldnt be here 
	//enti->AddComponent<Character>(); //this definitely shouldnt be here 
	//enti->AddComponent<Enemy>(-0.5f, -0.35f, "assets/characters/enemy_01"); //this definitely shouldnt be here 
	//enti->AddComponent<Enemy>(-0.95f, -0.55f, "assets/characters/enemy_01"); //this definitely shouldnt be here 
	//enti->AddComponent<ActionBar>(); //this definitely shouldnt be here 
	m_environment.push_back(enti);

	std::shared_ptr<Entity> cave = m_scene->AddEntity();
	cave->AddComponent<Transform>(glm::vec3(0.0f, 0, -2.0f), glm::vec3(0, 0, 0), glm::vec3(1.25f, 1, 1));
	cave->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(cave);

	std::shared_ptr<Entity> bg = m_scene->AddEntity();
	bg->AddComponent<Transform>(glm::vec3(1.20f, 0, -3.75f), glm::vec3(0, 0, 0), glm::vec3(1.25f, 1, 1));
	bg->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(bg);

	std::shared_ptr<Entity> trees = m_scene->AddEntity();
	trees->AddComponent<Transform>(glm::vec3(4.50f, 0, -2.70f), glm::vec3(0, 140, 0), glm::vec3(1.25f, 1.25f, 1.25f));
	trees->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(trees);

	std::shared_ptr<Entity> mount = m_scene->AddEntity();
	mount->AddComponent<Transform>(glm::vec3(3.50f, 0, -4.00f), glm::vec3(0, 140, 0), glm::vec3(1.25f, 1.25f, 1.25f));
	mount->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(mount);

	std::shared_ptr<Entity> mount2 = m_scene->AddEntity();
	mount2->AddComponent<Transform>(glm::vec3(3.00f, -0.25f, -4.50f), glm::vec3(0, 140, 0), glm::vec3(1.25f, 1.25f, 1.25f));
	mount2->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(mount2);

	std::shared_ptr<Entity> mount3 = m_scene->AddEntity();
	mount3->AddComponent<Transform>(glm::vec3(5.20f, -0.25f, -0.50f), glm::vec3(0, 140, 0), glm::vec3(1.25f, 1.25f, 1.25f));
	mount3->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(mount3);

	std::shared_ptr<Entity> enti2 = m_scene->AddEntity();
	std::shared_ptr<Transform> tran2 = enti2->AddComponent<Transform>(glm::vec3(1.50f, -0.5f, -0.20f), glm::vec3(0, 0, 0), glm::vec3(5, 0.1f, 5));
	std::shared_ptr<MeshRenderer> com2 = enti2->AddComponent<MeshRenderer>(m_mesh, m_grass);
	m_environment.push_back(enti2);

	std::shared_ptr<Entity> enti3 = m_scene->AddEntity();
	std::shared_ptr<Transform> tran3 = enti3->AddComponent<Transform>(glm::vec3(1, 0, -2), glm::vec3(0, 0, 0), glm::vec3(0.1f, 0.1f, 0.1f));
	std::shared_ptr<MeshRenderer> com3 = enti3->AddComponent<MeshRenderer>(_c->GetResources()->Load<Mesh>("assets/skybox.obj"), _c->GetResources()->Load<Texture>("assets/sky.bmp"));
	m_environment.push_back(enti3);

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
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/hit.png", "Attack", BE_STAFF,10));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/cure.png", "Cure", BE_LIGHT,20));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/holy.png", "Holy Light", BE_LIGHT,20));

	std::shared_ptr<Entity> TurnOrder = m_scene->AddEntity();
	std::shared_ptr<TurnBar> to = TurnOrder->AddComponent<TurnBar>();
	to->SetCombatants(m_party, m_enemies);
	to->SetAB(oAB);
	to->SetAbilities(abilities);
	m_environment.push_back(TurnOrder);


}