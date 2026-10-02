AUDIO_DIR = audios
RANDOM_DIR = Random
RANDOM2_DIR = Random2

AUDIO_FILES = $(wildcard $(AUDIO_DIR)/*.wav) $(wildcard $(AUDIO_DIR)/*.mp3)

AUDIO_OBJS = $(notdir $(patsubst %.wav, %.o, $(patsubst %.mp3, %.o, $(AUDIO_FILES))))
LDFLAGS = -Wl,-z,notext

all: random2
random: $(RANDOM_DIR)/random.c $(AUDIO_OBJS)
	gcc -o random $(RANDOM_DIR)/random.c $(AUDIO_OBJS) $(LDFLAGS)
	rm -f $(AUDIO_OBJS)

%.o: $(AUDIO_DIR)/%.wav
	cd $(AUDIO_DIR) && objcopy -I binary -O elf64-x86-64 -B i386 $(notdir $<) ../$@

%.o: $(AUDIO_DIR)/%.mp3
	cd $(AUDIO_DIR) && objcopy -I binary -O elf64-x86-64 -B i386 $(notdir $<) ../$@

random2: $(RANDOM2_DIR)/random2.c
	gcc -o random2 $(RANDOM2_DIR)/random2.c

clean:
	rm -rf random2 random *.o

.PHONY: all clean