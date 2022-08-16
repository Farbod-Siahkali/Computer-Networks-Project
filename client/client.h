#pragma once
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "message.h"

using namespace std;

void send_message(vector<string> user_names,string input_array[5],vector<uint16_t> users,int clientSd);

void list_users(int clientSd,vector<uint16_t>& users,vector<string>& user_names,uint16_t& id);

void recieve_message(int clientSd, vector<uint16_t>& users, vector<string>& user_names, uint16_t& id);

void connect_socket(int clientSd, const char * userName);

int setup(const char *serverIp, int serverPort);
