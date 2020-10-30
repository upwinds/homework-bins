`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/28 20:47:13
// Design Name: 
// Module Name: machine
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


`timescale 1ns / 1ps
module led_module(
    input [4:0] NUM,
    output reg [7:0] a_to_g
    );

always @(*) 
            case(NUM)
            0:a_to_g=8'b11111100;
            1:a_to_g=8'b01100000;
            2:a_to_g=8'b11011010;
            3:a_to_g=8'b11110010;
            4:a_to_g=8'b01100110;
            5:a_to_g=8'b10110110;
            6:a_to_g=8'b10111110;
            7:a_to_g=8'b11100000;
            8:a_to_g=8'b11111110;
            9:a_to_g=8'b11110110;
            'hF: a_to_g=8'b10001110;
            'hC: a_to_g=8'b10011100;
            20:a_to_g=8'b11111101;
            21:a_to_g=8'b01100001;
            22:a_to_g=8'b11011011;
            23:a_to_g=8'b11110011;
            24:a_to_g=8'b01100111;
            25:a_to_g=8'b10110111;
            26:a_to_g=8'b10111111;
            27:a_to_g=8'b11100001;
            28:a_to_g=8'b11111111;
            29:a_to_g=8'b11110111;
    
            
            default: a_to_g=8'b10001110; 
        endcase 
endmodule



