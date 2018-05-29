#include "MyApp.h"
#include <QHostInfo>
#include <QMovie>
#include <opencv/highgui.h>  //����opencv��ͷ�ļ�  
#include <opencv/cv.h>  




QFile* MyApp::m_pFileLog=NULL;





QImage MatToQImage( const cv::Mat& mat )
{
	// 8-bits unsigned, NO. OF CHANNELS = 1      
	if (mat.type() == CV_8UC1)  
	{  
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);  
		// Set the color table (used to translate colour indexes to qRgb values)      
		image.setColorCount(256);  
		for (int i = 0; i < 256; i++)  
		{  
			image.setColor(i, qRgb(i, i, i));  
		}  
		// Copy input Mat      
		uchar *pSrc = mat.data;  
		for (int row = 0; row < mat.rows; row++)  
		{  
			uchar *pDest = image.scanLine(row);  
			memcpy(pDest, pSrc, mat.cols);  
			pSrc += mat.step;  
		}  
		return image;  
	}  
	// 8-bits unsigned, NO. OF CHANNELS = 3      
	else if (mat.type() == CV_8UC3)  
	{  
		// Copy input Mat     
		const uchar *pSrc = (const uchar*)mat.data;  
		// Create QImage with same dimensions as input Mat      
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);  
		return image.rgbSwapped();  
	}  
	else if (mat.type() == CV_8UC4)  
	{  
		// Copy input Mat      
		const uchar *pSrc = (const uchar*)mat.data;  
		// Create QImage with same dimensions as input Mat      
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);  
		return image.copy();  
	}  
	else  
	{  
		return QImage();  
	}
}












MyApp::MyApp(int& argc, char **argv, int flags)
	:QApplication(argc, argv, flags),
	m_AppState(MyApp::MyAppState::CREATED),
	m_isAppStateChanged(false),
	checkStateTimer(new QTimer(this)),
	m_AppSplash(NULL)
{
	m_Config=new QSettings(QApplication::applicationDirPath() + "\\" + AppConfig, QSettings::IniFormat, NULL);
	_application_dir = qApp->applicationDirPath().toLocal8Bit().data();
	QApplication::font().setStyleStrategy(QFont::PreferAntialias);
	//������
	 m_MainWnd=new MyAppMainWindow(this);
	
	 //������
	 m_central_widget= static_cast<CentralWidget *>(m_MainWnd->centralWidget());
	//��½����
    m_Login=new MyAppLogin();
	read_config();
	//m_Login->setStyleSheet("border-image:url(:/Resources/dogyear.png)");

	connect(m_Login,SIGNAL(LoginSuccessed()),m_MainWnd,SLOT(LoginSuccessed()));
	m_pTimer_check_update = new QTimer(this);
	m_pTimer_check_update->setInterval(60000);
	QFile cfgFile(QApplication::applicationDirPath() + "/" +AppConfig);
	if(!cfgFile.exists())
	{//�����ڣ�����
		cfgFile.open(QIODevice::WriteOnly);
		cfgFile.close();
	}
	setApplicationName("XH_Client");
	achieveLocalIp();//�õ�ipv4��ַ

}

MyApp::~MyApp()
{
	delete m_Login;
	delete m_MainWnd;
	delete m_Config;

}

void MyApp::achieveLocalIp()
{
	QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
	foreach(QHostAddress address, info.addresses())
	{
		if(address.protocol() == QAbstractSocket::IPv4Protocol)
		{//ֻȡipv4Э��ĵ�ַ  
			qDebug() << address.toString();
			_local_ip = address.toString().toStdString();
			break;
		}
	}
}

