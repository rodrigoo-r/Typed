use crate::adt::lang::AST;
use crate::core::frontend::parser::Rule;

fn fmt_use(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let literal = children[0].borrow();
    let literal = literal.value.as_ref().unwrap();
    let literal = literal.as_ref();

    res.push_str("import(");
    res.push_str(literal);
    res.push_str(")\n");
}

fn fmt_kind(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let kind = children[0].borrow();

    match kind.rule {
        Rule::Integer => {
            res.push_str("int");
        }

        Rule::Float => {
            res.push_str("real");
        }

        Rule::Boolean => {
            res.push_str("bool");
        }

        Rule::String => {
            res.push_str("str");
        }

        Rule::Dictionary => {
            res.push_str("dict");
        }

        Rule::List => {
            res.push_str("arr");
        }

        _ => {}
    }
}

fn fmt_args(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();
        let children = child.children.borrow();
        let children = children.iter();

        for child in children {
            let child = child.borrow();

            match child.rule {
                Rule::Identifier => {
                    let value = child.value.as_ref().unwrap();
                    res.push_str("    ");
                    res.push_str(&value);
                    res.push_str(": ");
                }

                Rule::Kind => {
                    fmt_kind(&child, res);
                    res.push_str("\n");
                }

                _ => {}
            }
        }
    }
}

fn fmt_depth(depth: usize, res: &mut String) {
    for _ in 0..depth {
        res.push_str("    ");
    }
}

fn fmt_call_args(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let max = children.len() - 1;

    for i in 0..children.len() {
        let child = children[i].borrow();

        fmt_expr(&child, res, 0);

        if i != max {
            res.push_str(", ");
        }
    }
}

fn fmt_call(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                let value = child.value.as_ref().unwrap();
                res.push_str(&value);
                res.push_str("(");
            }

            Rule::Call_Arguments => {
                fmt_call_args(&child, res);
            }

            _ => {}
        }
    }

    res.push_str(")");
}

fn fmt_arithmetic(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                res.push_str(" -> ");

                let value = child.value.as_ref().unwrap();
                res.push_str(&value);
            }

            Rule::Expression => {
                fmt_expr(&child, res, 0);
            }

            _ => {}
        }
    }
}

fn fmt_add(
    ast: &AST,
    res: &mut String
) {
    res.push_str("+ ");
    fmt_arithmetic(ast, res);
}

fn fmt_sub(
    ast: &AST,
    res: &mut String
) {
    res.push_str("- ");
    fmt_arithmetic(ast, res);
}

fn fmt_mul(
    ast: &AST,
    res: &mut String
) {
    res.push_str("* ");
    fmt_arithmetic(ast, res);
}

fn fmt_div(
    ast: &AST,
    res: &mut String
) {
    res.push_str("/ ");
    fmt_arithmetic(ast, res);
}

fn fmt_not(
    ast: &AST,
    res: &mut String
) {
    res.push_str("! ");

    let children = ast.children.borrow();
    let child = children[0].borrow();
    fmt_expr(&child, res, 0);
}

fn fmt_binary_expr(
    ast: &AST,
    res: &mut String,
    op: &str
) {
    let children = ast.children.borrow();
    let lhs = children[0].borrow();
    let rhs = children[1].borrow();

    res.push_str(op);
    res.push_str(" ");
    fmt_expr(&lhs, res, 0);
    res.push_str(" -> ");
    fmt_expr(&rhs, res, 0);
}

fn fmt_equal(
    ast: &AST,
    res: &mut String,
) {
    fmt_binary_expr(ast, res, "==");
}

fn fmt_and(
    ast: &AST,
    res: &mut String,
) {
    fmt_binary_expr(ast, res, "&&");
}

fn fmt_or(
    ast: &AST,
    res: &mut String
) {
    fmt_binary_expr(ast, res, "||");
}

fn fmt_gt(
    ast: &AST,
    res: &mut String
) {
    fmt_binary_expr(ast, res, ">");
}

fn fmt_lt(
    ast: &AST,
    res: &mut String
) {
    fmt_binary_expr(ast, res, "<");
}

fn fmt_gte(
    ast: &AST,
    res: &mut String
) {
    fmt_binary_expr(ast, res, ">=");
}

fn fmt_lte(
    ast: &AST,
    res: &mut String
) {
    fmt_binary_expr(ast, res, "<=");
}

