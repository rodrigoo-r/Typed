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
use std::cell::{RefCell, RefMut};
use crate::adt::lang::{ASTValue, File, Kind, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{*};
use crate::adt::runtime::Object::NonHashable;
use crate::adt::variable::ScopedStack;
use crate::core::backend::expression;
use crate::support::runtime::kind::{check_kind, convert_kind};

pub fn evaluate<'a>(
    file: &'a File<'a>,
    expr: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionResult<'a> {
    let children = expr.children.borrow();

    let data = children.get(0).unwrap();
    let data = data.borrow();
    let (name, kind) = convert_kind(&data);
    let initial;

    // Determine if the declaration has an initializer
    if children.len() > 1 {
        let init = children.get(1).unwrap().borrow();
        initial = expression::evaluate(file, &init, stack)?.0;

        check_kind(
            kind,
            &initial,
            expr
        )?;

    } else {
        match kind {
            Kind::Integer => {
                initial = Object::Hashable(HashableObject::Integer(0));
            }

            Kind::Float => {
                initial = Object::Hashable(
                    HashableObject::Float(
                        Float::from(0.0)
                    )
                );
            }

            Kind::String => {
                initial = Object::Hashable(
                    HashableObject::String(
                        ASTValue::Borrowed("")
                    )
                );
            }

            Kind::Boolean => {
                initial = Object::Hashable(
                    HashableObject::Boolean(false)
                );
            }

            Kind::Dictionary => {
                initial = NonHashable(
                    NonHashableObject::Dictionary(
                        RuntimeDictionary::new(RefCell::new(Dictionary::new()))
                    )
                );
            }

            Kind::List => {
                initial = NonHashable(
                    NonHashableObject::List(
                        RuntimeList::new(RefCell::new(List::new()))
                    )
                );
            }
            
            _ => unreachable!()
        }
    }

    // Insert the variable into the stack
    stack.push(name, &initial);

    Ok(Object::Void)
}