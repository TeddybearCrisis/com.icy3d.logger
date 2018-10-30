//
// Created by sgreve on 13.09.2018.
//

#pragma once

#define SPD_LOG_CONCAT_HELPER(x,y) x##y
#define SPD_LOG_CONCAT(x, y) SPD_LOG_CONCAT_HELPER(x, y)
#define SPD_LOG_VARNAME SPD_LOG_CONCAT(spd_log_message, __LINE__)
#define LOG_SS(SPD_LOG_LEVEL, SPD_LOG_MESSAGE) \
			{ \
				stringstream SPD_LOG_VARNAME; \
				SPD_LOG_VARNAME << "[" << __FUNCTION__ << "] "; \
				SPD_LOG_VARNAME << SPD_LOG_MESSAGE; \
				LogMaster::getInstance().getLogger()->SPD_LOG_LEVEL(SPD_LOG_VARNAME.str()); \
			}

#define LOG_DIR "logs"
#define LOGT(message) LOG_SS(trace,message)
#define LOGD(message) LOG_SS(debug,message)
#define LOGI(message) LOG_SS(info,message)
#define LOGW(message) LOG_SS(warn,message)
#define LOGE(message) LOG_SS(error,message)
#define LOGC(message) LOG_SS(critical,message)

// ATTENTION: make sure Windows.h is included in the main project before the following includes
#include <sstream>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "Log4netFormatter.h"

using namespace spdlog;
using namespace spdlog::sinks;
using namespace spdlog::level;

/**
 * SINGLETON Implementation of a wrapper class for SPD_LOG usage.
 * Usage:
 *  call LogMaster::init( ... , ... , ... ) once.
 * Afterwards you can use the definitions:
 *  LOGT, LOGD, LOGI, LOGW, LOGE
 */
class IcyLog {
public:

    static IcyLog &getInstance();

    static void init(const string &loggerName, level_enum consoleLogLevel, level_enum fileLogLevel);

    // Don't Implement
    IcyLog(IcyLog const &) = delete;

    // Don't implement
    void operator=(IcyLog const &) = delete;

    logger *getLogger() { return _logger; }

private:
    // Constructor (the {} brackets) are needed here.
    IcyLog() : _logger(nullptr) {}

    ~IcyLog() { delete _logger; }

    logger *_logger;
    shared_ptr<stdout_color_sink_mt> _console_sink;
    shared_ptr<basic_file_sink_mt> _file_sink;
    Log4netFormatter _formatter;
//    level_formatter _f;


    void initInstance(const string &loggerName, level_enum consoleLogLevel, level_enum fileLogLevel);

    string getLogFilename(const string &loggerName);
};