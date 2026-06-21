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
use std::collections::HashMap;
use std::rc::Rc;
use crate::adt::runtime::Object;

pub type NestedStack<'a> =
    Rc<RefCell<ScopedStack<'a>>>;

pub type Variable<'a> =
    Rc<RefCell<Object<'a>>>;

#[derive(Clone)]
pub struct ScopedStack<'a> {
    inner: HashMap<&'a str, Variable<'a>>,
    parent: Option<NestedStack<'a>>,
}

impl <'a> ScopedStack<'a> {
    pub fn new(parent: Option<NestedStack<'a>>) -> NestedStack<'a> {
        NestedStack::new(
            RefCell::new(
                Self {
                    inner: HashMap::new(),
                    parent,
                }
            )
        )
    }

    pub fn nest(&self) -> NestedStack<'a> {
        ScopedStack::new(
            Some(
                Rc::new(
                    RefCell::new(
                        self.clone()
                    )
                )
            )
        )
    }

    pub fn push(&mut self, name: &'a str, value: &Object<'a>) {
        self.inner.insert(name, Variable::new(RefCell::new(value.clone())));
    }

    pub fn search(&self, name: &str) -> Option<Variable<'a>> {
        let mut current = self.parent.clone();

        if let Some(var) = self.inner.get(name) {
            return Some(var.clone());
        }

        while let Some(scope) = current {
            let scope_ref = scope.borrow();

            if let Some(var) = scope_ref.inner.get(name) {
                return Some(var.clone());
            }

            current = scope_ref.parent.clone();
        }

        None
    }
}