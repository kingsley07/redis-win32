## 修改Redis on Windows 上Win32_Interop.lib和WS2_32.lib冲突的问题

- Win32_Interop.lib(Win32_FDAPI.obj) : error LNK2005: accept 已经在 WS2_32.lib(WS2_32.dll) 中定义
- Win32_Interop.lib(Win32_FDAPI.obj) : error LNK2005: bind 已经在 WS2_32.lib(WS2_32.dll) 中定义
- Win32_Interop.lib(Win32_FDAPI.obj) : error LNK2005: getpeername 已经在 WS2_32.lib(WS2_32.dll) 中定义
- Win32_Interop.lib(Win32_FDAPI.obj) : error LNK2005: htons 已经在 WS2_32.lib(WS2_32.dll) 中定义
- Win32_Interop.lib(Win32_FDAPI.obj) : error LNK2005: listen 已经在 WS2_32.lib(WS2_32.dll) 中定义
- Win32_Interop.lib(Win32_FDAPI.obj) : error LNK2005: select 已经在 WS2_32.lib(WS2_32.dll) 中定义
- Win32_Interop.lib(Win32_FDAPI.obj) : error LNK2005: socket 已经在 WS2_32.lib(WS2_32.dll) 中定义
- E:\Git\Redis\Debug\Redis.exe : fatal error LNK1169: 找到一个或多个多重定义的符号

