#!/usr/bin/env python

from argparse import ArgumentParser
from threading import Barrier, current_thread, Thread

NUM_THREADS = 3
barrier = Barrier(NUM_THREADS)

def thread_func(use_barrier):
    print(f'Before barrier: thread name = {current_thread().name}')

    # Wait for the barrier.
    if use_barrier:
        barrier.wait()

    print(f'After barrier: thread name = {current_thread().name}')

def main():
    parser = ArgumentParser('Display the functionality of a barrier')
    parser.add_argument('--use-barrier', action='store_true')
    args = parser.parse_args()

    threads = []
    for i in range(NUM_THREADS):
        t = Thread(target=thread_func, name=f'thread-{i}',
            args=(args.use_barrier,))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

if __name__ == '__main__':
    main()
