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
use std::ops::DerefMut;
use crate::adt::error::RuntimeError;
use crate::adt::lang::{File, Kind, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::adt::variable::ScopedStack;
use crate::core::backend::{body, expression};
use crate::execute_or_return;
use crate::support::runtime::kind::{check_kind, convert_kind};
use crate::support::runtime::object::{get_float, get_integer};

pub fn evaluate<'a>(
    file: &'a File<'a>,
    expr: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionResult<'a> {
    let children = expr.children.borrow();
    let stack = stack.nest();
    let mut stack = stack.borrow_mut();
    let declaration = children.get(0).unwrap();
    let declaration = declaration.borrow();
    let initial = children.get(1).unwrap();
    let end = children.get(2).unwrap();
    let step = children.get(3).unwrap();
    let body = children.get(4).unwrap();
    let (name, kind) = convert_kind(&declaration);

    let initial = initial.borrow();
    let end = end.borrow();
    let step = step.borrow();
    let body = body.borrow();

    let initial = expression::evaluate(file, &initial, &mut stack)?;
    let end = expression::evaluate(file, &end, &mut stack)?;
    let step = expression::evaluate(file, &step, &mut stack)?;

    if
        kind != Kind::Integer &&
        kind != Kind::Float
    {
        return Err(
            RuntimeError::invalid_loop_variable(expr)
        );
    }

    check_kind(kind.clone(), &initial, expr)?;
    check_kind(kind.clone(), &end, expr)?;
    check_kind(kind.clone(), &step, expr)?;

    // Insert the variable into the stack
    stack.push(name, &initial);

    if kind == Kind::Integer {
        let mut initial = get_integer(&initial, expr)?;
        let end = get_integer(&end, expr)?;
        let step = get_integer(&step, expr)?;
        let max = end - step;

        if step == 0 {
            return Err(RuntimeError::invalid_loop_step(expr));
        }

        while initial <= max {
            execute_or_return!(body::evaluate(file, &body, &mut stack));

            let var = stack.search(name).unwrap();
            let mut var = var.borrow_mut();
            let var = var.deref_mut();

            let
                Object::Hashable(HashableObject::Integer(var))
                = var else { unreachable!() };

            *var += step;
            initial = *var;
        }
    } else {
        let mut initial = get_float(&initial, expr)?;
        let end = get_float(&end, expr)?;
        let step = get_float(&step, expr)?;
        let max = end - step;

        if step == 0.0 {
            return Err(RuntimeError::invalid_loop_step(expr));
        }

        while initial <= max {
            execute_or_return!(body::evaluate(file, &body, &mut stack));

            let var = stack.search(name).unwrap();
            let mut var = var.borrow_mut();
            let var = var.deref_mut();

            let
                Object::Hashable(HashableObject::Float(var))
            = var else { unreachable!() };

            *var += step;
            initial = *var;
        }
    }

    Ok(Object::Void)
}