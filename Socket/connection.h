//
// Created by cenkerkaraors on 13.12.2020.
//

#ifndef UNIX_SOK_CONNECTION_H
#define UNIX_SOK_CONNECTION_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "string.h"
#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <netdb.h>
#include <sys/types.h>
#include "Threadpool.h"

class Connection
{
public:
    //Operator Mode Variables
    int operator_socket;
    struct sockaddr_un operator_sockaddr;
    // Station Mode Variables
    int station_socket;
    struct sockaddr_un station_sockaddr;
    int station_connection;
    bool isOperator;

    //Common
    Connection(bool mode);
    void operate();
    void use_console(int connection);
    int send_data(int connection, uint8_t * buffer);
    int receive_data(int connection);

    //Operator
    void operator_start();
    int operator_accept();
    void operator_handle(int connection);
    void operate_operator();

    // Station
    void station_start();
    void station_handle(int connection);
    void operate_station();
};



#endif //UNIX_SOK_CONNECTION_H