bool MyApp::StartApp()
{

	///////////���һ���������棬�Ӿ����޿��٣����ڼ��أ���ѯ�ȵ�ʱ�䣩/////////////////////
	QWriteLocker locker(&this->_lock);
    Qt::Alignment topRight=Qt::AlignRight||Qt::AlignTop;



	

	if(NULL ==  m_AppSplash)
	{
		//QPixmap pixmap("splash.gif");  
		QPixmap pixmap(":/Resources/dogyear.png");  
		
		m_AppSplash=new QSplashScreen(pixmap);
	   m_AppSplash->setAutoFillBackground(true);
		//m_AppSplash->setStyleSheet("border-image:url(:/Resources/dogyear.png)");
	}
	m_AppSplash->show();
	m_AppSplash->showMessage(tr("��............."),1,Qt::black);
	
#ifndef NDEBUG
	CreateLogFile();
#endif
	QTime t;
	t.start();


	cv::VideoCapture splashCapture("dota.avi");
	if(splashCapture.isOpened())
	{
		cv::Mat frame;
		while(t.elapsed()<7000)
		{
			if(t.elapsed()>2000)
			{
				splashCapture>>frame;
				if(!frame.empty())
				{
					m_AppSplash->setPixmap(QPixmap::fromImage(MatToQImage(frame)));	
				}
			}
			
			QCoreApplication::processEvents();
		}
		splashCapture.release();
	}
	else
	{
		while(t.elapsed()<1000)
		{
			QCoreApplication::processEvents();
			m_AppSplash->repaint();
		}

		m_AppSplash->showMessage(tr("Ŭ��.........."),topRight,Qt::black);
		while(t.elapsed()<2000)
		{
			m_AppSplash->repaint();
			QCoreApplication::processEvents();
		}

		m_AppSplash->showMessage(tr("���..........."),topRight,Qt::black);
		while(t.elapsed()<3000)
		{
			m_AppSplash->repaint();
			QCoreApplication::processEvents();
		}
	}
	
	m_Login->show();
	m_AppSplash->finish(m_Login);
	delete m_AppSplash;
	m_AppSplash= NULL;
	return true;
	
}

void MyApp::CreateLogFile()
{

	if(!MyApp::m_pFileLog)
	{
		QString _strFileName = QCoreApplication::applicationDirPath() + '/' + AppLog;
		MyApp::m_pFileLog = new QFile(_strFileName);
		MyApp::m_pFileLog->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text | QIODevice::Unbuffered);
		qInstallMsgHandler(MyApp::messageHandle);
	}
}

bool MyApp::read_config()
{
	QSettings   cfg(QApplication::applicationDirPath() + "\\" + AppConfig, QSettings::IniFormat, NULL);

	QString     strFirst = cfg.value("ContentTest/First", "").toString();
	QString     strSecond = cfg.value("ContentTest/Second", "").toString();

	if(strFirst.length() == 0)
	{
		qDebug() << "can not find m_FirstAnswer!";
		return false;
	}
	else
	{
		m_FirstAnswer=strFirst.toLatin1();
	}
	if(strSecond.length() == 0)
	{
		qDebug() << "can not find m_SecondAnswer!";
		return false;
	}
	else
	{
		m_SecondAnswer=strSecond.toLatin1();
	}

	//_msgsvr_url = v.toLatin1();
	_msgsvr_username = "MSG_USERNAME";
	_msgsvr_passwd = "MSG_PASSWORD";

	/*v = cfg.value("IOTP/SERVER_PORT", "").toString();
	if(v.length() == 0)
	{
	qDebug() << "can not find IOTP SERVER PORT configuration!";
	return false;
	}*/
	QRegExp uuidReg("[0-9A-Za-z]{8}-[0-9A-Za-z]{4}-[0-9A-Za-z]{4}-[0-9A-Za-z]{4}-[0-9A-Za-z]{12}");
	bool b = uuidReg.isValid();
	//������ʽ��regular expression��������һ�����ַ�����������һ��������Ȼ��ȥ��֤��һ�����ַ������Ƿ�������������
	//��֤UUID�Ƿ���Ч
	b = uuidReg.exactMatch((cfg.value("ContentTest/UUID", "").toString()).toLatin1());
	if(b)
	{
	
	}
	else
	{
	
	}
	m_LastLoginAnswer=cfg.value("ContentTest/LastLogin", "").toString().toLatin1();
	
	////��֤�ͻ���UUID�Ƿ���Ч
	//v = cfg.value("IOTP/CLIENT_UID", "").toString();
	//if(v.length() == 0)
	//{
	//	
	//	qDebug() << "can not find IOTP CLIENT UID configuration!";
	//	return false;
	//}
	//b = uuidReg.exactMatch(v);
	//if(b)
	//{
	//	QByteArray ba = v.toLatin1();
	//	
	//}
	//else
	//{
	//	
	//	return false;
	//}

	//_last_login_name = cfg.value("IOTP/LAST_LOGIN", "").toString().toLocal8Bit();
	//QString pwd = cfg.value("IOTP/LAST_LOGIN_PWD", "").toString();
	////_last_login_pwd = pwd.isEmpty() ? "" : getXorEncryptDecrypt(pwd, 11).toLocal8Bit();
	///*_login_window->set_login_name(_last_login_name);
	//_login_window->set_login_pwd(_last_login_pwd);*/
	return true;
}

