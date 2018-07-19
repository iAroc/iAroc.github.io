
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <switch.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <malloc.h>
#include <dirent.h>
#include <stdlib.h>
#include <poll.h>

#include <fcntl.h> /* Added for the nonblocking socket */

#define MYPORT 3456    /* the port users will be connecting to */
#define BACKLOG 10     /* how many pending connections queue will hold */

#define SOCK_BUFFERSIZE 32768
#define LISTEN_PORT     65432


static struct sockaddr_in serv_addr;
static struct sockaddr_in their_addr;
socklen_t          their_addrlen = sizeof(their_addr);
int	currentDataSocket = -1;

char*			string_read;
char*			string_write;
bool			readyToWrite = false;
int				length = 0;
char*			ptr;

int listenfd = -1;
int rc = -1;

char* CreateAnswerToSend() {
	char *Command = strtok(string_read, " ");
	char *RestOfString = strtok(NULL, " ");
	char *RequiredPath = strtok(RestOfString, " ");
	printf("Command: %s\n", Command);
	printf("RequiredPath: %s\n", RequiredPath);

	// Generate Json of all Files/Folders
	int DirJson_len = 2;
	char *DirJson = (char*)malloc(DirJson_len);
	strcpy(DirJson, "[");

	DIR* dir;
	struct dirent* ent;

	dir = opendir(RequiredPath);
	if (dir != NULL)
	{
		bool first = true;
		while ((ent = readdir(dir)))
		{
			if (first) {
				first = false;
			}
			else {
				DirJson_len += 1;
				DirJson = (char*)realloc(DirJson, DirJson_len);
				strncat(DirJson, ",", DirJson_len);
			}
			DirJson_len += 9;
			DirJson = (char*)realloc(DirJson, DirJson_len);
			strncat(DirJson, "{\"Name\":\"", DirJson_len);

			DirJson_len += strlen(ent->d_name);
			DirJson = (char*)realloc(DirJson, DirJson_len);
			strncat(DirJson, ent->d_name, DirJson_len);

			DirJson_len += 9;
			DirJson = (char*)realloc(DirJson, DirJson_len);
			strncat(DirJson, "\",\"Type\":", DirJson_len);

			char TypeStr[10];
			sprintf(TypeStr, "%d", ent->d_type);

			DirJson_len += strlen(TypeStr);
			DirJson = (char*)realloc(DirJson, DirJson_len);
			strncat(DirJson, TypeStr, DirJson_len);

			DirJson_len += 1;
			DirJson = (char*)realloc(DirJson, DirJson_len);
			strncat(DirJson, "}", DirJson_len);
		}
		closedir(dir);
	}
	else {
		// Its not a Dir, try if its a file
		FILE *file;
		char *FileBuffer;
		char *FileBufferHex;
		unsigned long fileLen;
		file = fopen(RequiredPath, "rb");
		if (file == NULL) {
			printf("File open failed, errno = %d\n", errno);
		}
		else {
			printf("Sending File %s\n", RequiredPath);
			//Get file length
			fseek(file, 0, SEEK_END);
			fileLen = ftell(file);
			fseek(file, 0, SEEK_SET);

			FileBuffer = (char *)malloc(fileLen + 1);
			fread(FileBuffer, fileLen, 1, file);
			fclose(file);


			//Transfer as Hex
			FileBufferHex = (char *)malloc((fileLen * 2) + 1);
			size_t insz = fileLen;
			char * pin = FileBuffer;
			const char * hex = "0123456789ABCDEF";
			char * pout = FileBufferHex;
			for (; pin < FileBuffer + insz; pout += 2, pin++) {
				pout[0] = hex[(*pin >> 4) & 0xF];
				pout[1] = hex[*pin & 0xF];
			}

			DirJson_len += 10;
			DirJson = (char*)realloc(DirJson, DirJson_len);
			strncat(DirJson, "{\"Value\":\"", DirJson_len);

			DirJson_len += (fileLen * 2);
			DirJson = (char*)realloc(DirJson, DirJson_len);
			strncat(DirJson, FileBufferHex, DirJson_len);


			DirJson_len += 2;
			DirJson = (char*)realloc(DirJson, DirJson_len);
			strncat(DirJson, "\"}", DirJson_len);
		}
	}
	DirJson_len += 1;
	DirJson = (char*)realloc(DirJson, DirJson_len);
	strncat(DirJson, "]", DirJson_len);


	// Generate HTTP-Answer
	size_t RequestAnswer_len = 1;
	char *RequestAnswer = (char*)malloc(RequestAnswer_len);

	char StrToAdd1[] = "HTTP/1.1 200 OK\r\nServer: Nintendo Switch\r\nConnection: close\r\nContent-Lenght: ";
	RequestAnswer_len += strlen(StrToAdd1);
	RequestAnswer = (char*)realloc(RequestAnswer, RequestAnswer_len);
	strcpy(RequestAnswer, StrToAdd1);

	char StrToAdd2[12];
	sprintf(StrToAdd2, "%d", DirJson_len);
	RequestAnswer_len += strlen(StrToAdd2);
	RequestAnswer = (char*)realloc(RequestAnswer, RequestAnswer_len);
	strncat(RequestAnswer, StrToAdd2, RequestAnswer_len);

	char StrToAdd3[] = "\r\nContent-Type: text/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n";
	RequestAnswer_len += strlen(StrToAdd3);
	RequestAnswer = (char*)realloc(RequestAnswer, RequestAnswer_len);
	strncat(RequestAnswer, StrToAdd3, RequestAnswer_len);

	RequestAnswer_len += strlen(DirJson);
	RequestAnswer = (char*)realloc(RequestAnswer, RequestAnswer_len);
	strncat(RequestAnswer, DirJson, RequestAnswer_len);

	char StrToAdd4[] = "\r\n\r\n";
	RequestAnswer_len += strlen(StrToAdd4);
	RequestAnswer = (char*)realloc(RequestAnswer, RequestAnswer_len);
	strncat(RequestAnswer, StrToAdd4, RequestAnswer_len);

	return RequestAnswer;
}

