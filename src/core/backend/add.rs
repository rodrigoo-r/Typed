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
use std::ops::{Deref, DerefMut};
use crate::adt::lang::{File, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{Object, HashableObject};
use crate::adt::variable::NestedStack;
use crate::core::backend::expression;
use crate::support::runtime::{get_float, get_integer};

pub fn evaluate<'a>(
    file: &'a File<'a>,
    expr: &AST<'a>,
    stack: &NestedStack<'a>
) -> ExecutionResult<'a> {
    let deref_stack = stack.borrow();
    let children = expr.children.borrow();
    let expr = children.get(0).unwrap();
    let expr = expr.borrow();
    let expr_result = expression::evaluate(file, &expr, stack)?;
    let target = children.get(1).unwrap();
    let target = target.borrow();
    let target = target.value.unwrap();

    // Get the target value
    let target = deref_stack.search(target).unwrap();
    let target = target.deref();
    let target_borrow = target.borrow();
    
    if let Object::Hashable(HashableObject::Integer(_)) = *target_borrow {
        let mut mut_ref = target.borrow_mut();
        let mut_ref = mut_ref.deref_mut();
        let 
            Object::Hashable(HashableObject::Integer(i))
        = mut_ref else { unreachable!() };
        
        let source = get_integer(&expr_result, &expr)?;

        *i += source;
    } else if let Object::Hashable(HashableObject::Float(_)) = *target_borrow {
        let mut mut_ref = target.borrow_mut();
        let mut_ref = mut_ref.deref_mut();
        let 
            Object::Hashable(HashableObject::Float(f)) 
        = mut_ref else { unreachable!() };
        
        let source = get_float(&expr_result, &expr)?;
        
        *f += source;
    }
    
    Ok(Object::Void)
}