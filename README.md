<div align="center">
    <h1>Typed</h1>
    <p>A text processing DSL with verbose, English-like syntax</p>
    <hr>
</div>

# Typed

Typed is an experimental scripting language and interpreter for text processing.
It is written in Rust and uses a deliberately explicit, English-like syntax for
declaring procedures, calling built-in packages, working with strings, and
running small automation scripts.

## Features

- Procedure-based programs with a `Main` entry point.
- Primitive kinds: `String`, `Integer`, `Float`, `Boolean`, `List`, and
  `Dictionary`.
- English-like control flow with `If`, `Else_If`, `Else`, `While`, and `For`.
- Built-in runtime packages for IO, strings, lists, dictionaries, and file
  system operations.
- Single-line and multiline strings, including escape sequences.
- A Pest grammar and Rust frontend, middle-end, and backend pipeline.

## Getting Started

### Requirements

- Rust toolchain with Cargo

### Build

```sh
cargo build
```

### Run a Typed file

```sh
cargo run -- run example/Test.typed
```

You can also run any `.typed` file:

```sh
cargo run -- run path/to/script.typed
```

## Example

```typed
Use IO;
Use Strings;

Procedure Main
Begin
    Declare
        Name as String
    With
        "Typed"
    ;

    Call
        Print_Line
    With
        "$S",
        Call
            String_Format
        With
            "Hello, $S!",
            Name
        End_Call
    End_Call;
End_Procedure
```

## Language Overview

A Typed program is made of package imports and procedure declarations.

```typed
Use IO;

Procedure Main
Begin
    Call
        Print_Line
    With
        "Hello from Typed"
    End_Call;
End_Procedure
```

Procedures can accept typed arguments and return a typed value:

```typed
Procedure Greeting
With Arguments
    Name as String
Returns String
Begin
    Return
        Call
            String_Format
        With
            "Hello, $S",
            Name
        End_Call
    ;
End_Procedure
```

Variables are declared with `Declare`:

```typed
Declare
    Count as Integer
With
    1
;
```

Arithmetic assignment statements mutate existing variables:

```typed
Add 1 To Count;
Subtract 1 From Count;
Multiply 2 By Count;
Divide 2 By Count;
```

## Built-in Packages

Import packages with `Use Package_Name;`.

| Package | Procedures |
| --- | --- |
| `IO` | `Print`, `Print_Line`, `Read_Line` |
| `Strings` | `String_Format`, `String_Access`, `String_Add`, `String_Size`, `String_Split`, `String_Trim_Left`, `String_Trim_Right`, `String_Trim`, `String_Contains`, `String_Replace_One`, `String_Replace_Many`, `String_Replace_All`, `String_To_Lower`, `String_To_Upper` |
| `Lists` | `List_Access`, `List_Add`, `List_Pop`, `List_Size`, `List_Set`, `List_Join` |
| `Dictionaries` | `Dictionary_Access`, `Dictionary_Set`, `Dictionary_Remove`, `Dictionary_Size` |
| `File_System` | `Create_Directory`, `Create_File`, `Process_Cwd`, `File_Exists`, `File_Name`, `Is_Absolute_Path`, `Is_Directory`, `Is_File`, `Is_Relative_Path`, `Is_System_Link`, `Join_Path`, `Read_File`, `Scan_Directory`, `To_Absolute_Path`, `Write_File` |

## Project Layout

```text
src/
|-- adt/          Core data types, errors, and aliases
|-- cli/          Command-line interface
|-- core/         Parser frontend, middle-end, and execution backend
|-- runtime/      Built-in runtime packages
|-- support/      Shared helper utilities
`-- main.rs       Entry point

grammar/
`-- grammar.pest  Typed grammar

example/
`-- *.typed       Example Typed programs
```

## Contributing

Contributions are welcome. Please follow the conventions in
[`Contributing/StyleGuide.md`](Contributing/StyleGuide.md), including the Rust
file header, formatting rules, naming conventions, and runtime package layout.

## License

Typed is released under the Apache License 2.0. See [`LICENSE`](LICENSE) for
details.
