import hashlib
import itertools
from threading import Thread

password_hash = '59a5abc2a99b95be73c31ea272ab0f2f2fe42fec30367155cb73f6f6cef1f4e6ee37f586cbd02cc738a87a5d6add3ba31dbeaf39ec77cad910837c94c65837fb'

password_len = 4

charset = 'abcdefghijklmnopqrstuvwxyz'

def worker(first_char, result):
    for p in itertools.product(charset, repeat = password_len - 1):
        password = first_char + ''.join(p)

        if hashlib.sha512(password.encode()).hexdigest() == password_hash:
            result.append(password)
            return

    result.append(None)

if __name__ == '__main__':
    threads = []
    results = []

    for i in range(len(charset)):
        res = []
        t = Thread(target = worker, args = (charset[i], res))
        t.start()

        threads.append(t)
        results.append(res)

    for i in range(len(charset)):
        threads[i].join()

    for i in range(len(charset)):
        result = results[i][0]

        if result:
            print(f'worker {i} found {result}')
        else:
            print(f'worker {i} didn\'t find anything')

