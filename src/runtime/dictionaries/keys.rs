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
use crate::adt::lang::{RuntimeArguments, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{List, NonHashableObject, Object, RuntimeList};
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::object::get_dictionary;

pub fn keys<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let dict_obj = args.get(0).unwrap();
    let dict = get_dictionary(dict_obj, trace)?;

    let dict = dict.borrow();
    let mut keys = List::new();

    for key in dict.keys() {
        keys.push(
            Object::Hashable(
                key.clone()
            )
        );
    }

    continue_execution(
        Object::NonHashable(
            NonHashableObject::List(
                RuntimeList::new(
                    RefCell::new(keys)
                )
            )
        )
    )
}