#include "Transform.h"
#include "Entity.h"

Transform::Transform()
{

	m_position.x = 1; 
	m_position.y = 1; 
	m_position.z = 1; 
	
	m_rotation.x = 0; 
	m_rotation.y = 0; 
	m_rotation.z = 0; 
	
	m_scale.x = 1; 
	m_scale.y = 1; 
	m_scale.z = 1;

	m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(m_position)));
}

Transform::Transform(glm::vec3 _p, glm::vec3 _r, glm::vec3 _s) 
{ 
	m_position = _p; 
	m_rotation = _r; 
	m_scale = _s; 

	m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(m_position)));

}

void Transform::OnInit()
{
}

void Transform::OnTick()
{
	m_rotation.x += 0.01f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
	front.y = sin(glm::radians(m_rotation.y));
	front.z = cos(glm::radians(m_rotation.y)) * sin(glm::radians(m_rotation.x));
	m_front = glm::normalize(front);
}

glm::vec3 Transform::GetPosition()
{ 
	//std::shared_ptr<Entity> ent = GetEntity();
	glm::vec3 position = m_position;
	//if(ent->m_parent != nullptr)
	//	position = position * ent->m_parent->GetComponent<Transform>()->GetPosition();
	return position;
}

glm::vec3 Transform::GetRotation()
{
	//std::shared_ptr<Entity> ent = GetEntity();
	glm::vec3 rotation = m_rotation;
	//if (ent->m_parent != nullptr)
	//	rotation = rotation * ent->m_parent->GetComponent<Transform>()->GetRotation();
	return rotation;
}

glm::vec3 Transform::GetScale()
{
	return m_scale; 
}
