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
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::object::get_string;

pub fn contains<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let origin = args.get(0).unwrap();
    let needle = args.get(1).unwrap();
    let origin = get_string(origin, trace)?;
    let needle = get_string(needle, trace)?;

    continue_execution(
        Object::Hashable(
            HashableObject::Boolean(
                origin.contains(needle)
            )
        )
    )
}