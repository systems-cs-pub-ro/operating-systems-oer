# COMPUTE

1. [Processes](#1-processes)
1. [Threads](#2-threads---backstory)
1. [Scheduling](#3-scheduling)
1. [Synchronization](#4-synchronization)

---

### Backstory

Apps running while you are doing your homework:
* Code editor
* Browser with 10+ https://stackoverflow.com/ tabs
* Discord
* Spotify
* Torrent client
* Crypto miner
* The OS itself

Only one CPU. How?

----

### Some CPU internals

![CPU Internals](media/cpu-internals.jpg)

* More **cores** per CPU
* Still not enough for all processes

----

### All Processes in a System

```
student@os:~$ ps -e | wc -l
32

student@os:~$ ps -e
  PID TTY          TIME CMD
    1 ?        00:00:00 init
  914 ?        00:00:00 init
 2582 ?        00:00:07 gpg-agent
19812 ?        00:00:00 init
19813 ?        00:00:00 init
19814 pts/0    00:00:00 bash
20650 ?        00:00:00 init
20651 ?        00:00:00 init
20652 pts/1    00:00:00 sh
20653 pts/1    00:00:00 sh
20658 pts/1    00:00:00 sh
20661 pts/1    00:00:03 node
20672 ?        00:00:00 init
20673 ?        00:00:00 init
20674 pts/2    00:00:00 node
20681 pts/1    00:00:00 node
20701 ?        00:00:00 init
20702 ?        00:00:00 init
20703 pts/3    00:00:01 node
20722 pts/1    00:00:00 node
20733 pts/1    00:00:18 node
20796 pts/1    00:00:25 node
20915 ?        00:00:00 init
20916 ?        00:00:00 init
20917 pts/4    00:00:00 bash
20964 pts/4    00:00:00 python3
20981 ?        00:00:00 init
20982 ?        00:00:00 init
20983 pts/5    00:00:00 bash
21045 pts/5    00:00:00 ps
```

Way more processes than cores!