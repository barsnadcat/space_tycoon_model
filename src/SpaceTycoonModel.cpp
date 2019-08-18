#include <iostream>
#include <easylogging++.h>

bool Do(int param)
{
	LOG(INFO) << "Do " << param;
	return true;
}