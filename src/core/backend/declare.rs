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
use crate::adt::lang::{File, Kind, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{Dictionary, Float, HashableObject, List, NonHashableObject, Object, StringKind};
use crate::adt::runtime::Object::NonHashable;
use crate::adt::variable::NestedStack;
use crate::core::backend::expression;
use crate::core::frontend::parser;
use crate::support::runtime::kind::check_kind;

pub fn evaluate<'a>(
    file: &'a File<'a>,
    expr: &AST<'a>,
    stack: &NestedStack<'a>
) -> ExecutionResult<'a> {
    let children = expr.children.borrow();

    let data = children.get(0).unwrap();
    let data = data.borrow();
    let data_children = data.children.borrow();
    let name = data_children.get(0).unwrap().borrow();
    let kind = data_children.get(1).unwrap().borrow();
    let initial;

    // Determine if the declaration has an initializer
    if children.len() > 1 {
        let init = children.get(1).unwrap().borrow();
        initial = expression::evaluate(file, &init, stack)?;

        check_kind(
            match kind.rule {
                parser::Rule::Integer => Kind::Integer,
                parser::Rule::Float => Kind::Float,
                parser::Rule::String => Kind::String,
                parser::Rule::Boolean => Kind::Boolean,
                parser::Rule::Dictionary => Kind::Dictionary,
                parser::Rule::List => Kind::List,

                _ => { unreachable!() }
            },
            &initial,
            expr
        )?;

    } else {
        match kind.rule {
            parser::Rule::Integer => {
                initial = Object::Hashable(HashableObject::Integer(0));
            }

            parser::Rule::Float => {
                initial = Object::Hashable(
                    HashableObject::Float(
                        Float::from(0.0)
                    )
                );
            }

            parser::Rule::String => {
                initial = Object::Hashable(
                    HashableObject::String(
                        StringKind::Static("")
                    )
                );
            }

            parser::Rule::Boolean => {
                initial = Object::Hashable(
                    HashableObject::Boolean(false)
                );
            }

            parser::Rule::Dictionary => {
                initial = NonHashable(
                    NonHashableObject::Dictionary(
                        Dictionary::new()
                    )
                );
            }

            parser::Rule::List => {
                initial = NonHashable(
                    NonHashableObject::List(
                        List::new()
                    )
                );
            }

            _ => { unreachable!() }
        }
    }

    // Insert the variable into the stack
    let mut stack = stack.borrow_mut();
    stack.push(name.value.unwrap(), &initial);

    Ok(Object::Void)
}