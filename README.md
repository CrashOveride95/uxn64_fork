# UXN64

This is a port of the [UXN virtual machine][uxn] for the Nintendo 64 (N64). UXN
is a project created by the artist collective and research studio [100
rabbits][100r]. It can be used to write small graphical applications, tools and
games. Programs written for UXN are distributed via bytecode compiled roms, akin
to classic console emulators.

[uxn]: https://wiki.xxiivv.com/site/uxn.html
[100r]: https://100r.co/

## Building from source

To build this project, you will need a [MIPS III compatible][n64brew-gcc]
compiler toolchain and [the official N64 sdk (libultra)][n64ultra]. For this
guide I'll assume you are using Linux and your toolchain and sdk will be located
at `/opt/n64sdk/` and `/opt/n64sdk/libultra/` respectively.

### The toolchain

Paraphrasing the installation guide from the [N64brew wiki][n64brew-gcc]. This
installation will take some time. Also before you start make sure you export
your path as follows. You probably don't need to install newlib for this
project, but just in case we'll follow the full procedure.

```
PATH=/opt/n64sdk/bin:$PATH
```

#### Prepare the SDK directory

```
mkdir /opt/n64sdk
sudo chown <yourusername> /opt/n64sdk
```

#### Binutils

```
git clone git://sourceware.org/git/binutils-gdb.git /tmp/binutils
cd /tmp/binutils
mkdir build
cd build
../configure --target=mips32-elf --prefix=/opt/n64sdk --with-cpu=vr4300 --disable-nls --with-sysroot=/opt/n64sdk/mips32-elf/sysroot
make -j8 # select the number of cores you want to use. here I'm using 8.
make install
```

#### GCC and Newlib

```
# GCC (part 1)
git clone git://gcc.gnu.org/git/gcc.git /tmp/gcc
cd /tmp/gcc
mkdir build
cd build
../configure --target=mips32-elf --prefix=/opt/n64sdk --with-languages=c,c++ --disable-shared --disable-threads --disable-nls --without-headers --disable-multilib --with-newlib --with-sysroot=/opt/n64sdk/mips32-elf/sysroot --with-arch=vr4300 --with-abi=32
make -j8 all-gcc
make install-gcc
make -j8 all-target-libgcc
make install-target-libgcc

# Newlib
git clone git://sourceware.org/git/newlib-cygwin.git /tmp/newlib
cd /tmp/newlib
mkdir build
cd build
../configure --prefix=/usr --target=mips32-elf --disable-threads --disable-libssp CFLAGS_FOR_TARGET='-march=vr4300 -mfix4300 -G 0'
make -j8
make DESTDIR=/opt/n64sdk/mips32-elf/sysroot install
cd /opt/n64sdk/mips32-elf/sysroot/usr
mv mips32-elf/* .
rmdir mips32-elf

# GCC (part 2)
cd /tmp/gcc/build
make -j8 all-target-libgcc
make install-target-libgcc
```

### Libultra

An iso image for the official N64 SDK can be found [in archive.org][n64ultra].
Download the iso and mount it to your filesystem:

```
mkdir /tmp/cdrom
sudo mount -o loop "N64 Dev kit full.iso" /tmp/cdrom
cd /tmp/cdrom
cp -r ultra /opt/n64sdk/libultra
```

### This project

If everything is installed correctly, you should be able to clone this project
as follows:

```
git clone https://git.badd10de.dev/uxn64/
cd uxn64
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

[n64brew-gcc]: https://n64brew.dev/wiki/Building_GCC
[n64ultra]: https://archive.org/details/nintendo-64-developers-toolkit-v-5.0
