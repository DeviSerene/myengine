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
#include <myengine/Collider.h>
#include "BlurEffect.h"
#include "CollisionChecker.h"

BattleScene::BattleScene(std::shared_ptr<Core> _c)
	:Scene(_c)
{
	m_core = _c;


}

void BattleScene::OnDeInit()
{
	if (!m_entities.empty())m_entities.clear();
	if (!m_environment.empty())m_environment.clear();
	if (!m_party.empty())m_party.clear();
	if (!m_enemies.empty())m_enemies.clear();
}

void BattleScene::OnInit()
{
	std::shared_ptr<Core> _c = m_core.lock();

	std::shared_ptr<Entity> m_camera = AddEntity();
	m_camera->AddComponent<Camera>();
	_c->AddCamera(m_camera);
	std::shared_ptr<BlurEffect> be = m_camera->AddComponent<BlurEffect>();

	m_mesh = _c->GetResources()->Load<Mesh>("assets/Cube.obj");
	m_grass = _c->GetResources()->Load<Texture>("assets/grass.bmp");
	std::shared_ptr<Entity> camera2 = AddEntity();
	camera2->AddComponent<Camera>();
	camera2->GetComponent<Camera>()->SetPos(glm::vec3(1, 1, 1));
	//_c->AddCamera(camera2);

	std::shared_ptr<Entity> enti = AddEntity();
	enti->AddComponent<Transform>(glm::vec3(3.55f, 0, 0), glm::vec3(0, 30, 0), glm::vec3(1, 1, 1));
	enti->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	enti->AddComponent<BattleBackground>();
	m_environment.push_back(enti);

	std::shared_ptr<Entity> cave = AddEntity();
	cave->AddComponent<Transform>(glm::vec3(0.0f, 0, -2.0f), glm::vec3(0, 0, 0), glm::vec3(1.25f, 1, 1));
	cave->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(cave);

	std::shared_ptr<Entity> bg = AddEntity();
	bg->AddComponent<Transform>(glm::vec3(1.20f, 0, -3.75f), glm::vec3(0, 0, 0), glm::vec3(1.25f, 1, 1));
	bg->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(bg);

	std::shared_ptr<Entity> trees = AddEntity();
	trees->AddComponent<Transform>(glm::vec3(4.50f, 0, -2.70f), glm::vec3(0, 140, 0), glm::vec3(1.25f, 1.25f, 1.25f));
	trees->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(trees);

	std::shared_ptr<Entity> mount = AddEntity();
	mount->AddComponent<Transform>(glm::vec3(3.50f, 0, -4.00f), glm::vec3(0, 140, 0), glm::vec3(1.25f, 1.25f, 1.25f));
	mount->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	mount->AddComponent<Collider>();
	m_environment.push_back(mount);

	std::shared_ptr<Entity> mount2 = AddEntity();
	mount2->AddComponent<Transform>(glm::vec3(3.00f, -0.25f, -4.50f), glm::vec3(0, 140, 0), glm::vec3(1.25f, 1.25f, 1.25f));
	mount2->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	mount2->AddComponent<Collider>();
	std::shared_ptr<CollisionChecker>ce = mount2->AddComponent<CollisionChecker>();
	ce->SetEntity(m_environment[1]);
	m_environment.push_back(mount2);

	std::shared_ptr<Entity> mount3 = AddEntity();
	mount3->AddComponent<Transform>(glm::vec3(5.20f, -0.25f, -0.50f), glm::vec3(0, 140, 0), glm::vec3(1.25f, 1.25f, 1.25f));
	mount3->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/cube.bmp"));
	m_environment.push_back(mount3);

	std::shared_ptr<Entity> enti2 = AddEntity();
	std::shared_ptr<Transform> tran2 = enti2->AddComponent<Transform>(glm::vec3(1.50f, -0.5f, -0.20f), glm::vec3(0, 0, 0), glm::vec3(5, 0.1f, 5));
	std::shared_ptr<MeshRenderer> com2 = enti2->AddComponent<MeshRenderer>(m_mesh, m_grass);
	m_environment.push_back(enti2);

	std::shared_ptr<Entity> enti3 = AddEntity();
	std::shared_ptr<Transform> tran3 = enti3->AddComponent<Transform>(glm::vec3(1, 0, -2), glm::vec3(0, 0, 0), glm::vec3(0.1f, 0.1f, 0.1f));
	std::shared_ptr<MeshRenderer> com3 = enti3->AddComponent<MeshRenderer>(_c->GetResources()->Load<Mesh>("assets/skybox.obj"), _c->GetResources()->Load<Texture>("assets/sky.bmp"));
	m_environment.push_back(enti3);

	//------------------------------------------------------------------
		///Party and enemies
	//------------------------------------------------------------------

	std::shared_ptr<Entity> ophilia = AddEntity();
	ophilia->AddComponent<Character>();
	ophilia->GetComponent<Character>()->SetBlurEffect(be);
	std::shared_ptr<ActionBar> oAB = ophilia->AddComponent<ActionBar>();
	m_party.push_back(ophilia);

	std::shared_ptr<Entity> enemy1 = AddEntity();
	enemy1->AddComponent<Enemy>(-0.5f, -0.35f, "assets/characters/enemy_01");
	enemy1->GetComponent<Enemy>()->AddWeakness(BE_LIGHT);
	m_enemies.push_back(enemy1);

	std::shared_ptr<Entity> enemy2 = AddEntity();
	enemy2->AddComponent<Enemy>(-0.95f, -0.55f, "assets/characters/enemy_02");
	enemy2->GetComponent<Enemy>()->AddWeakness(BE_STAFF);
	m_enemies.push_back(enemy2);


	std::shared_ptr<Entity> abilityEntity = AddEntity();
	std::vector<std::shared_ptr<Ability>> abilities;
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/staff", "Attack", BE_STAFF, 10, 0));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/cure", "Cure", BE_LIGHT, 20, 5));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/holy", "Holy Light", BE_LIGHT, 20, 5));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/wolf", "Attack", BE_SWORD, 10, 0));
	abilities.push_back(abilityEntity->AddComponent<Ability>("assets/bunny", "Attack", BE_AXE, 9, 0));

	std::shared_ptr<Entity> TurnOrder = AddEntity();
	std::shared_ptr<TurnBar> to = TurnOrder->AddComponent<TurnBar>();
	to->SetCombatants(m_party, m_enemies);
	to->SetAB(oAB);
	to->SetAbilities(abilities);
	to->PlayMusic("assets/Battle.ogg");
	m_environment.push_back(TurnOrder);

}