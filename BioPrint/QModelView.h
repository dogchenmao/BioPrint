#pragma once

#include <QtWidgets/QOpenGLWidget>
#include "ui_QModelView.h"
#include <QOpenGLFunctions>
#include <QStyleFactory>
#include "TCamera.h"


#define MAX_FILE_NUMBER         20                  // 最多添加的文件数量
#define MAX_SAMEFILE_NUMBER     10                  // 同时添加最大相同文件数目
#define MODEL_VIEW_AT           0.75                // 模型显示视角位置
#define MODEL_COLOR             RGB(126, 126, 126)   // 模型显示颜色
#define MODEL_HIGHLIGHT_COLOR   RGB(0, 200, 0)      // 模型高亮显示颜色
#define WIRE_FRAME_COLOR        RGB(240, 255, 240)         // 
//#define WIRE_FRAME_COLOR        RGB(100, 100, 100)  // 模型线颜色

typedef struct _AUX_RGBImageRec {
	GLint sizeX, sizeY;
	unsigned char *data;
} AUX_RGBImageRec;

class QModelView : public QOpenGLWidget
{
	Q_OBJECT

private:
	void invertMatrix(const GLdouble *m, GLdouble *out);
	void map2Sphere(double px, double py, double& vx, double& vy, double& vz);
private:
	double _matrix[16];
	double _inverse_matrix[16];
	bool _is_init;
	bool m_isTexturesLoaded;

	GLuint texture[1];

	TCamera m_Camera;
	int m_BoxList;

protected:
	void resizeGL(int w, int h) override;
	void initializeGL() override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent *event) override;
	void timerEvent(QTimerEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

public:
	QModelView(QWidget *parent = Q_NULLPTR);
	~QModelView();

public:
	
	void SetBkground();
	void DrawBox(double x, double y, double z);

	// initializing
	void Init(void);
	void GLSetupRC();
	void GLResize(int cx, int cy, double pos);
	void Ready();
	void Finish();
	void ReleaseRC();

public:
	// camera operation
	void SetScale(double scale);
	void GetScale(double& scale);
	void SetWindow(double width, double height);
	void GetWindow(double& width, double& height);
	void SetProjection();
	void SetProjectionBody(double left, double right, double bottom,
		double top, double near, double Far);
	void GetProjectionBody(double& left, double& right, double& bottom,
		double& top, double& znear, double& zfar);

public:
	//  transformation
	void TransformPosition(const int &x, const int &y, double &px, double &py, double &pz);
	void RefreshMatrix();
	const double *GetMatrix();
	const double *GetInverseMatrix();

public:
	// 计算旋转轴和旋转角度
	void CalRotateVars(double star_x, double star_y, double end_x, double end_y,
		double& angle, double& r_vx, double& r_vy, double& r_vz);

protected:
	void SetViewDirection(int nDirection);
	void SetDefaultView();
	void RenderScene();
private:
	bool m_bMouseTracking;
	int m_ModelCount_Last;

	bool    m_ReDraw;						// 窗口是否需要重绘(因为BCGSoft有BUG, 窗口发生改变后会调用OnDraw函数9次之多)
	bool    m_bLButtonDown;                 // 鼠标左键按下标志，用于判断鼠标拖动时是否需要更新模型的3维坐标
	bool    m_bRButtonDown;                 // 鼠标右键按下标志，用于判断鼠标拖动时是否需要更新模型的3维坐标

	double  m_LButton_x;					// 鼠标左键按下时的x坐标
	double  m_LButton_y;					// 鼠标左键按下时的y坐标
	double  m_RButton_x;					// 鼠标中建按下时的x坐标
	double  m_RButton_y;					// 鼠标中建按下时的y坐标

	// 旋转角度、轴分量
	double  m_angle;
	double  m_rotate_xc;
	double  m_rotate_yc;
	double  m_rotate_zc;
	// 旋转角度、轴分量
	double  m_box_angle;
	double  m_box_rotate_xc;
	double  m_box_rotate_yc;
	double  m_box_rotate_zc;


	// 模型平移X分量
	double  m_pan_dx;
	// 模型平移Y分量
	double  m_pan_dy;
	// 模型平移Z分量
	double  m_pan_dz;

	// 平移开始X坐标
	double m_pan_sx;
	// 平移开始Y坐标
	double m_pan_sy;
	// 平移开始Z坐标
	double m_pan_sz;
	// 平移终点X坐标
	double m_pan_ex;
	// 平移终点Y坐标
	double m_pan_ey;
	// 平移终点Z坐标
	double m_pan_ez;

	// 缩放
	short m_scale_zdelta;
	double m_scale_dx;
	double m_scale_dy;
	double m_scale_dz;

	bool m_AutoRotate;
	// Implementation

	bool m_ViewSTL;
private:
	Ui::QModelView ui;

};
