with Cli.Core;
with Cli.Exceptions;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Exceptions; use Ada.Exceptions;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Typed is
   Path : Unbounded_String;
begin
   Path := To_Unbounded_String (Cli.Core.Process);
   Put_Line ("Path: " & To_String (Path));

exception
   when Cli.Exceptions.No_Arguments =>
      Put_Line ("Error: missing argument.");
   when E : others =>
      Put_Line ("Unexpected error: " & Exception_Message (E));
end Typed;