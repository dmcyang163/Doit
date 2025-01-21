import PyInstaller.__main__
import subprocess
import sys
import os
import time
from concurrent.futures import ProcessPoolExecutor


def build_with_pyinstaller(script_path):
    # 此函数用于使用 PyInstaller 打包脚本
    start_time = time.time()  # 记录开始时间
    output_dir = os.path.normpath(os.path.join("dist", os.path.splitext(os.path.basename(script_path))[0]))
    command = [
        "--onefile",
        "--distpath=" + output_dir,
        script_path
    ]
    try:
        PyInstaller.__main__.run(command)
        end_time = time.time()  # 记录结束时间
        return end_time - start_time  # 返回该脚本的打包时间
    except Exception as e:
        print(f"Error running command: {command}, Exception: {e}")
        return None


def build_with_nuitka(script_path):
    # 此函数用于使用 Nuitka 打包脚本
    # 获取虚拟环境的路径
    venv_path = sys.prefix
    nuitka_path = os.path.normpath(os.path.join(venv_path, "Scripts", "nuitka.cmd"))
    # 获取脚本文件名（不含路径）
    script_name = os.path.basename(script_path)
    output_dir = os.path.normpath(os.path.join("dist", os.path.splitext(script_name)[0]))
    command = [
        nuitka_path,
        "--onefile",
        "--output-dir=" + output_dir,
        "--jobs=" + str(os.cpu_count()),  # 使用 CPU 核心数进行并行编译
        # "--enable-plugin=upx",  # 启用Nuitka的UPX插件
        script_path
    ]
    try:
        start_time = time.time()  # 记录开始时间
        subprocess.run(command, check=True)  # 使用 shell=True 谨慎使用
        end_time = time.time()  # 记录结束时间
        return end_time - start_time  # 返回该脚本的打包时间
    except FileNotFoundError as e:
        print(f"Error running command: {command}, Exception: {e}")
        return None


def package_scripts(scripts, packager):
    packager_functions = {
        'pyinstaller': build_with_pyinstaller,
        'nuitka': build_with_nuitka
    }
    if packager not in packager_functions:
        print(f"Unsupported packager: {packager}")
        return []
    script_times = []
    with ProcessPoolExecutor(max_workers=os.cpu_count()) as executor:
        build_function = packager_functions[packager]
        futures = [executor.submit(build_function, script) for script in scripts]
        for future in futures:
            script_time = future.result()
            if script_time:
                script_times.append(script_time)
    return script_times


if __name__ == "__main__":
    # 待打包文件的相对路径
    scripts = [
        "loger.py",
        "sigmoid.py"
    ]
    # 选择打包工具，'pyinstaller' 或 'nuitka'
    if len(sys.argv) > 1:
        packager = sys.argv[1]
        if packager not in ['pyinstaller', 'nuitka']:
            print(f"Unsupported packager: {packager}. Please use 'pyinstaller' or 'nuitka'.")
            sys.exit(1)
    else:
        packager = 'pyinstaller'

    script_times = []  # 存储每个脚本的打包时间
    total_start_time = time.time()  # 记录开始打包所有脚本的总时间

    script_times = package_scripts(scripts, packager)

    total_end_time = time.time()  # 记录结束打包所有脚本的总时间
    total_time = total_end_time - total_start_time  # 计算总打包时间

    # 输出每个脚本的打包时间
    for i, script in enumerate(scripts):
        if packager == 'pyinstaller':
            if i < len(script_times):
                print(f"Packaging {script} completed in {script_times[i]:.2f} seconds.")
            else:
                print(f"Packaging {script} failed.")
        elif packager == 'nuitka':
            if i < len(script_times):
                print(f"Packaging {script} completed in {script_times[i]:.2f} seconds.")
            else:
                print(f"Packaging {script} failed.")

    print(f"Total packaging time for all scripts: {total_time:.2f} seconds.")  # 输出打包所有脚本的总时间