#include "XYArray.h"

ASErr XYArray::Spread(int width)
{
	multiArray newXYData(width);
	int count = 0;

	//loop through every row
	for (int i = 0; i < this->xyArray[0].size(); i++)
	{
		if (count == width){
			count = 0;
		}

		newXYData[count].push_back(this->xyArray[0][i]);
		count++;
	}

	this->xyArray = newXYData;

	return ASErr();
}

int XYArray::Size()
{
	return this->xyArray.size()*this->xyArray[0].size();
}

void XYArray::FlipV(){
	for (int i = 0; i < this->xyArray.size(); i++)
	{
		reverse(this->xyArray[i].begin(), this->xyArray[i].end());
	}
}

void XYArray::FlipH(){
	reverse(this->xyArray.begin(), this->xyArray.end());
}