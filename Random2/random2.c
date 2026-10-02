#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

void error_exit(char *msg, int exit_status){
    perror(msg);
    exit(exit_status);
}

void play_audio(char *namefile){
    execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", namefile, (char*)NULL);

    if(errno == ENOENT){
        error_exit("Error: 'ffmpeg' no està instal·lat o no s'ha trobat al PATH del sistema.\n", errno);
    }
    if(errno == EACCES){
        error_exit("Error: el programa no té permissos per executar ffplay.\n", errno);
    }
    else
        error_exit("Ha fallat la mutació a ffplay", 1);
}

void play_audio_2(int argc, char *argv[]){
    int ret;
    
    if((ret = fork()) < 0) error_exit("Error en fork", 1);
    if(ret == 0){
        char *name;
        int r = rand() % (argc - 1);
        play_audio(argv[r+1]);
    
    }
    waitpid(-1, NULL, 0);
}



void Usage(){
    printf("Usage: random2 [name_of_audio_file] ... [name_of_audio_file]\n");
}


int main(int argc, char *argv[]){

    if(argc == 1){
        Usage();
        exit(1);
    }


    srand(time(NULL));


    while(1){
       int r = rand() % 10;
        if(r == 1){
            play_audio_2(argc, argv);
        }

        sleep(10);
    }
    
}