package Ansi is
   type Ansi_Color is new String;
   type Ansi_Style is new String;
   type Ansi_Escape is new String;

   -- ANSI escape codes for terminal formatting
   Escape       : constant Ansi_Escape := ASCII.ESC & "[";
   Regular_Tone : constant Ansi_Escape := Escape & "3"; -- Default text color
   Bright_Tone  : constant Ansi_Escape := Escape & "9"; -- Bright text color

   -- Text colors
   Red    : constant Ansi_Color := Ansi_Color (Regular_Tone & "1m");
   Green  : constant Ansi_Color := Ansi_Color (Regular_Tone & "2m");
   Yellow : constant Ansi_Color := Ansi_Color (Regular_Tone & "3m");
   Blue   : constant Ansi_Color := Ansi_Color (Regular_Tone & "4m");
   Magenta: constant Ansi_Color := Ansi_Color (Regular_Tone & "5m");
   Cyan   : constant Ansi_Color := Ansi_Color (Regular_Tone & "6m");
   White  : constant Ansi_Color := Ansi_Color (Regular_Tone & "7m");

   -- Bright text colors
   Bright_Red    : constant Ansi_Color := Ansi_Color (Bright_Tone & "1m");
   Bright_Green  : constant Ansi_Color := Ansi_Color (Bright_Tone & "2m");
   Bright_Yellow : constant Ansi_Color := Ansi_Color (Bright_Tone & "3m");
   Bright_Blue   : constant Ansi_Color := Ansi_Color (Bright_Tone & "4m");
   Bright_Magenta: constant Ansi_Color := Ansi_Color (Bright_Tone & "5m");
   Bright_Cyan   : constant Ansi_Color := Ansi_Color (Bright_Tone & "6m");
   Bright_White  : constant Ansi_Color := Ansi_Color (Bright_Tone & "7m");
   
   -- Text styles
   Bold      : constant Ansi_Style := Ansi_Style (Escape & "1m");
   Underline : constant Ansi_Style := Ansi_Style (Escape & "4m");
   Reset     : constant Ansi_Style := Ansi_Style (Escape & "0m");

end Ansi;