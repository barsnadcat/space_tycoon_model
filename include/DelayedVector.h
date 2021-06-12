#pragma once

#include <vector>
#include <memory>

template<typename T>
class DelayedVector
{
public:
	using TPtr = std::unique_ptr<T>;
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
