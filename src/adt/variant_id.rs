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
use std::ops::Deref;
use crate::adt::runtime::{HashableObject, Object};

fn get_variant_id(obj: &Object) -> u8 {
    match obj {
        Object::Hashable(_) => 0,
        Object::NonHashable(_) => 1,
        Object::Void => 2,
        Object::Any(_) => 3
    }
}

impl<'a> Object<'a> {
    fn variant_id(&self) -> u8 {
        if let Object::Any(a) = self {
            let obj = a.borrow();
            let obj = obj.deref();

            get_variant_id(obj)
        } else {
            get_variant_id(self)
        }
    }
}

impl<'a> HashableObject<'a> {
    pub fn variant_id(&self) -> u8 {
        match self {
            HashableObject::String(_) => 0,
            HashableObject::Integer(_) => 1,
            HashableObject::Boolean(_) => 2,
            HashableObject::Float(_) => 3
        }
    }
}