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
use crate::adt::lang::{ASTValue, RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object};

pub fn cwd<'a>(
    _: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let path = std::env::current_dir();
    if path.is_err() {
        return Err(
            RuntimeError::could_not_read(trace)
        );
    }
    
    let path = path.unwrap();
    let path = path.to_str();
    
    if path.is_none() {
        return Err(
            RuntimeError::could_not_read(trace)
        );   
    }
    
    let path = path.unwrap();
    Ok(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(path.to_string())
            )
        )
    )
}