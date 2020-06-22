
#include <curl/curl.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <zmq.hpp>

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/time.h>
#include <fstream>
#include <unistd.h>

#include <chrono> // timeout

int NUM = 1000;

namespace zmq
{
    class Monitor : public monitor_t
    {
    public:
        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_connected;
        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_connect_delayed;
        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_connect_retried;
        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_listening;
        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_bind_failed;
        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_accepted;
        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_accept_failed;

        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_closed;
        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_close_failed;
        std::function<void(const zmq_event_t &event_, const char *addr_)> C_on_event_disconnected;

    public:
        virtual void on_monitor_started()
        {
        }
        virtual void on_event_connected(const zmq_event_t &event_, const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_connected)
            {
                C_on_event_connected(event_, addr_);
            }
        }
        virtual void on_event_connect_delayed(const zmq_event_t &event_,
                                              const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_connect_delayed)
            {
                C_on_event_connect_delayed(event_, addr_);
            }
        }
        virtual void on_event_connect_retried(const zmq_event_t &event_,
                                              const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_connect_retried)
            {
                C_on_event_connect_retried(event_, addr_);
            }
        }
        virtual void on_event_listening(const zmq_event_t &event_, const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_listening)
            {
                C_on_event_listening(event_, addr_);
            }
        }
        virtual void on_event_bind_failed(const zmq_event_t &event_, const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_bind_failed)
            {
                C_on_event_bind_failed(event_, addr_);
            }
        }
        virtual void on_event_accepted(const zmq_event_t &event_, const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_accepted)
            {
                C_on_event_accepted(event_, addr_);
            }
        }
        virtual void on_event_accept_failed(const zmq_event_t &event_, const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_accept_failed)
            {
                C_on_event_accept_failed(event_, addr_);
            }
        }
        virtual void on_event_closed(const zmq_event_t &event_, const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_closed)
            {
                C_on_event_closed(event_, addr_);
            }
        }
        virtual void on_event_close_failed(const zmq_event_t &event_, const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_close_failed)
            {
                C_on_event_close_failed(event_, addr_);
            }
        }
        virtual void on_event_disconnected(const zmq_event_t &event_, const char *addr_)
        {
            (void)event_;
            (void)addr_;
            if (C_on_event_disconnected)
            {
                C_on_event_disconnected(event_, addr_);
            }
        }
#if ZMQ_VERSION >= ZMQ_MAKE_VERSION(4, 2, 3)
        virtual void on_event_handshake_failed_no_detail(const zmq_event_t &event_,
                                                         const char *addr_)
        {
            (void)event_;
            (void)addr_;
        }
        virtual void on_event_handshake_failed_protocol(const zmq_event_t &event_,
                                                        const char *addr_)
        {
            (void)event_;
            (void)addr_;
        }
        virtual void on_event_handshake_failed_auth(const zmq_event_t &event_,
                                                    const char *addr_)
        {
            (void)event_;
            (void)addr_;
        }
        virtual void on_event_handshake_succeeded(const zmq_event_t &event_,
                                                  const char *addr_)
        {
            (void)event_;
            (void)addr_;
        }
#elif ZMQ_VERSION >= ZMQ_MAKE_VERSION(4, 2, 1)
        virtual void on_event_handshake_failed(const zmq_event_t &event_,
                                               const char *addr_)
        {
            (void)event_;
            (void)addr_;
        }
        virtual void on_event_handshake_succeed(const zmq_event_t &event_,
                                                const char *addr_)
        {
            (void)event_;
            (void)addr_;
        }
#endif
        virtual void on_event_unknown(const zmq_event_t &event_, const char *addr_)
        {
            (void)event_;
            (void)addr_;
        }
    };
}; // namespace zmq

struct ChronoScope
{
    std::chrono::system_clock::time_point start;
    std::string strTag;
    ChronoScope(const std::string &strFunctionName)
    {
        start = std::chrono::system_clock::now();
        strTag = strFunctionName;
    }

    ~ChronoScope()
    {
        std::stringstream threadID;
        threadID << std::this_thread::get_id();
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        std::cout << "[" << threadID.str() << "]"
                  << "[" << strTag << "]"
                  << "ChronoScope: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << "us." << std::endl;

        std::cout << "timestamp is : " << std::chrono::duration_cast<std::chrono::milliseconds>(end.time_since_epoch()).count() << std::endl;
    }
};

std::string strEnvironmenttr;

using namespace zmq;

void ReadCommand(
    const int argc,
    char **argv)
{
    int32_t ch;

    while ((ch = getopt(argc, argv, "e:n:")) != -1)
    {
        switch (ch)
        {
        case 'e':
            strEnvironmenttr = optarg;
            break;
        case 'n':
            NUM = atoi(optarg);
            break;
        default:
            break;
        }
    }
}

