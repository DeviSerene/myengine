#include "BattleScene.h"
#include "Character.h"

BattleScene::BattleScene(std::shared_ptr<Core> _c)
{
	m_core = _c;
	std::vector<std::shared_ptr<Entity>> m_entities;

	m_scene = std::shared_ptr<Scene>(new Scene(_c));
	_c->SetScene(m_scene);

	std::shared_ptr<Entity> enti = m_scene->AddEntity();

	std::shared_ptr<Transform> tran = enti->AddComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(50, 50, 50), glm::vec3(1, 1, 1));
	enti->AddComponent<BattleBackground>();
	enti->AddComponent<Character>();

	/*
	std::shared_ptr<Entity> enti2 = m_scene->AddEntity();
	std::shared_ptr<Transform> tran2 = enti2->AddComponent<Transform>(glm::vec3(1, 1, -1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	std::shared_ptr<MeshRenderer> com2 = enti2->AddComponent<MeshRenderer>();
	for (int i = 0; i < 100; i++)
	{
		m_entities.push_back(m_scene->AddEntity());
		m_entities[i]->AddComponent<Transform>(glm::vec3(rand() % 10, rand() % 10, -(rand() % 10)), glm::vec3(rand() % 10, rand() % 10, -(rand() % 10)), glm::vec3((0.1 + (0.1f * (rand() % 10))), (0.1 + (0.1f * (rand() % 10))), (0.1 + (0.1f * (rand() % 10)))));
		m_entities[i]->AddComponent<MeshRenderer>();
	}

	if (enti->GetComponent<MeshRenderer>())
		std::cout << "Has a MESH";
		*/
}