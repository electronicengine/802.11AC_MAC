//
// Created by cenkerkaraors on 13.12.2020.
//
#include "connection.h"


void Connection::operator_start()
{
    Logging::printAll(sta_color, "Operator Started");


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
    socklen_t addr_length = sizeof(station_sockaddr);
    int new_connection = accept(operator_socket, (struct sockaddr *) &operator_sockaddr, &addr_length);


    return new_connection;
}


void Connection::operator_handle(int connection)
{
    if(connection == -1)
    {
        Logging::printAll(sta_color, "Failed to Connect");

    }
    else
    {
        use_console(connection);

    }
    Logging::printAll(sta_color, "Closing Connection");
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
    Logging::printAll(sta_color, "Station Started");

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
        Logging::printAll(sta_color, "Failed to Connect");
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
    unlink(SERVER_PATH);
    close(station_socket);
    exit(0);
}




// Common -------------------------------------------------------------------------------------------------




void Connection::operate()
{
    if(isOperator) operate_operator();
    else operate_station();
}


Connection::Connection(bool mode, Logging::LogColor color) {
    isOperator = mode;
    sta_color = color;
}

template <typename T>
int Connection::send_data(int connection, T& buffer, int size) {
    int status = write(connection, buffer, size);

    if(status > 0)
    {
        Logging::printAll(sta_color, "Sent: ", buffer);
    }
    else Logging::printAll(sta_color, "Failed to Sent");
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

    if(status < 0) Logging::printAll(sta_color, "Failed to Receive");
    else
    {
        Logging::printAll(sta_color, "Received: ",incoming_buffer);
    }
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
            {
                std::cout << "Sending: ";
                std::string user_input;
                std::cin.clear();
                std::getline(std::cin.ignore(),user_input);
                const char * data = user_input.c_str();
                send_data(connection,data,strlen(data));
                break;
            }

            case 2:
                receive_data(connection);
                break;

            case 3:
                if(isOperator)
                {
                    run_Condition = 0;
                    Logging::printAll(sta_color, "Server Closing");
                    close(operator_socket);
                    unlink(SERVER_PATH);
                }
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