static void C_on_event_connected(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

static void C_on_event_connect_delayed(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

static void C_on_event_connect_retried(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

static void C_on_event_listening(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

static void C_on_event_bind_failed(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

static void C_on_event_accepted(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

static void C_on_event_accept_failed(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

static void C_on_event_closed(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

static void C_on_event_close_failed(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

static void C_on_event_disconnected(const zmq_event_t &event_, const char *addr_)
{
    std::cout << __FUNCTION__ << addr_ <<std::endl;
}

std::string strJson = R"({})";

static void monitor(zmq::socket_t& sockethandle)
{
    zmq::Monitor CSMonitor;

    CSMonitor.C_on_event_connected = C_on_event_connected;
    CSMonitor.C_on_event_connect_delayed = C_on_event_connect_delayed;
    CSMonitor.C_on_event_connect_retried = C_on_event_connect_retried;
    CSMonitor.C_on_event_listening = C_on_event_listening;
    CSMonitor.C_on_event_bind_failed = C_on_event_bind_failed;
    CSMonitor.C_on_event_accepted = C_on_event_accepted;
    CSMonitor.C_on_event_accept_failed = C_on_event_accept_failed;
    CSMonitor.C_on_event_closed = C_on_event_closed;
    CSMonitor.C_on_event_close_failed = C_on_event_close_failed;
    CSMonitor.C_on_event_disconnected = C_on_event_disconnected;

    CSMonitor.monitor(sockethandle,"inproc://monitor-pub");
}

void pub()
{
    try
    {
        /* code */
        int send_hwm_ = NUM;

        zmq::context_t context;
        zmq::socket_t backend(context, socket_type::push);

        //std::thread monitorfunc(monitor,std::ref(backend));

        backend.bind("tcp://10.254.0.42:10001");
        backend.set(zmq::sockopt::sndhwm, send_hwm_);
        backend.set(zmq::sockopt::connect_timeout, 1000);

        zmq::socket_t syncbackend(context, socket_type::req);
        syncbackend.bind("tcp://10.254.0.42:10002");

        ChronoScope(__FUNCTION__);

        for (uint32_t i = 0; i < NUM; i++)
        {
            if(i == 0)
            {
                const_buffer syncsub("ack", 3);
                syncbackend.send(syncsub);
                zmq::message_t syncmessage;
                recv_result_t result = syncbackend.recv(syncmessage);
                if (result.has_value())
                {
                    std::cout << "sync message : " << syncmessage.to_string() << std::endl;
                }
            }

            std::string SendMsg = std::string(strJson) + std::to_string(i);
            zmq::message_t message(SendMsg.begin(), SendMsg.end());
            send_result_t resut = backend.send(message,send_flags::none);
            if(resut.has_value())
            {
                std::cout << "resut: " << resut.value() << std::endl;
            }
        }

        //monitorfunc.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void sub()
{
    int recv_hwm_ = NUM;

    zmq::context_t context;
    zmq::socket_t frontend(context, socket_type::pull);

    //std::thread monitorfunc(monitor,std::ref(frontend));

    frontend.connect("tcp://10.254.0.42:10001");
    frontend.set(zmq::sockopt::rcvhwm, recv_hwm_);
    frontend.set(zmq::sockopt::connect_timeout, 1000);
    uint32_t count = 0;

    ChronoScope(__FUNCTION__);

    zmq::socket_t syncfrontend(context, socket_type::rep);
    syncfrontend.connect("tcp://10.254.0.42:10002");

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    bool sendFlag = false;

    for (;;)
    {
        //if(count % 1000 == 0 && sendFlag == false)
        if(sendFlag == false)
        {
            zmq::message_t syncmessage;
            recv_result_t syncresult = syncfrontend.recv(syncmessage);
            if (syncresult.has_value())
            {
                std::cout << "syncfrontend result : " << syncmessage.to_string() << std::endl;
                zmq::message_t ackmessage("ack", 3);
                syncfrontend.send(ackmessage,send_flags::none);
                sendFlag = true;
                std::cout << "sendFlag is :" << sendFlag << std::endl;
            }
        }
        zmq::message_t message;
        recv_result_t result = frontend.recv(message);

        if (result.has_value())
        {
            //std::cout << message.to_string() << std::endl;
            count++;
            std::cout << "count is: " << count << std::endl;
            if(count == 1)
            {
                start = std::chrono::system_clock::now();
            }

            if (count == NUM)
            {
                std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
                std::cout << "[" << __FUNCTION__ << "]"
                          << "ChronoScope: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                          << "ms." << std::endl;
                break;
            }

            if(count % 1000 == 0)
            {
                //sendFlag = false;
            }
        }
        else
        {
            continue;
        }
    }

    //monitorfunc.join();
}

int main(int argc, char **argv)
{
    ReadCommand(argc, argv);

    if (strEnvironmenttr == "pub")
    {
        pub();
    }
    else if (strEnvironmenttr == "sub")
    {
        sub();
    }
    return 0;
}