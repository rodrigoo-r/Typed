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
use std::ops::Deref;
use crate::adt::error::{ErrorKind, ExecutionError};
use crate::adt::lang::AST;
use crate::adt::result::ExecutionResult;
use crate::adt::variable::NestedStack;

pub fn evaluate<'a>(
    id: &AST<'a>,
    stack: &NestedStack<'a>
) -> ExecutionResult<'a> {
    let name = id.value.unwrap();
    let deref_stack = stack.borrow();
    let value = deref_stack.search(name);
    
    if value.is_none() {
        return Err(
            ExecutionError{
                kind: ErrorKind::UndefinedSymbol,
                message: "Undefined symbol",
                line: id.line,
                column: id.column
            }
        );
    }
    
    Ok(value.unwrap().deref().borrow().clone())
}