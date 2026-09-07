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
use crate::support::runtime::object::{get_set};

pub fn values<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let set_obj = args.get(0).unwrap();
    let set = get_set(set_obj, trace)?;
    let set = set.borrow();
    
    let mut list = List::new();
    for value in set.iter() {
        list.push(Object::Hashable(value.clone()));
    }

    continue_execution(
        Object::NonHashable(
            NonHashableObject::List(
                RuntimeList::new(RefCell::new(list))
            )
        )
    )
}