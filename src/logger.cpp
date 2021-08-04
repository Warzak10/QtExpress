#include "logger.h"

#include <QDateTime>
#include <QApplication>

Logger* Logger::m_instance = nullptr;

Logger::Logger(const QString& file) : m_showDateTime(true)
{
	m_file.setFileName(file);
	m_stream.setDevice(&m_file);
	m_stream.setCodec("UTF-8");

	qInstallMessageHandler(this->messageHandler);
}

Logger *Logger::instance()
{
	initialize();
	return m_instance;
}

void Logger::initialize(const QString &file)
{
	if(m_instance == nullptr) m_instance = new Logger(file);
}

void Logger::terminate()
{
	if(m_instance != nullptr){
		delete m_instance;
		m_instance = nullptr;
		qInstallMessageHandler(0);
	}
}

void Logger::write(const QString& msg)
{
	Logger *l = instance();
	QByteArray localMsg = msg.toUtf8();
	l->m_file.open(QIODevice::Append | QIODevice::Text);
	l->m_stream << localMsg << endl;
	l->m_file.close();
}

void Logger::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QString fmsg = msg;
#ifdef QT_MESSAGELOGCONTEXT
	const char *file = context.file ? context.file : "";
	const char *function = context.function ? context.function : "";
	fmsg.append(QString(" (%1:%2, %3)").arg(file).arg(context.line).arg(function));
#else
	Q_UNUSED(context);
#endif
	switch (type) {
	case QtDebugMsg:	fmsg.prepend("Debug:    "); break;
	case QtInfoMsg:		fmsg.prepend("Info:     "); break;
	case QtWarningMsg:	fmsg.prepend("Warning:  "); break;
	case QtCriticalMsg:	fmsg.prepend("Critical: "); break;
	case QtFatalMsg:	fmsg.prepend("Fatal:    "); break;}

	Logger *l = instance();
	if(l->m_showDateTime) fmsg.prepend(QDateTime::currentDateTime().toString("dd.MM.yy hh:mm:ss "));
	write(fmsg);

	switch (type) {
	case QtCriticalMsg:
	case QtFatalMsg:
		qApp->exit(1);
	default: break;}
}
