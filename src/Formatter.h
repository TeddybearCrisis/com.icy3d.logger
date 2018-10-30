//
// Created by sgreve on 13.09.2018.
//

#pragma once

#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/details/pattern_formatter.h>

namespace icy3d {

class Formatter : public spdlog::formatter {

public:

    friend class FormatterTest;

    static std::string timePointToString(spdlog::log_clock::time_point tp);

    Formatter();

    void format(const spdlog::details::log_msg &msg, fmt::memory_buffer &dest) override;

    std::unique_ptr<formatter> clone() const override;

private:
    std::map<int, const char *> _levelMap;

};

}