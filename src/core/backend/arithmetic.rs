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
use crate::adt::error::RuntimeError;
use crate::adt::lang::{File, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{Object, HashableObject};
use crate::adt::variable::ScopedStack;
use crate::core::backend::expression;
use crate::core::frontend::parser::Rule;
use crate::support::runtime::execution::continue_execution;
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
) -> ExecutionTupleResult<'a> {
    let children = expr.children.borrow();
    let target = children.get(0).unwrap();
    let target = target.borrow();
    let (expr_result, _) = expression::evaluate(file, &target, stack)?;
    let target = children.get(1).unwrap();
    let target = target.borrow();
    let target = target.value.as_ref().unwrap();

    // Get the target value
    let target = stack.search(target);
    if target.is_none() {
        return Err(RuntimeError::undefined_symbol(&expr));
    }

    let target = target.unwrap();
    let target = target.deref();

    {
        // Do type checking
        check_obj_kind(&target.borrow(), &expr_result, &expr)?;
    }

    let mut is_integer = false;
    let mut is_float = false;

    {
        let target_borrow = target.borrow();
        if let Object::Hashable(HashableObject::Integer(_)) = *target_borrow {
            is_integer = true;
        } else if let Object::Hashable(HashableObject::Float(_)) = *target_borrow {
            is_float = true;
        }
    }

    if is_integer {
        let mut mut_ref = target.borrow_mut();
        let mut_ref = mut_ref.deref_mut();
        let
            Object::Hashable(HashableObject::Integer(i))
        = mut_ref else { unreachable!() };

        let source = get_integer(&expr_result, &expr)?;

        perform_op(i, &expr, source);
    } else if is_float {
        let mut mut_ref = target.borrow_mut();
        let mut_ref = mut_ref.deref_mut();
        let
            Object::Hashable(HashableObject::Float(f))
        = mut_ref else { unreachable!() };

        let source = get_float(&expr_result, &expr)?;
        perform_op(f, &expr, source);
    }
    
    continue_execution(Object::Void)
}