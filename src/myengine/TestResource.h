#pragma once
#include "Resource.h"

class TestResource : public Resource
{
public:
	TestResource();
	
	static std::shared_ptr<TestResource> Create();
	static std::shared_ptr<TestResource> Load(std::string _path);

	bool GetData() { return m_data; }

private:
	bool m_data;
};