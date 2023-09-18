# UXN64

This is a port of the [UXN virtual machine][uxn] for the Nintendo 64 (N64). UXN
is a project created by the artist collective and research studio [100
rabbits][100r]. It can be used to write small graphical applications, tools and
games. Programs written for UXN are distributed via bytecode compiled roms, akin
to classic console emulators.

[uxn]: https://wiki.xxiivv.com/site/uxn.html
[100r]: https://100r.co/

## Building from source

To build this project, you will need an install of the [modern SDK](https://crashoveride95.github.io/modernsdk/index.html)

### This project

If everything is installed correctly, you should be able to clone this project
as follows:

```
git clone https://github.com/CrashOveride95/uxn64_fork
cd uxn64_fork
git submodule init
git submodule update
make UXN_ROM=/path/to/uxn/rom.rom
```

Since we are embedding the rom in the n64 file, to create different rom names
for each respective uxn rom we can change the `TARGET` from the default `uxn64`:

```
make UXN_ROM=screen.rom TARGET=uxn64-screen # creates uxn64-screen.n64
make UXN_ROM=audio.rom TARGET=uxn64-audio   # creates uxn64-audio.n64
```
