###
 # @Author: dylan
 # @Date: 2021-06-27 16:03:09
 # @LastEditTime: 2021-06-27 18:10:13
 # @LastEditors: dylan
 # @Description: generate a large file
 # @FilePath: /TCPIP_NetworkProgramming/ch15/genData.sh
### 
#!/bin/bash
touch data.txt
dd if=/dev/zero of=./data.txt bs=1024 count=$((200*1024))
