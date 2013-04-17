#include <iostream>
#include "bpn_conn.hpp"
using namespace std;
//using namespace BpNet;


int main()
{
    BpNet::bpn_conn con("127.0.0.1", 80, BpNet::TCP);
    cout << BpNet::bpn_conn::get_domain_ip("www.baidu.com") << endl;
    //con.run(hello);

    return 0;
}

