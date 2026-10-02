# Random_Sound
Some basic program that lets you reproduce some random audio using the ffplay executable. There are two versions: 
- `random`: it has already in it the naming of the files *Not recommended*
- `random2`: when you execute it, you need to give the naming of the audio files.

## OS
>[!IMPORTANT]
>Only linux compatible, sorry windows cock suckers ;).

## A few things to say
Part of random.c has been written with the help of AI. Mainly all the part of converting the sound into object files and creating the audio buffer so that ffplay could read it. I can understand a part of what it is doing although I'm not an expert and I'm not exactly sure what everything does. Despite this, I'll try to learn more and more so that I can confidently say that understand and even tweak it if necessary. (I see it as copying something from stackoverflow and not understanding everything is there).

## Dependencies
To use the program you must have installed ffmpeg:  
**Update packages and install the ffmpeg package**
- Ubuntu/Debian
```bash
sudo apt update
sudo apt upgrade
sudo apt install ffmpeg
```

- Arch based
```bash
sudo pacman -Syu ffmpeg
```

-Fedora/Red Hat
Fedora already comes with a ffmpeg package.

## Instalation
You have two options:
- The first one is the prefered and it is to install it from the [release](https://github.com/calvazo-dev/Random_Sound/releases) section, just install the binary and execute it.
- The second option is to clone the repository and compile the program manually.

## Usage
If you've just installed the executable from [releases](https://github.com/calvazo-dev/Random_Sound/releases), then you must give the program the permission to work. In order to do it you must type:
```bash
chmod +x random
```
or
```bash
chmod +x random2
```
For random2, type the name of the program followed by the name of the audio files.
```bash
./random2 AntonioLobato.wav AntonioLobato.wav BetterCaulSaul.ogg Yoda.wav
```
For random, just type the name of the program.
```bash
./random
```

## Compiling
For the sake of those who don't know how to compile a program, there's a **makefile**. It lets you just type make **name of _program_** and it will compile it for you.  
- **Compile random2**:
```bash
make random2
```
- **Compile random**:
```bash
make random
```

- **Compile both**
```bash
make
```

If you want to remove all possible compiled programs, just write:
```bash
make clean
```