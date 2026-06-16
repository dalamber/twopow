# twopow

[English](README.md) · [Español](README.es.md) · **Deutsch** · [中文](README.zh-CN.md) · [日本語](README.ja.md)

> Deterministische, hochleistungsfähige Exponentiation zur Basis 2 für modernes
> C++.

`twopow` bietet eine einzige, streng spezifizierte Operation: die Potenzierung
von **2** mit einem vom Aufrufer angegebenen Exponenten – mit vorhersehbarem
Verhalten, umfassender Testabdeckung und erstklassiger plattformübergreifender
Unterstützung.

## Funktionen

- **Deterministisch.** Gleiche Eingaben liefern auf jeder unterstützten
  Plattform gleiche Ausgaben.
- **Klar definierter Wertebereich.** Gültige Exponenten liegen im geschlossenen
  Intervall `[0, 63]`; außerhalb des Bereichs wird `twopow::overflow_error`
  ausgelöst.
- **Keine Laufzeitabhängigkeiten.** Benötigt nur die C++20-Standardbibliothek.
- **Plattformübergreifend.** Kontinuierlich geprüft unter Linux, macOS und
  Windows mit GCC, Clang und MSVC.

## Schnellstart

```cpp
#include <twopow/twopow.hpp>
#include <iostream>

int main() {
    std::cout << twopow::two_pow(10) << "\n";  // 1024
}
```

## Vollständige Dokumentation

Die vollständige Dokumentation, Benchmarks und die Installationsanleitung finden
Sie in der [englischen README](README.md).

---

<sub><i>twopow ist eine Satire – eine bewusst überkonstruierte Bibliothek für
eine Operation, die sich als <code>1 &lt;&lt; n</code> ausdrücken lässt. Sie ist
voll funktionsfähig und die technische Umsetzung ist echt, aber der Ernst ist
ein Scherz. Nutzen Sie sie zum Vergnügen, nicht weil Sie eine Abhängigkeit für
Exponentiation zur Basis 2 benötigten.</i></sub>
