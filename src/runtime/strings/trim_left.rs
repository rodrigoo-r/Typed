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
use crate::adt::lang::{RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object, StringKind};
use crate::support::runtime::object::get_string;

pub fn trim_left<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let origin_obj = args.get(0).unwrap();
    let origin = get_string(origin_obj, trace)?;
    
    // If the string is static, we can trim it without allocating
    if let Object::Hashable(
        HashableObject::String(
            StringKind::Static(s)
        )
    ) = origin_obj {
        let trimmed = s.trim_start();
        return Ok(
            Object::Hashable(
                HashableObject::String(
                    StringKind::Static(trimmed)
                )
            )
        );
    }
    
    // Otherwise, we need to allocate a new string
    let trimmed = String::from(origin.trim_start());
    
    Ok(
        Object::Hashable(
            HashableObject::String(
                StringKind::Dynamic(trimmed)
            )
        )
    )
}