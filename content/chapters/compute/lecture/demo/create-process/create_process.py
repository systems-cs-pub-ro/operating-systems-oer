#!/usr/bin/env python

from multiprocessing import Process
from os import getpid, getppid
from time import sleep

def proc(msg):
    print(f'[child] PID = {getpid()}; PPID = {getppid()}')
    print(f'[child] Message from parent: {msg}')

    sleep(5)

def main():
    print(f'[parent] PID = {getpid()}')

    # Create a Process object.
    p = Process(target=proc, args=('OS Rullz!',))
    # The child process hasn't started yet, so no PID.
    print(f'[parent] Before starting, child PID = {p.pid}')

    p.start()
    print(f'[parent] After starting, child PID = {p.pid}')

    # Wait until process finishes.
    p.join()

    # Or kill it. Why doesn't the child print anything?
    # p.kill()

if __name__ == '__main__':
    main()
