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
use std::collections::{ HashSet};
use crate::adt::runtime::{HashableObject};

#[derive(Debug, Clone)]
pub struct Set<'a> {
    inner: HashSet<HashableObject<'a>>,
    order: Vec<HashableObject<'a>>
}

impl <'a> Set<'a> {
    pub fn new() -> Self {
        Self {
            inner: HashSet::new(),
            order: Vec::new()
        }
    }

    pub fn insert(&mut self, key: HashableObject<'a>) {
        if self.inner.insert(key.clone()) {
            self.order.push(key);
        }
    }

    pub fn contains(&self, key: &HashableObject<'a>) -> bool {
        self.inner.contains(key)
    }

    pub fn remove(&mut self, key: &HashableObject<'a>) -> bool {
        if self.inner.remove(key) {
            self.order.retain(|k| k != key);
            true
        } else {
            false
        }
    }

    pub fn iter(&self) -> impl Iterator<Item = &HashableObject<'a>> {
        self.order.iter()
    }

    pub fn size(&self) -> usize {
        self.inner.len()
    }

    pub fn values(&self) -> impl Iterator<Item = &HashableObject<'a>> {
        self.order.iter()
    }
}