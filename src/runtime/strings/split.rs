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
use std::cell::RefCell;
use crate::adt::lang::{ASTValue, RuntimeArguments, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{HashableObject, NonHashableObject, Object, RuntimeList};
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::object::get_string;

pub fn split<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let origin = args.get(0).unwrap();
    let delim = args.get(1).unwrap();

    let origin = get_string(origin, trace)?;
    let delim = get_string(delim, trace)?;

    let result: RuntimeList = RuntimeList::new(RefCell::new(vec![]));
    let parts: Vec<&str> = origin.split(delim).collect();

    for part in parts {
        let mut result = result.borrow_mut();
        let obj = Object::Hashable(HashableObject::String(
            ASTValue::Owned(
                part.to_string()
            )
        ));

        result.push(obj);
    }

    continue_execution(
        Object::NonHashable(
            NonHashableObject::List(
                result
            )
        )
    )
}