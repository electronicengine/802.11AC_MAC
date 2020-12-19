//
// Created by cenkerkaraors on 13.12.2020.
//
#include "connection.h"
#define SERVER_PATH "/home/cenkerkaraors/Desktop/Bitirme/Socket/socket_temp"
#define TRANSMISSON_SIZE    2048

void Connection::operator_start()
{
    operator_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    bzero((char *) &operator_sockaddr, sizeof(operator_sockaddr));
    operator_sockaddr.sun_family = AF_UNIX;

    strcpy(operator_sockaddr.sun_path, SERVER_PATH);

    //int true_control = 1;
    //setsockopt(operator_socket, SOL_SOCKET, SO_REUSEADDR, &true_control,sizeof(int));

    bind(operator_socket, (struct sockaddr*) &operator_sockaddr, sizeof(operator_sockaddr));

    listen(operator_socket, 3);
}


int Connection::operator_accept()
{
    int new_connection = accept(operator_socket, NULL, NULL);

    return new_connection;
}


void Connection::operator_handle(int connection)
{
    if(connection == -1)
    {
        printf("Failed to connect \n");
    }
    else
    {
        use_console(connection);

    }
    std::cout << "Closing Connection" << std::endl;
    close(connection);
    unlink(SERVER_PATH);
}


void Connection::operate_operator()
{
    operator_start();
    printf("Started the operator\n");
    auto tp = Threadpool(3);

    while(true)
    {
        if(tp.getActiveWorkers() < tp.getWorkerSize()) {
            int new_connection = operator_accept();
            if (new_connection != -1) {
                std::cout << " Active Workers: " << tp.getActiveWorkers() << std::endl;
                tp.pushWork(&Connection::operator_handle, this, new_connection);
            }
        }
    }
}




// Client -------------------------------------------------------------------------------------------------




void Connection::station_start() {
    // Connect server in here
    //socket
    station_socket = socket(AF_UNIX,SOCK_STREAM,0);
    bzero((char *) &station_sockaddr, sizeof(station_sockaddr));
    // address of socket
    station_sockaddr.sun_family = AF_UNIX;

    strcpy(station_sockaddr.sun_path, SERVER_PATH);

    station_connection = connect(station_socket,(struct sockaddr *) &station_sockaddr,sizeof(station_sockaddr));
}


void Connection::station_handle(int connection) {
    // Exchange messages with server here
    if (connection == -1) {
        printf("Failed to connect \n");
    }
    else {
        use_console(station_socket);
    }
}


void Connection::operate_station()
{
    station_start();
    printf("station_connection: %d\n", station_connection);
    station_handle(station_connection);
    close(station_socket);
    exit(0);
}




// Common -------------------------------------------------------------------------------------------------




void Connection::operate()
{
    if(isOperator) operate_operator();
    else operate_station();
}


Connection::Connection(bool mode) {
    isOperator = mode;
}


int Connection::send_data(int connection, uint8_t * buffer) {
    int status = write(connection,buffer, sizeof(buffer));

    if(status > 0)
    {
        std::cout << "Message Sent: " << buffer << std::endl;
    }
    else std::cout << "Failed to Sent" << std::endl;

    return status;
}



int Connection::receive_data(int connection) {
    uint8_t incoming_buffer[256] = "";
    int status = read(connection,&incoming_buffer, sizeof(incoming_buffer));

    if(status < 0) std::cout << "Failed to Receive" << std::endl;
    else std::cout << "Message Received: " << incoming_buffer << std::endl;

    bzero(incoming_buffer, sizeof(incoming_buffer));

    return status;
}


void Connection::use_console(int connection) {
    int run_Condition = 1;
    while(run_Condition)
    {
        int command;
        std::cout << "Command: ";
        std::cin >> command;
        switch (command) {
            case 0:
                run_Condition = 0;
                break;
            case 1:
                std::cout << "Sending: ";
                uint8_t outgoing[256];
                std::cin >> outgoing;
                send_data(connection,outgoing);
                break;
            case 2:
                receive_data(connection);
                break;
            default:
                run_Condition = 0;
                break;
        }
    }
}
