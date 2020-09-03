#pragma once
#include "pch.h"
/*
Caden Stewart
CSCE 463 - Fall 2020
*/

#define INITIAL_BUF_SIZE 2048

void winsock_test(char* str);

class Socket {
	SOCKET sock; // socket handle
	char* buf; // current buffer
	int allocatedSize; // bytes allocated for buf
	int curPos; // current position in buffer 
	int statusCode; // HTTP status code received in header
	std::string baseURL; //http://[url no request]
	fd_set readfds; //https://www.binarytides.com/multiple-socket-connections-fdset-select-linux/

	timeval timeout;

public:
	bool Read();
	void printHeader();
	bool verifyHeader();
	void parsePage();
	int getStatus() { return statusCode; }
	bool Send(char* host, const char* req);
	Socket(SOCKET sock, std::string host);
	~Socket();
};

