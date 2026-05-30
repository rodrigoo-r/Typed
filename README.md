<div align="center">
    <h1>Typed</h1>
    <p>A text processing DSL</p>
    <hr>
    <h3>Welcome</h3>
    <hr>
</div>

Typed is a C++20 interpreter for a text-processing DSL. It provides a small CLI for running `.typed` scripts, a lexer/parser pipeline, and runtime packages for common scripting tasks such as printing, regular expressions, strings, lists, dictionaries, math, and filesystem operations.

## Features

- Human-readable DSL syntax for procedures, variables, conditionals, loops, arithmetic, and function calls
- Built-in runtime packages:
    - `IO`
    - `Regex_Engine`
    - `Strings`
    - `Lists`
    - `Dictionaries`
    - `Math`
    - `File_System`
- C++ frontend/middle-end/backend pipeline for lexing, parsing, preprocessing, and execution
- CLI entry point for running Typed source files
- Apache 2.0 licensed

## Example

```typed
Use IO;
Use Strings;

Procedure Main
With Arguments
Begin
    Declare
        Name as String
    With
        "Typed";

    Call
        Print_Line
    With
        "Hello from $S!",
        Name
    End_Call;

    Declare
        Message as String
    With
        Call
            String_To_Upper
        With
            "text processing"
        End_Call;

    Call
        Print_Line
    With
        "$S",
        Message
    End_Call;
End_Procedure
```

More examples are available in [`Example/`](Example/).

## Requirements

- A C++20 compiler
- CMake 4.2 or newer
- Git, for dependencies downloaded through CMake `FetchContent`
- On macOS: `xxhash` installed through Homebrew

```sh
brew install xxhash
```

The build downloads these dependencies automatically:

- [CLI11](https://github.com/CLIUtils/CLI11)
- [Celery](https://github.com/rodrigoo-r/Celery)
- [unordered_dense](https://github.com/martinus/unordered_dense)
- [magic_enum](https://github.com/Neargye/magic_enum)
- [Abseil](https://github.com/abseil/abseil-cpp)
- [RE2](https://github.com/google/re2)
- [xxHash](https://github.com/Cyan4973/xxHash), except on macOS where the project links the Homebrew installation

## Build

```sh
cmake -S . -B build
cmake --build build
```

The executable is built as `Typed`.

## Usage

Run a Typed script with the `run` subcommand:

```sh
./build/Typed run Example/Test.typed
```

## Language Overview

A Typed program is organized around procedures. The main entry point is a `Procedure Main` block.

```typed
Procedure Main
With Arguments
Begin
    # Program body
End_Procedure
```

Import runtime packages with `Use`:

```typed
Use IO;
Use Regex_Engine;
Use Lists;
```

Declare variables with explicit types:

```typed
Declare
    Count as Integer
With
    5;
```

Call runtime procedures with `Call ... With ... End_Call`:

```typed
Call
    Print_Line
With
    "Count: $I",
    Count
End_Call;
```

Typed currently includes examples of:

- arithmetic with `Add`, `Multiply`, and `Divide`
- `If`, `Else_If`, and `Else`
- `For` loops
- `While` loops
- list and dictionary manipulation
- string formatting and transformations
- regular expression matching and replacement

## Project Layout

```text
.
├── BlackMagic/          # Build-time templates for generated CLI code
├── Build/               # CMake build helpers
├── Contributing/        # Contribution notes and style guide
├── Example/             # Example .typed programs
├── Src/
│   ├── ADT/             # Core data types and exceptions
│   ├── Core/            # Frontend, middle-end, and backend interpreter logic
│   ├── Runtime/         # Built-in runtime packages
│   ├── Support/         # Shared helpers
│   ├── Terminal/        # CLI entry point and subcommands
│   └── User/            # User-facing entry point
├── CMakeLists.txt
└── LICENSE
```

## Contributing

See [`Contributing/StyleGuide.md`](Contributing/StyleGuide.md) for the project style guide.

## License

Typed is released under the [Apache License 2.0](LICENSE).