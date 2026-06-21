<div align="center">
    <h1>Typed</h1>
    <p>A text processing DSL</p>
    <hr>
</div>

**Typed** is a statically-typed, English-like domain-specific language designed for text processing. It features a verbose, readable syntax where keywords like `Declare`, `Call`, and `Add` make programs easy to follow — even for non-programmers.

Built with Rust and powered by a [PEG](https://en.wikipedia.org/wiki/Parsing_expression_grammar) parser, Typed offers procedures, control flow, arithmetic, and a growing set of standard libraries for I/O, strings, regex, math, file system operations, and more.

## Features

- **Readable syntax** — English-like keywords (`Declare`, `Call`, `Add … To`, `If … Then`)
- **Static typing** — `String`, `Integer`, `Float`, `Boolean`, `List`, `Dictionary`
- **Procedures** — with typed arguments and return values
- **Control flow** — `If` / `Else_If` / `Else`, `For`, `While`
- **Arithmetic** — `Add`, `Subtract`, `Multiply`, `Divide`
- **String formatting** — format specifiers (`$S`, `$I`, `$F`) for easy interpolation
- **Standard libraries** — `IO`, `Strings`, `Regex`, `Math`, `Lists`, `Dictionaries`, `File_System`
- **Comments** — line comments with `#`

## Getting Started

### Prerequisites

- [Rust](https://www.rust-lang.org/tools/install) (edition 2024)

### Build

```bash
cargo build --release
```

### Run

```bash
cargo run -- path/to/script.typed
```

Or, after building:

```bash
./target/release/Typed path/to/script.typed
```

## Language Overview

### Hello World

```
Use IO;

Procedure Main
Begin
    Call
        Print_Line
    With
        "Hello, World!"
    End_Call;
End_Procedure
```

### Variables

Variables are declared with `Declare`, specifying a name, type, and optional initial value:

```
Declare
    Name as String
With
    "Alice"
;

Declare
    Age as Integer
With
    30
;
```

### Procedures

Procedures are defined with `Procedure … End_Procedure`. They can accept typed arguments and declare a return type:

```
Procedure Greet
With Arguments
    Name as String
Returns String
Begin
    Return "Hello, $S";
End_Procedure
```

### Control Flow

#### If / Else_If / Else

```
If X Then
Begin
    # ...
End_If
Else_If Y Then
Begin
    # ...
End_Else_If
Else
Begin
    # ...
End_Else
```

#### For Loop

```
For I as Integer In 0 To 10 Step 1 Do
Begin
    # ...
End_For
```

#### While Loop

```
While Condition Do
Begin
    # ...
End_While
```

### Arithmetic

Arithmetic operations modify a variable in place:

```
Declare Result as Integer With 5;

Add 15 To Result;        # Result is now 20
Subtract 3 From Result;  # Result is now 17
Multiply 2 By Result;    # Result is now 34
Divide 2 By Result;      # Result is now 17
```

### Calling Procedures

Use `Call … End_Call` to invoke a procedure, with `With` to pass arguments:

```
Call
    Print
With
    "$S",
    Name
End_Call;
```

### String Formatting

Format specifiers are used in strings passed to `Print` and `Print_Line`:

| Specifier | Type      |
|-----------|-----------|
| `$S`      | String    |
| `$I`      | Integer   |
| `$F`      | Float     |

### Standard Libraries

Import libraries with `Use`:

```
Use IO;
Use Strings;
Use Regex;
Use Math;
Use Lists;
Use Dictionaries;
Use File_System;
```

| Library        | Description                          |
|----------------|--------------------------------------|
| `IO`           | Input/output (`Print`, `Print_Line`, `Read_Line`) |
| `Strings`      | String manipulation (`String_Access`, …) |
| `Regex`        | Regular expressions (`Regex_Replace_One`, …) |
| `Math`         | Mathematical functions               |
| `Lists`        | List operations                      |
| `Dictionaries` | Dictionary operations                |
| `File_System`  | File I/O (`Read_File`, `Write_File`, `Scan_Directory`, …) |

### Comments

Line comments start with `#`:

```
# This is a comment
Declare X as Integer With 42; # Inline comment
```

## Full Example

```
Use Regex;
Use IO;

Procedure Main
Begin
    Declare
        My_Regex_Pattern as String
    With
        "[a-zA-Z0-9]+"
    ;

    Declare
        My_Replaced_String as String
    With
        Call
            Regex_Replace_One
        With
            My_Regex_Pattern,
            "Hello, World!",
            "Hi"
        ;

    Call
        Print
    With
        "$S",
        My_Replaced_String
    ;

    Declare
        Result as Integer
    With
        5;

    Add
        15
    To
        Result;

    Call
        Print
    With
        "$I",
        Result
    ;
End_Procedure
```

## Contributing

See the [Style Guide](Contributing/StyleGuide.md) for code conventions and contribution guidelines.

## License

This project is licensed under the [Apache License 2.0](LICENSE).
