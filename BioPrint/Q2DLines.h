#pragma once
#include "qvector.h"
#include "Point5D.h"
class Q2DLines :public QVector<Point5D*>
{
public:
	Q2DLines(void);
	Q2DLines(const Q2DLines&);
	~Q2DLines(void);
	const Q2DLines& operator= (const Q2DLines&);

};

