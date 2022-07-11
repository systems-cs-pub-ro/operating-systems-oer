#!/usr/bin/env python

from os import getpid, getppid
from time import sleep
from threading import Thread

def thread(msg):
    print(f'[thread] PID = {getpid()}; PPID = {getppid()}')
    print(f'[thread] Message from main thread: {msg}')

    sleep(5)

def main():
    print(f'[main] PID = {getpid()}; PPID = {getppid()}')

    # Create a Thread object.
    t = Thread(target=thread, args=('OS Rullz!',))
    # Start the thread.
    t.start()

    # Wait until thread finishes.
    # We can't kill a thread. Why?
    t.join()

if __name__ == '__main__':
    main()
