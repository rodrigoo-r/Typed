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
use crate::adt::error::ExecutionError;
use crate::adt::lang::{RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object, StringKind};
use crate::support::runtime::object::{get_integer, get_string};

pub fn replace_many<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let origin = args.get(0).unwrap();
    let needle = args.get(1).unwrap();
    let replacement = args.get(2).unwrap();
    let count = args.get(3).unwrap();
    let origin = get_string(origin, trace)?;
    let needle = get_string(needle, trace)?;
    let replacement = get_string(replacement, trace)?;
    let count = get_integer(count, trace)?;
    
    if count < 0 {
        return Err(
            ExecutionError::out_of_bounds(trace)
        )
    }

    Ok(
        Object::Hashable(
            HashableObject::String(
                StringKind::Dynamic(
                    origin.replacen(needle, replacement, count as usize)
                )
            )
        )
    )
}