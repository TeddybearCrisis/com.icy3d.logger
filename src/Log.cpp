//
// Created by sgreve on 13.09.2018.
//


#include "Log.h"
#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>

using namespace icy3d;
using namespace std;
using namespace cppfs;
using namespace spdlog::sinks;
using namespace spdlog::level;

Log &Log::getInstance() {
    static Log instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
}

void Log::init(const std::string &loggerName, const std::string &logFolder, spdlog::level::level_enum consoleLogLevel,
              spdlog::level::level_enum fileLogLevel) {
    Log::getInstance().initInstance(loggerName, logFolder, consoleLogLevel, fileLogLevel);
}

void Log::initInstance(const std::string &loggerName, std::string logFolder, spdlog::level::level_enum consoleLogLevel,
                       spdlog::level::level_enum fileLogLevel) {
    _console_sink = make_shared<stdout_color_sink_mt>();
    _console_sink->set_level(consoleLogLevel);
    //_console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");
    _console_sink->set_formatter(std::make_unique<Formatter>());

    string filename = getLogFilename(logFolder, loggerName);

    _file_sink = make_shared<basic_file_sink_mt>(filename, true);
    _file_sink->set_level(fileLogLevel);
    _file_sink->set_formatter(std::make_unique<Formatter>());

    _logger = new spdlog::logger(loggerName, {_console_sink, _file_sink});
    _logger->set_level(spdlog::level::trace);
    _logger->flush_on(spdlog::level::trace);

    LOGI("application started");
}

string Log::getLogFilename(const string &logFolder, const string &loggerName) {
    FileHandle fh = fs::open(logFolder);
    if (!fh.exists()) {
        fh.createDirectory();
    }

    stringstream logFileName;
    logFileName << logFolder << "/";
    logFileName << Log::getLocalTimePrefix() << "_" << loggerName << ".log";
    string filename = logFileName.str();
    return filename;
}


string Log::getLocalTimePrefix() {
    time_t now = time(nullptr);
    char buf[sizeof("YYYY-MM-DD_HH-MM-SS")];
    struct tm *timeInfo = localtime(&now);
    char *bufEnd(buf + strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", timeInfo));
    string result(buf, bufEnd);
    return result;
}



