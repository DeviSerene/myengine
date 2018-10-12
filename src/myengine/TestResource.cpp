#include "TestResource.h"

TestResource::TestResource()
{

}

std::shared_ptr<TestResource> TestResource::Create()
{
	std::shared_ptr<TestResource> rtn = std::shared_ptr<TestResource>(new TestResource());
	rtn->m_timer = 0;
	rtn->m_data = true;
	return rtn;
}

std::shared_ptr<TestResource> TestResource::Load(std::string _path)
{
	std::shared_ptr<TestResource> rtn = std::shared_ptr<TestResource>(new TestResource());
	rtn->m_data = true;
	rtn->m_path = _path;
	rtn->m_timer = 0;
	return rtn;
}
