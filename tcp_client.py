#******************************************************************************
# File Name:   tcp_client.py
#
# Description: A simple python based TCP client.
# 
#******************************************************************************
# $ Copyright 2021-2023 Cypress Semiconductor $
#******************************************************************************

#!/usr/bin/env python
import socket
import optparse
import time
import sys

BUFFER_SIZE = 1024

# IP details for the TCP server
DEFAULT_IP   = '192.168.10.1'   # IP address of the TCP server
DEFAULT_PORT = 50007             # Port of the TCP server

DEFAULT_KEEP_ALIVE = 1           # TCP Keep Alive: 1 - Enable, 0 - Disable

print("================================================================================")
print("TCP Client")
print("================================================================================")
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, DEFAULT_KEEP_ALIVE)
s.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, 10)
s.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, 1)
s.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, 2)
s.connect((DEFAULT_IP, DEFAULT_PORT))
print("Connected to TCP Server (IP Address: ", DEFAULT_IP, "Port: ", DEFAULT_PORT, " )")
    
while 1:
    print("================================================================================")        
    data = s.recv(BUFFER_SIZE);
    print("Command from Server:")
    if data.decode('utf-8') == '0':
        print("LED OFF")
        message = 'LED OFF ACK'
        s.send(message.encode('utf-8'))
    if data.decode('utf-8') == '1':
        print("LED ON")
        message = 'LED ON ACK'
        s.send(message.encode('utf-8'))
    print("Acknowledgement sent to server")        

# [] END OF FILE
