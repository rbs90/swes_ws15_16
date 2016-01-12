with Ada.Streams.Stream_IO;
with Ada.Text_IO;
with GNAT.Sockets;  use GNAT.Sockets;

procedure File_Read is
   type SixteenBit is mod 2**16;
   DoubleByte : SixteenBit;
   Random_File : Ada.Streams.Stream_IO.File_Type;
   X : integer;

   Client  : Socket_Type;
   Address : Sock_Addr_Type;
   Channel : Stream_Access; 
begin
	x := 0;
	Ada.Streams.Stream_IO.Open (File => Random_File,
                               Mode => Ada.Streams.Stream_IO.In_File,
				               Name => "/dev/random");

	Create_Socket (Client);
    Address.Addr := Inet_Addr("127.0.0.1");
    Address.Port := 20001;
	Connect_Socket (Client, Address);
	Channel := Stream (Client);

	While_Loop :
	    while X <= 10 loop
			X := X + 1;
		    SixteenBit'Read (Ada.Streams.Stream_IO.Stream (Random_File), DoubleByte);
		    --Ada.Text_IO.Put_Line ("Number:" & Integer'image(SixteenBit'Pos(DoubleByte)));
			Ada.Text_IO.Put_Line ("Number:" & SixteenBit'image(DoubleByte));
			SixteenBit'Write (Channel, DoubleByte);
		    delay Duration(1);
	    end loop While_Loop;
	Ada.Streams.Stream_IO.Close (Random_File);
	Close_Socket (Client);      

end File_Read;
