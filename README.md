# retro-chat
Simple terminal chat.

# Installation
1. Install [boost.asio](https://think-async.com/Asio/).

```Shell
Ubuntu
------
$ sudo apt-get install libboost-all-dev

MacOS
-----
$ brew install boost
```

2. Clone the repository

```Shell
$ git clone https://github.com/tralf-strues/retro-chat.git
```

3. Build

```Shell
$ cd retro-chat
$ sh ./build.sh
```

# Usage
There are the following options:
```Shell
$ ./build/retro-chat --help
Simple terminal chat
Usage:
  retro-chat [OPTION...]

  -h, --help          Help
  -p, --port arg      Port on which to be based (default: 1234)
  -u, --username arg  Username
  -s, --server        Run as a chat server
```

You have to **specify username** and one of the users has to **run as a chat server**!