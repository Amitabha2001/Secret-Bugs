echo ------------------- AmiOS Build System --------------------

REM Lets Assemble the Assembler Programs
cd C:\MASM\BIN
ml /AT /c C:\AmiOS\AmiOS\KernelEntry.asm

cd C:\NASM
nasm -f bin C:\AmiOS\AmiOS\Boot.asm -o C:\AmiOS\AmiOS\Build\BootLoader.bin
nasm -f bin C:\AmiOS\AmiOS\Shell.asm -o C:\AmiOS\AmiOS\Build\Shellii.bin
REM nasm -f obj C:\AmiOS\AmiOS\Interrupts.asm -o C:\AmiOS\AmiOS\Interrupts.obj

REM Lets Compile the C Programs
cd C:\MSVC\MSVC15\BIN
cl /AT /Gs /Gx /c /Zl C:\AmiOS\AmiOS\Kernel.cpp
cl /AT /Gs /Gx /c /Zl C:\AmiOS\AmiOS\Display.cpp
cl /AT /Gs /Gx /c /Zl C:\AmiOS\AmiOS\Disk.cpp
cl /AT /Gs /Gx /c /Zl C:\AmiOS\AmiOS\String.cpp
cl /AT /Gs /Gx /c /Zl C:\AmiOS\AmiOS\System.cpp
cl /AT /Gs /Gx /c /Zl C:\AmiOS\AmiOS\Memory.cpp
cl /AT /Gs /Gx /c /Zl C:\AmiOS\AmiOS\Kernel.cpp
cl /AT /Gs /Gx /c /Zl C:\AmiOS\AmiOS\Process.cpp

REM Copy all object files.
copy /b C:\MASM\BIN\KernelEntry.obj C:\AmiOS\AmiOS\KernelEntry.obj
copy /b C:\MSVC\MSVC15\BIN\Kernel.obj  C:\AmiOS\AmiOS\Kernel.obj
copy /b C:\MSVC\MSVC15\BIN\Display.obj C:\AmiOS\AmiOS\Display.obj
copy /b C:\MSVC\MSVC15\BIN\Disk.obj C:\AmiOS\AmiOS\Disk.obj
copy /b C:\MSVC\MSVC15\BIN\String.obj C:\AmiOS\AmiOS\String.obj
copy /b C:\MSVC\MSVC15\BIN\System.obj C:\AmiOS\AmiOS\System.obj
copy /b C:\MSVC\MSVC15\BIN\Memory.obj C:\AmiOS\AmiOS\Memory.obj
copy /b C:\MSVC\MSVC15\BIN\Process.obj C:\AmiOS\AmiOS\Process.obj

REM Call Linker.
cd C:\MASM\BIN
link /T /MAP /NOD C:\AmiOS\AmiOS\KernelEntry.obj C:\AmiOS\AmiOS\Kernel.obj C:\AmiOS\AmiOS\Display.obj C:\AmiOS\AmiOS\Disk.obj C:\AmiOS\AmiOS\String.obj C:\AmiOS\AmiOS\System.obj C:\AmiOS\AmiOS\Memory.obj C:\AmiOS\AmiOS\Process.obj
copy /b C:\MASM\BIN\KernelEntry.com C:\AmiOS\AmiOS\Build\Kernel.com

REM Make our floppy image.
cd C:\FatX
FATX -b C:\AmiOS\AmiOS\Build\BootLoader.bin -k C:\AmiOS\AmiOS\Build\Kernel.com -o C:\AmiOS\AmiOS\Build\AmiOS.img C:\AmiOS\AmiOS\Build\Shellii.bin

REM Add the magic bytes with the file.

REM Delete Object Files.
del C:\AmiOS\AmiOS\KernelEntry.obj
del C:\AmiOS\AmiOS\Kernel.obj
del C:\AmiOS\AmiOS\Display.obj
del C:\AmiOS\AmiOS\Disk.obj
del C:\AmiOS\AmiOS\String.obj
del C:\AmiOS\AmiOS\System.obj
del C:\AmiOS\AmiOS\Memory.obj
del C:\AmiOS\AmiOS\Process.obj
del C:\MASM\BIN\KernelEntry.obj
del C:\MSVC\MSVC15\BIN\Kernel.obj
del C:\MSVC\MSVC15\BIN\Display.obj
del C:\MSVC\MSVC15\BIN\Disk.obj
del C:\MSVC\MSVC15\BIN\String.obj
del C:\MSVC\MSVC15\BIN\System.obj
del C:\MSVC\MSVC15\BIN\Memory.obj
del C:\MSVC\MSVC15\BIN\Process.obj

cd C:\Bochs
bochs -f C:\AmiOS\AmiOS\Build\boschsrc.bxrc

echo -------------------- Build Complete ------------------