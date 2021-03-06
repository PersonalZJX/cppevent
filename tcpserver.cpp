#include <algorithm>
#include <signal.h>

#include "tcpserver.h"
#include "event.h"
#include "connection.h"
#include "eventloop.h"
#include "tcp_address.h"

namespace cppevent{

TcpServer::TcpServer(EventLoop *loop, size_t port):
    loop_(loop),
    port_(port),
    listener_(loop, port),
    connections_()
{
    listener_.setNewConnectionCallback(
                std::bind(&TcpServer::newConnection,this,
                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

TcpServer::~TcpServer(){}

void TcpServer::start()
{
    log("Server started.");
    signal(SIGPIPE, SIG_IGN);
    log("Set SIGPIPE ignore");
    listener_.listen();
}

void TcpServer::setMessageCallback(const MessageCallback &cb)
{
    messageCallback_ = cb;
}

void TcpServer::setConnectionCallback(const ConnectionCallback &cb)
{
    connectionCallback_ = cb;
}

void TcpServer::newConnection(int sockfd, sockaddr_in *addr, size_t size)
{
    TcpAddress tcpAddr;
    tcpAddr.ip_ = inet_ntoa(addr->sin_addr);
    tcpAddr.port_ =  ntohs(addr->sin_port);

    setnonblocking(sockfd);
    ConnectionPtr conn = std::make_shared<Connection>(loop_, sockfd);
    conn->setAddress(tcpAddr);
    conn->setMessageCallback(messageCallback_);
    conn->setConnectionCallback(std::bind(&TcpServer::handleConnection, this, std::placeholders::_1));
    conn->setConnectionStatus(STATUS_CONNECTING);
    connections_[sockfd] = conn;
    handleConnection(conn);
}

void connKeep(ConnectionPtr conn)
{

}

void TcpServer::handleConnection(const ConnectionPtr& conn)
{
    if(connectionCallback_)
    {
        connectionCallback_(conn);
    }
    if(!conn->connecting())
    {
        //让这个conn指针被std::bind保存一份, 可以让他的生命周期延长到下一次的loop开始
        loop_->addTask(std::bind(connKeep, conn));
        auto iter = connections_.find(conn->fd());
        assert(iter != connections_.end());
        connections_.erase(iter);
    }
}

}

