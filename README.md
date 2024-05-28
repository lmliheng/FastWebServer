# 仓库目前处于灰度发布阶段




## Web服务器雏形

这是一个简单的Web服务器，它能够接收HTTP GET请求，并返回一个静态的HTML页面。
这个项目主要用于演示如何使用C语言的套接字编程来实现基本的网络通信。

## 项目结构
```bash
web_server/
|-- src/
| |-- main.c // 主函数入口
| |-- server.c // 服务器核心逻辑
| |-- request.c // 请求处理逻辑
| |-- response.c // 响应生成逻辑
|-- includes/
| |-- server.h // 服务器相关函数声明
| |-- request.h // 请求处理函数声明
| |-- response.h // 响应生成函数声明
|-- static/
| |-- index.html // 默认返回的HTML页面
```

## 编译和运行

1. 确保你已经安装了C编译器（如GCC）。
2. 打开终端或命令提示符，导航到项目根目录（`web_server/`）。
3. 使用以下命令编译项目：

```bash
gcc -Wall -g -o web_server src/main.c src/server.c src/request.c src/response.c -Iincludes
```
编译完成后，运行生成的可执行文件：
```bash
./web_server
```
现在，你的Web服务器应该已经启动并监听端口8080。在浏览器中访问http://localhost:8080，你应该能看到static/index.html中的内容

