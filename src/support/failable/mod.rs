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
use std::process::exit;
use crate::adt::error::ExecutionError;
use crate::adt::result::RuntimeResult;
use colored::Colorize;
use pest::error::Error;
use pest::iterators::Pairs;
use crate::core::frontend::parser::Rule;

fn print_considerations() {
    println!(
        "{} if you believe this is a mistake, please open an issue at:",
        "[note]".bold().bright_magenta()
    );

    println!(
        "{}",
        "  https://github.com/rodrigoo-r/Typed/issues".bright_cyan()
    );
}

fn print_err_msg(message: &str) {
    println!(
        "{} {}",
        "[error]".bright_red(),
        message
    );
}

fn print_err_base(
    message: &str,
    line: &usize,
    column: &usize
) {
    print_err_msg(message);

    println!(
        "{}  {} {}{}{}",
        "│".bright_black(),
        "└─ at".italic().bright_black(),
        line.to_string().italic().bright_blue(),
        ":".italic().bright_black(),
        column.to_string().italic().bright_magenta()
    );
}

fn print_traceable_err(err: &ExecutionError) {
    print_err_base(&err.message, &err.line, &err.column);

    // Print a white line
    println!();

    print_considerations();
}

fn print_non_traceable_err<T: std::error::Error>(err: T) {
    print_err_msg(err.to_string().as_str());

    println!(
        "{}",
        "└── this exception is not traceable".bright_black()
    );

    print_considerations();
}

pub fn catch<Success>(
    result: &RuntimeResult<Success>
) -> &Success {
    if result.is_err() {
        let result = result.as_ref();
        let err = result.err();

        print_traceable_err(err.unwrap());
        exit(1)
    }

    result.as_ref().unwrap()
}

pub fn catch_pest<'source>(
    result: &'source Result<Pairs<Rule>, Error<Rule>>
) -> &'source Pairs<'source, Rule> {
    let result = result.as_ref();

    if result.is_err() {
        let err = result.err().unwrap();
        let msg = err.to_string();

        print_err_msg("parsing error:");
        println!("{}", msg);

        exit(1)
    }

    result.unwrap()
}

pub fn catch_non_traceable<
    Success,
    T: std::error::Error
>(
    result: &Result<Success, T>
) -> &Success {
    let result = result.as_ref();

    if result.is_err() {
        let err = result.err().unwrap();
        print_non_traceable_err(err);
        exit(1)
    }

    result.unwrap()
}