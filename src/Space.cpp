#include <Space.h>

#include <Entity.h>

void UpdateObjects(ObjectSPs& container, UpdateContext& uc)
{
	for (ObjectSP object : container)
	{
		object->Update(uc);
	}
}

void DeleteObjects(ObjectSPs& container)
{
	auto predicate = [](auto const& p)
					 {
						 return p->entity->GetHealth() == 0;
					 };
	container.erase(std::remove_if(container.begin(), container.end(), predicate), container.end());
}

void Space::Update(UpdateContext& uc)
{
	for(auto& it: mContent)
	{
		UpdateObjects(it.second, uc);
	}
	for(auto& it: mContent)
	{
		DeleteObjects(it.second);
	}
}

void Space::Add(ObjectSP object)
{
	object->entity->SetParent(mThisObject.shared_from_this());
	mContent[object->id].push_back(object);
}
