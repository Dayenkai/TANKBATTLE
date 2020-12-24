void	Move(TANK *Tank, BODY *Body, MAP *map, char direction)
{

	int	pass = 0;
	BODY	*first_element = Body;
	
	if (direction == 'R')
			{
				//system("clear");
				Erase_Tank(Tank, map, Body, Tank->Previous_Body_Number, 1);
				Body = BODY_Change(Body,1);
				if(Tank->Previous_Body_Number != 1)
					{
						Calculate_new_pos(Tank, map, Body);
						pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y);
					}
				else
					pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y + 1);
				if (pass == 1)
					{
						if (Tank->Previous_Body_Number == 1)
							Tank->pos_y++;
						put_tab_in_map(Tank, map, Body);
						Tank->Previous_Body_Number = 1;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Tank->Previous_Body_Number);
						Tank->pos_x = Tank->new_x;
						Tank->pos_y = Tank->new_y;
						put_tab_in_map(Tank, map, Body);
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
					}
					gotoxy(1,1);
				}
	if (direction == 'L')
			{
				Erase_Tank(Tank, map, Body, Tank->Previous_Body_Number, 3);
				Body = BODY_Change(Body,3);
				if( Tank->Previous_Body_Number != 3)
					{
						Calculate_new_pos(Tank, map, Body);
						pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y);
					}
				else
					pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y - 1);
				if (pass == 1)
					{
						if (Tank->Previous_Body_Number == 3)
							Tank->pos_y--;
						put_tab_in_map(Tank, map, Body);
						Tank->Previous_Body_Number = 3;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Tank->Previous_Body_Number);
						Tank->pos_x = Tank->new_x;
						Tank->pos_y = Tank->new_y;
						put_tab_in_map(Tank, map, Body);
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
					}
				gotoxy(1,1);
			}
	if (direction == 'U')
			{
				Erase_Tank(Tank, map, Body, Tank->Previous_Body_Number, 0);
				if( Tank->Previous_Body_Number != 0)
					{
						Calculate_new_pos(Tank, map, Body);
						pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y);
					}
				else
					pass = pass_or_not(Tank, map, Body, Tank->pos_x - 1, Tank->pos_y);
				if (pass == 1)
					{
						if (Tank->Previous_Body_Number == 0)
							Tank->pos_x--;
						put_tab_in_map(Tank, map, Body);
						Tank->Previous_Body_Number = 0;
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Tank->Previous_Body_Number);
						Tank->pos_x = Tank->new_x;
						Tank->pos_y = Tank->new_y;
						put_tab_in_map(Tank, map, Body);
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
					}
				gotoxy(1,1);
			}
	if (direction == 'D')
			{
				Erase_Tank(Tank, map, Body, Tank->Previous_Body_Number, 2);
				Body = BODY_Change(Body,2);
				if( Tank->Previous_Body_Number != 2)
					{
						Calculate_new_pos(Tank, map, Body);
						pass = pass_or_not(Tank, map, Body, Tank->pos_x, Tank->pos_y);
					}
				else
					pass = pass_or_not(Tank, map, Body, Tank->pos_x + 1, Tank->pos_y);
				if (pass == 1)
					{
						if(Tank->Previous_Body_Number == 2)
							Tank->pos_x++;
						put_tab_in_map(Tank, map, Body);
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
						Tank->Previous_Body_Number = 2;
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Tank->Previous_Body_Number);
						Tank->pos_x = Tank->new_x;
						Tank->pos_y = Tank->new_y;
						put_tab_in_map(Tank, map, Body);
						print_tank_on_screen(Body, Tank, Tank->pos_x, Tank->pos_y);
					}
				gotoxy(1,1);
			}

}

