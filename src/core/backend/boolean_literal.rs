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
    match child.rule {
        crate::core::frontend::parser::Rule::True_Literal => {
            continue_execution(Object::Hashable(HashableObject::Boolean(true)))
        }
        crate::core::frontend::parser::Rule::False_Literal => {
            continue_execution(Object::Hashable(HashableObject::Boolean(false)))
        }
        _ => {
            Err(RuntimeError::malformed_literal(child))
        }
    }
}