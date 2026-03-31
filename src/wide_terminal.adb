with Ada.Wide_Text_IO;
with Ada.Text_IO;
with Ansi; use Ansi;

package body Wide_Terminal is

   procedure Set_Color (Color : Ansi.Ansi_Color) is
      use Ada.Text_IO;
   begin
      Put (String (Color));
   end Set_Color;

   procedure Write (Text : Wide_String) is
      use Ada.Wide_Text_IO;
   begin
      Put (Text);
   end Write;

   procedure Write_Line (Text : Wide_String) is
      use Ada.Wide_Text_IO;
   begin
      Put_Line (Text);
   end Write_Line;

   procedure Write_Colored (Prefix : Ansi.Ansi_Color; Text : Wide_String) is
      use Ada.Wide_Text_IO;
   begin
      Set_Color (Prefix);
      Put (Text); -- Reset to default after writing
      Ada.Text_IO.Put (String (Ansi.Reset));
   end Write_Colored;

   procedure Write_Line_Colored (Prefix : Ansi.Ansi_Color; Text : Wide_String) is
      use Ada.Wide_Text_IO;
   begin
      Set_Color (Prefix);
      Put (Text); -- Reset to default after writing
      Ada.Text_IO.Put_Line (String (Ansi.Reset));
   end Write_Line_Colored;

end Wide_Terminal;