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
    let value = child.value.unwrap();

    if value.eq("True") {
        return Ok(Object::Hashable(HashableObject::Boolean(true)));
    }

    if value.eq("False") {
        return Ok(Object::Hashable(HashableObject::Boolean(false)));
    }

    Err(
RuntimeError::malformed_literal(child), )
}