module machine(
    input clk,
    input coin_half,
    input coin_one,
    input sell_cola,
    input sell_milk,
    input sell_tea,
    input full_stock,
    (* clock_buffer_type="none" *)input account,
	 output reg cola_out,
	 output reg tea_out,
	 output reg milk_out,
    input coin_return,
    output [3:0]an,
    output [3:0]bn,
    output [7:0]a_to_g,
    output [7:0]a_to_g2
	
    );	
	reg [32:0]clk_cnt;                     //clock count
	reg [3:0] t_led_bits ;
	reg [3:0] t_led_bits2 ;
	reg [4:0]NUM;                         //number printed on the segment LEDs
	reg [4:0]NUM2; 
	wire [1:0]s ;
	wire q;
	reg [15:0]stock;
	reg [3:0]stock_cola;
	reg [3:0]stock_milk;
	reg [3:0]stock_tea;
	reg [15:0]total_money;
	reg [15:0]display;
	reg [15:0]display2;
	reg timer;
	reg [26:0]timer_cnt;
	
	reg not_spark;
	
	initial
		begin
		    stock='hC555;
		    display2=stock;
			stock_cola = 5;
			stock_milk = 5;
			stock_tea = 5;
			not_spark = 0;
			total_money = 0;
			clk_cnt = 0;
			timer = 0;
			timer_cnt = 0;
			display = 0;
		end
	
	always @(posedge clk )         //deal the clock and clear events
	begin
		if(timer==0)
			timer_cnt = 0;
		if (timer==1 && account == 1)
		begin
			timer_cnt = 0;
			timer_cnt = timer_cnt - 1;
		end
		clk_cnt = clk_cnt +1;                     //if clock flip, count clock 
			if(clk_cnt[32:29]>15)                    //if count was full, back to zero
			 clk_cnt = 0; 
		if(timer_cnt != 0)
			timer_cnt = timer_cnt - 1;
	end 

	
	always @(posedge account)
		begin
			timer = 0;
			if(coin_one)
				total_money[7:4] = total_money[7:4] + 1;
				if(total_money[3:0]>9)
				begin
					total_money[3:0] = total_money[3:0] - 10;
					total_money[7:4] = total_money[7:4] + 1;
				end
				if(total_money[7:4]>9)
				begin
					total_money[7:4] = total_money[7:4] - 10;
					total_money[11:8] = total_money[11:8] + 1;
				end
				if(total_money[11:8]>9)
				begin
					total_money[11:8] = total_money[11:8] - 10;
					total_money[15:12] = total_money[15:12] + 1;
				end				
				display = total_money;
				not_spark = 1;
				cola_out = 0;
				tea_out = 0;
				milk_out = 0;
			if(coin_half)
				total_money[3:0] = total_money[3:0] + 5;
				if(total_money[3:0]>9)
				begin
					total_money[3:0] = total_money[3:0] - 10;
					total_money[7:4] = total_money[7:4] + 1;
				end
				if(total_money[7:4]>9)
				begin
					total_money[7:4] = total_money[7:4] - 10;
					total_money[11:8] = total_money[11:8] + 1;
				end
				if(total_money[11:8]>9)
				begin
					total_money[11:8] = total_money[11:8] - 10;
					total_money[15:12] = total_money[15:12] + 1;
				end								
				display = total_money;
				not_spark = 1;
				cola_out = 0;
				tea_out = 0;
				milk_out = 0;		
			if(full_stock)
				begin
				    stock='hC555;
				    display2=stock;
					stock_cola = 5;
					stock_tea = 5;
					stock_milk = 5;
					display = total_money;
					not_spark = 1;
					cola_out = 0;
					tea_out = 0;
					milk_out = 0;
				end
			if(coin_return)
				begin
					display = total_money;
					total_money = 0;
					not_spark = 0;
					cola_out = 0;
					tea_out = 0;
					milk_out = 0;
				end
			if(sell_cola)
				begin
					if(stock_cola == 0)
					begin
						display = 'hFFFF;
						not_spark = 1;
						cola_out = 0;
						tea_out = 0;
						milk_out = 0;
					end
					else if(total_money < 'h0020)
					begin
						display = 'hCC20;
						not_spark = 0;
						timer = 1;
						cola_out = 0;
						tea_out = 0;
						milk_out = 0;					
					end
					else
					begin
					total_money[7:4] = total_money[7:4] - 2;
					
					
					if(total_money[3:0]>9)
					begin
						total_money[3:0] = total_money[3:0] - 6;
						total_money[7:4] = total_money[7:4] - 1;
					end
					if(total_money[7:4]>9)
					begin
						total_money[7:4] = total_money[7:4] - 6;
						total_money[11:8] = total_money[11:8] - 1;
					end
					if(total_money[11:8]>9)
					begin
						total_money[11:8] = total_money[11:8] - 6;
						total_money[15:12] = total_money[15:12] - 1;
					end									
					if(total_money[15:12]>9)
						total_money[15:12] = total_money[15:12] - 6;					
					
					
					stock[3:0]=stock[3:0]-1;
					display2 = stock;
					stock_cola = stock_cola - 1;
					display = total_money;
					not_spark = 1;
					cola_out = 1;
					end
				end
			if(sell_tea)
				begin
					if(stock_tea == 0)
					begin
						display = 'hFFFF;
						not_spark = 1;
						cola_out = 0;
						tea_out = 0;
						milk_out = 0;						
					end
					else if(total_money < 'h0030)
						begin
						display = 'hCC30;
						not_spark = 0;
						timer = 1;
						cola_out = 0;
						tea_out = 0;
						milk_out = 0;						
						end
					else
					begin
					total_money[7:4] = total_money[7:4] - 3;
					
					
					if(total_money[3:0]>9)
					begin
						total_money[3:0] = total_money[3:0] - 6;
						total_money[7:4] = total_money[7:4] - 1;
					end
					if(total_money[7:4]>9)
					begin
						total_money[7:4] = total_money[7:4] - 6;
						total_money[11:8] = total_money[11:8] - 1;
					end
					if(total_money[11:8]>9)
					begin
						total_money[11:8] = total_money[11:8] - 6;
						total_money[15:12] = total_money[15:12] - 1;
					end					
					if(total_money[15:12]>9)
						total_money[15:12] = total_money[15:12] - 6;
					
					stock[7:4]=stock[7:4]-1;
                    display2 = stock;
					stock_tea = stock_tea - 1;
					display = total_money;
					not_spark = 1;
					tea_out = 1;
					end
				end
			if(sell_milk)
				begin
					if(stock_milk == 0)
					begin
						display = 'hFFFF;
						not_spark = 1;
						cola_out = 0;
						tea_out = 0;
						milk_out = 0;						
					end
					else if(total_money < 'h0035)
						begin
						display = 'hCC35;
						not_spark = 0;
						timer = 1;
						cola_out = 0;
						tea_out = 0;
						milk_out = 0;						
						end
					else
					begin
					total_money[3:0] = total_money[3:0] - 5;
					
					
					if(total_money[3:0]>9)
					begin
						total_money[3:0] = total_money[3:0] - 6;
						total_money[7:4] = total_money[7:4] - 1;
					end
					if(total_money[7:4]>9)
					begin
						total_money[7:4] = total_money[7:4] - 6;
						total_money[11:8] = total_money[11:8] - 1;
					end
					if(total_money[11:8]>9)
					begin
						total_money[11:8] = total_money[11:8] - 6;
						total_money[15:12] = total_money[15:12] - 1;
					end					
					if(total_money[15:12]>9)
						total_money[15:12] = total_money[15:12] - 6;					
					
					total_money[7:4] = total_money[7:4] - 3;
					
					
					if(total_money[3:0]>9)
					begin
						total_money[3:0] = total_money[3:0] - 6;
						total_money[7:4] = total_money[7:4] - 1;
					end
					if(total_money[7:4]>9)
					begin
						total_money[7:4] = total_money[7:4] - 6;
						total_money[11:8] = total_money[11:8] - 1;
					end
					if(total_money[11:8]>9)
					begin
						total_money[11:8] = total_money[11:8] - 6;
						total_money[15:12] = total_money[15:12] - 1;
					end					
					if(total_money[15:12]>9)
						total_money[15:12] = total_money[15:12] - 6;						
					
				    stock[11:8]=stock[11:8]-1;
                    display2 = stock;
					stock_milk = stock_milk - 1;
					display = total_money;
					not_spark = 1;
					milk_out = 1;
					end
				end			
		end
		
	assign s[1:0] = clk_cnt[16:15];         

    assign an = t_led_bits ;
    assign bn = t_led_bits2 ;
	always @(*) 
		case(s[1:0])                         
				2'b00: begin NUM = display[3:0];t_led_bits = 4'b0001;end 
                2'b01: if(display[7:4]=='hF)
                                            begin 
                                            NUM = display[7:4];
                                            t_led_bits = 4'b0010;
                                            end
                                            else
                                            begin
                                            NUM = display[7:4]+20;t_led_bits = 4'b0010;
                                            end
                2'b10: begin NUM = display[11:8];t_led_bits = 4'b0100;end
                2'b11: begin NUM = display[15:12];t_led_bits = 4'b1000;end

		endcase

always @(*) 
		case(s[1:0])                         
				2'b00: begin NUM2 = display2[7:4];t_led_bits2 = 4'b0001;end 
                2'b01: begin NUM2 = display2[11:8];t_led_bits2 = 4'b0010;end
                2'b10: begin NUM2 = display2[3:0];t_led_bits2 = 4'b0100;end
                2'b11: begin NUM2 = display2[15:12];t_led_bits2 = 4'b1000;end
             
		endcase


	led_module  A1(.NUM(NUM),.a_to_g(a_to_g));
    led_module  A2(.NUM(NUM2),.a_to_g(a_to_g2));