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
use std::hash::Hash;
use std::ops::Deref;
use crate::adt::lang::ASTValue;
use crate::adt::runtime::{HashableObject, Object};

fn hash_obj<H: std::hash::Hasher>(obj: &HashableObject, state: &mut H) {
    match obj {
        HashableObject::String(s) => {
            match s {
                ASTValue::Borrowed(s) => {
                    s.hash(state)
                }
                ASTValue::Owned(d) => {
                    d.hash(state)
                }
            }
        },
        HashableObject::Integer(i) => i.hash(state),
        HashableObject::Boolean(b) => b.hash(state),
        HashableObject::Float(f) => f.to_bits().hash(state),
    }
}

impl <'a> Hash for HashableObject<'a> {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        std::mem::discriminant(self).hash(state);

        hash_obj(self, state)
    }
}

impl <'a> Hash for Object<'a> {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        std::mem::discriminant(self).hash(state);

        match self {
            Object::Hashable(h) => h.hash(state),
            Object::Any(a) => {
                let obj = a.borrow();
                let obj = obj.deref();

                if let Object::Hashable(hashable) = obj {
                    hashable.hash(state);
                }

                panic!("Cannot hash a non-hashable object");
            }

            Object::Void |
            Object::NonHashable(_) => {
                panic!("Cannot hash a non-hashable object");
            },
        }
    }
}