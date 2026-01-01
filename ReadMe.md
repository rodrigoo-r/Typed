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

Welcome to the main repository of the **Zelix Programming Language** — a next-generation,
mission-critical systems language built for correctness, safety, and raw performance.

This repository contains the Zelix compiler.  
The standard library lives in the [stdlib] repo.


### ⚡ What is Zelix?

**Zelix** is an imperative, statically-typed, ownership-aware systems language with a focus on:

- **Formal correctness**
- **Zero-cost abstractions**
- **No garbage collector**
- **Predictable memory behavior**
- **Compile-time verification of safety guarantees**

Zelix introduces a unique **contract system** and an optional 
**Perfect Execution Mode (PEM)**, a symbolic, non-executing engine that 
formally proves the absence of memory safety violations, undefined behavior,
and contract violations at compile time.

---

### ⚡ Why Zelix?

### 🧠 **Contract-Driven Safety**
Zelix's type system supports **contracts**: compile-time promises expressing 
constraints such as:

```zx
let ages: (num: contract(1, 100))[contract(1, 3)] = [1, 2, 3];
```

Contracts apply to:
- values
- types
- functions
- structs/packs
- memory regions
- relational rules between parameters

If the compiler can’t prove a contract, it inserts runtime checks, 
unless your project is in strict mode, where unverifiable code 
is rejected.

### 🧮 Formally Verified

Zelix contains 2 layers of formal verification:

- **PEM** (Perfect Execution Mode): a symbolic execution engine that 
  verifies memory safety, undefined behavior freedom, and contract adherence
  at compile time.
- **Mathematical proofs**: Zelix also mathematically proves complex contracts 
  using an SMT solver backend, ensuring your code adheres to specified constraints.
  There is no spec needed, user code will be verified against its own contracts.

### ⚙️ Performance Without a GC

Zelix compiles directly to native code via LLVM.
There is:
- no runtime
- no garbage collector
- no borrow-checker complexity
- predictable performance
- zero-cost shared/unique pointer abstractions

### 🔒 Memory Model Built for Critical Software
- shared<T> — shared, reference-counted pointers
- unique<T> — uniquely-owned pointers
- raw pointers with well-defined “no-escape” contracts
- verified invariants on structs
- compile-time detection of pointer misuse, aliasing violations, and lifetime leaks

### 🧨 Unsafe — When You REALLY Need It

Unsafe code allows:
- inline assembly
- inline LLVM IR
- C ABI FFI
- unrestricted pointer operations

Values returning from unsafe blocks must satisfy their declared contracts, 
ensuring safety boundaries remain sound.

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
   git clone https://github.com/zelix-lang/Zelix.git
   cd Zelix
   ./build.sh
   mv ./build/zelix /usr/local/bin/zelix
    ```
2. **Download and run the automatic installer**:
   ```bash
   git clone https://github.com/zelix-lang/installer.git
   cd installer
   ./install.sh
   ```
3. **Use a package manager**: Zelix is available on various package managers.
   - **Homebrew**: 
    ```bash
    brew tap zelix-lang/installer-brew
    brew install zelix-lang
    ```
    - **AUR**:
    ```bash
    yay -S zelix-lang
    ```
    - **Debian/Fedora-based distributions and Windows**:
    Unfortunately, Zelix is not available on these package managers yet.
    You can use the **build from source** method instead.

---

### 👾 Supported Platforms & Architectures

Zelix can run on almost any platform that supports 
a C compiler and LLVM.

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