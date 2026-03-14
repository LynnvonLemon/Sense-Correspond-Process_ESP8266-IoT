
This directory is intended for PlatformIO Test Runner and project tests.

Unit Testing is a software testing method by which individual units of
source code, sets of one or more MCU program modules together with associated
control data, usage procedures, and operating procedures, are tested to
determine whether they are fit for use. Unit testing finds problems early
in the development cycle.

More information about PlatformIO Unit Testing:
- https://docs.platformio.org/en/latest/advanced/unit-testing/index.html

## ⚠️ 已知问题

### NTP 库冲突
由于 UDP 端口冲突，NTP 相关文件已移至 `test/` 文件夹。如需使用 NTP 时间同步：

1. 将 `test/NTPClient.cpp` 移回 `src/` 目录
2. 取消忽视NTPClient库
2. 注释相关冲突代码
3. 重新编译

**冲突原因**：ESP Mail Client 和 NTPClient 可能同时使用 UDP 端口 123。