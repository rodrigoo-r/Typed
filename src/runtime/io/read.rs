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
use std::io;
use crate::adt::error::RuntimeError;
use crate::adt::lang::{ASTValue, RuntimeArguments, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::support::runtime::execution::continue_execution;

pub fn read<'a>(
    _: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let mut input = String::new();

    // Read the line
    let res = io::stdin()
        .read_line(&mut input);

    if res.is_err() {
        return Err(
            RuntimeError::could_not_read(trace)
        )
    }

    // Remove the newline character
    input.pop();

    continue_execution(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(input)
            )
        )
    )
}