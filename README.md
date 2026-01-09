## A simple directory pretty-printer for linux written in C
Nothing fancy, just prints directory and subdirectory structure.
Works on linux.
_(originally was made as "i wonder if i still remember C" project, so nothing 
much cool here)_
## Get and Build
Clone the repo:
```bash 
git clone --depth 1 https://github.com/Freemorger/rdwalker.git 
```
Go to cloned dir: 
```bash 
cd rdwalker/
```
Compile:
```bash
gcc rdwalker.c -o rdwalk
```
## Run
```bash 
./rdwalk dir 
```
Or to rdwalk current dir, just run it with no arguments:
```bash
./rdwalk
```
To print every file and directory, including hidden ones:
```bash 
./rdwalk dir -a 
``` 
E.g. with current dir: 
```bash 
./rdwalk ./ -a 
```
