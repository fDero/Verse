![license: MIT](https://img.shields.io/badge/license-MIT-blue)
![version: pre-release](https://img.shields.io/badge/version-pre--release-orange)

# Verse
Compiler and interpreter of the verse programming language. 

### Language
Verse is a strictly typed, general purpuse, not garbage collected and data oriented programming language. It shares some key features with
modern programming languages like Go and Rust while keeping it's core as simple as possible. The Verse documentation explains in great
detail every aspect of the language and is supposed to be easy to read even if Verse is the first programming language you learn.

### Installation via NPM
If you want to install Verse with npm, you can just run the following command in your shell. This will work cross-platform on 
every machine as long as **npm** is installed.
```bash
>> npm install verse
```

### Installation via APT
Reminder: **apt** only works on linux, more specifically, it only works on Debian-based linux distributions
like (but not only) Ubuntu and Mint. If you do not run these operating system you can't install Verse via **apt** and you will need to
choose another installation option.

### Build from source
If you want to build everything from source it's required for you to also install **git**, **g++** and **make** (or *cmake*).
The installation if you're building from source should be correctly performed with the following commands:
```bash
>> git clone https://github.com/fDero/Verse
```
```bash
>> make build
```
