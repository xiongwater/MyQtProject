#include "PaintWidget.h"
#include<QPainter>
#include<QPrintDialog>
#include<QPrinter>

 

/*���캯����ʼ������*/
PaintWidget::PaintWidget()

{


    image=QImage(this->size().width(),this->size().height(),QImage::Format_RGB32);  //�����ĳ�ʼ����С��Ϊ400*300��ʹ��32λ��ɫ
    backColor=qRgb(255,255,255);  //������ʼ������ɫʹ�ð�ɫ
    image.fill(backColor);

    modified=false;
    //modified=true;

    scale=1;
    angle=0;
    shear=0;

    penColor=Qt::black;
    brushColor=Qt::black;
    penWidth=1;
    penStyle=Qt::SolidLine;
    curShape=None;

    isDrawing=false;


}

/*�����ػ溯��*/
void PaintWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //painter.drawImage(0,0,image);

    //�����ػ��¼�����
    painter.scale(scale,scale);
    if(isDrawing)  //������ڻ�������ͼ�Σ�����ʾ��ʱ��ͼ���ϵ�����
    {
        painter.drawImage(0,0,tempImage);
    }
    else
    {
        if(angle)
        {
            QImage copyImage=image;  //�½���ʱ��copyImage��������������ת����
            QPainter pp(&copyImage);
            QPointF center(copyImage.width()/2.0,copyImage.height()/2.0);
            pp.translate(center);
            pp.rotate(angle);
            pp.translate(-center);
            pp.drawImage(0,0,image);
            image=copyImage;  //ֻ�Ḵ��ͼƬ�ϵ����ݣ����Ḵ������ϵͳ
            angle=0;  //�����ת�󽫽Ƕ�ֵ������Ϊ0

            /*QPointF center(image.width()/2.0,image.height()/2.0);
            painter.translate(center);
            painter.rotate(angle);
            painter.translate(-center);*/

        }
        if(shear)
        {
            //painter.shear(shear,shear);
            QImage copyImage=image;
            QPainter pp(&copyImage);
            pp.shear(shear,shear);
            pp.drawImage(0,0,image);
            image=copyImage;
            shear=0;
        }
        painter.drawImage(0,0,image);

    }


}


QSize PaintWidget::getImageSize()
{
    return image.size()*scale;
}

/*������갴�¡��ƶ����ͷź���*/
void PaintWidget::mousePressEvent(QMouseEvent*event)
{
    if(event->button()==Qt::LeftButton)  //������������
    {
        lastPoint=event->pos();  //������ָ�뵱ǰ������Ϊ��ʼ����
        isDrawing=true;
    }
}


