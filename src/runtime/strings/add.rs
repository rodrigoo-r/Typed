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

pub fn add<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let origin = args.get(0).unwrap();
    let addition = args.get(1).unwrap();
    
    let origin = get_string(origin, trace)?;
    let addition = get_string(addition, trace)?;
    let mut result = String::from(origin);
    result.push_str(addition);
    
    Ok(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(result)
            )
        )
    )
}