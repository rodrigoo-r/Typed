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
use std::cell::RefMut;
use std::ops::Deref;
use crate::adt::error::RuntimeError;
use crate::adt::lang::AST;
use crate::adt::result::ExecutionResult;
use crate::adt::variable::ScopedStack;

pub fn evaluate<'a>(
    id: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionResult<'a> {
    let name = id.value.as_ref().unwrap();
    let value = stack.search(name);
    
    if value.is_none() {
        return Err(RuntimeError::undefined_symbol(id));
    }
    
    Ok(value.unwrap().deref().borrow().clone())
}