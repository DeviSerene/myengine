#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Resource.h"

//to go up a directory, use "../" !

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
	std::shared_ptr<T> Create();

	void CleanUp(float& _deltaTime);

private:
	std::vector<std::shared_ptr<Resource>> m_resources;

};
