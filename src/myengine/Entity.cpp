#include "Entity.h"
#include "Component.h"
#include "Core.h"

Entity::Entity()
{
}

Entity::~Entity()
{

}


template <typename T>
std::shared_ptr <T> Entity::AddComponent()
{
	std::shared_ptr <T> rtn = (std::shared_ptr <T>)new T();
	rtn->Init();
	return rtn;
}


template <typename T, typename A>
std::shared_ptr <T> Entity::AddComponent(A _a)
{
	std::shared_ptr <T> rtn = (std::shared_ptr <T>)new T(_a);
	rtn->Init();
	return rtn;
}

template <typename T, typename A, typename B>
std::shared_ptr <T> Entity::AddComponent(A _a, B _b)
{
	std::shared_ptr <T> rtn = (std::shared_ptr <T>)new T(_a, _b);
	rtn->Init();
	return rtn;
}

template <typename T, typename A, typename B, typename C>
std::shared_ptr <T> Entity::AddComponent(A _a, B _b, C _c)
{
	std::shared_ptr <T> rtn = (std::shared_ptr <T>)new T(_a, _b, _c);
	rtn->Init();
	return rtn;
}

template <typename T, typename A, typename B, typename C, typename D>
std::shared_ptr <T> Entity::AddComponent(A _a, B _b, C _c, D _d)
{
	std::shared_ptr <T> rtn = (std::shared_ptr <T>)new T(_a, _b, _c, _d);
	rtn->Init();
	return rtn;
}
