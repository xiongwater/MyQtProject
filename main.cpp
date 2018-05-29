#include "MyApp.h"
#include <QtGui/QApplication>
#include <Qdir>
#include <QThreadPool>
#include <QTextCodec>
#include <QTranslator>


int main(int argc, char *argv[])
{

	//�������ã��������Ľ��������룩
	//QTextCodec* codec=QTextCodec::codecForName("GBK");//��� 2 �Ǵ˴� ��GBK�� ��Ϊ ��UTF-8��
	//QTextCodec::setCodecForCStrings(codec);
	//QTextCodec::setCodecForTr(codec);
	//QTextCodec::setCodecForLocale(codec);

	//�����Ͳ����ڱ��˵����ϲ���ȷ��
	QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));





	QThreadPool *qtp = QThreadPool::globalInstance();//��ȡȫ���̳߳�
	

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int n = qtp->maxThreadCount();    
	qtp->setMaxThreadCount(n * 100);  //���߳�������Ϊ  ������ * 20
	qtp->setExpiryTimeout(-1);//�����߳̽���ʱ�� -1��ʾ������


	
	MyApp MyApp(argc,argv);
	MyApp.setWindowIcon(QIcon(":/Resources/Myicon.png"));
	//�������Ӧ�ó���ĵ�ǰ����Ŀ¼Ϊpath�����Ŀ¼���ɹ��ı䣬�����棬���򷵻ؼ١�
	QDir::setCurrent(QApplication::applicationDirPath());
	



	//����Qt�е���Դ�ļ���ʹQt��ʾ���ģ�����QMessageBox���ı����Ҽ��˵��ȣ�
	QTranslator translator;
	translator.load("translations/qt_zh_CN");
	MyApp.installTranslator(&translator);
	try
	{
		MyApp.StartApp();
		return MyApp.exec();
	}
	catch(...)
	{
		MyApp.exit();
	}
	return 0;
}
