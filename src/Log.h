//
// Created by sgreve on 13.09.2018.
//

#pragma once

#define SPD_LOG_CONCAT_HELPER(x, y) x##y
#define SPD_LOG_CONCAT(x, y) SPD_LOG_CONCAT_HELPER(x, y)
#define SPD_LOG_VARNAME SPD_LOG_CONCAT(spd_log_message, __LINE__)
#define LOG_SS(SPD_LOG_LEVEL, SPD_LOG_MESSAGE) \
            { \
                stringstream SPD_LOG_VARNAME; \
                SPD_LOG_VARNAME << "[" << __FUNCTION__ << "] "; \
                SPD_LOG_VARNAME << (SPD_LOG_MESSAGE); \
                Log::getInstance().getLogger()->SPD_LOG_LEVEL(SPD_LOG_VARNAME.str()); \
            }

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
#include "Formatter.h"

namespace icy3d {

/**
 * SINGLETON Implementation of a wrapper class for SPD_LOG usage.
 * Usage:
 *  call icy3d::Log::init( ..., ... ) once.
 * Afterwards include this header and you can use the following definitions:
 *  LOGT, LOGD, LOGI, LOGW, LOGE
 */
class Log {
public:
    friend class LogTest;

    static Log &getInstance();

    static void init(const std::string &loggerName,
                     const std::string &logFolder = std::string("logs"),
                     spdlog::level::level_enum consoleLogLevel = spdlog::level::info,
                     spdlog::level::level_enum fileLogLevel = spdlog::level::trace);


// Don't Implement
    Log(Log const &) = delete;

// Don't implement
    void operator=(Log const &) = delete;

    spdlog::logger *getLogger() { return _logger; }

private:
// Constructor (the {} brackets) are needed here.
    Log() : _logger(nullptr) {}

    ~Log() { delete _logger; }

    spdlog::logger *_logger;

    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> _console_sink;
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> _file_sink;

    void initInstance(const std::string &loggerName,
                      std::string logFolder,
                      spdlog::level::level_enum consoleLogLevel,
                      spdlog::level::level_enum fileLogLevel);

    std::string getLogFilename(const std::string &logFolder, const std::string &loggerName);

    /**
    * @brief gets the current timestamp (up to seconds) as sortable string in local format.
    * uses deprecated methods and only runs on win at the moment.
    * @return the current timestamp as string
    */
    static std::string getLocalTimePrefix();
};

}