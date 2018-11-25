#include "DeathScene.h"
#include <myengine/Mesh.h>
#include <myengine/Resources.h>
#include <myengine/Sound.h>
#include "GameOver.h"

DeathScene::DeathScene(std::shared_ptr<Core> _c)
	:Scene(_c)
{
	m_core = _c;
}

void DeathScene::OnDeInit()
{
	if (!m_entities.empty())m_entities.clear();
	if (!m_environment.empty())m_environment.clear();
}

void DeathScene::OnInit()
{
	std::shared_ptr<Entity> m_camera = AddEntity();
	m_camera->AddComponent<Camera>();
	m_core.lock()->AddCamera(m_camera);

	std::shared_ptr<Entity> enti = AddEntity();
	enti->AddComponent<GameOver>();
	m_environment.push_back(enti);
}