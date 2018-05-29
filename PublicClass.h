//#include <Qt>
#include <QSlider>
#include <QDateTime>
#include <QProxyStyle>


//��ʽ��
class PlaybackSliderStyle : public QProxyStyle
{

public:
	explicit PlaybackSliderStyle(QStyle *base);
	~PlaybackSliderStyle();

	int styleHint(StyleHint hint, const QStyleOption * = 0, const QWidget * = 0, QStyleHintReturn * = 0) const;
};
























//ý�岥���õĻ�����
class MediaPlayerSlider : public QSlider 
{
	Q_OBJECT


private:
	QDateTime _beginTime;//��ʼʱ��
	QDateTime _endTime;//����ʱ��
	QDateTime _currentTime;//��ǰʱ��
	qreal _scale;//����
	QTimer *_timer;//��ʱ��
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