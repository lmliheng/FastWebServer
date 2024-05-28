#include "server.h"

int main() {
    int port = 8080; // 监听端口
    start_server(port);
    return 0;
}

/*
web_server/
|-- src/
|   |-- main.c       // 主函数入口
|   |-- server.c     // 服务器核心逻辑
|   |-- request.c    // 请求处理逻辑
|   |-- response.c   // 响应生成逻辑
|-- includes/
|   |-- server.h     // 服务器相关函数声明
|   |-- request.h    // 请求处理函数声明
|   |-- response.h   // 响应生成函数声明
|-- static/
|   |-- index.html   // 默认返回的HTML页面
|-- Makefile         // 编译规则

*/

//编译：