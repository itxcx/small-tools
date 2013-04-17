#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

namespace BpNet{
//connect type
enum {TCP,UDP};

class bpn_conn
{
private:
    int         _sockfd;
    std::string _addr;
    int         _port;
    int         _type;
    std::string _ip;
    void        (*m_handle_func)(void*);
    sockaddr_in dst_addr;
public:
    bpn_conn(const std::string& addr, const int& port,
             const int& type = BpNet::TCP, void (*handle_func)(void*) = NULL):
        _addr(addr), _port(port), _type(type), m_handle_func(handle_func)
    {
        _sockfd = 0;
        std::string _ip = get_domain_ip(addr);

        //set addr infomation
        memset(&dst_addr, 0, sizeof(dst_addr));
        dst_addr.sin_port = htons((in_port_t)_port);
        dst_addr.sin_family = _type == AF_INET;
        dst_addr.sin_addr.s_addr = inet_addr(_ip.c_str());

        //set connect type
        if (_type == BpNet::TCP)
            _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        else
            _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    }
    int connect(unsigned timeout_sec = 0)
    {
        if (timeout_sec)
        {
            alarm(timeout_sec);
            ::connect(_sockfd, (sockaddr *)&dst_addr, sizeof(dst_addr));
            alarm(0);
        }
        else
            ::connect(_sockfd, (sockaddr *)&dst_addr, sizeof(dst_addr));

        //time out handles....
        return _sockfd;
    }

    static std::string get_domain_ip(const std::string &domain)
    {
        addrinfo hints, *host_info;
        char ipstr[INET6_ADDRSTRLEN];

        memset(&hints, 0, sizeof(host_info));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        //get the ip of domain name
        getaddrinfo(domain.c_str(), "80", &hints, &host_info);
        if (NULL != host_info)
        {
            sockaddr_in *tmp;
            tmp = (sockaddr_in*)(host_info->ai_addr);
            inet_ntop(AF_INET, &(tmp->sin_addr), ipstr, sizeof ipstr);
        }
        freeaddrinfo(host_info);
        host_info = NULL;
        return std::string(ipstr);
    }
    ~bpn_conn()
    {
        if(sockfd) ::close(sockfd);
    }

    void set_handle(void(*handle_func)(void *))
    {
        m_handle_func = handle_func;
    }

    void close()
    {
        ::close(_sockfd);
        _sockfd = 0;
    }
};
}   //namespace BpNet end