bool send_all(int socket, void *buffer, size_t length)
{
	char *ptr = (char*)buffer;
	while (length > 0)
	{
		int i = send(socket, ptr, length, 0);
		if (i < 1) {
			printf("sending ERROR: %d %s\n", errno, strerror(errno));

		}
		ptr += i;
		length -= i;
	}
	return true;
}

bool createSocket() {
	static const SocketInitConfig socketInitConfig = {
		.bsdsockets_version = 1,

		.tcp_tx_buf_size = 8 * SOCK_BUFFERSIZE,
		.tcp_rx_buf_size = 8 * SOCK_BUFFERSIZE,
		.tcp_tx_buf_max_size = 16 * SOCK_BUFFERSIZE,
		.tcp_rx_buf_max_size = 16 * SOCK_BUFFERSIZE,

		.udp_tx_buf_size = 0x2400,
		.udp_rx_buf_size = 0xA500,

		.sb_efficiency = 8,
	};
	Result ret = socketInitialize(&socketInitConfig);
	if (ret < 0) {
		printf("Could not Initialize Socket\n");
		return -1;
	}

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		printf("socket: %d %s\n", errno, strerror(errno));
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = gethostid();
	serv_addr.sin_port = htons(LISTEN_PORT);

	int yes = 1;
	rc = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	if (rc != 0)
	{
		printf("setsockopt: %d %s\n", errno, strerror(errno));
		return -1;
	}

	rc = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (rc != 0)
	{
		printf("bind: %d %s\n", errno, strerror(errno));
		return -1;
	}

	rc = listen(listenfd, 5);
	if (rc != 0)
	{
		printf("listen: %d %s\n", errno, strerror(errno));
		return -1;
	}
	int flags = fcntl(listenfd, F_GETFL, 0);
	rc = fcntl(listenfd, F_SETFL, flags | O_NONBLOCK);

	return 0;
}

void shutdownSocket() {
	rc = shutdown(currentDataSocket, SHUT_WR);

	struct pollfd      pollinfo;
	pollinfo.fd = currentDataSocket;
	pollinfo.events = POLLIN;
	pollinfo.revents = 0;
	rc = poll(&pollinfo, 1, 250);

	/* set linger to 0 */
	struct linger linger;
	linger.l_onoff = 1;
	linger.l_linger = 0;
	rc = setsockopt(currentDataSocket, SOL_SOCKET, SO_LINGER, &linger, sizeof(linger));

	rc = close(currentDataSocket);
	currentDataSocket = -1;

	free(string_read);
	free(string_write);
}

int main(int argc, char **argv) {

	nifmInitialize();
	gfxInitDefault();
	consoleInit(NULL);

	rc = createSocket();
	if (rc < 0) {
		printf("Error in Creating the Socket\n");
		return -1;
	}

	printf("Accepting Connections on: %s:%u\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));

	// Main loop
	while (appletMainLoop())
	{
		int connfd = accept(listenfd, (struct sockaddr*)&their_addr, &their_addrlen);
		if (connfd != -1) {
			printf("Accepted a new connection from %s:%u\n", inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port));
			string_read = (char*)malloc(5000);
			int flags = fcntl(connfd, F_GETFL, 0);
			rc = fcntl(connfd, F_SETFL, flags | O_NONBLOCK);
			currentDataSocket = connfd;
		}

		if (currentDataSocket > 0) {
			rc = recv(currentDataSocket, string_read, 5000, 0);
			if (rc < 0 && errno != EWOULDBLOCK)
			{
				printf("Error in recv: %d %s\n", errno, strerror(errno));
			}
			else if(rc > 0) {
				char* AnswerToSend = CreateAnswerToSend();
				string_write = (char*)malloc(strlen(AnswerToSend) + 1);
				strcpy(string_write, AnswerToSend);
				string_write[strlen(AnswerToSend) + 1] = 0;
				printf("Ready to write\n");

				ptr = (char*)string_write;
				length = strlen(string_write);
				free(AnswerToSend);
				readyToWrite = true;
			}
		}

		if (readyToWrite) {
			if (length > 0) {
				int i = send(currentDataSocket, ptr, length, 0);
				if (i < 1) {
					printf("sending ERROR: %d %s\n", errno, strerror(errno));
				}
				ptr += i;
				length -= i;
			}
			else {
				shutdownSocket();
				readyToWrite = false;
			}
		}


		hidScanInput();

		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS) {
			break;
		}
		if (kDown & KEY_B) {
			break;
		}

		gfxFlushBuffers();
		gfxSwapBuffers();
		gfxWaitForVsync();
	}

	socketExit();
	gfxExit();
	return 0;
}
