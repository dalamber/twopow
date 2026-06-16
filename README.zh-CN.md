# twopow

[English](README.md) · [Español](README.es.md) · [Deutsch](README.de.md) · **中文** · [日本語](README.ja.md)

> 面向现代 C++ 的确定性、高性能的以 2 为底的幂运算库。

`twopow` 提供唯一且经过严格规范的操作：将 **2** 提升到调用方指定的指数，具有可预测
的行为、详尽的测试覆盖以及一流的跨平台支持。

## 特性

- **确定性。** 相同的输入在每个受支持的平台上都产生相同的输出。
- **明确定义的取值域。** 有效指数位于闭区间 `[0, 63]`；超出范围的指数会抛出
  `twopow::overflow_error`。
- **零运行时依赖。** 仅依赖 C++20 标准库。
- **跨平台。** 在 Linux、macOS 和 Windows 上，使用 GCC、Clang 和 MSVC 持续验证。

## 快速开始

```cpp
#include <twopow/twopow.hpp>
#include <iostream>

int main() {
    std::cout << twopow::two_pow(10) << "\n";  // 1024
}
```

## 完整文档

完整文档、基准测试和安装指南请参阅[英文 README](README.md)。

---

<sub><i>twopow 是一部讽刺作品——一个为可表达为 <code>1 &lt;&lt; n</code> 的运算而
刻意过度设计的库。它完全可用，工程实现也是真实的，但其严肃感是一个玩笑。请将它用于
娱乐，而不是因为你真的需要一个以 2 为底的幂运算依赖。</i></sub>
