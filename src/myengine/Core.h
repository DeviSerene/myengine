#include <memory>

class Core
{
public:
	Core();
	~Core();

	static std::shared_ptr<Core> init() { return (std::shared_ptr<Core>)new Core(); };

private:

};
