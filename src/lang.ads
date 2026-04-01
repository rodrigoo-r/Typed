with Support.String;

package Lang is

   type Token_Kind is (
      -- Literals
      String_Literal,
      Integer_Literal,
      True_Literal,
      False_Literal,

      -- Arithmetic Operators
      Add,
      Subtract,
      Multiply,
      Divide,

      -- Boolean Operators
      Boolean_And,
      Boolean_Or,
      Boolean_Not,

      -- Comparison Operators
      Equal,
      Not_Equal,
      Less,
      Less_Equal,
      Greater,
      Greater_Equal,

      -- Variable Definitions
      Define,
      As,

      -- Control Flow
      Control_If,
      Control_Else,
      Control_While,
      Control_For,
      Control_Return,
      Control_Break,
      Control_Continue,

      -- Declarations
      Declaration_Procedure,

      -- Instructions
      Instruction_Declare,
      Instruction_Println,
      Instruction_Print,
      Instruction_Call,
      Instruction_Assert,
      Instruction_Exit,

      -- Identifiers
      Identifier
   );

   type Token is record
      Text   : Support.String.View;
      Line   : Positive;
      Column : Positive;
      Kind   : Token_Kind;
   end record;

end Lang;