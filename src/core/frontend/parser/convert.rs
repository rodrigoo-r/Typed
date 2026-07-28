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

#[macro_export]
macro_rules! convert_grammar {
    (
        $edition:ident
    ) => {
        pub fn convert<'source>(
            pairs: Pairs<'source, crate::core::frontend::parser::$edition::Rule>,
            do_unescape: bool
        ) -> AST<'source> {
            let result = Rc::new(RefCell::new(
                AST{
                    line: 0,
                    column: 0,
                    rule: crate::core::frontend::parser::$edition::Rule::Program.into(),
                    value: None,
                    children: RefCell::new(Vec::new())
                }
            ));

            let mut queue: VecDeque<(Pairs<crate::core::frontend::parser::$edition::Rule>, ChildAST<'source>)>
                = VecDeque::new();

            queue.push_back((pairs, Rc::clone(&result)));

            while !queue.is_empty() {
                let (pairs, parent) = queue.pop_front().unwrap();

                for inner in pairs.into_iter() {
                    let parent = Rc::clone(&parent);
                    let rule = inner.as_rule();

                    // Skip if the rule is EOI
                    if rule == crate::core::frontend::parser::$edition::Rule::EOI {
                        continue;
                    } else if rule == crate::core::frontend::parser::$edition::Rule::Program {
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
                                rule: crate::core::frontend::parser::Rule::from(rule),
                                children: RefCell::new(Vec::new())
                            }
                        )
                    );

                    match rule {
                        crate::core::frontend::parser::$edition::Rule::Identifier |
                        crate::core::frontend::parser::$edition::Rule::Float_Literal |
                        crate::core::frontend::parser::$edition::Rule::Integer_Literal =>
                            child.borrow_mut().value = Some(Cow::Borrowed(val)),

                        crate::core::frontend::parser::$edition::Rule::String_Literal => {
                            if do_unescape {
                                // Remove the quotes
                                let s = &val[1..val.len()-1];
                                let s = unescape(&s, line_col.0, line_col.1);
                                let s = catch_parse(&s);
    
                                child.borrow_mut().value = Some(s.clone());
                            } else {
                                child.borrow_mut().value = Some(Cow::Borrowed(val));
                            }
                        },

                        // Ignore boolean literals
                        crate::core::frontend::parser::$edition::Rule::True_Literal |
                        crate::core::frontend::parser::$edition::Rule::False_Literal => {}

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
    };
}