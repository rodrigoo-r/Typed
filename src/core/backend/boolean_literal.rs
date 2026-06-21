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
    match child.rule {
        crate::core::frontend::parser::Rule::True_Literal => {
            Ok(Object::Hashable(HashableObject::Boolean(true)))
        }
        crate::core::frontend::parser::Rule::False_Literal => {
            Ok(Object::Hashable(HashableObject::Boolean(false)))
        }
        _ => {
            Err(RuntimeError::malformed_literal(child))
        }
    }
}