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
use std::str::FromStr;
use crate::adt::error::{ErrorKind, ExecutionError};
use crate::adt::lang::AST;
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{Float, HashableObject, Object};

pub fn evaluate<'a>(
    child: &AST<'a>
) -> ExecutionResult<'a> {
    let value = child.value.unwrap();
    
    // Parse the value
    let value = Float::from_str(value);
    
    if value.is_err() {
        return Err(
            ExecutionError{
                kind: ErrorKind::MisformedLiteral,
                message: "Invalid float literal",
                line: child.line,
                column: child.column
            }
        );
    }
    
    Ok(
        Object::Hashable(
            HashableObject::Float(
                value.unwrap()
            )
        )
    )
}