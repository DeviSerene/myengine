#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Transform.h"
#include "myengine/Collider.h"
#include "myengine/Collisions.h"

class CollisionChecker : public Component
{
public:
	std::shared_ptr<Entity> CheckCol(std::shared_ptr<Entity> _e) { m_collisionCheck = _e; }
	void OnInit();
	void OnTick();
private:
	std::weak_ptr<Transform> m_t;
	std::weak_ptr<Collider> m_col;
	std::weak_ptr<Entity> m_collisionCheck;
};