fn fmt_expr(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let expr = children[0].borrow();

    fmt_depth(depth, res);

    match expr.rule {
        Rule::Call => {
            fmt_call(&expr, res);
        }

        Rule::Add => {
            fmt_add(&expr, res);
        }

        Rule::Subtract => {
            fmt_sub(&expr, res);
        }

        Rule::Multiply => {
            fmt_mul(&expr, res);
        }

        Rule::Divide => {
            fmt_div(&expr, res);
        }

        Rule::Not => {
            fmt_not(&expr, res);
        }

        Rule::Equal => {
            fmt_equal(&expr, res);
        }

        Rule::And => {
            fmt_and(&expr, res);
        }

        Rule::Or => {
            fmt_or(&expr, res);
        }

        Rule::Greater => {
            fmt_gt(&expr, res);
        }

        Rule::Greater_Equal => {
            fmt_gte(&expr, res);
        }

        Rule::Less => {
            fmt_lt(&expr, res);
        }

        Rule::Less_Equal => {
            fmt_lte(&expr, res);
        }

        Rule::Identifier |
        Rule::Integer_Literal |
        Rule::Float_Literal => {
            let value = expr.value.as_ref().unwrap();
            res.push_str(value.as_ref());
        }

        Rule::String_Literal => {
            let value = expr.value.as_ref().unwrap();
            res.push_str(&value);
        }

        Rule::True_Literal => {
            res.push_str("true");
        }

        Rule::False_Literal => {
            res.push_str("false");
        }

        _ => {}
    }
}

fn fmt_declaration_data(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                res.push_str(&child.value.as_ref().unwrap());
                res.push_str(": ");
            }

            Rule::Kind => {
                fmt_kind(&child, res);
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
    fmt_depth(depth, res);
    res.push_str("let ");

    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Declaration_Data => {
                fmt_declaration_data(&child, res);
            }

            Rule::Expression => {
                res.push_str(" ->\n");
                fmt_expr(&child, res, depth + 1);
            }

            _ => {}
        }
    }

    res.push_str("\n");
}

fn fmt_return(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_depth(depth, res);
    res.push_str("> ");

    let children = ast.children.borrow();
    let expr = children[0].borrow();

    fmt_expr(&expr, res, 0);
}

fn fmt_for(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    fmt_depth(depth, res);
    res.push_str("loop ");

    let mut has_in = false;
    let mut has_to = false;

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Declaration_Data => {
                fmt_declaration_data(&child, res);
                res.push_str(" -> ");
            }

            Rule::Expression => {
                fmt_depth(depth, res);
                if !has_in {
                    has_in = true;
                } else if !has_to {
                    res.push_str("..");
                    has_to = true;
                } else {
                    res.push_str(" +");
                }

                fmt_expr(&child, res, 0);
            }

            Rule::Body => {
                fmt_body(&child, res, depth + 1);
                fmt_depth(depth, res);
                res.push_str("<=for\n");
            }

            _ => {}
        }
    }
}

fn fmt_condition(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Expression => {
                fmt_expr(&child, res, 0);
            }

            Rule::Body => {
                fmt_body(&child, res, depth + 1);
            }

            _ => {}
        }
    }
}

fn fmt_if(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_depth(depth, res);
    res.push_str("if ");
    fmt_condition(&ast, res, depth);
    fmt_depth(depth, res);
    res.push_str("<=if\n");
}

fn fmt_else_if(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_depth(depth, res);
    res.push_str("elseif ");
    fmt_condition(&ast, res, depth + 1);
    fmt_depth(depth, res);
    res.push_str("End_Else_If\n");
}

fn fmt_else(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_depth(depth, res);
    res.push_str("else");

    let children = ast.children.borrow();
    let body = children[0].borrow();

    fmt_body(&body, res, depth + 1);
    fmt_depth(depth, res);
    res.push_str("<=else\n");
}

fn fmt_condition_group(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::If => {
                fmt_if(&child, res, depth);
            }

            Rule::Else_If => {
                fmt_else_if(&child, res, depth);
            }

            Rule::Else => {
                fmt_else(&child, res, depth);
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
    fmt_depth(depth, res);
    res.push_str("while ");
    fmt_condition(&ast, res, depth + 1);
    fmt_depth(depth, res);
    res.push_str("<=while\n");
}

fn fmt_body(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str(" =>\n");

    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Declare => {
                fmt_declare(&child, res, depth);
            }

            Rule::Return => {
                fmt_return(&child, res, depth);
            }

            Rule::For => {
                fmt_for(&child, res, depth);
            }

            Rule::Condition_Group => {
                fmt_condition_group(&child, res, depth);
            }

            Rule::While => {
                fmt_while(&child, res, depth);
            }

            Rule::Expression => {
                fmt_expr(&child, res, depth);
                res.push_str("\n");
            }

            _ => {}
        }
    }
}

fn fmt_proc(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    res.push_str("proc ");

    for child in children {
        let child = child.borrow();
        let value = child.value.as_ref();

        match child.rule {
            Rule::Identifier => {
                let value = value.unwrap();
                res.push_str(&value);
            }

            Rule::Procedure_Arguments => {
                res.push_str("(\n");
                fmt_args(&child, res);
                res.push_str(")");
            }

            Rule::Procedure_Return_Kind => {
                res.push_str(": ");
                fmt_kind(&child, res);
            }

            Rule::Body => {
                fmt_body(&child, res, 1);
            }

            _ => {}
        }
    }

    res.push_str("<=proc\n");
}

pub fn format(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Program => {
                format(&child, res);
            }

            Rule::Use => {
                fmt_use(&child, res);
            }

            Rule::Procedure => {
                fmt_proc(&child, res);
            }

            _ => {}
        }
    }
}