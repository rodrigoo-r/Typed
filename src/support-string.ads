package Support.String is

   type View is record
      Data   : access constant String;
      Start  : Positive;
      Length : Natural;
   end record;

   function Slice (S : aliased String; Start : Positive; Length : Natural) return View;
   function To_View (S : View) return View;

end Support.String;