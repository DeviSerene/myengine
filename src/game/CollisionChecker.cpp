#include "CollisionChecker.h"
#include "myengine/Entity.h"

void CollisionChecker::OnInit()
{
	m_t = GetEntity()->GetComponent<Transform>();
	m_col = GetEntity()->GetComponent<Collider>();
}

void CollisionChecker::OnTick()
{
	if (m_collisionCheck.expired())
		return;
	if (Collisions::BoxCollision(m_t.lock()->GetPos(), m_col.lock()->GetSize(), m_collisionCheck.lock()->GetComponent<Transform>()->GetPos(), m_collisionCheck.lock()->GetComponent<Collider>()->GetSize()))
	{
		std::cout << "Collision Detected";
	}
	
}