#include "Q2DLines.h"

Q2DLines::Q2DLines(void)
{

}

Q2DLines::Q2DLines(const Q2DLines& source)
{
	this->clear();
	this->append(source);
}
const Q2DLines& Q2DLines::operator= (const Q2DLines& source)
{
	this->clear();
	this->append(source);
	return *this;
}
Q2DLines::~Q2DLines(void)
{
}

