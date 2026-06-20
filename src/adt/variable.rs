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
use crate::adt::runtime::Object;

pub struct ScopedStack<'a, 'parent> {
    inner: HashMap<&'a str, Object<'a>>,
    parent: Option<&'parent ScopedStack<'a, 'parent>>,
}

impl <'a, 'parent> ScopedStack<'a, 'parent> {
    pub fn new(parent: Option<&'parent ScopedStack<'a, 'parent>>) -> Self {
        Self {
            inner: HashMap::new(),
            parent,
        }
    }
    
    pub fn nest(&'parent self) -> ScopedStack<'a, 'parent> {
        ScopedStack::new(Some(self))
    }
    
    pub fn push(&mut self, name: &'a str, value: &'parent Object<'a>) {
        self.inner.insert(name, value.clone());
    }
    
    pub fn search(&self, name: &str) -> Option<&Object<'a>> {
        let mut queue = vec![self];
        
        while !queue.is_empty() {
            let stack = queue.pop().unwrap();
            
            if stack.inner.contains_key(name) {
                return stack.inner.get(name);
            }
            
            if let Some(parent) = &stack.parent {
                queue.push(parent);
            }
        }
        
        None
    }
}