![license: MIT](https://img.shields.io/badge/license-MIT-blue)
![version: pre-release](https://img.shields.io/badge/version-pre--release-red)

# Verse
Compiler and interpreter of the verse programming language. 

### Language
Verse is a strictly typed, general purpuse, not garbage collected and data oriented programming language. It shares some key features with
modern programming languages like Go and Rust while keeping it's core as simple as possible. The Verse documentation explains in great
detail every aspect of the language and is supposed to be easy to read even if Verse is the first programming language you learn.

### Installation via NPM
If you want to install Verse with **npm**, you can just run the following command in your shell. This will work cross-platform on 
every machine as long as **npm** is installed.
```bash
>> npm install verse
```

### Installation via APT
If you want to install Verse with **apt**, you can just run the following command in your shell. As a reminder, keep in mind that **apt**
is the default package-manager of Debian-based linux distributions like (but not only) *Ubuntu*, *Mint*.
```bash
>> apt-get install verse
```

### Installation via PACMAN
If you want to install Verse with **pacman**, you can just run the following command in your shell. As a reminder, keep in mind that **pacman**
is the default package-manager of Arch linux.
```bash
>> pacman -S verse
```

### Build from source
If you want to build everything from source it's required for you to also install **git**, **g++** and **make** (or *cmake*).
The installation if you're building from source should be correctly performed with the following commands:
```bash
>> git clone https://github.com/fDero/Verse
```
```bash
>> cd Verse
```
```bash
>> make build
```
If everything worked out as expected 
you should see the verse executable now in 
the folder you're in, to complete the installation
move the file in a folder recognized as part of the 
path of your system, in linux for example such a folder
could be ```/usr/bin```




