<div align="center">
    <img src="https://assets.zelixlang.dev/logo.png?update=true" height="60" width="60">
    <h1>The Zelix Programming Language</h1>
    A safe, high-performance systems language.
    <br>
    <br>

[![GitHub](https://img.shields.io/github/license/zelix-lang/Zelix)](LICENSE)
![GitHub repo size](https://img.shields.io/github/repo-size/zelix-lang/Zelix)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/zelix-lang/Zelix)
![GitHub Repo stars](https://img.shields.io/github/stars/zelix-lang/Zelix?style=flat)

[Website][Website] | [Documentation][Documentation] | [Contributing][Contributing]
</div>

---

[Website]: https://zelixlang.dev
[Documentation]: https://docs.zelixlang.dev
[Contributing]: Contributing.md
[stdlib]: https://github.com/zelix-lang/stdlib

Welcome to the repository of `Zelix::Typed`, an interpreted 
text processor, widely used in the Zelix programming language 
compiler toolchain.

`Zelix::Typed` is responsible for parsing and interpreting
glue code files written in `.zt` files, which are used to
manipulate and generate text during the compilation process.

---

### 📦 Installation

Before you begin, please make sure you have the following prerequisites installed:
- A C and C++ compiler (GCC or Clang are recommended).
- CMake (version 3.16 or higher), can be uninstalled after Zelix is installed.
- A Git client (for cloning the repository)
- **LLVM (version 16 or higher).**

> **Note**: C++ Compilers can be uninstalled after Zelix is installed if they are no longer a dependency.
> However, C compilers and libc must remain available, since the Zelix compilers relies on `cc`.

Installation is simple. There are three main ways to install Zelix:

1. **Build from source**: Clone the repository and run the build script.
   ```bash
   git clone https://github.com/zelix-lang/Typed.git
   cd Zelix
   ./Build.sh
   mv ./build/zelix /usr/local/bin/zelix
    ```
2. **Download and run the automatic installer**:
   ```bash
   git clone https://github.com/zelix-lang/Typed.git
   cd installer
   ./Install.sh
   ```

---

### 🤝 Getting Involved
We welcome contributions! Whether you're fixing bugs, adding features, or improving documentation, your help is
appreciated. Check out our [Contributing Guide][Contributing] for more details.

---

If you consider Zelix has inspired you to create something amazing,
you can read the [Zelix Internals Book](https://docs.zelixlang.dev/zelix-internals-book)
to learn how Zelix works under the hood and how it was implemented and written from scratch.

---

### 📚 Documentation
For detailed documentation, including language features, standard library usage, and more,
please visit our [Documentation][Documentation] page.

---

### 📝 License
Zelix is licensed under the [Apache License 2.0](LICENSE).