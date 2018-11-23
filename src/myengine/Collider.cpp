#include "Collider.h"

Collider::Collider()
{
	m_boxSize = glm::vec3(1, 1, 1);
}

Collider::Collider(glm::vec3 _size)
{
	m_boxSize = _size;
}