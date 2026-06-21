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
use crate::adt::lang::{File, Procedure, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::Object;
use crate::adt::variable::ScopedStack;
use crate::core::backend::{body, expression};
use crate::core::frontend::parser::Rule;
use crate::support::runtime::object::get_boolean;

pub fn evaluate<'a>(
    file: &'a File<'a>,
    procedure: &Procedure<'a>,
    expr: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionResult<'a> {
    let children = expr.children.borrow();

    for child in children.iter() {
        let child = child.borrow();

        if child.rule != Rule::Else {
            let children = child.children.borrow();
            let condition = children.get(0).unwrap();
            let body = children.get(1).unwrap();

            let condition = condition.borrow();
            let body = body.borrow();

            // Evaluate condition
            let condition_obj = expression::evaluate(file, &condition, stack)?;
            let condition = get_boolean(&condition_obj, &condition)?;

            if condition {
                return body::evaluate(file, procedure, &body, stack);
            }
        } else {
            // Execute the body directly
            let children = child.children.borrow();
            let body = children.get(0).unwrap();
            let body = body.borrow();

            return body::evaluate(file, procedure, &body, stack);
        }
    }

    Ok(Object::Void)
}