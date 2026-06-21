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
use memchr::memchr;
use crate::adt::error::ParseError;
use crate::adt::lang::ASTValue;
use crate::adt::result::ParseResult;

fn hex_digit(c: char) -> Option<u8> {
    if c >= '0' && c <= '9' {
        Some(c as u8 - '0' as u8)
    } else if c >= 'a' && c <= 'f' {
        Some(c as u8 - 'a' as u8 + 10)
    } else if c >= 'A' && c <= 'F' {
        Some(c as u8 - 'A' as u8 + 10)
    } else {
        None
    }
}

pub fn unescape<'a>(
    s: &'a str,
    line: usize,
    column: usize
) -> ParseResult<'a> {
    let mut result = Vec::<u8>::new();

    let mut slice = s.as_bytes();
    while let Some(idx) = memchr(b'\\', slice) {
        // Append the string before the escape sequence
        result.extend(&slice[0..idx]);

        if idx + 1 >= slice.len() {
            return Err(ParseError::invalid_escape_sequence(line, column));
        }

        // Get the next character
        let sequence = &slice[idx+1..idx+2];
        let sequence = sequence.first().unwrap();
        slice = &slice[idx + 2..];

        match sequence {
            b'n' => result.push('\n' as u8),
            b't' => result.push('\t' as u8),
            b'r' => result.push('\r' as u8),
            b'\\' => result.push('\\' as u8),

            b'X' |
            b'x' => {
                if slice.len() < 2 {
                    return Err(ParseError::invalid_escape_sequence(line, column));
                }

                // Get the next two characters
                let sequence = &slice[0..3];
                let hex_digit_1 = hex_digit(sequence[0] as char).unwrap();
                let hex_digit_2 = hex_digit(sequence[1] as char).unwrap();

                let c = (hex_digit_1 << 4) | hex_digit_2;
                result.push(c);
                slice = &slice[2..]; // Skip the next 2 hex characters
            }

            _ => {}
        }
    }

    // If the slice has the same length as the original, we can return the original string
    if slice.len() == s.len() {
        return Ok(ASTValue::Borrowed(s.as_ref()));
    }

    // Add the rest of the string
    result.extend(slice);
    Ok(ASTValue::Owned(String::from_utf8(result).unwrap()))
}