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
use crate::adt::error::RuntimeError;
use crate::adt::lang::AST;
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object};

pub fn evaluate<'a>(
    child: &AST<'a>
) -> ExecutionResult<'a> {
    let value = child.value.as_ref().unwrap();
    
    // Parse the value
    let value = value.parse::<isize>();

    if value.is_err() {
        return Err(RuntimeError::malformed_literal(child));
    }
    
    Ok(
        Object::Hashable(
            HashableObject::Integer(
                value.unwrap()
            )
        )
    )
}