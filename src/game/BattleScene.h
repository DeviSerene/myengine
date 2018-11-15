#include <iostream>
#include <fstream>
#include <memory>
#include <myengine/Transform.h>
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

class BattleScene
{
public:
	BattleScene(std::shared_ptr<Core> _c);

private:
	std::shared_ptr<Scene> m_scene;
	std::weak_ptr<Core> m_core;
};