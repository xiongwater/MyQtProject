
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
	: QSlider(Qt::Horizontal, parent)//水平滑动条
	, _scale(0)//缩放倍数
	, _timer(new QTimer(this))//计时器
{
	//_timer->setInterval(1000);
	_timer->setSingleShot(false);//如果参数为true，表示只触发发一次
	connect(_timer, SIGNAL(timeout()), SLOT(steping()));//每隔一段时间，触发steping

	setTracking(false);//
	setMouseTracking(false);//
	setStyle(new PlaybackSliderStyle(style()));//设置风格
	connect(this, SIGNAL(valueChanged(int)), SLOT(trySeekTimePoint(int)));//滑动条上面的值的变化会触发trySeekTimePoint
}

MediaPlayerSlider::~MediaPlayerSlider()
{

}
//设置当前时间
void MediaPlayerSlider::setDateTime(const QDateTime &time)
{
	Q_ASSERT(_scale != 0);//缩放倍数不能为0
	int sec = _beginTime.secsTo(time);//返回从这个日期到dt的秒数（如果dt早于这个日期，返回的为负数）。
	//int val = sec / maximum() * _scale;
	int val = sec / _scale;//
	Q_ASSERT(val >= 0);
	blockSignals(true);//如果block为真，阻塞信号，或者如果block为假，取消信号阻塞。如果信号被阻塞，被发射的信号消失在超空间。
	setValue(val);
	blockSignals(false);//取消阻塞

	_currentTime = time;//设置当前时间
	emit timepointChanged();//发出时间变化信号
}

void MediaPlayerSlider::setTimeRange(const QDateTime &begin, const QDateTime &end)
{
	if (_beginTime == begin && _endTime == end) return;
	_beginTime = begin;
	_endTime = end;
	_currentTime = _beginTime;
	int duration = _beginTime.secsTo(_endTime);
	setRange(0, qBound<int>(0, duration, 500));//qBound(min,value,max)，二分法返回大于value的第一个值
	_scale = (qreal)duration / maximum();//频率越高，倍数越大
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
	//如果是时间倒退，则加-1秒即可
	setDateTime(_currentTime.addSecs(1));

}



//国标转utf8
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

//utf8 转国标
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