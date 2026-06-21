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
use crate::adt::lang::{ASTValue, RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::support::runtime::object::get_string;

pub fn to_absolute_path<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let path = args.get(0).unwrap();
    let path = get_string(path, trace)?;

    let res = std::path::Path::new(path);
    let abs = std::path::absolute(res);

    if abs.is_err() {
        return Err(
            crate::adt::error::RuntimeError::could_not_read(trace)
        );
    }

    let res = abs.unwrap();

    Ok(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(
                    res.to_str().unwrap().to_owned()
                )
            )
        )
    )
}