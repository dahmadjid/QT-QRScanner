#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <QDebug>
#include <QHash>
#include <QDateTime>
#include <QObject>





class Logger {
private:

    

	/// @brief The file object where logs are written to.
    static std::fstream log_file;

	/// @brief Whether the logger has being initialized.
    static bool is_init;

	/// @brief The different type of contexts.
    static const QHash<QtMsgType, QString> context_names;

public:

    Logger();


    ~Logger();

	/// @brief The function which handles the logging of text.
    static void messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);
};
