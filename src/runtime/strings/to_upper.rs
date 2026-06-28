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

pub fn to_upper<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let origin = args.get(0).unwrap();
    let origin = get_string(origin, trace)?;
    
    continue_execution(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(
                    origin.to_uppercase()
                )
            )
        )
    )
}