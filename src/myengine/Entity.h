#pragma once
#include <memory>
#include <vector>


class Core;
class Component;

#define ADDCOMPONENT \
m_components.push_back(rtn); \
rtn->SetEntity(shared_from_this()); \
rtn->OnInit(); \
return rtn; \


class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity();
	~Entity();
	void Init() {}
	void SetCore(std::shared_ptr<Core> _c) { m_core = _c; }
	std::shared_ptr<Core> GetCore() { return m_core.lock(); }
	
	std::shared_ptr <Entity> AddChild()
	{
		std::shared_ptr<Entity> rtn = std::shared_ptr<Entity>(new Entity());
		rtn->SetCore(m_core.lock());
		rtn->m_alive = true;
		rtn->Init();
		rtn->m_parent = shared_from_this();
		m_children.push_back(rtn);
		return rtn;
	}

	template <typename T>
	std::shared_ptr <T> AddComponent()
	{
		std::shared_ptr <T> rtn = std::shared_ptr <T>(new T());
		rtn->SetEntity(shared_from_this());
		ADDCOMPONENT
	}

	template <typename T, typename A>
	std::shared_ptr <T> AddComponent(A _a)
	{
		std::shared_ptr <T> rtn = std::shared_ptr <T>(new T(_a));
		ADDCOMPONENT
	}


	template <typename T, typename A, typename B>
	std::shared_ptr <T> AddComponent(A _a, B _b)
	{
		std::shared_ptr <T> rtn = std::shared_ptr <T>(new T(_a, _b));
		ADDCOMPONENT
	}

	template <typename T, typename A, typename B, typename C>
	std::shared_ptr <T> AddComponent(A _a, B _b, C _c)
	{
		std::shared_ptr <T> rtn = std::shared_ptr <T>(new T(_a, _b, _c));
		ADDCOMPONENT
	}

	template <typename T, typename A, typename B, typename C, typename D>
	std::shared_ptr <T> AddComponent(A _a, B _b, C _c, D _d)
	{
		std::shared_ptr <T> rtn = std::shared_ptr <T>(new T(_a, _b, _c, _d));
		ADDCOMPONENT
	}

	template <typename T, typename A, typename B, typename C, typename D, typename E>
	std::shared_ptr <T> AddComponent(A _a, B _b, C _c, D _d, E _e)
	{
		std::shared_ptr <T> rtn = std::shared_ptr <T>(new T(_a, _b, _c, _d, _e));
		ADDCOMPONENT
	}

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		std::shared_ptr<T> rtn;
		if (!m_components.empty())
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				rtn = std::static_pointer_cast<T>(m_components[i]);
				if (rtn)
					return rtn;
			}
		}
		return rtn;
	}

	void Tick();
	void Display();
	void Gui();
	void PostProcess();
	bool m_alive;
	std::shared_ptr<Entity> m_parent;
	std::vector<std::shared_ptr<Entity>> m_children;

protected:
	std::vector<std::shared_ptr<Component>> m_components;
	std::weak_ptr<Core> m_core;


};