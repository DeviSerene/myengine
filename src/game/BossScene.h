#include <iostream>
#include <fstream>
#include <memory>
#include <myengine/Transform.h>
#include <myengine/Texture.h>
#include <myengine/MeshRenderer.h>
#include <myengine/SpriteRenderer.h>
#include <myengine/Component.h>
#include <myengine/Entity.h>
#include <myengine/Core.h>
#include <myengine/Camera.h>
#include <myengine/MyEngineException.h>
#include <myengine/Scene.h>
#include <Windows.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "TestScene.h"
#include "BattleBackground.h"

class BossScene : public Scene
{
public:
	BossScene(std::shared_ptr<Core> _c);
	void OnInit();
	void OnDeInit();
private:
	std::weak_ptr<Core> m_core;
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Texture> m_grass;

	std::vector<std::shared_ptr<Entity>> m_environment;
	std::vector<std::shared_ptr<Entity>> m_party;
	std::vector<std::shared_ptr<Entity>> m_enemies;
};