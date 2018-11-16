#include "BattleScene.h"
#include "Character.h"
#include "TestScene.h"
#include <myengine/Mesh.h>
#include <myengine/Resources.h>

BattleScene::BattleScene(std::shared_ptr<Core> _c)
{
	m_core = _c;
	std::vector<std::shared_ptr<Entity>> m_entities;

	m_scene = std::shared_ptr<Scene>(new Scene(_c));
	_c->SetScene(m_scene);
	m_mesh = _c->GetResources()->Load<Mesh>("assets/box.obj");
	m_grass = _c->GetResources()->Load<Texture>("assets/grass.bmp");

	std::shared_ptr<Entity> enti = m_scene->AddEntity();

	std::shared_ptr<Transform> tran = enti->AddComponent<Transform>(glm::vec3(3.55f, 0, 0), glm::vec3(0, 30, 0), glm::vec3(1, 1, 1));
	enti->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/house.bmp"));
	enti->AddComponent<Character>(); //this shouldnt be here 
	enti->AddComponent<BattleBackground>(); //this shouldnt be here 
	std::shared_ptr<Entity> cave = m_scene->AddEntity();
	cave->AddComponent<Transform>(glm::vec3(0.0f, 0, -2.0f), glm::vec3(0, 0, 0), glm::vec3(1.25f, 1, 1));
	cave->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/house.bmp"));

	std::shared_ptr<Entity> bg = m_scene->AddEntity();
	bg->AddComponent<Transform>(glm::vec3(1.20f, 0, -3.75f), glm::vec3(0, 0, 0), glm::vec3(1.25f, 1, 1));
	bg->AddComponent<MeshRenderer>(m_mesh, _c->GetResources()->Load<Texture>("assets/house.bmp"));


	std::shared_ptr<Entity> enti2 = m_scene->AddEntity();
	std::shared_ptr<Transform> tran2 = enti2->AddComponent<Transform>(glm::vec3(1.50f, -0.5f, -0.20f), glm::vec3(0, 0, 0), glm::vec3(5, 0.1f, 5));
	std::shared_ptr<MeshRenderer> com2 = enti2->AddComponent<MeshRenderer>(m_mesh, m_grass);

	std::shared_ptr<Entity> enti3 = m_scene->AddEntity();
	std::shared_ptr<Transform> tran3 = enti3->AddComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.1f, 0.1f, 0.1f));
	std::shared_ptr<MeshRenderer> com3 = enti3->AddComponent<MeshRenderer>(_c->GetResources()->Load<Mesh>("assets/skybox.obj"), _c->GetResources()->Load<Texture>("assets/sky.bmp"));

/*
	for (int i = 0; i < 100; i++)
	{
		m_entities.push_back(m_scene->AddEntity());
		m_entities[i]->AddComponent<Transform>(glm::vec3(rand() % 10, rand() % 10, -(rand() % 10)), glm::vec3(rand() % 10, rand() % 10, -(rand() % 10)), glm::vec3((0.1 + (0.1f * (rand() % 10))), (0.1 + (0.1f * (rand() % 10))), (0.1 + (0.1f * (rand() % 10)))));
		m_entities[i]->AddComponent<MeshRenderer>();
//		m_entities[i]->GetComponent<MeshRenderer>()->SetMesh(m_mesh);
	}
*/
		
}