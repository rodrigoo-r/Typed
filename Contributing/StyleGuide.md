<div align="center">
    <h1>Typed</h1>
    <p>A text processing DSL</p>
    <hr>
    <h3>Style Guide</h3>
    <hr>
</div>

This guide describes the preferred style for changes to Typed. It covers C++ source, CMake build files, runtime packages, examples, and documentation.

The short version: match the surrounding file, keep interpreter phases separated, prefer clear typed data over clever control flow, and run the formatter before submitting changes.

## Project Shape

Typed is organized by interpreter responsibility:

- `Src/ADT/` contains small data types, exception types, stream wrappers, maps, lists, scopes, and traceable runtime structures.
- `Src/Core/Frontend/` contains lexing and parsing.
- `Src/Core/MiddleEnd/` contains preprocessing and procedure/file discovery.
- `Src/Core/Backend/` contains execution and AST walking.
- `Src/Runtime/` contains built-in DSL packages such as `IO`, `Strings`, `Lists`, `Dictionaries`, `Math`, `RegexEngine`, and `FileSystem`.
- `Src/Support/` contains shared helpers used across interpreter layers.
- `Src/Terminal/` contains CLI entry points and subcommand handlers.
- `Src/User/` contains user-facing process entry points.
- `Build/` contains CMake helper modules.
- `BlackMagic/` contains templates and build-time inputs for generated CLI code.
- `Example/` contains `.typed` example programs.

Put new code in the narrowest directory that owns the concept. For example, a helper used only by `Runtime/Strings` belongs in `Src/Runtime/Strings`; a helper shared by several runtime packages belongs in `Src/Support/Runtime`.

## Formatting

Use the repository `.clang-format` file for C++ formatting.

Key formatting rules:

- C++ uses Allman braces.
- Indentation is 4 spaces.
- Tabs are not used.
- The column limit is 120.
- Continuation indentation is 8 spaces.
- Keep at most two consecutive empty lines.
- Put a newline at end of file.
- System includes come before local includes.
- Local includes use quotes.

Example:

```cpp
ADT::Runtime::Object Strings::Format(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &obj = args[0];
    auto str = Support::Runtime::AccessString(obj);
    Celery::Str::String result;

    Support::Format::Format(
        str,
        args,
        result,
        trace->line,
        trace->column
    );

    return {
        ADT::Runtime::ObjectType::OwnedString,
        std::move(result)
    };
}
```

Prefer multiline signatures when a function has multiple parameters or when the line would become dense. Keep very small constructors and simple one-line definitions compact only when that matches the surrounding file.

## File Headers

Most source files include the project banner and a creation note. Preserve the existing banner in files that already have it. When adding a new C++ source or header, follow the local pattern:

```cpp
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

//
// Created by [Your Name] on M/D/YY.
//
```

Do not churn headers in unrelated files.

## C++ Language Style

Typed is a C++20 project. Prefer the existing project vocabulary and dependency types:

- Use `Celery::Array::Vector`, `Celery::Str::External`, and `Celery::Str::String` where neighboring code already uses them.
- Use `ADT::List::Object`, `ADT::Map::*`, `ADT::Runtime::Object`, and `ADT::Runtime::ObjectType` for interpreter values.
- Use references for required mutable inputs.
- Use pointers where the AST and existing ownership model already use raw AST pointers.
- Use `auto` when the type is obvious from the right-hand side or when it avoids repeated long ADT/Celery names.
- Spell out public API types in declarations when they help readers understand the contract.
- Prefer early validation and typed exceptions over sentinel values.
- Move owned values into runtime objects when returning owned strings or collections.

Avoid broad rewrites that replace established project types with standard-library equivalents unless the change is intentionally architectural.

## Naming

Follow the existing naming conventions:

- Namespaces use PascalCase segments: `Typed::Core::Frontend::Parser`.
- Classes and structs use PascalCase: `Machine`, `Walker`, `Object`.
- Functions and methods use PascalCase: `Parse`, `Walk`, `TypeCheck`.
- Local variables use snake_case when they are more than a simple word: `args_node`, `body_queue`.
- Very short local names are acceptable for simple loops or character scanners: `c`, `i`.
- Type aliases use PascalCase: `TreePtr`, `TokenStreamView`, `RunnableRef`.
- Runtime package maps are named `Package`.
- DSL runtime procedure names use underscore-separated Pascal words: `String_To_Upper`, `File_Exists`.
- DSL variables in examples use PascalCase or descriptive names: `Name`, `My_List`, `Result`.

Name files after the primary concept they define. Runtime functions should generally have matching `.h` and `.cpp` files, such as `TrimLeft.h` and `TrimLeft.cpp`.

## Namespaces

Use fully qualified namespaces in declarations and namespace blocks. Implementation files may use local `using namespace` declarations near the top when that is already the local style.

Header files should avoid `using namespace`.

Preferred header shape:

```cpp
#pragma once
#include "ADT/Lang/AST.h"
#include "ADT/List/Object.h"
#include "ADT/Runtime/Object.h"

namespace Typed::Runtime::Strings
{
    ADT::Runtime::Object Format(ADT::List::Object &, ADT::Lang::AST *);
}
```

## Includes

Keep includes minimal and direct:

- Include the header that declares the current implementation first in `.cpp` files when practical.
- Put external/system includes before local project includes when both are present.
- Prefer direct includes over relying on transitive includes.
- Preserve the spacing style already used in nearby files.

Example:

```cpp
#include "Format.h"

#include <Celery/Io/Stream.h>

#include "ADT/Exception/MismatchedArgCount.h"
#include "ADT/List/Object.h"
#include "ADT/Runtime/Object.h"
```

