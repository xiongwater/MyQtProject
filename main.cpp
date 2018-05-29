#include "MyApp.h"
#include <QtGui/QApplication>
#include <Qdir>
#include <QThreadPool>
#include <QTextCodec>
#include <QTranslator>


int main(int argc, char *argv[])
{

	//编码设置（否则中文将出现乱码）
	//QTextCodec* codec=QTextCodec::codecForName("GBK");//情况 2 是此处 “GBK” 变为 “UTF-8”
	//QTextCodec::setCodecForCStrings(codec);
	//QTextCodec::setCodecForTr(codec);
	//QTextCodec::setCodecForLocale(codec);

	//这样就不会在别人电脑上不正确了
	QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));





	QThreadPool *qtp = QThreadPool::globalInstance();//获取全局线程池
	

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int n = qtp->maxThreadCount();    
	qtp->setMaxThreadCount(n * 100);  //将线程数设置为  核心数 * 20
	qtp->setExpiryTimeout(-1);//设置线程结束时间 -1表示不结束


	
	MyApp MyApp(argc,argv);
	MyApp.setWindowIcon(QIcon(":/Resources/Myicon.png"));
	//设置你的应用程序的当前工作目录为path。如果目录被成功改变，返回真，否则返回假。
	QDir::setCurrent(QApplication::applicationDirPath());
	



	//加载Qt中的资源文件，使Qt显示中文（包括QMessageBox、文本框右键菜单等）
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
