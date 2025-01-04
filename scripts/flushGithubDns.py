import socket
import subprocess
import time
import os

def get_github_ip():
    try:
        ip = socket.gethostbyname("github.com")
        print(f"当前 GitHub 的 IP 地址: {ip}")
        return ip
    except socket.gaierror as e:
        print(f"无法获取 GitHub 的 IP 地址: {e}")
        return None


def refresh_dns_windows():
    try:
        subprocess.run(["ipconfig", "/flushdns"], check=True)
        print("Windows DNS 缓存已刷新")
    except subprocess.CalledProcessError as e:
        print(f"刷新 Windows DNS 缓存失败: {e}")


def refresh_dns_linux():
    try:
        # 尝试使用 systemd-resolve
        subprocess.run(["systemd-resolve", "--flush-caches"], check=True)
        print("Linux (systemd) DNS 缓存已刷新")
    except subprocess.CalledProcessError:
        try:
            # 尝试使用 nscd 服务
            subprocess.run(["sudo", "service", "nscd", "restart"], check=True)
            print("Linux (nscd) DNS 缓存已刷新")
        except subprocess.CalledProcessError as e:
            print(f"刷新 Linux DNS 缓存失败: {e}")


def main():
    while True:
        github_ip = get_github_ip()
        if github_ip:
            print("GitHub IP 地址获取成功，刷新 DNS 缓存")
            if os.name == 'nt':  # Windows
                refresh_dns_windows()
            elif os.name == 'posix':  # Linux
                refresh_dns_linux()
        else:
            print("无法获取 GitHub IP 地址，不进行 DNS 刷新")
        # 每 30 分钟刷新一次
        time.sleep(1800)


if __name__ == "__main__":
    main()