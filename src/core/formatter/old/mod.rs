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

    res.push_str("Use ");
    res.push_str(literal);
    res.push_str(";\n");
}

fn fmt_kind(
    ast: &AST,
    res: &mut String
) {
    let children = ast.children.borrow();
    let kind = children[0].borrow();

    match kind.rule {
        Rule::Integer => {
            res.push_str("Integer");
        }

        Rule::Float => {
            res.push_str("Float");
        }

        Rule::Boolean => {
            res.push_str("Boolean");
        }

        Rule::String => {
            res.push_str("String");
        }

        Rule::Dictionary => {
            res.push_str("Dictionary");
        }

        Rule::List => {
            res.push_str("List");
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
                    res.push_str(" as ");
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
    res: &mut String,
    depth: usize
) {
    res.push_str("With\n");

    let children = ast.children.borrow();
    let max = children.len() - 1;

    for i in 0..children.len() {
        let child = children[i].borrow();

        fmt_expr(&child, res, depth);

        if i != max {
            res.push_str(",\n");
        } else {
            res.push_str("\n");
            fmt_depth(depth - 1, res);
        }
    }
}

fn fmt_call(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("Call\n");

    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                fmt_depth(depth + 1, res);
                let value = child.value.as_ref().unwrap();
                res.push_str(&value);
                res.push_str("\n");
                fmt_depth(depth, res);
            }

            Rule::Call_Arguments => {
                fmt_call_args(&child, res, depth + 1);
            }

            _ => {}
        }
    }

    res.push_str("End_Call");
}

fn fmt_arithmetic(
    ast: &AST,
    res: &mut String,
    dst_keyword: &str,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                fmt_depth(depth, res);
                res.push_str(dst_keyword);
                res.push_str(" ");

                let value = child.value.as_ref().unwrap();
                res.push_str(&value);
            }

            Rule::Expression => {
                fmt_expr(&child, res, depth + 1);
                res.push_str("\n");
            }

            _ => {}
        }
    }
}

fn fmt_add(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("Add\n");
    fmt_arithmetic(ast, res, "To", depth);
}

fn fmt_sub(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("Subtract\n");
    fmt_arithmetic(ast, res, "From", depth);
}

fn fmt_mul(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("Multiply\n");
    fmt_arithmetic(ast, res, "By", depth);
}

fn fmt_div(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("Divide\n");
    fmt_arithmetic(ast, res, "By", depth);
}

fn fmt_not(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    res.push_str("Not(\n");

    let children = ast.children.borrow();
    let child = children[0].borrow();
    fmt_expr(&child, res, depth + 1);

    res.push_str("\n");
    fmt_depth(depth, res);
    res.push_str(")");
}

fn fmt_binary_expr(
    ast: &AST,
    res: &mut String,
    separator: &str,
    depth: usize
) {
    let children = ast.children.borrow();
    let lhs = children[0].borrow();
    let rhs = children[1].borrow();

    res.push_str("(\n");
    fmt_expr(&lhs, res, depth + 1);
    res.push_str("\n");
    fmt_depth(depth, res);
    res.push_str(") ");

    res.push_str(separator);

    res.push_str(" (\n");
    fmt_expr(&rhs, res, depth + 1);
    res.push_str("\n");
    fmt_depth(depth, res);
    res.push_str(")");
}

fn fmt_equal(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_binary_expr(ast, res, "=", depth);
}

fn fmt_and(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_binary_expr(ast, res, "And", depth);
}

fn fmt_or(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_binary_expr(ast, res, "Or", depth);
}

fn fmt_gt(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_binary_expr(ast, res, ">", depth);
}

fn fmt_lt(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_binary_expr(ast, res, "<", depth);
}

fn fmt_gte(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_binary_expr(ast, res, ">=", depth);
}

fn fmt_lte(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_binary_expr(ast, res, "<=", depth);
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
            fmt_call(&expr, res, depth);
        }

        Rule::Add => {
            fmt_add(&expr, res, depth);
        }

        Rule::Subtract => {
            fmt_sub(&expr, res, depth);
        }

        Rule::Multiply => {
            fmt_mul(&expr, res, depth);
        }

        Rule::Divide => {
            fmt_div(&expr, res, depth);
        }

        Rule::Not => {
            fmt_not(&expr, res, depth);
        }

        Rule::Equal => {
            fmt_equal(&expr, res, depth);
        }

        Rule::And => {
            fmt_and(&expr, res, depth);
        }

        Rule::Or => {
            fmt_or(&expr, res, depth);
        }

        Rule::Greater => {
            fmt_gt(&expr, res, depth);
        }

        Rule::Greater_Equal => {
            fmt_gte(&expr, res, depth);
        }

        Rule::Less => {
            fmt_lt(&expr, res, depth);
        }

        Rule::Less_Equal => {
            fmt_lte(&expr, res, depth);
        }

        Rule::Identifier |
        Rule::Integer_Literal |
        Rule::Float_Literal => {
            let value = expr.value.as_ref().unwrap();
            res.push_str(value.as_ref());
        }

        Rule::String_Literal => {
            let value = expr.value.as_ref().unwrap();
            let is_multi_line = value.contains("\n");

            if is_multi_line {
                res.push_str("`");
            } else {
                res.push_str("\"");
            }

            res.push_str(&value);

            if is_multi_line {
                res.push_str("`");
            } else {
                res.push_str("\"");
            }
        }

        Rule::True_Literal => {
            res.push_str("True");
        }

        Rule::False_Literal => {
            res.push_str("False");
        }

        _ => {}
    }
}

