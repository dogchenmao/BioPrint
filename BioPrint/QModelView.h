#pragma once

#include <QtWidgets/QOpenGLWidget>
#include "ui_QModelView.h"
#include <QOpenGLFunctions>
#include <QStyleFactory>
#include "TCamera.h"


#define MAX_FILE_NUMBER         20                  // �����ӵ��ļ�����
#define MAX_SAMEFILE_NUMBER     10                  // ͬʱ��������ͬ�ļ���Ŀ
#define MODEL_VIEW_AT           0.75                // ģ����ʾ�ӽ�λ��
#define MODEL_COLOR             RGB(126, 126, 126)   // ģ����ʾ��ɫ
#define MODEL_HIGHLIGHT_COLOR   RGB(0, 200, 0)      // ģ�͸�����ʾ��ɫ
#define WIRE_FRAME_COLOR        RGB(240, 255, 240)         // 
//#define WIRE_FRAME_COLOR        RGB(100, 100, 100)  // ģ������ɫ

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
	// ������ת�����ת�Ƕ�
	void CalRotateVars(double star_x, double star_y, double end_x, double end_y,
		double& angle, double& r_vx, double& r_vy, double& r_vz);

protected:
	void SetViewDirection(int nDirection);
	void SetDefaultView();
	void RenderScene();
private:
	bool m_bMouseTracking;
	int m_ModelCount_Last;

	bool    m_ReDraw;						// �����Ƿ���Ҫ�ػ�(��ΪBCGSoft��BUG, ���ڷ����ı������OnDraw����9��֮��)
	bool    m_bLButtonDown;                 // ���������±�־�������ж�����϶�ʱ�Ƿ���Ҫ����ģ�͵�3ά����
	bool    m_bRButtonDown;                 // ����Ҽ����±�־�������ж�����϶�ʱ�Ƿ���Ҫ����ģ�͵�3ά����

	double  m_LButton_x;					// ����������ʱ��x����
	double  m_LButton_y;					// ����������ʱ��y����
	double  m_RButton_x;					// ����н�����ʱ��x����
	double  m_RButton_y;					// ����н�����ʱ��y����

	// ��ת�Ƕȡ������
	double  m_angle;
	double  m_rotate_xc;
	double  m_rotate_yc;
	double  m_rotate_zc;
	// ��ת�Ƕȡ������
	double  m_box_angle;
	double  m_box_rotate_xc;
	double  m_box_rotate_yc;
	double  m_box_rotate_zc;


	// ģ��ƽ��X����
	double  m_pan_dx;
	// ģ��ƽ��Y����
	double  m_pan_dy;
	// ģ��ƽ��Z����
	double  m_pan_dz;

	// ƽ�ƿ�ʼX����
	double m_pan_sx;
	// ƽ�ƿ�ʼY����
	double m_pan_sy;
	// ƽ�ƿ�ʼZ����
	double m_pan_sz;
	// ƽ���յ�X����
	double m_pan_ex;
	// ƽ���յ�Y����
	double m_pan_ey;
	// ƽ���յ�Z����
	double m_pan_ez;

	// ����
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
