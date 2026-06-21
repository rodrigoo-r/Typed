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
use crate::adt::lang::{RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object, StringKind};
use crate::support::runtime::object::{get_integer, get_string};

pub fn access<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let str_obj = args.get(0).unwrap();
    let idx = args.get(1).unwrap();

    let str = get_string(str_obj, trace)?;
    let idx = get_integer(idx, trace)?;

    if idx < 0 {
        return Err(
            RuntimeError::out_of_bounds(trace)
        );
    }

    let idx = idx as usize;
    if idx >= str.len() {
        return Err(
            RuntimeError::out_of_bounds(trace)
        );
    }

    // If the original string is static, we can just return the character
    if let Object::Hashable(HashableObject::String(StringKind::Static(s))) = str_obj {
        let slice = &s[idx-1..idx];

        return Ok(
            Object::Hashable(
                HashableObject::String(
                    StringKind::Static(slice)
                )
            )
        );
    }

    // Create the result in an owned string to avoid memory leaks
    let result = str.chars().nth(idx).unwrap();
    Ok(
        Object::Hashable(
            HashableObject::String(
                StringKind::Dynamic(String::from(result))
            )
        )
    )
}