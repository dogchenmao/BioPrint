#include "BioPrint.h"
#include <QtWidgets/QApplication>
#include "Point5D.h"
#include "Q2DLines.h"
#include "QSTLSolid.h"
#include "QGCodeParser.h"
#include "QGCodeSolid.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BioPrint w;
	w.show();

	return a.exec();
}

