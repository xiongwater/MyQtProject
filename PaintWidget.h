#pragma once
#include "qwidget.h"
#include<QMouseEvent>
#include<QPoint>
class PaintWidget :
	public QWidget
{
	Q_OBJECT
public:
	PaintWidget(void);
	//~PaintWidget(void);
	
public:
	//explicit PaintWidget();
	void setImageSize(int width,int height);  //�����ı仭����С����
	void setImageColor(QColor color);  //�����ı仭����ɫ����

	bool isModified() const{return modified;}  //�жϻ��������Ƿ񱻸��Ĺ�
	bool saveImage(const QString&fileName,const char*fileFormat); //����ͼƬ
	bool openImage(const QString&fileName);  //��ͼƬ

	QSize getImageSize();

	void doPrint();  //��ӡ�˵����ܺ�������

	//���߲˵����ܺ�������
	void zoomIn();  //�Ŵ�
	void zoomOut();  //��С
	void zoom_1();  //��ԭ
	void doRotate();  //��ת
	void doShear();  //����
	void doClear();  //���

	//������ɫ
	void setPenStyle(Qt::PenStyle style);  //���û��ʷ��
	void setPenWidth(int width);  //���û��ʿ��
	void setPenColor(QColor color);  //���û�����ɫ
	void setBrushColor(QColor color);  //���������ɫ

	enum ShapeType  //ö�ٱ���������ͼ�ε�ѡ��
	{
		None,
		Line,
		Rectangle,
		Ellipse,
		ERASE
	};
	void setShape(ShapeType shape);  //����Ҫ���Ƶ�ͼ��


protected:
	void paintEvent(QPaintEvent*);  //�ػ��¼�

	void mousePressEvent(QMouseEvent*);  //��갴���¼�
	void mouseMoveEvent(QMouseEvent*);  //����ƶ��¼�
	void mouseReleaseEvent(QMouseEvent*);  //����ͷ��¼�
	void paint(QImage&theImage);
	void changeEvent(QEvent *e);
	virtual void resizeEvent(QResizeEvent *e);
private:
	QImage image;  //QImage��������������ϻ�ͼ
	QRgb backColor;  //QRgb��ɫ���󣬴洢image�ı���ɫ

	QPoint lastPoint,endPoint;  //��������������������ָ���ǰ����������

	bool modified;  //��־�����Ƿ񱻸��Ĺ�


	//���߱�������
	qreal scale;  //������
	int angle;  //�Ƕ�
	qreal shear;  //������

	//����������
	QColor penColor;  //������ɫ
	QColor brushColor;  //�����ɫ
	int penWidth;  //���ʿ��
	Qt::PenStyle penStyle;  //���ʷ��
	ShapeType curShape;  //��ǰͼ��

	QImage tempImage;  //��ʱ��ͼ��
	bool isDrawing;  //�Ƿ��ڻ�������ͼ��


signals:

	public slots:
};

