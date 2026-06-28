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
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::support::runtime::execution::continue_execution;

pub fn evaluate<'a>(
    child: &AST<'a>
) -> ExecutionTupleResult<'a> {
    let value = child.value.as_ref().unwrap();
    
    // Parse the value
    let value = value.parse::<isize>();

    if value.is_err() {
        return Err(RuntimeError::malformed_literal(child));
    }
    
    continue_execution(
        Object::Hashable(
            HashableObject::Integer(
                value.unwrap()
            )
        )
    )
}