## Headers

Use `#pragma once`.

Headers should contain declarations, lightweight structs, type aliases, inline package maps, and small constructors when needed. Keep implementation details in `.cpp` files unless the code is templated or intentionally inline.

When a header exposes a runtime function, keep the declaration compact:

```cpp
namespace Typed::Runtime::Lists
{
    ADT::Runtime::Object Size(ADT::List::Object &, ADT::Lang::AST *);
}
```

## Error Handling

Use typed exceptions from `Src/ADT/Exception/` for interpreter errors. Exceptions should carry trace data when the error can be connected to source code.

Preferred pattern:

```cpp
if (proc == runnable.procedures.end())
{
    throw ADT::Exception::UnknownProcedure(line, column);
}
```

When adding a new exception:

- Place it under `Src/ADT/Exception/`.
- Derive from `Celery::Except::Exception`.
- Derive from `Core::Traceable` when line and column matter.
- Keep the message short and stable.

## Runtime Objects

Runtime functions return `ADT::Runtime::Object`. Always set both the `ObjectType` and the value consistently.

Examples:

```cpp
return {
    ADT::Runtime::ObjectType::Integer,
    size
};
```

```cpp
return {
    ADT::Runtime::ObjectType::OwnedString,
    std::move(result)
};
```

Use `Support::Runtime::TypeChecker` or existing access helpers before reading values from runtime objects. Do not assume that callers passed the correct DSL type.

## Runtime Packages

Each runtime package should be self-contained:

- Put package functions in `Src/Runtime/<PackageName>/`.
- Provide a `.h` declaration and `.cpp` implementation for each operation.
- Register public operations in `Package.h`.
- Keep DSL-facing procedure names descriptive and consistent with the package prefix.
- Keep argument names short but meaningful in package maps, such as `s` for string, `i` for index, `p` for path, and `m` for max/count when the surrounding package already uses that convention.
- Include return type and mutability behavior accurately in `Package.h`.

When adding a new operation, update both the implementation and the package map. If the operation should be visible to examples or docs, update `README.md` or `Example/`.

## Parser And Backend Code

Parser and backend code should be direct and readable. These files encode the language, so clarity matters more than abstraction.

Preferred patterns:

- Keep one grammar/action concept per method when possible.
- Keep AST node allocation in parser helpers.
- Preserve trace information on AST nodes and runtime errors.
- In backend code, evaluate children explicitly and name intermediate nodes when it clarifies intent.
- Use small helper methods for recurring behavior such as condition evaluation, arithmetic, and calls.

Avoid hiding language semantics behind generic utilities unless the behavior is truly reused across several constructs.

## DSL Style

Examples should show idiomatic Typed code. Use the readable block form for procedures, declarations, calls, loops, and conditionals.

Preferred:

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
        "Hello, $S!",
        Name
    End_Call;
End_Procedure
```

Use compact one-line forms only in examples where the brevity helps, such as a short arithmetic statement:

```typed
Add 1 To I;
```

DSL naming rules:

- Keywords use PascalCase or project-defined keyword casing: `Procedure`, `Declare`, `With`, `Begin`.
- Built-in procedure names use underscores between words: `Print_Line`, `String_Access`.
- Use semicolons consistently where the language expects statement termination.
- Use comments to explain example intent, not to repeat the code.

## Comments

Write comments when they preserve reasoning that is not obvious from the code. Good comments explain why a guard, workaround, generated macro, or interpreter step exists.

Good:

```cpp
// Prevent numbers like "1.12.2"
if (state.IsFloatLiteral())
{
    throw ADT::Exception::UnknownToken(
        state.GetLine(),
        state.GetColumn()
    );
}
```

Avoid comments that only restate the next line.

## CMake Style

Keep CMake modular and consistent with the existing `Build/` priority system.

Use:

- 4-space indentation in multiline CMake calls.
- PascalCase or project-style variable names already used by the surrounding module.
- Small helper modules under `Build/Helper/` when logic is reused.
- Priority modules under `Build/Priority/<Priority>/` when build order matters.
- `FetchContent_Declare` for external dependencies that the project owns through CMake.

When adding generated code behavior, keep templates or inputs under `BlackMagic/` and generation logic under `Build/`.

## Documentation

Documentation should be concise and example-driven.

- `README.md` should explain what Typed is, how to build it, how to run it, and where the major folders are.
- `Contributing/StyleGuide.md` should explain contributor expectations and code style.
- `Example/` should contain runnable `.typed` programs that demonstrate language behavior.
- Prefer short code samples over long prose when documenting DSL features.
- Keep dependency versions and build requirements accurate.

## Git And Review Hygiene

Before opening a pull request:

1. Format changed C++ files with the repository `.clang-format`.
2. Build the project:

   ```sh
   cmake -S . -B build
   cmake --build build
   ```

3. Run at least one representative example:

   ```sh
   ./build/Typed run Example/Test.typed
   ```

4. Keep pull requests focused on one behavior or cleanup area.
5. Mention any runtime package, grammar, or build behavior that changed.
6. Update examples or docs when changing DSL-facing behavior.

## Checklist For New Runtime Functions

Use this checklist when adding a built-in procedure:

- Add `<Name>.h` with the function declaration.
- Add `<Name>.cpp` with the implementation.
- Validate argument types before reading values.
- Return the correct `ADT::Runtime::ObjectType`.
- Move owned values when returning owned memory.
- Add the function to the package's `Package.h`.
- Add or update an example if the feature is user-facing.
- Build and run a script that exercises the new function.

