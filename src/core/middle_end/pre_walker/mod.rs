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
use crate::adt::error::RuntimeError;
use crate::adt::lang::{ASTValue, Argument, File, Kind, Procedure, AST};
use crate::adt::result::RuntimeResult;
use crate::adt::runtime::{GlobalPackageDictionary, PackageDictionary};
use crate::core::frontend::parser::Rule;
use crate::core::frontend::parser::Rule::{Procedure_Arguments, Procedure_Return_Kind};

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
) -> RuntimeResult<&'a PackageDictionary<'a>> {
    let children = ast.children.borrow();
    let literal = children[0].borrow();
    let literal = literal.value.as_ref().unwrap();
    let literal = literal.as_ref();

    let pkg = global_package.get(literal);

    match pkg {
        None => {
            Err(RuntimeError::could_not_find_library(ast))
        }
        Some(procedures) => {
            Ok(procedures)
        }
    }
}

fn convert_procedure<'a>(ast: &AST<'a>)
    -> (ASTValue<'a>, Procedure<'a>)
{
    let children = ast.children.borrow();
    let name = children[0].borrow();
    let name = name.value.as_ref().unwrap();

    let mut body_idx = 1;
    let mut body = &children[body_idx];
    let mut vec: Vec<Argument<'a>> = Vec::new();
    let mut body_ref = body.borrow();
    let mut ret_type = None as Option<Kind>;

    if body_ref.rule == Procedure_Arguments {
        let args = body;
        let args = args.borrow();
        body_idx += 1;
        body = &children[body_idx];
        body_ref = body.borrow();

        // Process the arguments
        for arg in args.children.borrow().iter() {
            let arg = arg.borrow();
            let arg_children = arg.children.borrow();

            let name = arg_children[0].borrow();
            let name = name.value.as_ref().unwrap();

            let kind = arg_children[1].borrow();

            // Insert the argument into the procedure
            vec.push(
                Argument{
                    name: name.clone(),
                    kind: convert_kind(kind)
                }
            );
        }
    }

    if body_ref.rule == Procedure_Return_Kind {
        let ret_type_ast = body;
        let ret_type_ast = ret_type_ast.borrow();
        body_idx += 1;
        body = &children[body_idx];
        
        let kind = convert_kind(ret_type_ast);
        ret_type = Some(kind);
    }

    (
        name.clone(),
        Procedure{
            body: Some(body.clone()),
            arguments: vec,
            variadic: false,
            native: None,
            ret: ret_type
        }
    )
}

pub fn convert<'a>(
    ast: AST<'a>,
    global_package: &'a GlobalPackageDictionary<'a>
) -> RuntimeResult<File<'a>> {
    let mut result = File{
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
                    result.procedures.insert(
                        ASTValue::Borrowed(name),
                        proc.clone()
                    );
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