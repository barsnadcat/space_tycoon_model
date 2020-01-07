#pragma once

class IEntity
{
public:
	IEntity() = default;
	virtual ~IEntity() = default;

	virtual void Update() {}
};