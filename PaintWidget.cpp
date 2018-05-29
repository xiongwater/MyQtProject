#include "PaintWidget.h"
#include<QPainter>
#include<QPrintDialog>
#include<QPrinter>

 

/*构造函数初始化对象*/
PaintWidget::PaintWidget()

{


    image=QImage(this->size().width(),this->size().height(),QImage::Format_RGB32);  //画布的初始化大小设为400*300，使用32位颜色
    backColor=qRgb(255,255,255);  //画布初始化背景色使用白色
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

/*定义重绘函数*/
void PaintWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //painter.drawImage(0,0,image);

    //更改重绘事件函数
    painter.scale(scale,scale);
    if(isDrawing)  //如果正在绘制特殊图形，则显示临时绘图区上的内容
    {
        painter.drawImage(0,0,tempImage);
    }
    else
    {
        if(angle)
        {
            QImage copyImage=image;  //新建临时的copyImage，利用它进行旋转操作
            QPainter pp(&copyImage);
            QPointF center(copyImage.width()/2.0,copyImage.height()/2.0);
            pp.translate(center);
            pp.rotate(angle);
            pp.translate(-center);
            pp.drawImage(0,0,image);
            image=copyImage;  //只会复制图片上的内容，不会复制坐标系统
            angle=0;  //完成旋转后将角度值重新设为0

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

/*定义鼠标按下、移动、释放函数*/
void PaintWidget::mousePressEvent(QMouseEvent*event)
{
    if(event->button()==Qt::LeftButton)  //当鼠标左键按下
    {
        lastPoint=event->pos();  //获得鼠标指针当前坐标作为起始坐标
        isDrawing=true;
    }
}


void PaintWidget::mouseMoveEvent(QMouseEvent*event)
{
    if(event->buttons()&Qt::LeftButton)  //如果鼠标左键按着的同时移动鼠标
    {
        endPoint=event->pos();  //获得鼠标指针当前坐标作为终止坐标

        if(curShape==None || curShape==ERASE)  //如果不进行特殊图形绘制，则直接在image上绘制
        {
            isDrawing=false;
            paint(image);  //绘制图形

        }
        else  //如果绘制特殊图形，则再临时绘图区tempImage上绘制
        {
            tempImage=image;  //每次绘制tempImage前用上一次image中的图片对其进行填充
            paint(tempImage);
        }
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent*event)
{
    if(event->button()==Qt::LeftButton)  //如果鼠标左键释放
    {
        endPoint=event->pos();  //获得鼠标指针当前坐标作为终止坐标
        isDrawing=false;
        paint(image);  //绘制图形

    }
}

void PaintWidget::paint(QImage&theImage)
{
    QPainter pp(&theImage);  //在theImage上绘图

    /*
    pp.drawLine(lastPoint,endPoint);  //由起始坐标和终止坐标绘制直线
    update();  //进行更新界面显示，可引起窗口重绘事件，重绘窗口
    */

//    QPainter pp(&theImage);  //在zheImage上绘图
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
    case None:  //不绘制特殊图形
        {
            pp.drawLine(lastPoint/scale,endPoint/scale);  //由起始坐标和终止坐标绘制直线
            lastPoint=endPoint;  //让终止坐标变为起始坐标
            break;
        }
    case Line:  //绘制直线
        {
            pp.drawLine(lastPoint/scale,endPoint/scale);
            break;
        }
    case Rectangle:  //绘制矩形
        {
            pp.drawRect(x,y,w,h);
            break;
        }
    case Ellipse:  //绘制椭圆
        {
            pp.drawEllipse(x,y,w,h);
            break;
        }
    case ERASE:  //橡皮擦
        {
            rect=QRect(lastPoint,QPoint(lastPoint.x()+10,lastPoint.y()+10));  //橡皮擦大小
            pp.eraseRect(rect);
            lastPoint=endPoint;
            break;
        }
    }
    update();  //进行更新界面显示，可引起窗口重绘事件，重绘窗口
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
    backColor=color.rgb();  //因为image的背景色要用QRgb类型的颜色，所以这里进行了转换
    image.fill(backColor);
    update();
}

 

bool PaintWidget::saveImage(const QString&fileName,const char*fileFormat)
{
    QImage visibleImage=image;

    if(visibleImage.save(fileName,fileFormat))  //实现了文件存储
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

//编辑菜单功能函数定义

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
    image.fill(backColor);  //用现在的画布背景色进行填充
    update();
}


//画笔填充函数定义
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
