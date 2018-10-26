## 使用 VS Code 编译 C 语言示例代码

参考: [C/C++ for Visual Studio Code (Preview)](https://code.visualstudio.com/docs/languages/cpp)

### 安装

1. 确保系统上安装有 LLVM/Clang （可以安装 Xcode 或 Xcode 命令行工具）（GCC 也 OK，但是个人是使用 clang 的）
2. VS Code 安装 C/C++ 插件(ms-vscode.cpptools)

### 基本配置

1. C/C++ 环境基本配置 (通过命令 : `C/CPP: Edit configurations...`)
   生成的默认配置如下 `.vscode/c_cpp.properties.json`

```json
{
  "configurations": [
    {
      "name": "Mac",
      "includePath": ["${workspaceFolder}/**"],
      "defines": [],
      "macFrameworkPath": [
        "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk/System/Library/Frameworks"
      ],
      "compilerPath": "/usr/bin/clang",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "intelliSenseMode": "clang-x64"
    }
  ],
  "version": 4
}
```

## 编译配置

编译文件而不是编译项目。
因为我们此仓库主要是用来学习一门语言，所以主要是简短的示例代码，所以主要需要做的是要编译当前文件。

1. 默认编译当前文件

```json
{
  // See https://go.microsoft.com/fwlink/?LinkId=733558
  // for the documentation about the tasks.json format
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build current file",
      "type": "shell",
      "command": "clang",
      "args": ["-g", "${file}"],
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}
```

2. 启动的配置如下

```json
{
  "name": "Launch current file",
  "type": "cppdbg",
  "request": "launch",
  "program": "${workspaceFolder}/a.out",
  "args": [],
  "stopAtEntry": false,
  "cwd": "${workspaceFolder}",
  "environment": [],
  "externalConsole": true,
  "MIMode": "lldb",
  "preLaunchTask": "build current file"
}
```

由于我们不必太在意输出的文件名及可执行文件名，就用默认的，这样也可以减少生成的二进制文件。
这样运行前选中我们的文件，再按 `Ctrl+F5` 即可运行。
