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
use crate::adt::lang::AST;
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, Object, StringKind};

pub fn evaluate<'a>(
    child: &AST<'a>
) -> ExecutionResult<'a> {
    Ok(
        Object::Hashable(
            HashableObject::String(
                StringKind::Static(
                    child.value.unwrap()
                )
            )
        )
    )
}