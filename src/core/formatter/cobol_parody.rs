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
use crate::adt::lang::AST;
use crate::core::frontend::parser::Rule;

fn fmt_depth(depth: usize, res: &mut String) {
    for _ in 0..depth {
        res.push_str("    ");
    }
}

fn fmt_kind(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let kind = children[0].borrow();

    match kind.rule {
        Rule::Integer => {
            res.push_str("INTEGER");
        }

        Rule::Float => {
            res.push_str("REAL");
        }

        Rule::Boolean => {
            res.push_str("BOOLEAN");
        }

        Rule::String => {
            res.push_str("UNBOUNDED-STRING");
        }

        Rule::Dictionary => {
            res.push_str("UNBOUNDED-DICTIONARY");
        }

        Rule::List => {
            res.push_str("UNBOUNDED-ARRAY");
        }

        _ => {}
    }
}

fn fmt_decl_data(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                res.push_str(child.value.as_ref().unwrap().as_ref());
                res.push_str(" IS ");
            }

            Rule::Kind => {
                fmt_kind(&child, res);
            }

            _ => {}
        }
    }
}

fn fmt_proc_args(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    res.push_str("ARGUMENT-DIVISION.\n");
    for child in children {
        let child = child.borrow();
        fmt_depth(1, res);

        fmt_decl_data(&child, res);
        res.push_str(".\n");
    }
}

fn fmt_proc_ret(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let kind = children[0].borrow();

    res.push_str("WHICH RETURNS ");
    fmt_kind(&kind, res);
    res.push_str(".\n");
}

fn fmt_call_args(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let max = children.len() - 1;

    res.push_str("\n");
    fmt_depth(depth, res);
    res.push_str("PROVIDED ARGUMENTS\n");

    for i in 0..=max {
        let child = children[i].borrow();
        fmt_expr(&child, res, depth + 1);

        if i != max {
            res.push_str(" AND");
        }

        res.push_str("\n");
    }
}

fn fmt_call(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    res.push_str("ACTION\n");
    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                fmt_depth(depth + 1, res);
                res.push_str(child.value.as_ref().unwrap().as_ref());
            }

            Rule::Call_Arguments => {
                fmt_call_args(&child, res, depth);
            }

            _ => {}
        }
    }

    fmt_depth(depth, res);
    res.push_str("END-ACTION");
}

fn fmt_arithmetic_op(
    ast: &AST,
    res: &mut String,
    separator: &str,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    res.push_str("\n");

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                res.push_str(child.value.as_ref().unwrap().as_ref());
            }

            Rule::Expression => {
                fmt_expr(&child, res, depth + 1);
                res.push_str("\n");
                fmt_depth(depth, res);
                res.push_str(separator);
                res.push_str(" ");
            }

            _ => {}
        }
    }
}

fn fmt_binary_op(
    ast: &AST,
    res: &mut String,
    separator: &str,
    depth: usize
) {
    let children = ast.children.borrow();
    let lhs = children[0].borrow();
    let rhs = children[1].borrow();

    res.push_str("IS\n");
    fmt_expr(&lhs, res, depth + 1);
    res.push_str("\n");
    fmt_depth(depth, res);
    res.push_str(separator);
    res.push_str("\n");
    fmt_expr(&rhs, res, depth + 1);
}

fn fmt_add(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("ADD");
    fmt_arithmetic_op(ast, res, "TO", depth);
}

fn fmt_sub(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("SUBTRACT");
    fmt_arithmetic_op(ast, res, "FROM", depth);
}

fn fmt_mul(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("MULTIPLY");
    fmt_arithmetic_op(ast, res, "BY", depth);
}

fn fmt_div(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("DIVIDE");
    fmt_arithmetic_op(ast, res, "BY", depth);
}

fn fmt_not(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let child = children[0].borrow();

    res.push_str("IS\n");
    fmt_expr(&child, res, depth + 1);
    res.push_str("\n");
    fmt_depth(depth, res);
    res.push_str("NOT TRUE");
}

fn fmt_expr(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_depth(depth, res);

    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Call => {
                fmt_call(&child, res, depth);
            }

            Rule::Add => {
                fmt_add(&child, res, depth);
            }

            Rule::Subtract => {
                fmt_sub(&child, res, depth);
            }

            Rule::Multiply => {
                fmt_mul(&child, res, depth);
            }

            Rule::Divide => {
                fmt_div(&child, res, depth);
            }

            Rule::True_Literal => {
                res.push_str("TRUE");
            }

            Rule::False_Literal => {
                res.push_str("FALSE");
            }

            Rule::Integer_Literal |
            Rule::String_Literal |
            Rule::Float_Literal => {
                res.push_str(child.value.as_ref().unwrap().as_ref());
            }

            Rule::And => {
                fmt_binary_op(&child, res, "AND", depth);
            }

            Rule::Or => {
                fmt_binary_op(&child, res, "OR", depth);
            }

            Rule::Not => {
                fmt_not(&child, res, depth);
            }

            Rule::Greater => {
                fmt_binary_op(&child, res, "GREATER THAN", depth);
            }

            Rule::Equal => {
                fmt_binary_op(&child, res, "EQUAL TO", depth);
            }

            Rule::Less => {
                fmt_binary_op(&child, res, "LESS THAN", depth);
            }

            Rule::Greater_Equal => {
                fmt_binary_op(&child, res, "GREATER THAN OR EQUAL TO", depth);
            }

            Rule::Less_Equal => {
                fmt_binary_op(&child, res, "LESS THAN OR EQUAL TO", depth);
            }

            Rule::Identifier => {
                res.push_str(child.value.as_ref().unwrap().as_ref());
            }

            _ => {}
        }
    }
}

