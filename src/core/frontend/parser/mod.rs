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

use pest_derive::Parser;
use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;
use pest::iterators::Pairs;
use crate::adt::lang::{ChildAST, AST};

#[derive(Parser)]
#[grammar = "grammar/grammar.pest"]
pub struct Parser;

pub fn convert<'source>(pairs: Pairs<'source, Rule>) -> AST<'source> {
    let result = Rc::new(RefCell::new(
        AST{
            line: 0,
            column: 0,
            rule: Rule::Program,
            value: None,
            children: RefCell::new(Vec::new())
        }
    ));

    let mut queue: VecDeque<(Pairs<Rule>, ChildAST<'source>)>
        = VecDeque::new();

    queue.push_back((pairs, Rc::clone(&result)));

    while !queue.is_empty() {
        let (pairs, parent) = queue.pop_front().unwrap();

        for inner in pairs.into_iter() {
            let parent = Rc::clone(&parent);
            let rule = inner.as_rule();

            // Skip if the rule is EOI
            if rule == Rule::EOI {
                continue;
            } else if rule == Rule::Program {
                queue.push_back(
                    (
                        inner.into_inner(),
                        Rc::clone(&parent)
                    )
                );

                continue;
            }

            let line_col = inner.as_span().start_pos().line_col();
            let val = inner.as_str();
            let child = Rc::new(
                RefCell::new(
                    AST{
                        value: None,
                        line: line_col.0,
                        column: line_col.1,
                        rule,
                        children: RefCell::new(Vec::new())
                    }
                )
            );

            match rule {
                Rule::Identifier |
                Rule::Float_Literal |
                Rule::Integer_Literal =>
                    child.borrow_mut().value = Some(val),

                Rule::String_Literal => {
                    // Remove the quotes
                    let s = &val[1..val.len()-1];
                    child.borrow_mut().value = Some(s);
                },

                // Ignore boolean literals
                Rule::True_Literal |
                Rule::False_Literal => {}

                // Everything else is appended to the queue
                _ => {
                    queue.push_back(
                        (
                            inner.into_inner(),
                            Rc::clone(&child)
                        )
                    );
                }
            }

            let parent = parent.borrow_mut();
            let mut children = parent.children.borrow_mut();
            children.push(Rc::clone(&child));
        }
    }

    Rc::into_inner(result)
        .unwrap()
        .into_inner()
}