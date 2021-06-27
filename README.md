<!--
 * @Author: dylan
 * @Date: 2021-06-27 17:59:55
 * @LastEditTime: 2021-06-27 18:21:25
 * @LastEditors: dylan
 * @Description: 
 * @FilePath: /TCPIP_NetworkProgramming/README.md
-->
# TCPIP_NetworkProgramming

本项目是学习《TCP/IP网络编程》耗时两周写的demo，所有程序都有基本的描述和注释，每个目录都有Makefile，make即可编译，方便运行测试。  

若要单独生成某个文件的可执行程序，可以打开Makefile查看具体的目标名，然后执行`make 目标名`即可。  

这本书可以算是Linux下网络编程最容易入门的书籍，看完并练习之后再进一步去看《Unix网络编程》和《Linux-UNIX系统编程手册》更佳。  

## 目录

```
.
├── README.md
├── ch1
│   ├── Makefile
│   ├── hello_client.c
│   └── hello_server.c
├── ch2
│   ├── Makefile
│   ├── tcp_client.c
│   └── tcp_server.c
├── ch3
│   ├── Makefile
│   └── endian_conv.c
├── ch4
│   ├── Makefile
│   ├── echo_client.c
│   └── echo_server.c
├── ch5
│   ├── Makefile
│   ├── echo_client2.c
│   ├── echo_server.c
│   ├── op_client.c
│   └── op_server.c
├── ch6
│   ├── Makefile
│   ├── bound_host1.c
│   ├── bound_host2.c
│   ├── uecho_client.c
│   ├── uecho_conn_client.c
│   └── uecho_server.c
├── ch7
│   ├── Makefile
│   ├── file_client.c
│   └── file_server.c
├── ch8
│   ├── Makefile
│   ├── gethostbyaddr.c
│   └── gethostbyname.c
├── ch9
│   ├── Makefile
│   ├── get_buf.c
│   ├── reuseadr_eclient.c
│   ├── reuseadr_eserver.c
│   ├── set_buf.c
│   └── sock_type.c
├── ch10
│   ├── Makefile
│   ├── echo_client.c
│   ├── echo_mpclient.c
│   ├── echo_mpserv.c
│   ├── fork.c
│   ├── remove_zombie.c
│   ├── sigaction.c
│   ├── signal.c
│   ├── wait.c
│   ├── waitpid.c
│   └── zombie.c
├── ch11
│   ├── Makefile
│   ├── echo_mpclient.c
│   ├── echo_storeserv.c
│   ├── pipe1.c
│   ├── pipe2.c
│   └── pipe3.c
├── ch12
│   ├── Makefile
│   ├── echo_client.c
│   ├── echo_selectserv.c
│   └── select.c
├── ch13
│   ├── Makefile
│   ├── oob_recv.c
│   └── oob_send.c
├── ch14
│   ├── Makefile
│   ├── news.txt
│   ├── news_receiver.c
│   ├── news_receiver_brd.c
│   ├── news_sender.c
│   └── news_sender_brd.c
├── ch15
│   ├── Makefile
│   ├── data.txt
│   ├── desto.c
│   ├── echo_stdclient.c
│   ├── echo_stdserver.c
│   ├── genData.sh
│   ├── stdcpy.c
│   ├── syscpy.c
│   └── todes.c
├── ch16
│   ├── Makefile
│   ├── dup.c
│   ├── sep_client.c
│   ├── sep_server.c
│   └── sep_server2.c
├── ch17
│   ├── Makefile
│   ├── echo_EPETserv.c
│   ├── echo_EPLTserv.c
│   ├── echo_client.c
│   └── echo_epollserv.c
└── ch18
    ├── Makefile
    ├── chat_client.c
    ├── chat_server.c
    ├── mutex.c
    ├── semaphore.c
    ├── thread1.c
    ├── thread2.c
    ├── thread3.c
    └── thread4.c
```

## 参考资料

[《TCP/IP网络编程》](https://book.douban.com/subject/25911735/)  