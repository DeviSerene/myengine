#include "Collisions.h"

bool Collisions::TriangleCollision(glm::vec3 a1, glm::vec3 b1, glm::vec3 c1,
	glm::vec3 a2, glm::vec3 b2, glm::vec3 c2)
{
	/*
	int NoDivTriTriIsect(float V0[3], float V1[3], float V2[3],
		float U0[3], float U1[3], float U2[3]);

	if (NoDivTriTriIsect((float*)&a1, (float*)&b1, (float*)&c1,
		(float*)&a2, (float*)&b2, (float*)&c2) == 1)
	{
		return true;
	}
	*/
	return false;
}

bool Collisions::MeshCollision(std::vector<glm::vec3> _mesh, std::vector<glm::vec3> _mesh2)
{
	/**/
	//get all triangles from the meshes and check if any of them collide
	for (int m1 = 0; m1 < _mesh.size()-3; m1++)
	{
		for (int m2 = 0; m2 < _mesh2.size()-3; m2++)
		{
			if (TriangleCollision(_mesh[m1], _mesh[m1 + 1], _mesh[m1 + 2],
				_mesh[m2], _mesh[m2 + 1], _mesh[m2 + 2]))
			{
				return true;
			}
		}
	}
	return false;
}

bool Collisions::BoxCollision(glm::vec3 _box1Pos, glm::vec3 _box1Size, glm::vec3 _box2Pos, glm::vec3 _box2Size)
{
	if (_box1Pos.x < _box2Pos.x)
	{
		if (_box1Pos.x + _box1Size.x < _box2Pos.x)
		{
			return false;
		}
	}
	else
	{
		if (_box2Pos.x + _box2Size.x < _box1Pos.x)
		{
			return false;
		}
	}
	if (_box1Pos.y < _box2Pos.y)
	{
		if (_box1Pos.y + _box1Size.y < _box2Pos.y)
		{
			return false;
		}
	}
	else
	{
		if (_box2Pos.y + _box2Size.y < _box1Pos.y)
		{
			return false;
		}
	}
	if (_box1Pos.z < _box2Pos.z)
	{
		if (_box1Pos.z + _box1Size.z < _box2Pos.z)
		{
			return false;
		}
	}
	else
	{
		if (_box2Pos.z + _box2Size.z < _box1Pos.z)
		{
			return false;
		}
	}
	return true;
}