void MyApp::messageHandle( QtMsgType type, const char *msg )
{
	if(!MyApp::m_pFileLog)
	{
		return;
	}

	QTextStream ts(MyApp::m_pFileLog);
	ts.setLocale(QLocale::Chinese);
	switch(type)
	{
	case QtDebugMsg:
		ts << QString("DEBUG ") << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ") << QString(msg) << endl;
		break;

	case QtWarningMsg:
		ts << QString("WARN ") << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ") << QString(msg) << endl;
		break;

	case QtCriticalMsg:
		ts << QString("ERROR ") << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ") << QString(msg) << endl;
		break;

	case QtFatalMsg:
		ts << QString("FATAL ") << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ") << QString(msg) << endl;
		break;
	}
}

bool MyApp::notify( QObject *obj, QEvent *e )
{
	//��д�¼��������⵽����ƶ��¼�
	if(dynamic_cast<QMouseEvent*>(e))
	{
		QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
		if(mouseEvent->type() == QEvent::MouseMove)
		{
			QPoint globalPos =mouseEvent->globalPos();
			QPoint relPos =m_central_widget->mapFromGlobal(globalPos);
			m_central_widget->handleMouseMove(relPos);

		}
	}
	return QApplication::notify(obj, e);
}

void MyApp::load_local_libraries( QString app_dir )
{
	//get plugin home directory
	if(!app_dir.endsWith("/"))
	{
		app_dir.append('/');
	}

	this->_plugins_dir = app_dir + QString(PLUGIN_DIR) + "/";
	QDir dir(this->_plugins_dir);
	if(!dir.exists())
	{
		if(!dir.mkpath(this->_plugins_dir))
		{
				this->_plugins_dir.toLocal8Bit().data();
		}
	}

	qDebug() << "Plugin home path:" << this->_plugins_dir;
	foreach(QString file, QDir(this->_plugins_dir).entryList(QDir::Files))
	{
		file = file.toLower();
		if(!file.endsWith(".dll"))
		{//platform specific.
			continue;
		}

		qDebug() << "Load library " << this->_plugins_dir + file;
		QString errmsg;
		if(!loadLibrary(this->_plugins_dir + file, &errmsg))
		{
			qCritical() << "Failed, error: " << errmsg;
			continue;
		}
	}

}

bool MyApp::loadLibrary(QString file_path, QString *error_msg)
{
	QWriteLocker locker(&this->_lock);

	QPluginLoader loader(file_path);

	bool b = loader.load();
	if(b)
		qDebug("loder ok!\r\n");
	else
		qDebug("loder error!\r\n");

	QObject *plugin = loader.instance();
	if (plugin)
	{
		return plugin;
	}
	else
		qDebug("loader.instance() error\r\n");

	return NULL;


	/*if(is_library_loaded(file_path))
	{
	qDebug() << "Library already loaded!";
	return true;
	}*/

	////load library
	//QLibrary *lib = new QLibrary(file_path, this);
	//if(false == lib->load())
	//{
	//	qDebug() << lib->errorString();
	//	if(error_msg)
	//	{
	//		*error_msg = lib->errorString();
	//	}
	//	return false;
	//}

	////resolve entry symbol
	//PLUGIN_FACTOTRY_ENTRIES *entries = NULL;
	//__IOTP_PLUGIN_LIB_ENTRY func = (__IOTP_PLUGIN_LIB_ENTRY)lib->resolve("IOTP_PLUGIN_LIB_ENTRY");
	//if(!func)
	//{
	//	qDebug() << "Not found library entry function symbol!";
	//	if(error_msg)
	//	{
	//		*error_msg = QString("No entry function symbol!");
	//	}
	//	delete lib;
	//	return false;
	//}

	////call to get the entries.
	//try
	//{
	//	entries = (PLUGIN_FACTOTRY_ENTRIES *)func();
	//}
	//catch(...)
	//{
	//	qDebug() << "Call library entry function error!";
	//	if(error_msg)
	//	{
	//		*error_msg = QString("Call entry point function error!");
	//	}
	//	delete lib;
	//	return false;
	//}

	////create an plugin lib instance and save it.
	//PluginLibrary *plugin_lib = new PluginLibrary(this, file_path, lib, entries);

	////hash loaded plugins.
	//for(unsigned int i = 0; i < plugin_lib->_factory_count; i++)
	//{
	//	qDebug() << "load plugin factory [" << plugin_lib->_factories[i]->get_name() << "]";
	//	QString id(plugin_lib->_factories[i]->get_uuid());
	//	if(_plugins.value(id) == NULL)
	//	{
	//		_plugins.insert(id, plugin_lib->_factories[i]);
	//	}
	//	else
	//	{
	//		qCritical() << "fond duplicate plugin factory identifier " << id << "!";
	//	}
	//}

	////hash loaded library
	//_libraries.insert(file_path, plugin_lib);
	return true;
}
