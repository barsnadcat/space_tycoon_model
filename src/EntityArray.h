#pragma once

#include <vector>

template<typename T>
class EntityVector
{
private:
	struct Element
	{
		T entity;
	};

private:
	std::vector<Element> mEntities;
};