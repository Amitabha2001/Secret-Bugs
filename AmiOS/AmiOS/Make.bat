echo ------------------- AmiOS Build System --------------------

REM Lets Assemble the Assembler Programs
cd ...\MASM\BIN
ml /AT /c ...\KernelEntry.asm

cd ...\NASM
nasm -f bin ...\Boot.asm -o ...\Build\BootLoader.bin
nasm -f bin ...\Shell.asm -o ...\Build\Shellii.bin

REM Lets Compile the C Programs
cd ...\MSVC\BIN
cl /AT /Gs /Gx /c /Zl ...\Kernel.cpp
cl /AT /Gs /Gx /c /Zl ...\Display.cpp
cl /AT /Gs /Gx /c /Zl ...\Disk.cpp
cl /AT /Gs /Gx /c /Zl ...\String.cpp
cl /AT /Gs /Gx /c /Zl ...\System.cpp
cl /AT /Gs /Gx /c /Zl ...\Memory.cpp
cl /AT /Gs /Gx /c /Zl ...\Kernel.cpp
cl /AT /Gs /Gx /c /Zl ...\Process.cpp

REM Copy all object files.
copy /b ...\MSVC\BIN\KernelEntry.obj ...\KernelEntry.obj
copy /b	...\MSVC\BIN\Kernel.obj  ...\Kernel.obj
copy /b ...\MSVC\BIN\Display.obj ...\Display.obj
copy /b ...\MSVC\BIN\Disk.obj ...\Disk.obj
copy /b ...\MSVC\BIN\String.obj ...\String.obj
copy /b ...\MSVC\BIN\System.obj ...\System.obj
copy /b ...\MSVC\BIN\Memory.obj ...\Memory.obj
copy /b ...\MSVC\BIN\Process.obj ...\Process.obj

REM Call Linker.
cd ...\MASM\BIN
link /T /MAP /NOD ...\KernelEntry.obj ...\Kernel.obj ...\Display.obj ...\Disk.obj ...\String.obj ...\System.obj ...\Memory.obj ...\Process.obj
copy /b C:\MASM\BIN\KernelEntry.com C:\AmiOS\AmiOS\Build\Kernel.com

REM Make our floppy image.
cd ...\FatX
FATX -b ...\Build\BootLoader.bin -k ...\Build\Kernel.com -o ...\Build\AmiOS.img ...\Build\Shellii.bin

REM Add the magic bytes with the file.

REM Delete Object Files.
del ...\KernelEntry.obj
del ...\Kernel.obj
del ...\Display.obj
del ...\Disk.obj
del ...\String.obj
del ...\System.obj
del ...\Memory.obj
del ...\Process.obj
del ...\MASM\BIN\KernelEntry.obj
del ...\MSVC\BIN\Kernel.obj
del ...\MSVC\BIN\Display.obj
del ...\MSVC\BIN\Disk.obj
del ...\MSVC\BIN\String.obj
del ...\MSVC\BIN\System.obj
del ...\MSVC\BIN\Memory.obj
del ...\MSVC\BIN\Process.obj

cd C:\Bochs
bochs -f C:\AmiOS\AmiOS\Build\boschsrc.bxrc

echo -------------------- Build Complete ------------------