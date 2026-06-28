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
use std::path::Path;
use crate::adt::error::RuntimeError;
use crate::adt::lang::{ASTValue, RuntimeArguments, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::object::get_string;

pub fn file_name<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let path = args.get(0).unwrap();
    let path = get_string(path, trace)?;

    let res = Path::new(path);
    let stem = res.file_stem();
    if stem.is_none() {
        return Err(
            RuntimeError::could_not_read(trace)
        );
    }

    let stem = stem.unwrap();
    let stem = stem.to_str();

    if stem.is_none() {
        return Err(
            RuntimeError::could_not_read(trace)
        );
    }

    let stem = stem.unwrap();
    continue_execution(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(stem.to_string())
            )
        )
    )
}