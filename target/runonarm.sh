#!/bin/sh
echo "run the command of runing code.s on arm"
arm-linux-gcc -g targetcode.s -o targetcode -static
qemu-arm ./targetcode
echo "finish this progarm"
