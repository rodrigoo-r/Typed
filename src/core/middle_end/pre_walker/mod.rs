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
use std::cell::Ref;
use std::collections::HashMap;
use crate::adt::error::{ErrorKind, ExecutionError};
use crate::adt::lang::{Argument, File, Kind, Procedure, AST};
use crate::adt::result::RuntimeResult;
use crate::adt::runtime::{GlobalPackageDictionary, PackageDictionary};
use crate::core::frontend::parser::Rule;
use crate::core::frontend::parser::Rule::Procedure_Arguments;

fn convert_kind(ast: Ref<AST>) -> Kind {
    match ast.rule {
        Rule::Integer => Kind::Integer,
        Rule::Float => Kind::Float,
        Rule::Boolean => Kind::Boolean,
        Rule::String => Kind::String,
        Rule::Dictionary => Kind::Dictionary,
        Rule::List => Kind::List,
        _ => Kind::Integer
    }
}

fn convert_use<'a>(
    ast: &AST,
    global_package: &'a GlobalPackageDictionary<'a>,
) -> RuntimeResult<'a, &'a PackageDictionary<'a>> {
    let children = ast.children.borrow();
    let literal = children[0].borrow();
    let literal = literal.value.unwrap();

    let pkg = global_package.get(literal);

    match pkg {
        None => {
            Err(ExecutionError{
                line: ast.line,
                column: ast.column,
                message: "imported library doesn't exist",
                kind: ErrorKind::CouldNotFindLibrary
            })
        }
        Some(procedures) => {
            Ok(procedures)
        }
    }
}

fn convert_procedure<'a>(ast: &AST<'a>)
    -> (&'a str, Procedure<'a>)
{
    let children = ast.children.borrow();
    let name = children[0].borrow();
    let name = name.value.unwrap();

    let proc: Option<Procedure<'a>>;
    let body = children[1].borrow();
    if body.rule == Procedure_Arguments {
        let args = body;
        let body = children[2].clone();
        let mut vec: Vec<Argument<'a>> = Vec::new();

        // Process the arguments
        for arg in args.children.borrow().iter() {
            let arg = arg.borrow();
            let arg_children = arg.children.borrow();

            let name = arg_children[0].borrow();
            let name = name.value.unwrap();

            let kind = arg_children[1].borrow();

            // Insert the argument into the procedure
            vec.push(
                Argument{
                    name,
                    kind: convert_kind(kind)
                }
            );
        }

        proc = Some(Procedure{
            body: Some(body),
            arguments: vec,
            variadic: false,
            native: None
        });
    } else {
        let body = children[1].clone();

        proc = Some(Procedure{
            body: Some(body),
            arguments: Vec::new(),
            variadic: false,
            native: None
        });
    }

    (name, proc.unwrap())
}

pub fn convert<'a>(
    ast: AST<'a>,
    global_package: &'a GlobalPackageDictionary<'a>
) -> RuntimeResult<'a, File<'a>> {
    let mut result = File{
        imports: Vec::new(),
        procedures: HashMap::new()
    };

    // Transverse the AST
    let children = ast.children.borrow();
    for child in children.iter() {
        let child = child.borrow();

        match child.rule {
            Rule::Use => {
                let dict = convert_use(&child, &global_package)?;
                for (name, proc) in dict.iter() {
                    result.procedures.insert(name, proc.clone());
                }
            }

            Rule::Procedure => {
                let (name, proc) = convert_procedure(&child);
                result.procedures.insert(name, proc);
            },

            // Rest of rules get ignored
            _ => {}
        };
    }

    Ok(result)
}