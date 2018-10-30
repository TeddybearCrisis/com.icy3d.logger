//
// Created by sgreve on 13.09.2018.
//

#pragma once

#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/details/pattern_formatter.h>


using namespace std;
using namespace spdlog;
using namespace spdlog::details;
using namespace spdlog::level;

class Log4netFormatter : public spdlog::formatter {

public:

    static string timePointToString(log_clock::time_point tp);

    Log4netFormatter();

    void format(const details::log_msg &msg, fmt::memory_buffer &dest) override;

    std::unique_ptr<formatter> clone() const override;

private:
    map<int, const char *> _levelMap;

};