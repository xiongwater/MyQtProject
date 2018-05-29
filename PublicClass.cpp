
#include <QToolTip>
#include <QTimer>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QButtonGroup>
#include <QToolButton>
#include <QLabel>
#include <QMouseEvent>
#include <QProxyStyle>
#include <QtCore/qmath.h>

#include <QDebug>
#include <PublicClass.h>



#include<Windows.h>





PlaybackSliderStyle::PlaybackSliderStyle(QStyle *base)
	: QProxyStyle(base)
{

}

PlaybackSliderStyle::~PlaybackSliderStyle()
{

}

//@override
int PlaybackSliderStyle::styleHint(StyleHint hint
	, const QStyleOption *opt, const QWidget *widget, QStyleHintReturn *returnData) const
{
	if (hint == QStyle::SH_Slider_AbsoluteSetButtons) {
		return Qt::LeftButton;
	}
	return QProxyStyle::styleHint(hint, opt, widget, returnData);
}











MediaPlayerSlider::MediaPlayerSlider(QWidget *parent)
	: QSlider(Qt::Horizontal, parent)//ˮƽ������
	, _scale(0)//���ű���
	, _timer(new QTimer(this))//��ʱ��
{
	//_timer->setInterval(1000);
	_timer->setSingleShot(false);//�������Ϊtrue����ʾֻ������һ��
	connect(_timer, SIGNAL(timeout()), SLOT(steping()));//ÿ��һ��ʱ�䣬����steping

	setTracking(false);//
	setMouseTracking(false);//
	setStyle(new PlaybackSliderStyle(style()));//���÷��
	connect(this, SIGNAL(valueChanged(int)), SLOT(trySeekTimePoint(int)));//�����������ֵ�ı仯�ᴥ��trySeekTimePoint
}

MediaPlayerSlider::~MediaPlayerSlider()
{

}
//���õ�ǰʱ��
void MediaPlayerSlider::setDateTime(const QDateTime &time)
{
	Q_ASSERT(_scale != 0);//���ű�������Ϊ0
	int sec = _beginTime.secsTo(time);//���ش�������ڵ�dt�����������dt����������ڣ����ص�Ϊ��������
	//int val = sec / maximum() * _scale;
	int val = sec / _scale;//
	Q_ASSERT(val >= 0);
	blockSignals(true);//���blockΪ�棬�����źţ��������blockΪ�٣�ȡ���ź�����������źű���������������ź���ʧ�ڳ��ռ䡣
	setValue(val);
	blockSignals(false);//ȡ������

	_currentTime = time;//���õ�ǰʱ��
	emit timepointChanged();//����ʱ��仯�ź�
}

void MediaPlayerSlider::setTimeRange(const QDateTime &begin, const QDateTime &end)
{
	if (_beginTime == begin && _endTime == end) return;
	_beginTime = begin;
	_endTime = end;
	_currentTime = _beginTime;
	int duration = _beginTime.secsTo(_endTime);
	setRange(0, qBound<int>(0, duration, 500));//qBound(min,value,max)�����ַ����ش���value�ĵ�һ��ֵ
	_scale = (qreal)duration / maximum();//Ƶ��Խ�ߣ�����Խ��
	Q_ASSERT(_scale != 0);
	reset();
}

void MediaPlayerSlider::reset()
{
	setDateTime(_beginTime);
}

void MediaPlayerSlider::start(int ms) const
{
	if (!_timer->isActive()) _timer->start(ms);
}

void MediaPlayerSlider::stop() 
{
	if (_timer->isActive()) {
		_timer->stop();
	}
}

QDateTime MediaPlayerSlider::currentTime() const
{
	return _currentTime;
}

//@override
void MediaPlayerSlider::mousePressEvent(QMouseEvent *ev)
{
	QSlider::mousePressEvent(ev);
	stop();
}

//@override
void MediaPlayerSlider::mouseMoveEvent(QMouseEvent *ev)
{
	QSlider::mouseMoveEvent(ev);

	const QDateTime &t = _beginTime.addSecs(ev->x() * maximum() / width() * _scale);
	QToolTip::showText(ev->globalPos(), t.toString("MM-dd hh:mm:ss"), this);
}

bool MediaPlayerSlider::finished() 
{
	if (value() == maximum()) {
		stop();
		this->reset();
		emit sliderFinished();
		return true;
	}
	return false;
}

void MediaPlayerSlider::trySeekTimePoint(int val)
{
	stop();
	const QDateTime &t = _beginTime.addSecs(val * _scale);
	setDateTime(t);
	QToolTip::showText(QCursor::pos(), t.toString("MM-dd hh:mm:ss"), this);

	if (!finished()) {
		emit seekTimepointRequest(t);

	}
}

//@slot
void MediaPlayerSlider::steping()
{
	if (finished()) return;
	//�����ʱ�䵹�ˣ����-1�뼴��
	setDateTime(_currentTime.addSecs(1));

}



//����תutf8
char* gb2312ToUTF8(const char* pGb2312)
{
	char* str = NULL;
#ifdef WIN32
	int len = MultiByteToWideChar(CP_ACP, 0, pGb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, pGb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
#elif DARWIN
	gb2312ToUtf8_alpha(str, pGb2312);
#endif
	return str;
}

//utf8 ת����
char* utf8TGb2312(const char* pUTF8)
{
	char* str = NULL;
#ifdef WIN32
	int len = MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
#elif DARWIN
	utf8ToGb2312_alpha(str, pUTF8);
#endif
	return str;
}