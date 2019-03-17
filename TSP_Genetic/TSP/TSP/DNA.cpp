#include "pch.h"
#include "DNA.h"

using namespace std;


DNA::DNA()
{
	fitness = 0.0;
}

DNA::DNA(vector<int> order_)
{
	order = order_;
	fitness = 0.0;
}