fn fmt_declaration_data(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Identifier => {
                fmt_depth(depth + 1, res);
                res.push_str(&child.value.as_ref().unwrap());
                res.push_str(" as ");
            }

            Rule::Kind => {
                fmt_kind(&child, res);
                res.push_str("\n");
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
    res.push_str("Declare\n");

    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Declaration_Data => {
                fmt_declaration_data(&child, res, depth);
            }

            Rule::Expression => {
                fmt_depth(depth, res);
                res.push_str("With\n");
                fmt_expr(&child, res, depth + 1);
                res.push_str("\n");
            }

            _ => {}
        }
    }

    fmt_depth(depth, res);
    res.push_str(";\n");
}

fn fmt_return(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_depth(depth, res);
    res.push_str("Return\n");

    let children = ast.children.borrow();
    let expr = children[0].borrow();

    fmt_expr(&expr, res, depth + 1);
    res.push_str("\n");
    fmt_depth(depth, res);
    res.push_str(";\n");
}

fn fmt_for(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    fmt_depth(depth, res);
    res.push_str("For\n");

    let mut has_in = false;
    let mut has_to = false;

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Declaration_Data => {
                fmt_declaration_data(&child, res, depth);
            }

            Rule::Expression => {
                fmt_depth(depth, res);
                if !has_in {
                    res.push_str("In\n");
                    has_in = true;
                } else if !has_to {
                    res.push_str("To\n");
                    has_to = true;
                } else {
                    res.push_str("Step\n");
                }

                fmt_expr(&child, res, depth + 1);
                res.push_str("\n");
            }

            Rule::Body => {
                fmt_depth(depth, res);
                res.push_str("Do\n");
                fmt_body(&child, res, depth + 1);
                fmt_depth(depth, res);
                res.push_str("End_For\n");
            }

            _ => {}
        }
    }
}

fn fmt_condition(
    ast: &AST,
    res: &mut String,
    separator: &str,
    depth: usize
) {
    let children = ast.children.borrow();
    let children = children.iter();

    for child in children {
        let child = child.borrow();

        match child.rule {
            Rule::Expression => {
                fmt_expr(&child, res, depth);
                res.push_str("\n");
            }

            Rule::Body => {
                fmt_depth(depth - 1, res);
                res.push_str(separator);
                res.push_str("\n");
                fmt_body(&child, res, depth);
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
    res.push_str("If\n");
    fmt_condition(&ast, res, "Then", depth + 1);
    fmt_depth(depth, res);
    res.push_str("End_If\n");
}

fn fmt_else_if(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_depth(depth, res);
    res.push_str("Else_If\n");
    fmt_condition(&ast, res, "Then", depth + 1);
    fmt_depth(depth, res);
    res.push_str("End_Else_If\n");
}

fn fmt_else(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_depth(depth, res);
    res.push_str("Else Then\n");

    let children = ast.children.borrow();
    let body = children[0].borrow();

    fmt_body(&body, res, depth + 1);
    fmt_depth(depth, res);
    res.push_str("End_Else\n");
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
    res.push_str("While\n");
    fmt_condition(&ast, res, "Do", depth + 1);
    fmt_depth(depth, res);
    res.push_str("End_While\n");
}

fn fmt_body(
    ast: &AST,
    res: &mut String,
    depth: usize
) {
    fmt_depth(depth - 1, res);
    res.push_str("Begin\n");

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
                res.push_str(";\n");
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

    res.push_str("Procedure ");

    for child in children {
        let child = child.borrow();
        let value = child.value.as_ref();

        match child.rule {
            Rule::Identifier => {
                let value = value.unwrap();
                res.push_str(&value);
                res.push_str("\n");
            }

            Rule::Procedure_Arguments => {
                res.push_str("With Arguments\n");
                fmt_args(&child, res);
            }

            Rule::Procedure_Return_Kind => {
                res.push_str("Returns ");
                fmt_kind(&child, res);
                res.push_str("\n");
            }

            Rule::Body => {
                fmt_body(&child, res, 1);
            }

            _ => {}
        }
    }

    res.push_str("End_Procedure\n");
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