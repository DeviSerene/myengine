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
#include "TitleScene.h"
#include "DeathScene.h"

void safe_main()
{
	std::cout << "Hello world" << std::endl;
	srand(time(NULL));
	std::shared_ptr<Core> core = Core::init();
	std::shared_ptr<BattleScene> bs = std::shared_ptr<BattleScene>(new BattleScene(core));
	std::shared_ptr<BossScene> bs2 = std::shared_ptr<BossScene>(new BossScene(core));
	std::shared_ptr<TitleScene> ts = std::shared_ptr<TitleScene>(new TitleScene(core));
	std::shared_ptr<DeathScene> ds = std::shared_ptr<DeathScene>(new DeathScene(core));
	core->AddScene(ts);
	core->AddScene(bs);
	core->AddScene(bs2);
	core->AddScene(ds);
	core->SetScene(0);

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
