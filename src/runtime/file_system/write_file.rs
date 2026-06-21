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
use crate::adt::runtime::Object;
use crate::support::runtime::object::get_string;

pub fn write_file<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let path = args.get(0).unwrap();
    let path = get_string(path, trace)?;
    let content = args.get(1).unwrap();
    let content = get_string(content, trace)?;

    let res = std::fs::write(path, content);
    if res.is_err() {
        return Err(
            RuntimeError::could_not_write(trace)
        );
    }
    
    Ok(Object::Void)
}