#include "Logger.h"

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED << x << RST
#define FGRN(x) KGRN << x << RST
#define FYEL(x) KYEL << x << RST
#define FBLU(x) KBLU << x << RST
#define FMAG(x) KMAG << x << RST
#define FCYN(x) KCYN << x << RST
#define FWHT(x) KWHT << x << RST

#define BOLD(x)	"\x1B[1m" << x << RST
#define UNDL(x)	"\x1B[4m" << x << RST


// #define LOG_TO_FILE
#define LOG_TO_CONSOLE

const char* log_file_path = "logs.txt";


std::fstream Logger::log_file;

bool Logger::is_init = false;

const QHash<QtMsgType, QString> Logger::context_names = {
    {QtMsgType::QtDebugMsg,		"DEBUG   "},
    {QtMsgType::QtInfoMsg,		"INFO    "},
    {QtMsgType::QtWarningMsg,	"WARNING "},
    {QtMsgType::QtCriticalMsg,	"CRITICAL"},
    {QtMsgType::QtFatalMsg,		"FATAL   "}
};

Logger::Logger()
{

    if (!is_init) 
    {

#ifdef LOG_TO_FILE
        log_file.open(log_file_path, std::ios_base::out);
#endif
        qInstallMessageHandler(Logger::messageOutput);


        Logger::is_init = true;
    }
}
Logger::~Logger()
{
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Logger::messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{

#if defined(LOG_TO_FILE) || defined(LOG_TO_CONSOLE)
#ifdef QT_MESSAGELOGCONTEXT
    std::string log = QObject::tr("%1 %2 : %3       (%4:%5:1  %6)").
		arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss.zzz")).
        arg(Logger::context_names.value(type)).
        arg(msg).
		arg(QString(context.file)).			// File name without file path
        arg(context.line).
        arg(QString(context.function)).	// Function name only
        toStdString();
#else
    std::string log = QObject::tr("%1 %2 : %3").
        arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss")).
        arg(Logger::context_names.value(type)).
        arg(msg).toStdString();
#endif
#endif

#ifdef LOG_TO_FILE
    log_file << log << std::endl;
#endif

#ifdef LOG_TO_CONSOLE
    switch(type) 
    {
        case QtMsgType::QtDebugMsg:
            std::cout << log << std::endl;
            break;
            
        case QtMsgType::QtInfoMsg:
            std::cout << FGRN(log) << std::endl;
            break;

        case QtMsgType::QtWarningMsg:
            std::cout << FYEL(log) << std::endl;
            break;

        case QtMsgType::QtCriticalMsg:
            std::cout << FRED(log) << std::endl;
            break;

        case QtMsgType::QtFatalMsg:
            std::cout << BOLD(FRED(log)) << std::endl;
            break;

        default:
            std::cout << log << std::endl;
            break;
        

    }
#endif
}
