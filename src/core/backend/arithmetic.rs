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
use std::ops::{Deref, DerefMut};
use crate::adt::lang::{File, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{Object, HashableObject};
use crate::adt::variable::ScopedStack;
use crate::core::backend::expression;
use crate::core::frontend::parser::Rule;
use crate::support::runtime::kind::check_obj_kind;
use crate::support::runtime::object::{get_float, get_integer};

fn perform_op<
    T:
        std::ops::AddAssign +
        std::ops::SubAssign +
        std::ops::MulAssign +
        std::ops::DivAssign
>(
    i: &mut T,
    expr: &AST,
    source: T
) {
    match expr.rule {
        Rule::Add => {
            *i += source;
        }

        Rule::Subtract => {
            *i -= source;
        }

        Rule::Multiply => {
            *i *= source;
        }

        Rule::Divide => {
            *i /= source;
        }

        _ => {}
    }
}

pub fn evaluate<'a>(
    file: &'a File<'a>,
    expr: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionResult<'a> {
    let children = expr.children.borrow();
    let expr = children.get(0).unwrap();
    let expr = expr.borrow();
    let expr_result = expression::evaluate(file, &expr, stack)?;
    let target = children.get(1).unwrap();
    let target = target.borrow();
    let target = target.value.unwrap();

    // Get the target value
    let target = stack.search(target).unwrap();
    let target = target.deref();
    let target_borrow = target.borrow();

    // Do type checking
    check_obj_kind(&target.borrow(), &expr_result, &expr)?;

    if let Object::Hashable(HashableObject::Integer(_)) = *target_borrow {
        let mut mut_ref = target.borrow_mut();
        let mut_ref = mut_ref.deref_mut();
        let
            Object::Hashable(HashableObject::Integer(i))
        = mut_ref else { unreachable!() };

        let source = get_integer(&expr_result, &expr)?;

        perform_op(i, &expr, source);
    } else if let Object::Hashable(HashableObject::Float(_)) = *target_borrow {
        let mut mut_ref = target.borrow_mut();
        let mut_ref = mut_ref.deref_mut();
        let
            Object::Hashable(HashableObject::Float(f))
        = mut_ref else { unreachable!() };

        let source = get_float(&expr_result, &expr)?;
        perform_op(f, &expr, source);
    }
    
    Ok(Object::Void)
}