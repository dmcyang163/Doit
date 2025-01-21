import functools
import logging
import time
import inspect
import threading
import os
import traceback
from logging.handlers import RotatingFileHandler
from datetime import datetime


def loger(func):
    """
    装饰器，将函数调用信息记录到以当前时间命名的文件，包括输入参数、返回值和执行时间，异常时记录异常信息。

    参数:
    func (function): 被装饰的函数。

    返回:
    function: 包装原函数的装饰器，添加日志记录功能。
    """
    # 生成日志文件名
    log_path = "log.log"  # 固定日志文件名
    local = threading.local()  # 为每个线程创建一个本地存储对象


    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        if not hasattr(local, 'logger'):
            # 创建线程本地的日志记录器
            logger = logging.getLogger()
            # 使用 RotatingFileHandler 进行日志文件的回滚
            handler = RotatingFileHandler(log_path, mode='a', maxBytes=1000000, backupCount=5)  # mode='a' 表示追加模式
            formatter = logging.Formatter(
                '%(asctime)s - [pid %(process)d - tid %(thread)d] - %(message)s')
            handler.setFormatter(formatter)
            logger.addHandler(handler)
            logger.setLevel(logging.INFO)
            local.logger = logger
        else:
            logger = local.logger

        start_time = time.time()
        # 获取调用函数的文件名和行号
        filename = inspect.getfile(func).split("/")[-1]  # 只取文件名部分
        lineno = inspect.currentframe().f_back.f_lineno
        try:
            # 调用原函数
            result = func(*args, **kwargs)
            end_time = time.time()
            execution_time = end_time - start_time
            # 获取进程 ID 和线程 ID
            pid = os.getpid()
            tid = threading.current_thread().ident
            # 记录函数调用结束、返回值和执行时间
            logger.info(
                f"[{execution_time:.4f}s] func {func.__name__} returned {result} at {filename}:{lineno} with args={args}, kwargs={kwargs}")
            return result
        except Exception as e:
            # 记录异常信息，包括调用栈信息
            stack_trace = ''.join(traceback.format_stack())
            logger.error(
                f"{func.__name__} raised an exception at {filename}:{lineno}: {str(e)}\n{stack_trace}")
            raise
    return wrapper


@loger
def add(x, y):
    time.sleep(1)  # 模拟函数执行时间
    return x + y


@loger
def multiply(x, y):
    time.sleep(2)  # 模拟函数执行时间
    return x * y


if __name__ == "__main__":
    import threading


    def run_add():
        print(add(3, 5))


    def run_multiply():
        print(multiply(4, 6))


    t1 = threading.Thread(target=run_add)
    t2 = threading.Thread(target=run_multiply)
    t1.start()
    t2.start()
    t1.join()
    t2.join()