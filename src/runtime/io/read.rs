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
use crate::adt::error::ExecutionError;
use crate::adt::lang::{RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object, StringKind};

pub fn read<'a>(
    _: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let mut input = String::new();

    // Read the line
    let res = io::stdin()
        .read_line(&mut input);

    if res.is_err() {
        return Err(
            ExecutionError::could_not_read(trace)
        )
    }

    // Remove the newline character
    input.pop();

    Ok(
        Object::Hashable(
            HashableObject::String(
                StringKind::Dynamic(input)
            )
        )
    )
}