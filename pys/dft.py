import cv2
import numpy as np
import matplotlib.pyplot as plt
import time
from scipy.fftpack import fft2, fftshift


def show_image_and_spectrum(axs, image, magnitude_spectrum, title, time_elapsed=None):
    axs[0].imshow(image, cmap='gray')
    if time_elapsed is not None:
        axs[0].set_title(f'{title}\nTime: {time_elapsed:.4f} s')
    else:
        axs[0].set_title(title)
    axs[0].axis('off')
    axs[1].imshow(magnitude_spectrum, cmap='gray')
    axs[1].set_title(f'{title} Magnitude Spectrum')
    axs[1].axis('off')


def read_image(image_path):
    # 读取图像并转换为灰度图
    return cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)


def numpy_dft_example(image_path):
    # 读取图像
    image = read_image(image_path)
    rows, cols = image.shape
    # 进行傅里叶变换
    start_time = time.time()
    dft = np.fft.rfft2(image)  # 使用 numpy.fft.rfft2 进行傅里叶变换
    numpy_dft_time = time.time() - start_time
    # 将零频率分量移到频谱中心
    dft_shift = np.fft.fftshift(dft)
    # 计算幅度谱
    magnitude_spectrum = 20 * np.log(np.abs(dft_shift))
    return image, magnitude_spectrum, numpy_dft_time


def scipy_dft_example(image_path):
    # 读取图像
    image = read_image(image_path)
    rows, cols = image.shape
    # 进行傅里叶变换
    start_time = time.time()
    dft = fft2(image)
    scipy_dft_time = time.time() - start_time
    # 将零频率分量移到频谱中心
    dft_shift = fftshift(dft)
    # 计算幅度谱
    magnitude_spectrum = 20 * np.log(np.abs(dft_shift))
    return image, magnitude_spectrum, scipy_dft_time


def opencv_dft_example(image_path):
    # 读取图像
    image = read_image(image_path)
    rows, cols = image.shape
    # 进行傅里叶变换
    start_time = time.time()
    dft = cv2.dft(np.float32(image), flags=cv2.DFT_COMPLEX_OUTPUT | cv2.DFT_SCALE)
    opencv_dft_time = time.time() - start_time
    # 将零频率分量移到频谱中心
    dft_shift = np.fft.fftshift(dft)

    # 分离实部和虚部
    magnitude_spectrum = 20 * np.log(cv2.magnitude(dft_shift[:, :, 0], dft_shift[:, :, 1]))
    return image, magnitude_spectrum, opencv_dft_time


def main():
    image_path = '../data/resized.jpg'
    # 使用 plt.subplots 函数创建子图
    fig, axs = plt.subplots(3, 2, figsize=(10, 15))
    # Numpy DFT 示例
    image, magnitude_spectrum, numpy_time = numpy_dft_example(image_path)
    show_image_and_spectrum(axs[0], image, magnitude_spectrum, 'Numpy', numpy_time)
    # Scipy DFT 示例
    image, magnitude_spectrum, scipy_time = scipy_dft_example(image_path)
    show_image_and_spectrum(axs[1], image, magnitude_spectrum, 'Scipy', scipy_time)
    # OpenCV DFT 示例
    image, magnitude_spectrum, opencv_time = opencv_dft_example(image_path)
    show_image_and_spectrum(axs[2], image, magnitude_spectrum, 'OpenCV', opencv_time)
    # 显示图像
    plt.show()
    # 打印性能测试结果
    print(f"Numpy DFT Time: {numpy_time:.4f} seconds")
    print(f"Scipy DFT Time: {scipy_time:.4f} seconds")
    print(f"OpenCV DFT Time: {opencv_time:.4f} seconds")


if __name__ == "__main__":
    main()