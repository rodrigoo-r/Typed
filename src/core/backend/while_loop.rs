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
use crate::adt::lang::{File, Kind, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::Object;
use crate::adt::variable::ScopedStack;
use crate::core::backend::{body, expression};
use crate::support::runtime::kind::check_kind;
use crate::support::runtime::object::get_boolean;

pub fn evaluate<'a>(
    file: &'a File<'a>,
    expr: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionResult<'a> {
    let children = expr.children.borrow();
    let condition = children.get(0).unwrap();
    let body = children.get(1).unwrap();

    let condition = condition.borrow();
    let body = body.borrow();

    loop {
        let condition = expression::evaluate(file, &condition, stack)?;
        check_kind(Kind::Boolean, &condition, expr)?;

        let condition = get_boolean(&condition, expr)?;

        // Break if the condition is false
        if !condition {
            break;
        }

        // Execute the body
        body::evaluate(file, &body, stack)?;
    }

    Ok(Object::Void)
}