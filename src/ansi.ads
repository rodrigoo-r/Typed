package Ansi is
   -- ANSI escape codes for terminal formatting
   Escape       : constant String := ASCII.ESC & "[";
   Regular_Tone : constant String := Escape & "3"; -- Default text color
   Bright_Tone  : constant String := Escape & "9"; -- Bright text color

   -- Text colors
   Red    : constant String := Regular_Tone & "1m";
   Green  : constant String := Regular_Tone & "2m";
   Yellow : constant String := Regular_Tone & "3m";
   Blue   : constant String := Regular_Tone & "4m";
   Magenta: constant String := Regular_Tone & "5m";
   Cyan   : constant String := Regular_Tone & "6m";
   White  : constant String := Regular_Tone & "7m";

   -- Bright text colors
   Bright_Red    : constant String := Bright_Tone & "1m";
   Bright_Green  : constant String := Bright_Tone & "2m";
   Bright_Yellow : constant String := Bright_Tone & "3m";
   Bright_Blue   : constant String := Bright_Tone & "4m";
   Bright_Magenta: constant String := Bright_Tone & "5m";
   Bright_Cyan   : constant String := Bright_Tone & "6m";
   Bright_White  : constant String := Bright_Tone & "7m";
   
   -- Text styles
   Bold      : constant String := Escape & "1m";
   Underline : constant String := Escape & "4m";
   Reset     : constant String := Escape & "0m";

end Ansi;