import hashlib
import itertools
import time
from multiprocessing import Pool

password_hash = '59a5abc2a99b95be73c31ea272ab0f2f2fe42fec30367155cb73f6f6cef1f4e6ee37f586cbd02cc738a87a5d6add3ba31dbeaf39ec77cad910837c94c65837fb'

password_len = 4

charset = 'abcdefghijklmnopqrstuvwxyz'

def worker(first_char):
    #time.sleep(10)

    for p in itertools.product(charset, repeat = password_len - 1):
        password = first_char + ''.join(p)

        if hashlib.sha512(password.encode()).hexdigest() == password_hash:
            return password

    return None

if __name__ == '__main__':
    with Pool(len(charset)) as p:
        result = p.map(worker, list(charset))

        for i in range(len(charset)):
            if result[i]:
                print(f'worker {i} found {result[i]}')
            else:
                print(f'worker {i} didn\'t find anything')
