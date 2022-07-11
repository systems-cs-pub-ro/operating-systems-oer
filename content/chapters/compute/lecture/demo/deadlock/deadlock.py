#!/usr/bin/env python

from time import sleep
from threading import Thread, Lock

resource1 = Lock()
resource2 = Lock()

def thread_1():
    # Lock `resource1` and then `resource2`.    
    resource1.acquire()
    print('Thread 1: locked resource 1. Waiting for resource 2...')

    # Add a delay to enforce the deadlock.
    # What might happen if we comment out the line below? Why?
    sleep(2)

    resource2.acquire()
    print('Thread 1: locked resource 2.');

    resource1.release()
    print('Thread 1: unlocked resource 1.')

    resource2.release()
    print('Thread 1: unlocked resource 2.')

def thread_2():
    # Lock `resource2` and then `resource1`.    
    resource2.acquire()
    print('Thread 2: locked resource 2. Waiting for resource 1...')

    # Add a delay to enforce the deadlock.
    # What might happen if we comment out the line below? Why?
    sleep(2)

    resource1.acquire()
    print('Thread 2: locked resource 1.');

    resource2.release()
    print('Thread 2: unlocked resource 2.')

    resource1.release()
    print('Thread 2: unlocked resource 1.')

def main():
    t1 = Thread(target=thread_1)
    t2 = Thread(target=thread_2)

    t1.start()
    t2.start()

    t1.join()
    t2.join()

if __name__ == '__main__':
    main()
