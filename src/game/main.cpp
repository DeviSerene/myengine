#include <iostream>
#include <fstream>
#include <memory>
#include <Windows.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <myengine/Core.h>
#include <myengine/MyEngineException.h>
#include "BattleScene.h"
#include "BossScene.h"

void safe_main()
{
	std::cout << "Hello world" << std::endl;
	srand(time(NULL));
	std::shared_ptr<Core> core = Core::init();
	std::shared_ptr<BossScene> bs = std::shared_ptr<BossScene>(new BossScene(core));

	core->Start();
}

int main()
{
	try
	{
		safe_main();
	}
	catch (MyEngineException e)
	{
		MessageBox(0, e.what(), "Error Box", 0);
	}
	catch (std::exception e)
	{
		MessageBox(0, e.what(), "Error Box",0);
	}
	catch (...)
	{
		MessageBox(0, "Something has been thrown.", "Error Box", 0);
	}

return 0;
}
