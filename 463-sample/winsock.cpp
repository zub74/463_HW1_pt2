/* winsock.cpp
 * CPSC 463 Sample Code 
 * by Dmitri Loguinov
 */
/*
Caden Stewart
CSCE 463 - Fall 2020
*/

#include "pch.h"
#include "winsock.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void winsock_test (char* str)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~Parsing
	//print received URL 
	printf("URL: %s\n", str);

	//Start Parsing
	printf("\tParsing URL... ");
	char* scheme = strstr(str, "http://");
	if (scheme != str) {
		printf("failed with invalid scheme\n");
		return;
	}
	else {
		str = str + 7; //skip scheme
	}

	//Strip fragment
	char* fragment = strchr(str, '#');
	if (fragment) {
		*fragment = NULL; //truncate
	}

	//Find query
	char* questionMark = strchr(str, '?');
	string query = "";
	if (questionMark) {
		query = questionMark; //easiest way to just make a variable containing the query
		*questionMark = NULL;
	}

	//Find request
	char* forwardSlash = strchr(str, '/');
	string request;
	if (forwardSlash) {
		request = forwardSlash;
		*forwardSlash = NULL;
	}
	else {
		request = '/';
	}
	string totalRequest = request + query;

	//get Port
	char* colon = strchr(str, ':');
	int port = 80;
	if (colon) {
		port = atoi(colon + 1);
		if (port < 1 && port > 65535) {
			printf("failed with invalid port\n");
			return;
		}
		*colon = NULL;
	}

	//output parsed result (port 80 is hardcoded for part 1)
	printf("host %s, port %d, request %s\n", str, port, totalRequest.c_str()); //had to use a c_str here, a regular string caused all sorts of weird 
	//~~~~~~~~~~~~~~~~~~~~~~~~~~Parsing
	
	WSADATA wsaData;

	//Initialize WinSock; once per program run
	WORD wVersionRequested = MAKEWORD(2,2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		printf("WSAStartup error %d\n", WSAGetLastError ());
		WSACleanup();	
		return;
	}
	

	// open a TCP socket
	SOCKET sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		printf ("socket() generated error %d\n", WSAGetLastError ());
		WSACleanup ();	
		return;
	}

	// structure used in DNS lookups
	struct hostent *remote; 

	// structure for connecting to server
	struct sockaddr_in server;

	// first assume that the string is an IP address
	DWORD IP = inet_addr (str);

	printf("\tDoing DNS... ");
	clock_t start = clock();

	if (IP == INADDR_NONE)
	{
		// if not a valid IP, then do a DNS lookup
		if ((remote = gethostbyname (str)) == NULL)
		{
			printf ("failed with %d\n", WSAGetLastError());
			return;
		}
		else // take the first IP address and copy into sin_addr
			memcpy ((char *)&(server.sin_addr), remote->h_addr, remote->h_length);
	}
	else
	{
		// if a valid IP, directly drop its binary version into sin_addr
		server.sin_addr.S_un.S_addr = IP;
	}

	clock_t end = clock();
	double elapsedTime = 1000 * ((double)(end - start) / CLOCKS_PER_SEC);
	printf("done in %g ms, found %s\n", elapsedTime, inet_ntoa(server.sin_addr));

	// setup the port # and protocol type
	server.sin_family = AF_INET;
	server.sin_port = htons (port);		// host-to-network flips the byte order

	// connect to the server on specified port
	cout << "      * Connecting on page... ";
	start = clock();
	if (connect (sock, (struct sockaddr*) &server, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		printf ("failed with error %d\n", WSAGetLastError ());
		return;
	}
	else {

	}
	end = clock();
	elapsedTime = 1000 * ((double)(end - start) / CLOCKS_PER_SEC);
	printf("done in %g ms\n", elapsedTime);

	// send HTTP requests here
	Socket mySock(sock, "http://" + string(str));
	//send get request
	mySock.Send(str, totalRequest.c_str());
	//read back response
	mySock.Read();
	//verify header response
	mySock.verifyHeader();
	//parse the page for links on a good response
	if (mySock.getStatus() >= 200 && mySock.getStatus() < 300) {
		mySock.parsePage(); 
	}
	//finally, print the header
	mySock.printHeader();

	// close the socket to this server; open again for the next one
	closesocket (sock);

	// call cleanup when done with everything and ready to exit program
	WSACleanup ();
}




//~~~~~~~~~~~~~~Socket code~~~~~~~~~~~~~~~~~~~

