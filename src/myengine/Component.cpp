#include "Component.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Core.h"
#include "Entity.h"


Component::Component()
{
	m_began = false;
}

Component::~Component()
{
}

std::shared_ptr<Scene> Component::GetScene()
{
	return m_entity.lock()->GetCore()->GetScene();
}

std::shared_ptr<Entity> Component::GetEntity()
{
	return m_entity.lock();
}

std::shared_ptr<Core> Component::GetCore()
{
	return m_entity.lock()->GetCore();
}

std::shared_ptr<Keyboard> Component::GetKeyboard()
{
	return m_entity.lock()->GetCore()->GetKeyboard();
}

std::shared_ptr<Environment> Component::GetEnvironment()
{
	return nullptr;
}

void Component::OnInit()
{

}

void Component::OnBegin()
{

}

void Component::OnTick()
{

}

void Component::OnDisplay()
{

}

void Component::OnGui()
{

}