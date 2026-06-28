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
use crate::adt::lang::{File, Procedure, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::variable::ScopedStack;
use crate::core::backend::expression;
use crate::support::runtime::execution::stop_execution;
use crate::support::runtime::kind::check_kind;

pub fn evaluate<'a>(
    file: &'a File<'a>,
    procedure: &Procedure<'a>,
    expr: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionTupleResult<'a> {
    let children = expr.children.borrow();

    // Process empty returns too
    if children.len() == 0 {
        return stop_execution(
            crate::adt::runtime::Object::Void
        );
    }

    // If the expression is not supposed to return, return an error
    if procedure.ret.is_none() {
        return Err(RuntimeError::unexpected_return(expr));
    }

    let expr = children.get(0).unwrap();
    let expr = expr.borrow();

    let (ret, _) = expression::evaluate(file, &expr, stack)?;
    
    check_kind(
        procedure.ret.as_ref().unwrap().clone(),
        &ret,
        &expr
    )?;
    
    stop_execution(ret)
}