# twopow

[English](README.md) · **Español** · [Deutsch](README.de.md) · [中文](README.zh-CN.md) · [日本語](README.ja.md)

> Exponenciación determinista en base 2 para C++ moderno, de alto rendimiento.

`twopow` ofrece una única operación, rigurosamente especificada: elevar **2** a
un exponente proporcionado por el usuario, con comportamiento predecible,
cobertura de pruebas exhaustiva y soporte multiplataforma de primera clase.

## Características

- **Determinista.** Las mismas entradas producen las mismas salidas en cada
  plataforma compatible.
- **Dominio bien definido.** Los exponentes válidos abarcan el intervalo cerrado
  `[0, 63]`; los exponentes fuera de rango lanzan `twopow::overflow_error`.
- **Sin dependencias en tiempo de ejecución.** Solo depende de la biblioteca
  estándar de C++20.
- **Multiplataforma.** Validada continuamente en Linux, macOS y Windows con GCC,
  Clang y MSVC.

## Inicio rápido

```cpp
#include <twopow/twopow.hpp>
#include <iostream>

int main() {
    std::cout << twopow::two_pow(10) << "\n";  // 1024
}
```

## Documentación completa

La documentación completa, los puntos de referencia y la guía de instalación
están disponibles en el [README en inglés](README.md).

---

<sub><i>twopow es una obra de sátira: una biblioteca deliberadamente
sobredimensionada para una operación que se expresa como <code>1 &lt;&lt;
n</code>. Es totalmente funcional y la ingeniería es real, pero la solemnidad es
una broma. Úsela para divertirse, no porque necesitara una dependencia de
exponenciación en base 2.</i></sub>
