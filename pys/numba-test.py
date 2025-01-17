from cachetools import cached, LRUCache
from numba import jit
import numpy as np

import timeit


def array_to_bytes_key(*args):
    # 假设第一个参数是 numpy.ndarray
    arr = args[0]
    return arr.tobytes()


@cached(cache=LRUCache(maxsize=1024*1024*16), key=array_to_bytes_key)
@jit(nopython=True, fastmath=False)
def numba_matrix_multiply(a, b):
    return np.dot(a, b)

from numba import config
print(f"Numba threads: {config.NUMBA_NUM_THREADS}")

if __name__ == "__main__":
    
    a = np.random.rand(1000, 1000)
    b = np.random.rand(1000, 1000)

    # 多次调用进行预编译
    for _ in range(10):
        numba_matrix_multiply(a, b)

    # 不使用 Numba 加速
    time1 = timeit.timeit(lambda: np.dot(a, b), number=200)
    print(f"Without Numba: {time1}")

    # 使用 Numba 加速
    time2 = timeit.timeit(lambda: numba_matrix_multiply(a, b), number=200)
    print(f"With Numba: {time2}")

    # 再次调用，查看性能提升
    time3 = timeit.timeit(lambda: numba_matrix_multiply(a, b), number=200)
    print(f"With Numba (without compilation): {time3}")