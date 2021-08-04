#ifndef LOGGER_H
#define LOGGER_H

#include <QTextStream>
#include <QFile>

class Logger
{
	public:

		static void initialize(const QString& file = "journal.log");
		static void terminate();
		static void write(const QString& msg);

	private:

		Logger(const QString& file);
		~Logger(){};
		Logger(const Logger&);
		Logger& operator=(const Logger&);

		static Logger* instance();
		static void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

		static Logger *m_instance;

		bool m_showDateTime;
		QFile m_file;
		QTextStream m_stream;
};

#endif // LOGGER_H
