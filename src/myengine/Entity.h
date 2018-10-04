#include <memory>
#include <vector>

class Core;
class Component;

class Entity
{
public:
	Entity();
	~Entity();
	std::shared_ptr<Core> GetCore() { return (std::shared_ptr<Core>)m_core; }

	template <typename T>
	std::shared_ptr <T> AddComponent();

	template <typename T, typename A>
	std::shared_ptr <T> AddComponent(A _a);

	template <typename T, typename A, typename B>
	std::shared_ptr <T> AddComponent(A _a, B _b);

	template <typename T, typename A, typename B, typename C>
	std::shared_ptr <T> AddComponent(A _a, B _b, C _c);

	template <typename T, typename A, typename B, typename C, typename D>
	std::shared_ptr <T> AddComponent(A _a, B _b, C _c, D _d);

private:
	std::vector<std::shared_ptr<Component>> m_components;
	std::weak_ptr<Core> m_core;
	void Tick() {};
	void Display() {};

};