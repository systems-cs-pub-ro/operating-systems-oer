#!/usr/bin/env python

from time import sleep
from threading import Thread, Condition

cond = Condition()

def waiting_thread():
    print('Waiting thread: waiting for main thread...')

    # Acquire the cond's underlying lock.
    cond.acquire()
    # Release the lock and wait for `notify`.
    cond.wait()

    print('Waiting thread: notified by main thread')

def main():
    t = Thread(target=waiting_thread)
    t.start()

    sleep(1)

    print('Main thread: type "notify" to notify waiting thread')

    while True:
        cmd = input()
        if cmd == 'notify':
            cond.acquire()
            # `notify` wakes up `waiting_thread`.
            cond.notify()
            # `notify` does not release the lock.
            cond.release()
            break

if __name__ == '__main__':
    main()