/*if (key == 108)
			Move(&Player, first_element, map, 'R');
		if (key == 107)
			Move(&Player, first_element, map, 'D');*/
			/*{
				//system("clear");
				Erase_Tank(&Player, map, Body, Player.Previous_Body_Number, 1);
				Body = BODY_Change(Body,1);
				if( Player.Previous_Body_Number != 1)
					{
						Calculate_new_pos(&Player, map, Body);
						pass = pass_or_not(&Player, map, Body, Player.pos_x, Player.pos_y);
					}
				else
					pass = pass_or_not(&Player, map, Body, Player.pos_x, Player.pos_y + 1);
				if (pass == 1)
					{
						if (Player.Previous_Body_Number == 1)
							Player.pos_y++;
						put_tab_in_map(&Player, map, Body);
						Player.Previous_Body_Number = 1;
						print_tank_on_screen(Body, &Player, Player.pos_x, Player.pos_y);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Player.Previous_Body_Number);
						Player.pos_x = Player.new_x;
						Player.pos_y = Player.new_y;
						put_tab_in_map(&Player, map, Body);
						print_tank_on_screen(Body, &Player, Player.pos_x, Player.pos_y);
					}
				gotoxy(1,1);
			}
		if (key == 106)
			{
				Erase_Tank(&Player, map, Body, Player.Previous_Body_Number, 3);
				Body = BODY_Change(Body,3);
				if( Player.Previous_Body_Number != 3)
					{
						Calculate_new_pos(&Player, map, Body);
						pass = pass_or_not(&Player, map, Body, Player.pos_x, Player.pos_y);
					}
				else
					pass = pass_or_not(&Player, map, Body, Player.pos_x, Player.pos_y - 1);
				if (pass == 1)
					{
						if (Player.Previous_Body_Number == 3)
							Player.pos_y--;
						put_tab_in_map(&Player, map, Body);
						Player.Previous_Body_Number = 3;
						print_tank_on_screen(Body, &Player, Player.pos_x, Player.pos_y);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Player.Previous_Body_Number);
						Player.pos_x = Player.new_x;
						Player.pos_y = Player.new_y;
						put_tab_in_map(&Player, map, Body);
						print_tank_on_screen(Body, &Player, Player.pos_x, Player.pos_y);
					}
				gotoxy(1,1);
			}
		if (key == 105)
			{
				Erase_Tank(&Player, map, Body, Player.Previous_Body_Number, 0);
				if( Player.Previous_Body_Number != 0)
					{
						Calculate_new_pos(&Player, map, Body);
						pass = pass_or_not(&Player, map, Body, Player.pos_x, Player.pos_y);
					}
				else
					pass = pass_or_not(&Player, map, Body, Player.pos_x - 1, Player.pos_y);
				if (pass == 1)
					{
						if (Player.Previous_Body_Number == 0)
							Player.pos_x--;
						put_tab_in_map(&Player, map, Body);
						Player.Previous_Body_Number = 0;
						print_tank_on_screen(Body, &Player, Player.pos_x, Player.pos_y);
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Player.Previous_Body_Number);
						Player.pos_x = Player.new_x;
						Player.pos_y = Player.new_y;
						put_tab_in_map(&Player, map, Body);
						print_tank_on_screen(Body, &Player, Player.pos_x, Player.pos_y);
					}
				gotoxy(1,1);
			}
		if (key == 107)
			{
				Erase_Tank(&Player, map, Body, Player.Previous_Body_Number, 2);
				Body = BODY_Change(Body,2);
				if( Player.Previous_Body_Number != 2)
					{
						Calculate_new_pos(&Player, map, Body);
						pass = pass_or_not(&Player, map, Body, Player.pos_x, Player.pos_y);
					}
				else
					pass = pass_or_not(&Player, map, Body, Player.pos_x + 1, Player.pos_y);
				if (pass == 1)
					{
						if(Player.Previous_Body_Number == 2)
							Player.pos_x++;
						put_tab_in_map(&Player, map, Body);
						print_tank_on_screen(Body, &Player, Player.pos_x, Player.pos_y);
						Player.Previous_Body_Number = 2;
					}
				else
					{
						Body = first_element;
						Body = BODY_Change(Body,Player.Previous_Body_Number);
						Player.pos_x = Player.new_x;
						Player.pos_y = Player.new_y;
						put_tab_in_map(&Player, map, Body);
						print_tank_on_screen(Body, &Player, Player.pos_x, Player.pos_y);
					}
				gotoxy(1,1);
			}*/
