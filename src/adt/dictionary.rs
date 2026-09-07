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
use std::collections::HashMap;
use crate::adt::runtime::{HashableObject, Object};
use crate::adt::set::Set;

#[derive(Debug, Clone)]
pub struct Dictionary<'a> {
    inner: HashMap<HashableObject<'a>, Object<'a>>,
    order: Set<'a>
}

impl <'a> Dictionary<'a> {
    pub fn new() -> Self {
        Self {
            inner: HashMap::new(),
            order: Set::new()
        }
    }

    pub fn insert(&mut self, key: HashableObject<'a>, value: Object<'a>) {
        if !self.inner.contains_key(&key) {
            self.order.insert(key.clone());
        }
        self.inner.insert(key, value);
    }

    pub fn get(&self, key: &HashableObject<'a>) -> Option<&Object<'a>> {
        self.inner.get(key)
    }

    pub fn contains(&self, key: &HashableObject<'a>) -> bool {
        self.inner.contains_key(key)
    }
    
    pub fn remove(&mut self, key: &HashableObject<'a>) -> bool {
        if self.inner.remove(key).is_some() {
            self.order.remove(key);
            true
        } else {
            false
        }
    }

    pub fn iter(&self) -> impl Iterator<Item = (&HashableObject<'a>, &Object<'a>)> {
        self.order.iter().filter_map(move |key| {
            self.inner.get(key).map(|value| (key, value))
        })
    }
    
    pub fn size(&self) -> usize {
        self.inner.len()
    }
    
    pub fn keys(&self) -> impl Iterator<Item = &HashableObject<'a>> {
        self.order.iter()
    }
}