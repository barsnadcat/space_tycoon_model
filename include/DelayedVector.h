#pragma once

#include <vector>
#include <memory>

//1 We need to update parent link too
//2 We can not use unique ptr - we need child to be present in two vectors simultaneusly during transition
//3 We should use raw pointers in interface - to avoid problem of "get shared from this"
// a. use raw pointer in vector, just add destructor
//4 How do we organise deletion of entity with children?
// a. Commit process has to go from leavs to root - when every thing is commited in children, you can move parent
//5 shtore shared ptrs internaly in vector and mAdd vectors - then it does not matter if oringal ovner of child is deleted before child is moved
// a. Then we should use shared ptr in interface as well! Then we facing get shared from this problem again
//6 Back to the begging - use raw pointers interanlly. But since parent does not actully manages it's children life time, 
// we have a problem - how to free memory.
// Ok if entity commits every thing in its vector -- can ve delete it saifly, since id now does manages its children life time?
// Here is the problem - if raw pointer is removed from vector, should we delete it, or not?
// Ok so, using same vector for location, update and memory managment is prolematic. Using separate vector in global state for update and memory management is problematic.
// But, what if same entities are present in two datastructures simultaneously - base class entity forms a double linked list - for updated and memory management, descendants use typed pointes for space and ownership hieracy
// Than we do not need two stage updates, because movemnt of any entity in space does not change it position in update linked list!


template<typename TChild, typename TParent>
class ChildrenVector
{
public:
	using TPtr = std::shared_ptr<TChild>;
	using TVector = std::vector<TPtr>;
	TVector v;
	void ScheduleAdd(TPtr element)
	{
		mToAdd.push_back(std::move(element));
	}
	void ScheduleDelete(TVector::iterator it)
	{
		mToDelete.push_back(it);
	}
	void Commit()
	{
		for (TVector::iterator it : mToDelete)
		{
			if (!mToAdd.empty())
			{
				*it = std::move(mToAdd.back());
				mToAdd.pop_back();
			}
			else
			{
				*it = std::move(v.back());
				v.pop_back();
			}
		}

		if (v.empty())
		{
			v = std::move(mToAdd);
		}
		else
		{
			v.reserve(v.size() + mToAdd.size());
			std::move(std::begin(mToAdd), std::end(mToAdd), std::back_inserter(v));
			mToAdd.clear();
		}
	}
private:
	std::vector<TVector::iterator> mToDelete;
	TVector mToAdd;
};

// Remove health check from update
// Add another udpate
// Entity should queue its removal from parent, but then, it have to know about parent? -- no good.
