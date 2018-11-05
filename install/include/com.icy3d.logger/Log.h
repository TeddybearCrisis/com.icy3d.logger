//
// Created by sgreve on 13.09.2018.
//

#pragma once

#include <sstream>

#define SPD_LOG_CONCAT_HELPER(x, y) x##y
#define SPD_LOG_CONCAT(x, y) SPD_LOG_CONCAT_HELPER(x, y)
#define SPD_LOG_VARNAME SPD_LOG_CONCAT(spd_log_message, __LINE__)
#define LOG_SS(SPD_LOG_LEVEL, SPD_LOG_MESSAGE) \
            { \
                std::stringstream SPD_LOG_VARNAME; \
                SPD_LOG_VARNAME << "[" << __FUNCTION__ << "] "; \
                SPD_LOG_VARNAME << SPD_LOG_MESSAGE; \
                Log::getInstance().getLogger()->SPD_LOG_LEVEL(SPD_LOG_VARNAME.str()); \
            }

#define LOGT(message) LOG_SS(trace,message)
#define LOGD(message) LOG_SS(debug,message)
#define LOGI(message) LOG_SS(info,message)
#define LOGW(message) LOG_SS(warn,message)
#define LOGE(message) LOG_SS(error,message)
#define LOGC(message) LOG_SS(critical,message)

#define DEFAULT_LOG_DIR "logs"

// ATTENTION: make sure Windows.h is included in the main project before the following includes

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "Formatter.h"

namespace icy3d {

/**
 * SINGLETON Implementation of a wrapper class for SPD_LOG usage.
 * Usage:
 *  call icy3d::Log::init( ..., ... ) once.
 * Afterwards include this header and you can use the following macros:
 *  LOGT, LOGD, LOGI, LOGW, LOGE
 */
class Log {
public:
    friend class LogTest;

    /**
   * @brief gets the current timestamp (up to seconds) as sortable string in local format.
   * uses deprecated methods and only runs on win at the moment.
   * @return the current timestamp as string
   */
    static std::string getLocalTimePrefix();

    static Log &getInstance();

    /** @brief SINGLETON Implementation of a wrapper class for SPD_LOG usage.
     * Usage:
     *  call icy3d::Log::init( ..., ... ) once.
     * Afterwards include this header and you can use the following macros:
     *  LOGT, LOGD, LOGI, LOGW, LOGE
     *  @param loggerName a name identifying this logger when mixed with other output
     *  @param logFolder set a custom subfolder to log data into. defaults to 'logs'
     *  @param consoleLogLevel defines the log level of the console logger
     *  @param fileLogLevel defines the log level of the file logger ('logs' directory)
    */
    static void init(const std::string &loggerName,
                     const std::string &logFolder = std::string(DEFAULT_LOG_DIR),
                     spdlog::level::level_enum consoleLogLevel = spdlog::level::info,
                     spdlog::level::level_enum fileLogLevel = spdlog::level::trace);


    /**
     * @brief don't implement. Use LOGI, ... , LOGE macros instead (see the head of this file)
     */
    Log(Log const &) = delete;

    /**
     * @brief don't implement. Use LOGI, ... , LOGE macros instead (see the head of this file)
     */
    void operator=(Log const &) = delete;

    /**
     * @brief don't implement. Use LOGI, ... , LOGE macros instead (see the head of this file)
     */
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


};

}