void PaintWidget::mouseMoveEvent(QMouseEvent*event)
{
    if(event->buttons()&Qt::LeftButton)  //������������ŵ�ͬʱ�ƶ����
    {
        endPoint=event->pos();  //������ָ�뵱ǰ������Ϊ��ֹ����

        if(curShape==None || curShape==ERASE)  //�������������ͼ�λ��ƣ���ֱ����image�ϻ���
        {
            isDrawing=false;
            paint(image);  //����ͼ��

        }
        else  //�����������ͼ�Σ�������ʱ��ͼ��tempImage�ϻ���
        {
            tempImage=image;  //ÿ�λ���tempImageǰ����һ��image�е�ͼƬ����������
            paint(tempImage);
        }
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent*event)
{
    if(event->button()==Qt::LeftButton)  //����������ͷ�
    {
        endPoint=event->pos();  //������ָ�뵱ǰ������Ϊ��ֹ����
        isDrawing=false;
        paint(image);  //����ͼ��

    }
}

void PaintWidget::paint(QImage&theImage)
{
    QPainter pp(&theImage);  //��theImage�ϻ�ͼ

    /*
    pp.drawLine(lastPoint,endPoint);  //����ʼ�������ֹ�������ֱ��
    update();  //���и��½�����ʾ�������𴰿��ػ��¼����ػ洰��
    */

//    QPainter pp(&theImage);  //��zheImage�ϻ�ͼ
    QPen pen=QPen();
    pen.setColor(penColor);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    QBrush brush=QBrush(brushColor);
    pp.setPen(pen);
    pp.setBrush(brush);
    QRect rect;

    int x,y,w,h;
    x=lastPoint.x()/scale;
    y=lastPoint.y()/scale;
    w=(endPoint.x()-x)/scale;
    h=(endPoint.y()-y)/scale;

    switch(curShape)
    {
    case None:  //����������ͼ��
        {
            pp.drawLine(lastPoint/scale,endPoint/scale);  //����ʼ�������ֹ�������ֱ��
            lastPoint=endPoint;  //����ֹ�����Ϊ��ʼ����
            break;
        }
    case Line:  //����ֱ��
        {
            pp.drawLine(lastPoint/scale,endPoint/scale);
            break;
        }
    case Rectangle:  //���ƾ���
        {
            pp.drawRect(x,y,w,h);
            break;
        }
    case Ellipse:  //������Բ
        {
            pp.drawEllipse(x,y,w,h);
            break;
        }
    case ERASE:  //��Ƥ��
        {
            rect=QRect(lastPoint,QPoint(lastPoint.x()+10,lastPoint.y()+10));  //��Ƥ����С
            pp.eraseRect(rect);
            lastPoint=endPoint;
            break;
        }
    }
    update();  //���и��½�����ʾ�������𴰿��ػ��¼����ػ洰��
    modified=true;
}


void PaintWidget::setImageSize(int width,int height)
{
	//Qt::IgnoreAspectRatio,Qt::SmoothTransformation
	image=image.scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
   // QImage newImage(width,height,QImage::Format_RGB32);
   // image=newImage;
    update();
}

 

void PaintWidget::setImageColor(QColor color)
{
    backColor=color.rgb();  //��Ϊimage�ı���ɫҪ��QRgb���͵���ɫ���������������ת��
    image.fill(backColor);
    update();
}

 

bool PaintWidget::saveImage(const QString&fileName,const char*fileFormat)
{
    QImage visibleImage=image;

    if(visibleImage.save(fileName,fileFormat))  //ʵ�����ļ��洢
    {
        modified=false;
        return true;
    }
    else
    {
        return false;
    }
}


bool PaintWidget::openImage(const QString&fileName)
{
    QImage loadedImage;
    if(!loadedImage.load(fileName))
        return false;

    QSize newSize=loadedImage.size();
    setImageSize(newSize.width(),newSize.height());
    image=loadedImage;

    modified=false;
    update();
    return true;
}

 


void PaintWidget::doPrint()
{
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog*printDialog=new QPrintDialog(&printer,this);
    if(printDialog->exec()==QDialog::Accepted)
    {
        QPainter painter(&printer);
        QRect rect=painter.viewport();
        QSize size=image.size();
        size.scale(rect.size(),Qt::KeepAspectRatio);
        painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0,0,image);

    }
}

//�༭�˵����ܺ�������

void PaintWidget::zoomIn()
{
    scale*=1.2;
    update();
}


void PaintWidget::zoomOut()
{
    scale/=1.2;
    update();
}

void PaintWidget::zoom_1()
{
    scale=1;
    update();
}

void PaintWidget::doRotate()
{
    angle+=90;
    update();
}

void PaintWidget::doShear()
{
    shear=0.2;
    update();
}

void PaintWidget::doClear()
{
    image.fill(backColor);  //�����ڵĻ�������ɫ�������
    update();
}


//������亯������
void PaintWidget::setPenStyle(Qt::PenStyle style)
{
    penStyle=style;
}

void PaintWidget::setPenWidth(int width)
{
    penWidth=width;
}

void PaintWidget::setPenColor(QColor color)
{
    penColor=color;
}

void PaintWidget::setBrushColor(QColor color)
{
    brushColor=color;
}

void PaintWidget::setShape(ShapeType shape)
{
    curShape=shape;
}

void PaintWidget::changeEvent( QEvent *e )
{
	QWidget::changeEvent(e);

	if(e->type()==QEvent::Resize)
	{
		setImageSize(this->size().width(),this->size().height());
	}
}

void PaintWidget::resizeEvent( QResizeEvent *e )
{
	QWidget::resizeEvent(e);
	setImageSize(this->size().width(),this->size().height());
}
