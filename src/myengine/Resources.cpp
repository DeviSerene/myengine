#include "Resources.h"
#include <iostream>
#include "Sound.h"

void Resources::CleanUp(float& _deltaTime)
{
	if (!m_resources.empty())
	{
		for (int i = 0; i < m_resources.size(); i++)
		{
			if (m_resources[i].use_count() < 2)
			{
				//if there is only one thing pointing to it, it needs to be set for deletion
				m_resources[i]->AddToTimer(_deltaTime);
				if (m_resources[i]->TimerFinished())
				{
					std::cout << "Resource:" << m_resources[i]->GetPath() << " deleted!" << std::endl;
					m_resources.erase(m_resources.begin() + i);
					i--;
				}
			}
			else
			{
				m_resources[i]->ResetTimer();
			}
		}
	}
}

void Resources::StopAllSounds()
{
	if (!m_resources.empty())
	{
		for (int i = 0; i < m_resources.size(); i++)
		{
			if(m_resources[i]->GetPath().size() > 4)
			{
				if (m_resources[i]->GetPath().substr(m_resources[i]->GetPath().length() - 4) == ".ogg")
				{
					std::shared_ptr<Sound> rtn =  std::static_pointer_cast<Sound>(m_resources[i]);
					rtn->Stop();
				}
			}
		}
	}
}