import numpy as np


def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def softmax(x):
    exp_x = np.exp(x)
    return exp_x / np.sum(exp_x)

# 示例使用
if __name__ == "__main__":
    x = np.array([-1, 0, 1, 2])
    print(sigmoid(x))

    x = np.array([1, 2, 3])
    print(softmax(x))