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
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::object::get_string;

pub fn trim<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let origin_obj = args.get(0).unwrap();
    let origin = get_string(origin_obj, trace)?;
    
    // If the string is static, we can trim it without allocating
    if let Object::Hashable(
        HashableObject::String(
            ASTValue::Borrowed(s)
        )
    ) = origin_obj {
        let trimmed = s.trim();
        return continue_execution(
            Object::Hashable(
                HashableObject::String(
                    ASTValue::Borrowed(trimmed)
                )
            )
        );
    }
    
    // Otherwise, we need to allocate a new string
    let trimmed = String::from(origin.trim());
    
    continue_execution(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(trimmed)
            )
        )
    )
}