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
use std::path::PathBuf;
use crate::adt::lang::{ASTValue, RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::support::runtime::object::{get_list, get_string};

pub fn join_path<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let list = args.get(0).unwrap();
    let list = get_list(list, trace)?;
    let list = list.borrow();

    let mut base = PathBuf::from("");

    for item in list.iter() {
        let item = get_string(item, trace)?;
        base.push(item);
    }

    let result = base.to_str();
    if result.is_none() {
        return Err(
            crate::adt::error::RuntimeError::could_not_read(trace)
        );
    }

    let base = result.unwrap();
    Ok(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(
                    base.to_owned()
                )
            )
        )
    )
}