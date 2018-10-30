//
// Created by sgreve on 13.09.2018.
//


#include "Formatter.h"
#include <sstream>
#include <iomanip>

using namespace icy3d;
using namespace std;
using namespace std::chrono;
using namespace spdlog;
using namespace spdlog::details;

Formatter::Formatter() {
    
    // attention don't use Level_enum values as key as this hashes the values different from int
    // https://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key

//    enum level_enum
//    {
//        trace = 0,
//        debug = 1,
//        info = 2,
//        warn = 3,
//        err = 4,
//        critical = 5,
//        off = 6
//    };


    _levelMap[0] = "TRACE";
    _levelMap[1] = "DEBUG";
    _levelMap[2] = "INFO";
    _levelMap[3] = "WARN";
    _levelMap[4] = "ERROR";
    _levelMap[5] = "CRITICAL";
    _levelMap[6] = "OFF";
}

void Formatter::format(const details::log_msg &msg, fmt::memory_buffer &dest) {
    int l = msg.level;
    const char *strLevel = _levelMap.at(l);

    // OLD:  [2018-09-13 11:26:20.268] [IcyMessageLogger] [error] hello error
    // GOAL: [2018-09-13 11:26:20.268] [ERROR] hello error

    stringstream ss;
    ss << "[" << timePointToString(msg.time) << "] ";
    //ss << "[" << *msg.logger_name << "] ";
    ss << "[" << strLevel << "] ";

    fmt_helper::append_c_str(ss.str().c_str(), dest);
    fmt_helper::append_buf(msg.raw, dest);
    fmt_helper::append_c_str("\n", dest);
}

std::unique_ptr<formatter> Formatter::clone() const {
    return unique_ptr<formatter>();
}

string Formatter::timePointToString(log_clock::time_point tp) {

    // better use
    // https://stackoverflow.com/questions/48217017/what-is-the-prettiest-way-to-convert-time-point-to-string

    using sc = std::chrono::system_clock;
    std::time_t t = sc::to_time_t(tp);
    char buf[26];
    strftime(buf, 26, "%Y-%m-%d %H:%M:%S", localtime(&t));
    std::string strDateTime(buf);

    milliseconds ms = duration_cast<milliseconds>(tp.time_since_epoch());
    auto fractional_seconds = static_cast<size_t>(ms.count() % 1000);

    stringstream s;
    s << strDateTime << "." << fractional_seconds;
    string result = s.str();
    return result;
}
