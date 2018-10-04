#include "Component.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Core.h"
#include "Entity.h"


Component::Component()
{
}

Component::~Component()
{
}

std::shared_ptr<Entity> Component::GetEntity()
{
	return (std::shared_ptr<Entity>)m_entity;
}

std::shared_ptr<Core> Component::GetCore()
{
	return nullptr;
}

std::shared_ptr<Keyboard> Component::GetKeyboard()
{
	return nullptr;
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