fn fmt_declare(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    fmt_depth(depth, res);
    res.push_str("DATA ");
    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Declaration_Data => {
                fmt_decl_data(&child, res);
                res.push_str(".\n");
            }

            Rule::Expression => {
                fmt_depth(depth, res);
                res.push_str("SYNERGIZES WITH\n");
                fmt_expr(&child, res, depth + 1);
                res.push_str(".\n");
            }

            _ => {}
        }
    }
}

fn fmt_ret(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let expr = children[0].borrow();

    fmt_depth(depth, res);
    res.push_str("ESCORT\n");
    fmt_expr(&expr, res, depth + 1);
    res.push_str("\n");
    fmt_depth(depth, res);
    res.push_str("TO DATA-DIVISION.\n");
}

fn fmt_for(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    fmt_depth(depth, res);
    res.push_str("PERFORMANCE-IMPROVEMENT-PLAN\n");

    let mut has_start = false;
    let mut has_end = false;

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Declaration_Data => {
                fmt_depth(depth + 1, res);
                fmt_decl_data(&child, res);
                res.push_str("\n");
            }

            Rule::Expression => {
                fmt_depth(depth, res);

                if !has_start {
                    res.push_str("THAT GOES FROM\n");
                    has_start = true;
                } else if !has_end {
                    res.push_str("TO\n");
                    has_end = true;
                } else {
                    res.push_str("WHICH INCREMENTS\n");
                }

                fmt_expr(&child, res, depth + 1);
                res.push_str("\n");
            }

            Rule::Body => {
                fmt_depth(depth, res);
                fmt_body(&child, res, depth + 1);
                fmt_depth(depth + 1, res);
                res.push_str("CIRCLE-BACK.\n");
                fmt_depth(depth, res);
                res.push_str("PERFORMANCE-IMPROVED.\n");
            }

            _ => {}
        }
    }
}

fn fmt_while(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    fmt_depth(depth, res);
    res.push_str("AS LONG AS\n");

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Expression => {
                fmt_expr(&child, res, depth + 1);
                res.push_str("\n");
                fmt_depth(depth, res);
                res.push_str("HOLDS DO\n");
            }

            Rule::Body => {
                fmt_depth(depth, res);
                fmt_body(&child, res, depth + 1);
                fmt_depth(depth + 1, res);
                res.push_str("CIRCLE-BACK.\n");
                fmt_depth(depth, res);
                res.push_str("END-AS-LONG-AS.\n");
            }

            _ => {}
        }
    }
}

fn fmt_conditional(
    ins: &str,
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    res.push_str(ins);
    res.push_str("\n");

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Expression => {
                fmt_expr(&child, res, depth + 1);
                res.push_str("\n");
            }

            Rule::Body => {
                fmt_depth(depth, res);
                fmt_body(&child, res, depth + 1);
                fmt_depth(depth, res);
                res.push_str("END-");
                res.push_str(ins);
                res.push_str(".\n");
            }

            _ => {}
        }
    }
}

fn fmt_else(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    fmt_depth(depth, res);
    res.push_str("FORFEITED\n");

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Body => {
                fmt_depth(depth, res);
                fmt_body(&child, res, depth + 1);
                fmt_depth(depth, res);
                res.push_str("END-FORFEITED.\n");
            }

            _ => {}
        }
    }
}

fn fmt_cond_group(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    fmt_depth(depth, res);
    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::If => {
                fmt_conditional(
                    "TAKE-THIS-OFFLINE",
                    &child,
                    res,
                    depth
                );
            }

            Rule::Else_If => {
                fmt_conditional(
                    "ALSO-OFFLINE",
                    &child,
                    res,
                    depth
                );
            }

            Rule::Else => {
                fmt_else(&child, res, depth);
            }

            _ => {}
        }
    }
}

fn fmt_body(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    res.push_str("WHICH EXECUTES\n");
    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::For => {
                fmt_for(&child, res, depth);
            }

            Rule::Condition_Group => {
                fmt_cond_group(&child, res, depth);
            }

            Rule::While => {
                fmt_while(&child, res, depth);
            }

            Rule::Declare => {
                fmt_declare(&child, res, depth);
            }

            Rule::Return => {
                fmt_ret(&child, res, depth);
            }

            Rule::Expression => {
                fmt_expr(&child, res, depth);
                res.push_str(".\n");
            }

            _ => {}
        }
    }
}

pub fn fmt_proc(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    res.push_str("ACTIONABLE ");

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                res.push_str(child.value.as_ref().unwrap().as_ref());
                res.push_str(" IS DEFINED AS\n");
            }

            Rule::Procedure_Arguments => {
                fmt_proc_args(&child, res);
            }

            Rule::Procedure_Return_Kind => {
                fmt_proc_ret(&child, res);
            }

            Rule::Body => {
                fmt_body(&child, res, 1);
                fmt_depth(1, res);
                res.push_str("STOP-RUN.\n");
            }

            _ => {}
        }
    }
}

pub fn fmt_use(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let child = children[0].borrow();
    let value = child.value.as_ref().unwrap();

    fmt_depth(1, res);
    res.push_str("DEPENDENCY ");
    res.push_str(&value);
    res.push_str(".\n");
}

pub fn format(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    let mut has_dependency_division = false;

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Program => {
                format(&child, res);
            }

            Rule::Use => {
                if !has_dependency_division {
                    res.push_str("DEPENDENCY-DIVISION.\n");
                    has_dependency_division = true;
                }

                fmt_use(&child, res);
            }

            Rule::Procedure => {
                fmt_proc(&child, res);
            }

            _ => {}
        }
    }
}