Socket::Socket(SOCKET sockIn, string host)
{
	// create this buffer once, then possibly reuse for multiple connections in Part 3
	buf = (char*)malloc(INITIAL_BUF_SIZE); // either new char [INITIAL_BUF_SIZE] or malloc (INITIAL_BUF_SIZE)
	allocatedSize = INITIAL_BUF_SIZE;
	curPos = 0;
	sock = sockIn;
	timeout.tv_sec = 10;
	statusCode = 0;
	baseURL = host;
	FD_ZERO(&readfds);
}

bool Socket::Send(char* host, const char* req) {
	string hostAddr(host);
	string request(req);

	string httpReq = "GET " + request + " HTTP/1.0\r\nUser-agent: ItsyBitsyCrawler/1.1\r\nHost: " + hostAddr + "\r\nConnection: close\r\n\r\n";
	if (send(sock, httpReq.c_str(), strlen(httpReq.c_str()), 0) == SOCKET_ERROR) {
		printf("Error Occurred during send! Error number: %d", WSAGetLastError());
		return false;
	}
	return true;
}

bool Socket::Read(void)
{
	clock_t start = clock();
	cout << "\tLoading... ";
	// set timeout to 10 seconds
	while (true)
	{
		FD_SET(sock, &readfds);

		// wait to see if socket has any data (see MSDN)
		if ((select(0, &readfds, 0, 0, &timeout)) > 0)
		{
			// new data available; now read the next segment
			int bytes = recv(sock, buf + curPos, allocatedSize - curPos, 0);
			if (bytes < 0) {
				// print WSAGetLastError()
				printf("Error Occurred during receive! Error number: %d", WSAGetLastError());
				break;
			}
			if (bytes == 0) {
				// NULL-terminate buffer
				buf[curPos] = NULL;
				clock_t end = clock();
				double elapsedTime = 1000 * ((double)(end - start) / CLOCKS_PER_SEC);
				printf("done in %g ms with %d bytes\n", elapsedTime, curPos);
				return true; // normal completion
			}

			curPos += bytes; // adjust where the next recv goes
			if (allocatedSize - curPos < INITIAL_BUF_SIZE / 2) {
				// resize buffer; you can use realloc(), HeapReAlloc(), or
				// memcpy the buffer into a bigger array
				buf = (char*)realloc(buf, allocatedSize * 2);
				allocatedSize *= 2;
			}

		}
		else if (&timeout) {
			// report timeout
			printf("timeout?\n");
			break;
		}
		else {
			// print WSAGetLastError()
			printf("Error Occurred waiting to receive! Error number: %d", WSAGetLastError());
			break;
		}
	}
	return false;
}

void Socket::printHeader() {
	char* headerEnd = strstr(buf, "\r\n\r\n");
	*headerEnd = NULL; //don't need the rest after it's been parsed anyways (for now at least)

	printf("\n----------------------------------------\n");
	cout << buf << endl << endl; //for some reason one of the responses had a formatting character that didn't work with printf
}

bool Socket::verifyHeader() {
	printf("      + Verifying header... ");
	char head[13] = { NULL }; //initialize all to null bytes
	memcpy(head, buf, 12); //copy the first 12 bytes into the head buffer
	char* validHeader = strstr(head, "HTTP/1."); //check to make sure the header starts with HTTP/1.
	if (validHeader && validHeader == head) {
		//so I wrote the code below when I didn't realize HTTP status codes are always 3 numbers long >:O
		char code[4] = { NULL };
		memcpy(code, head + 9, 3); //grab the code
		statusCode = atoi(code);
		printf("status code %d\n", statusCode);
		return true;
	}
	else {
		printf("failed with non-HTTP header\n");
		return false;
	}
	
}

void Socket::parsePage() {
	printf("\tParsing page... ");
	clock_t start = clock();

	// create new parser object
	HTMLParserBase* parser = new HTMLParserBase;

	char baseUrl[] = "http://www.tamu.edu";		// where this page came from; needed for construction of relative links

	int nLinks;
	char* linkBuffer = parser->Parse(buf, allocatedSize, (char*) baseURL.c_str(), (int)strlen(baseUrl), &nLinks);

	// check for errors indicated by negative values
	if (nLinks < 0) {
		printf("error occurred during parsing.\n");
		return;
	}

	clock_t end = clock();
	double elapsedTime = 1000 * ((double)(end - start) / CLOCKS_PER_SEC);
	printf("done in %g ms with %d links\n", elapsedTime, nLinks);

	delete parser;		// this internally deletes linkBuffer
}

Socket::~Socket() {
	free(buf);
}