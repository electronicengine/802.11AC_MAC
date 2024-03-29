//
// Created by cenkerkaraors on 19.12.2020.
//

#ifndef UNIX_SOCKET_LOGGING_H
#define UNIX_SOCKET_LOGGING_H

#include <iostream>

#include <sstream>
#include <cstdarg>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <fstream>

#include <map>

#define RESET           "\033[0m"
#define BLACK           "\033[30m"      /* Black */
#define RED             "\033[31m"      /* Red */
#define GREEN           "\033[32m"      /* Green */
#define YELLOW          "\033[33m"      /* Yellow */
#define BLUE            "\033[34m"      /* Blue */
#define MAGENTA         "\033[35m"      /* Magenta */
#define CYAN            "\033[36m"      /* Cyan */
#define WHITE           "\033[37m"      /* White */
#define BOLDBLACK       "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED         "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN       "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW      "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE        "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA     "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN        "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE       "\033[1m\033[37m"      /* Bold White */



namespace Logging
{

    extern bool ENABLE_RED_LOG;
    extern bool ENABLE_WHITE_LOG;
    extern bool ENABLE_MAGENTA_LOG;
    extern bool ENABLE_GREEN_LOG;
    extern bool ENABLE_BLUE_LOG;
    extern bool ENABLE_YELLOW_LOG;
    extern bool ENABLE_CYAN_LOG;

    void disableLogs();
    void enableLogs();


    enum LogColor
    {
        magenta,
        cyan,
        red,
        yellow,
        green,
        blue,
        white

    };

    template< typename T >
    inline std::string serializer(const T& t)
    {

        std::stringstream string_stream;
        string_stream << t;
        return string_stream.str();

    }


    template< typename T, typename ... Args >
    inline std::string serializer(const T& head, Args ... args)
    {
        return serializer( head ) + serializer( args... );
    }



    template<typename... TAIL>
    void printAll(LogColor Color, const TAIL&... tail)
    {
        std::ofstream log_file("/tmp/log_file.log", std::ios_base::app);

        std::string package = serializer(tail...);

        switch (Color)
        {
            case white:
                if(Logging::ENABLE_WHITE_LOG)
                {
                    std::cout << WHITE << package << std::endl;
                    log_file << "WHITE: " << package << std::endl;
                }
                    std::cout << WHITE << package << std::endl;

                break;
            case magenta:
                if(Logging::ENABLE_MAGENTA_LOG)
                {
                    std::cout << MAGENTA << package << std::endl;
                    log_file << "MAGENTA: " << package << std::endl;
                }
                    std::cout << MAGENTA << package << std::endl;

                break;
            case cyan:
                if(Logging::ENABLE_CYAN_LOG)
                {
                    std::cout << CYAN << package << std::endl;
                    log_file << "CYAN: " << package << std::endl;
                }
                    std::cout << CYAN << package << std::endl;

                break;
            case red:
                if(Logging::ENABLE_RED_LOG)
                {
                    std::cout << RED << package << std::endl;
                    log_file << "RED: " << package << std::endl;
                }

                    std::cout << RED << package << std::endl;

                break;
            case yellow:
                if(Logging::ENABLE_YELLOW_LOG)
                {
                    std::cout << YELLOW << package << std::endl;
                    log_file << "YELLOW: " << package << std::endl;
                }

                    std::cout << YELLOW << package << std::endl;

                break;
            case green:
                if(Logging::ENABLE_GREEN_LOG)
                {
                    std::cout << GREEN << package << std::endl;
                    log_file << "GREEN: " << package << std::endl;
                }
                    std::cout << GREEN << package << std::endl;

                break;
            case blue:
                if(Logging::ENABLE_BLUE_LOG)
                {
                    std::cout << BLUE << package << std::endl;
                    log_file << "BLUE: " << package << std::endl;
                }
                    std::cout << BLUE << package << std::endl;

                break;
            default:
                break;
        }

        log_file.close();


    }


}

#endif //UNIX_SOCKET_LOGGING_H
