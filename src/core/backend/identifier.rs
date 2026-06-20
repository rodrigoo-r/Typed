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
use crate::adt::error::{ErrorKind, ExecutionError};
use crate::adt::lang::AST;
use crate::adt::result::ExecutionResult;
use crate::adt::variable::ScopedStack;

pub fn evaluate<'a, 'stack>(
    id: &AST<'a>,
    stack: &'stack ScopedStack<'a, 'stack>
) -> ExecutionResult<'a> {
    let name = id.value.unwrap();
    let value = stack.search(name);
    
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
    
    Ok(value.unwrap().clone())
}