//#include <Qt>
#include <QSlider>
#include <QDateTime>
#include <QProxyStyle>


//样式类
class PlaybackSliderStyle : public QProxyStyle
{

public:
	explicit PlaybackSliderStyle(QStyle *base);
	~PlaybackSliderStyle();

	int styleHint(StyleHint hint, const QStyleOption * = 0, const QWidget * = 0, QStyleHintReturn * = 0) const;
};
























//媒体播放用的滑动条
class MediaPlayerSlider : public QSlider 
{
	Q_OBJECT


private:
	QDateTime _beginTime;//起始时间
	QDateTime _endTime;//结束时间
	QDateTime _currentTime;//当前时间
	qreal _scale;//倍数
	QTimer *_timer;//定时器
public:
	explicit MediaPlayerSlider(QWidget *parent = 0);
	~MediaPlayerSlider();

	void setDateTime(const QDateTime &);
	void setTimeRange(const QDateTime &begin, const QDateTime &end);
	void reset();
	QDateTime currentTime() const;

	void start(int ms = 1000) const;
	void stop();
	bool finished();

protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);





signals:
	void seekTimepointRequest(const QDateTime &);
	void timepointChanged();
	void sliderFinished();

	private slots:
		void trySeekTimePoint(int = 0);
		void steping();
};