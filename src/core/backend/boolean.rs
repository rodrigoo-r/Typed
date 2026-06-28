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
use crate::adt::lang::{File, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::adt::variable::ScopedStack;
use crate::core::backend::expression;
use crate::core::frontend::parser::Rule;
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::object::get_boolean;

fn not<'a>(
    expr: &AST<'a>,
    lhs: &Object<'a>,
) -> ExecutionTupleResult<'a> {
    let res = get_boolean(&lhs, expr)?;

    continue_execution(
        Object::Hashable(
            HashableObject::Boolean(
                !res
            )
        )
    )
}

pub fn op<'a>(
    file: &'a File<'a>,
    expr: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>,
    lhs: &Object<'a>,
    rule: Rule
) -> ExecutionTupleResult<'a> {
    let children = expr.children.borrow();
    let rhs = children.get(1).unwrap();
    let rhs = rhs.borrow();

    let (rhs_obj, _) = expression::evaluate(file, &rhs, stack)?;
    let rhs = get_boolean(&rhs_obj, &rhs)?;
    let lhs = get_boolean(&lhs, expr)?;

    continue_execution(
        Object::Hashable(
            HashableObject::Boolean(
                if rule == Rule::Or {
                    lhs || rhs
                } else {
                    lhs && rhs
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
    let children = expr.children.borrow();
    let lhs = children.get(0).unwrap();
    let lhs = lhs.borrow();

    let (res, _) = expression::evaluate(file, &lhs, stack)?;

    match expr.rule {
        Rule::Not => not(expr, &res),

        Rule::Or |
        Rule::And => {
            op(file, &expr, stack, &res, expr.rule)
        }

        _ => {
            unreachable!()
        }
    }
}