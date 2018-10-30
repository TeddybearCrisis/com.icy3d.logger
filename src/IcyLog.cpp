//
// Created by sgreve on 13.09.2018.
//


#include "IcyLog.h"

IcyLog &IcyLog::getInstance() {
    static IcyLog instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
}

void IcyLog::init(const string &loggerName, level_enum consoleLogLevel, level_enum fileLogLevel) {
    IcyLog::getInstance().initInstance(loggerName, consoleLogLevel, fileLogLevel);
}

void IcyLog::initInstance(const string &loggerName, level_enum consoleLogLevel, level_enum fileLogLevel) {
    _console_sink = make_shared<stdout_color_sink_mt>();
    _console_sink->set_level(consoleLogLevel);
    //_console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");
    _console_sink->set_formatter(std::make_unique<Log4netFormatter>());

    string filename = getLogFilename(loggerName);

    _file_sink = make_shared<basic_file_sink_mt>(filename, true);
    _file_sink->set_level(fileLogLevel);
	_file_sink->set_formatter(std::make_unique<Log4netFormatter>());

    _logger = new logger(loggerName, {_console_sink, _file_sink});
    _logger->set_level(level::trace);
	_logger->flush_on(level::trace);

	LOGI("application started");
}

string IcyLog::getLogFilename(const string &loggerName) {
    string logFolder(LOG_DIR);
    if (!Io::directoryExists((char *) logFolder.c_str())) {
        Io::createDirectory(logFolder);
    }

    stringstream logFileName;
    logFileName << logFolder << "/";
    logFileName << Io::getLocalTimePrefix() << "_" << loggerName << ".log";
    string filename = logFileName.str();
    return filename;
}



