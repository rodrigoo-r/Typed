<div align="center">
    <h1>Typed</h1>
    <p>A text processing DSL with verbose, English-like syntax</p>
    <hr>
</div>

**Typed** is a domain-specific language designed for text processing, built with Rust. It features a readable, keyword-driven syntax and comes with a standard library covering I/O, string manipulation, file system operations, lists, and dictionaries.

## Getting Started

### Prerequisites

- [Rust](https://www.rust-lang.org/tools/install) (edition 2024)

### Building

```bash
cargo build --release
```

### Running a Program

```bash
cargo run -- run <file.typed>
```

For example:

```bash
cargo run -- run example/Test.typed
```

## Language Overview

### File Extension

Typed source files use the `.typed` extension.

### Comments

Comments start with `#` and extend to the end of the line:

```
# This is a comment
```

### Data Types

| Type         | Keyword      |
|--------------|--------------|
| String       | `String`     |
| Integer      | `Integer`    |
| Float        | `Float`      |
| Boolean      | `Boolean`    |
| List         | `List`       |
| Dictionary   | `Dictionary` |

### Procedures

Programs are organized into procedures. Execution begins at `Main`:

```
Procedure Main
Begin
    # your code here
End_Procedure
```

Procedures can accept arguments and return values:

```
Procedure Greet
With Arguments
    Name as String
Returns String
Begin
    Return Name;
End_Procedure
```

### Variables

Variables are declared with `Declare`, specifying a name, type, and optional initial value:

```
Declare My_Variable as String With "Hello";
Declare Counter as Integer;
```

### Calling Procedures

Use `Call ... End_Call` to invoke a procedure. Arguments are passed after `With`:

```
Call Print_Line With "Hello, world!" End_Call;
```

Calls can be nested:

```
Declare Name as String
With
    Call Read_Line End_Call
;
```

### String Formatting

The `Print` and `Print_Line` functions accept a format string followed by arguments:

- `$S` — String
- `$I` — Integer
- `$F` — Float
- `$L` - List
- `$D` - Dictionary
- `$B` - Boolean

```
Call Print With "$S has $I items", Name, Count End_Call;
```

### String Literals

Single-line strings use double quotes, multi-line strings use backticks:

```
"single line"
`multi
line`
```

Escape sequences: `\\`, `\"`, `` \` ``, `\n`, `\r`, `\t`, `\0`, `\xHH`

### Arithmetic

Arithmetic operations modify a variable in place:

```
Declare Result as Integer With 10;
Add 5 To Result;
Subtract 3 From Result;
Multiply 2 By Result;
Divide 4 By Result;
```

### Control Flow

**If / Else_If / Else:**

```
If expression Then
Begin
    # ...
End_If
Else_If expression Then
Begin
    # ...
End_Else_If
Else
Begin
    # ...
End_Else
```

**While loop:**

```
While expression Do
Begin
    # ...
End_While
```

**For loop:**

```
For i as Integer In 0 To 10 Step 1 Do
Begin
    # ...
End_For
```

## Standard Libraries

Import a library with `Use`:

```
Use IO;
Use Strings;
```

### IO

| Function      | Description                |
|---------------|----------------------------|
| `Print`       | Print formatted output     |
| `Print_Line`  | Print formatted output with newline |
| `Read_Line`   | Read a line from stdin     |

### Strings

| Function           | Description                          |
|--------------------|--------------------------------------|
| `String_Access`    | Access a character by index          |
| `String_Add`       | Concatenate strings                  |
| `String_Contains`  | Check if a string contains a substring |
| `String_Format`    | Format a string                      |
| `String_Replace_All` | Replace all occurrences            |
| `String_Replace_Many` | Replace multiple patterns          |
| `String_Replace_One` | Replace first occurrence           |
| `String_Size`      | Get string length                    |
| `String_Split`     | Split a string                       |
| `String_To_Lower`  | Convert to lowercase                 |
| `String_To_Upper`  | Convert to uppercase                 |
| `String_Trim`      | Trim whitespace                      |
| `String_Trim_Left` | Trim leading whitespace              |
| `String_Trim_Right`| Trim trailing whitespace             |

### Lists

| Function       | Description                  |
|----------------|------------------------------|
| `List_Access`  | Access element by index      |
| `List_Add`     | Add an element               |
| `List_Join`    | Join elements into a string  |
| `List_Pop`     | Remove last element          |
| `List_Set`     | Set element at index         |
| `List_Size`    | Get list length              |

### Dictionaries

| Function             | Description                  |
|----------------------|------------------------------|
| `Dictionary_Access`  | Access value by key          |
| `Dictionary_Remove`  | Remove a key-value pair      |
| `Dictionary_Set`     | Set a key-value pair         |
| `Dictionary_Size`    | Get number of entries        |

### File_System

| Function              | Description                          |
|-----------------------|--------------------------------------|
| `Cwd`                 | Get current working directory        |
| `Create_Directory`    | Create a directory                   |
| `Create_File`         | Create a file                        |
| `File_Exists`         | Check if a file exists               |
| `File_Name`           | Get the file name from a path        |
| `Is_Absolute_Path`    | Check if a path is absolute          |
| `Is_Directory`        | Check if a path is a directory       |
| `Is_File`             | Check if a path is a file            |
| `Is_Relative_Path`    | Check if a path is relative          |
| `Is_System_Link`      | Check if a path is a symbolic link   |
| `Join_Path`           | Join path components                 |
| `Read_File`           | Read file contents                   |
| `Scan_Directory`      | List directory contents              |
| `To_Absolute_Path`    | Convert to absolute path             |
| `Write_File`          | Write contents to a file             |

## Example

```
Use IO;
Use Strings;

Procedure Main
Begin
    Call Print_Line With "Enter your name:" End_Call;

    Declare Name as String
    With
        Call Read_Line End_Call
    ;

    Call Print_Line With "Hello, $S", Name End_Call;
End_Procedure
```

## License

This project is licensed under the [Apache License 2.0](LICENSE).
