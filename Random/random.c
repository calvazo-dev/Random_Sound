#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

extern const char _binary_Yoda_wav_start[];
extern const char _binary_Yoda_wav_end[];

extern const char _binary_MetalPipe_wav_start[];
extern const char _binary_MetalPipe_wav_end[];

extern const char _binary_AntonioLobato_wav_start[];
extern const char _binary_AntonioLobato_wav_end[];

extern const char _binary_AntonioLobato2_wav_start[];
extern const char _binary_AntonioLobato2_wav_end[];

extern const char _binary_Hashire_wav_start[];
extern const char _binary_Hashire_wav_end[];

extern const char _binary_BetterCaulSaul_mp3_start[];
extern const char _binary_BetterCaulSaul_mp3_end[];

void error_exit(char *msg, int exit_status){
    perror(msg);
    exit(exit_status);
}

typedef struct{
    const char *data;
    size_t size;
} AudioFile;


void play_audio(int *pipe_fds){
    close(pipe_fds[1]);

    if(dup2(pipe_fds[0], STDIN_FILENO) < 0){
        perror("dup2 failed");
        _exit(1);
    }

    close(pipe_fds[0]);
    execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", "-i", "-",(char *) NULL);
    perror("execlp failed");
    _exit(1);
}


int main(int argc, char *argv[]){
    srand(time(NULL));

    AudioFile playlist[] = {
        {_binary_AntonioLobato_wav_start, _binary_AntonioLobato_wav_end - _binary_AntonioLobato_wav_start },
        {_binary_AntonioLobato2_wav_start, _binary_AntonioLobato2_wav_end - _binary_AntonioLobato2_wav_start },
        {_binary_BetterCaulSaul_mp3_start, _binary_BetterCaulSaul_mp3_end - _binary_BetterCaulSaul_mp3_start },
        {_binary_Hashire_wav_start, _binary_Hashire_wav_end - _binary_Hashire_wav_start },
        {_binary_MetalPipe_wav_start, _binary_MetalPipe_wav_end - _binary_MetalPipe_wav_start },
        {_binary_Yoda_wav_start, _binary_Yoda_wav_end - _binary_Yoda_wav_start }
    };

    int total_tracks = sizeof(playlist) / sizeof(playlist[0]);

    pid_t ret;

    while(1){
        AudioFile selected = playlist[rand() % total_tracks];

        int pipe_fds[2];

        if(pipe(pipe_fds) < 0){
            perror("pipe failed");
            return 1;
        }

        if((ret = fork()) < 0) error_exit("Error en fork", 1);
        if(ret == 0){
            play_audio(pipe_fds);
        }

        close(pipe_fds[0]);
        size_t bytes_written = 0;

        while (bytes_written < selected.size) {
            ssize_t result = write(pipe_fds[1], selected.data + bytes_written, selected.size - bytes_written);
            if (result < 0) {
                perror("write to pipe failed");
                break;
            }
            bytes_written += result;
        }

        // 3. Close write end to signal EOF (End of File) to ffplay
        close(pipe_fds[1]);

        waitpid(-1, NULL, 0);
        sleep(5);
    }
    
}