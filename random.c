#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>


void error_exit(char *msg, int exit_status){
    perror(msg);
    exit(exit_status);
}

void play_audio(char *namefile){
    execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", namefile, (char*)NULL);
    error_exit("Ha fallat la mutació a ffplay", 1);
}


int main(int argc, char *argv[]){
    srand(time(NULL));

    int r;
    int ret;

    while(1){
        r = rand() % 4;
        if((ret = fork()) < 0) error_exit("Error en fork", 1);
        if(ret == 0){
            char *name;

            switch(r){
                case 0:
                    name = "Yoda.wav";
                    break;
                case 1:
                    name = "MetalPipe.wav";
                    break;
                case 2:
                    name = "AntonioLobato.wav";
                    break;
                case 3:
                    name= "Hashire.wav";
                    break;
                default:
                    name = "AntonioLobato2.wav";
            }
            //char buff[80];
            //sprintf(buff, "%s", name);
            //write(1, buff, strlen(buff));
            play_audio(name);
        }
        waitpid(-1, NULL, 0);
        sleep(5);
    }
    
}