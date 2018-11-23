#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Resource.h"

//to go up a directory, use "../" !
/*!
If a user wishes to load a Resource, they need to go through Resources. With this factory system, they do not have to worry about memory management (too much).
Resources will try to load the resource via its path, checking if it is already in memory, returning it if it is so, or creating a new one if it is not.
If absolutely needed, Resources can also stop all sounds that are currently playing in memory.
*/

class Resources
{
public:
	template <typename T>
	std::shared_ptr <T> Load(std::string _path)
	{
		std::shared_ptr <T> rtn;
		if (!m_resources.empty())
		{
			for (int i = 0; i < m_resources.size(); i++)
			{
				if (m_resources[i]->GetPath() == _path)
				{
					rtn = std::static_pointer_cast<T>(m_resources[i]);
					if (rtn)
						return rtn;;
				}
			}
		}
		rtn = T::Load(_path);
		m_resources.push_back(rtn);
		return rtn;
	}

	template <typename T>
	std::shared_ptr <T> Create()
	{
		std::shared_ptr <T> rtn;
		rtn = T::Create();
		m_resources.push_back(rtn);
		return rtn;
	}

	void CleanUp(float& _deltaTime);

	void StopAllSounds();

private:
	std::vector<std::shared_ptr<Resource>> m_resources;

};
