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
use std::cell::RefMut;
use crate::adt::error::RuntimeError;
use crate::adt::lang::{File, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::adt::variable::ScopedStack;
use crate::core::backend::expression;
use crate::core::frontend::parser::Rule;
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::kind::check_obj_kind;
use crate::support::runtime::object::{get_boolean, get_float, get_integer, get_string};

fn perform_op<
    'a,
    T:
        std::cmp::PartialEq +
        std::cmp::PartialOrd
>(
    lhs: T,
    rhs: T,
    expr: &AST<'a>
) -> ExecutionTupleResult<'a> {
    continue_execution(
        Object::Hashable(
            HashableObject::Boolean(
                match expr.rule {
                    Rule::Equal => {
                        lhs == rhs
                    }

                    Rule::Greater => {
                        lhs > rhs
                    }

                    Rule::Less => {
                        lhs < rhs
                    }

                    Rule::Greater_Equal => {
                        lhs >= rhs
                    }

                    Rule::Less_Equal => {
                        lhs <= rhs
                    }

                    _ => {
                        unreachable!()
                    }
                }
            )
        )
    )
}

pub fn evaluate<'a>(
    file: &'a File<'a>,
    expr: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionTupleResult<'a> {
    let lhs = expr.children.borrow();
    let lhs = lhs.get(0).unwrap();
    let lhs = lhs.borrow();

    let rhs = expr.children.borrow();
    let rhs = rhs.get(1).unwrap();
    let rhs = rhs.borrow();

    // Evaluate the expressions
    let (lhs, _) = expression::evaluate(file, &lhs, stack)?;
    let (rhs, _) = expression::evaluate(file, &rhs, stack)?;

    check_obj_kind(
        &lhs,
        &rhs,
        expr
    )?;

    // Match the types
    match lhs.clone() {
        Object::Hashable(hashable) => {
            match hashable {
                HashableObject::String(s) => {
                    let lhs = s.as_ref();
                    let rhs = get_string(&rhs, expr)?;

                    perform_op(
                        lhs,
                        rhs,
                        expr
                    )
                }

                HashableObject::Integer(i) => {
                    let rhs = get_integer(&rhs, expr)?;

                    perform_op(
                        i,
                        rhs,
                        expr
                    )
                }

                HashableObject::Boolean(b) => {
                    let rhs = get_boolean(&rhs, expr)?;

                    perform_op(
                        b,
                        rhs,
                        expr
                    )
                }

                HashableObject::Float(f) => {
                    let rhs = get_float(&rhs, expr)?;

                    perform_op(
                        f,
                        rhs,
                        expr
                    )
                }
            }
        }

        Object::NonHashable(_) |
        Object::Void => {
            Err(
                RuntimeError::incomparable_types(expr)
            )
        }
    }
}