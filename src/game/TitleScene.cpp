#include "TitleScene.h"
#include "TitleButtons.h"
#include "BloomEffect.h"
#include <myengine/Mesh.h>
#include <myengine/Resources.h>
#include <myengine/Sound.h>

TitleScene::TitleScene(std::shared_ptr<Core> _c)
	:Scene(_c)
{
	m_core = _c;
}

void TitleScene::OnDeInit()
{
	if (!m_entities.empty())m_entities.clear();
	if (!m_environment.empty())m_environment.clear();
}

void TitleScene::OnInit()
{
	std::shared_ptr<Entity> m_camera = AddEntity();
	m_camera->AddComponent<Camera>();
	m_core.lock()->AddCamera(m_camera);
	std::shared_ptr<BloomEffect> be = m_camera->AddComponent<BloomEffect>();

	std::shared_ptr<Entity> enti = AddEntity();
	enti->AddComponent<TitleButtons>();
	m_environment.push_back(enti);

}