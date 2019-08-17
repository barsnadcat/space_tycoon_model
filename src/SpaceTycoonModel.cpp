#include <iostream>
#include <easylogging++.h>

void Do(int param)
{
	LOG(INFO) << "Do " << param;
}