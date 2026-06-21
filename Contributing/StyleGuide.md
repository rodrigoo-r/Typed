<div align="center">
    <h1>Typed</h1>
    <p>A text processing DSL</p>
    <hr>
    <h3>Welcome</h3>
    <hr>
</div>

# Style Guide

This document describes the coding conventions used throughout the Typed codebase. All contributions should follow these guidelines to keep the code consistent.

## File Header

Every `.rs` file must begin with the project license header block:

```rust
/*
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #                           Typed                     # *
 * #                   A text formatting DSL             # *
 * #                                                     # *
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #         Created by Rodrigo R. & Contributors        # *
 * #         Released under the Apache License 2.0       # *
 * #            Check LICENSE.MD for more info           # *
 * #                                                     # *
 * #-----------------------------------------------------# *
*/
```

Place `mod` declarations and `use` imports immediately after the header with no blank line before the first item.

## Formatting

- **Indentation:** 4 spaces. No tabs.
- **Line width:** Keep lines at a reasonable length; break long expressions across multiple lines.
- **Trailing whitespace:** Avoid trailing whitespace on any line.
- **Final newline:** End every file with a newline.

## Naming Conventions

| Element | Style | Example |
|---|---|---|
| Modules | `snake_case` | `file_system`, `str_conv` |
| Functions | `snake_case` | `read_file`, `get_string` |
| Structs / Enums | `PascalCase` | `RuntimeError`, `HashableObject` |
| Enum variants | `PascalCase` | `Object::Hashable`, `ASTValue::Owned` |
| Type aliases | `PascalCase` | `RuntimeList`, `PackageDictionary` |
| Local variables | `snake_case` | `scope_ref`, `current` |
| Lifetimes | Short lowercase letters | `'a` |
| Constants | `SCREAMING_SNAKE_CASE` | — |

## Imports

Order imports in three groups separated by blank lines:

1. Standard library (`std::`)
2. External crates (`ordered_float`, `pest`, etc.)
3. Internal crate paths (`crate::`)

```rust
use std::cell::RefCell;
use std::collections::HashMap;
use std::rc::Rc;

use ordered_float::OrderedFloat;

use crate::adt::lang::{ASTValue, Procedure};
```

When only internal imports are needed, no blank-line grouping is required:

```rust
use crate::adt::error::RuntimeError;
use crate::adt::lang::{ASTValue, RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
```

## Functions

### Signature Layout

For short signatures, a single line is fine. For longer signatures, place each parameter on its own line, the return type on a separate line, and the opening brace on the line after:

```rust
pub fn read_file<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    // body
}
```

### Return Expressions

Prefer the implicit return (final expression without `;`) for the main return path. Use explicit `return` only for early exits:

```rust
if res.is_err() {
    return Err(
        RuntimeError::could_not_read(trace)
    );
}

Ok(
    Object::Hashable(
        HashableObject::String(
            ASTValue::Owned(res)
        )
    )
)
```

## Type Aliases

Use `pub type` to simplify complex generic types. Place each alias on its own line or break across two lines when the definition is long:

```rust
pub type NestedStack<'a> =
    Rc<RefCell<ScopedStack<'a>>>;

pub type Variable<'a> =
    Rc<RefCell<Object<'a>>>;
```

## Structs and Enums

- Derive common traits on the line above the definition: `#[derive(Debug, Clone)]`.
- No space between the struct/variant name and `{` in literal expressions:

```rust
// Correct
RuntimeError{
    message,
    line: trace.line,
    column: trace.column
}

// Incorrect
RuntimeError {
    message,
    line: trace.line,
    column: trace.column
}
```

## Error Handling

- Define domain-specific error types in `adt/error.rs` (`RuntimeError`, `ParseError`).
- Provide named constructors on the error type for each error case:

```rust
pub fn undefined_procedure(trace: &AST) -> Self {
    RuntimeError::create(
        trace,
        "Undefined procedure"
    )
}
```

- Propagate errors with the `?` operator where possible.
- Return `Err(...)` explicitly for early exits with context-specific error constructors.

## Comments

- Use comments sparingly. The code should be self-explanatory.
- Use `//` for inline comments when they are needed.
- Do not use `///` doc comments; the project does not currently use them.

## Module Organization

- Each module directory contains a `mod.rs` that re-exports its submodules.
- Prefer one public function or type per file for runtime package implementations (e.g., `read_file.rs` exports `read_file`).
- Mark submodules `pub mod` when they need to be accessed from outside the parent module; use `mod` (private) otherwise.

## Project Layout

Follow the existing directory structure:

```
src/
├── adt/         # Core data types, error types, and type aliases
├── core/        # Frontend (lexer/parser), middle-end, and backend
├── runtime/     # Built-in runtime packages (IO, Strings, Lists, etc.)
├── support/     # Shared helpers (file I/O, string conversion, error handling)
└── main.rs      # Entry point
```

When adding a new runtime package:

1. Create a directory under `src/runtime/` with a `mod.rs`.
2. Add one file per procedure.
3. Register the package in `src/runtime/mod.rs`.

## Nesting and Wrapping

When constructing deeply nested values, place each layer on its own indented line:

```rust
Ok(
    Object::Hashable(
        HashableObject::String(
            ASTValue::Owned(
                res
            )
        )
    )
)
```

This applies to `Rc::new(RefCell::new(...))` chains, `Ok(...)` / `Err(...)` wrappers, and enum variant constructors.
