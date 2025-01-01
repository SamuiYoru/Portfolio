`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/06 01:51:42
// Design Name: 
// Module Name: final
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


module final(clk, rst, hsync, vsync, vga_r,vga_g, vga_b,keyclk,data,keydata2);
input clk;
input rst;
output hsync, vsync;
output [3:0] vga_r, vga_b, vga_g;
wire pclk;
wire valid;
wire [9:0] h_cnt, v_cnt;
reg [11:0] vga_data;
wire [11:0] rom_dout;
reg [11:0] rom_addr; // 2^14=16384
wire [11:0] rom_dout2;
reg [11:0] rom_addr2;
reg logo_area;
reg logo_area2;
reg [9:0] logo_x, logo_y, next_logo_x,
next_logo_y;
reg W,A,S,D,J;//鍵盤
reg a,b,c,d;//四個邊界控制
reg [9:0] v=10'd83;//圖片亮的位置
reg [9:0] h=10'd163;
reg [9:0] nexth,nextv;

parameter logo_length = 65;
parameter  logo_height = 55;

parameter logo_length2 = 48;
parameter  logo_height2 = 70;

input keyclk;
input data;
reg [3:0] count2;//keyboard計數
output reg [10:0] keydata2=11'b0;

dcm_25M  (
// Clock in ports
.clk_in1(clk), // input clk_in1
// Clock out ports
.clk_out1(pclk), // output clk_out1
// Status and control signals
.reset(rst));
ROM1 (
.clka(pclk), // input wire clka
.addra(rom_addr), // input
.douta(rom_dout)); // output
// module on p14.
ROM2 (
.clka(pclk), // input wire clka
.addra(rom_addr2), // input
.douta(rom_dout2)); // output
// module on p14.

SyncGeneration u2 (
.pclk(pclk),
.reset(rst),
.hSync(hsync),
.vSync(vsync),
.dataValid(valid),
.hDataCnt(h_cnt),
.vDataCnt(v_cnt) );

always@(*)
begin
a=0;
b=0;
c=0;
d=0;
/*
a = ((v_cnt >= 83) & (v_cnt<=398) & (h_cnt >= 163) & (h_cnt <= 238)) ? 1'b1 :1'b0;
b = ((v_cnt >= 323) & (v_cnt<=398) & (h_cnt >= 163) & (h_cnt <= 478)) ? 1'b1 :1'b0;
c = ((v_cnt >= 83) & (v_cnt<=398) & (h_cnt >= 403) & (h_cnt <= 478)) ? 1'b1 :1'b0;
d = ((v_cnt >= 83) & (v_cnt<=158) & (h_cnt >= 163) & (h_cnt <= 478)) ? 1'b1 :1'b0;
*/
end

always@(posedge clk or posedge rst)
if(rst)
begin
h<=10'd163;
v<=10'd83;
end
else
begin
h<=nexth;
v<=nextv;
end

always@(*)//要加入2個變數控制2個障礙物，現在還會直接穿越障礙物
if(rst)
begin
nexth<=10'd163;
nextv<=10'd83;
end
else
if(a)
if(A)
begin
nextv=v;
nexth=h;
end
else if(W==1 && d==0)
begin
nextv<=v-10'd80;
nexth<=h;
end
else if(D==1 && c==0)
begin
nextv<=v;
nexth<=h+10'd80;
end
else if(S==1 && b==0)
begin
nextv<=v+10'd80;
nexth<=h;
end
else
begin
nextv<=v;
nexth<=h;
end

else if(b)
if(S)
begin
nextv<=v;
nexth<=h;
end
else if(W==1 && d==0)
begin
nextv<=v-10'd80;
nexth<=h;
end
else if(D==1 && c==0)
begin
nextv<=v;
nexth<=h+10'd80;
end
else if(A==1 && a==0)
begin
nextv<=v;
nexth<=h-10'd80;
end
else
begin
nextv<=v;
nexth<=h;
end

else if(c)
if(D)
begin
nextv<=v;
nexth<=h;
end
else if(W==1 && d==0)
begin
nextv<=v-10'd80;
nexth<=h;
end
else if(S==1 && b==0)
begin
nextv<=v+10'd80;
nexth<=h;
end
else if(A==1 && a==0)
begin
nextv<=v;
nexth<=h-10'd80;
end
else
begin
nextv<=v;
nexth<=h;
end

else if(d)
if(W)
begin
nextv<=v;
nexth<=h;
end
else if(D==1 && c==0)
begin
nextv<=v;
nexth<=h+10'd80;
end
else if(S==1 && b==0)
begin
nextv<=v+10'd80;
nexth<=h;
end
else if(A==1 && a==0)
begin
nextv<=v;
nexth<=h-10'd80;
end
else
begin
nextv<=v;
nexth<=h;
end

else
if(W)
begin
nextv<=v-10'd80;
nexth<=h;
end
else if(D)
begin
nextv<=v;
nexth<=h+10'd80;
end
else if(S)
begin
nextv<=v+10'd80;
nexth<=h;
end
else if(A)
begin
nextv<=v;
nexth<=h-10'd80;
end


always@(posedge clk or posedge rst)//還未加入圖2 顯示//改
if(rst)
begin
logo_area = ((v_cnt >= 83) & (v_cnt<= 83 + logo_height - 1) & (h_cnt >= 163) & (h_cnt <= 163 + logo_length - 1)) ? 1'b1 :1'b0;
logo_area2 =1'b0;
end
else
begin
logo_area <= ((v_cnt >= v) & (v_cnt<= v + logo_height - 1) & (h_cnt >= h) & (h_cnt <= h + logo_length - 1)) ? 1'b1 :1'b0;
end

always@(*)
case(keydata2[8:1])
8'b00011101://W
begin
W=1;
A=0;
S=0;
D=0;
J=0;
end
8'b00011100://A
begin
W=0;
A=1;
S=0;
D=0;
J=0;
end
8'b00011011://S
begin
W=0;
A=0;
S=1;
D=0;
J=0;
end
8'b00100011://D
begin
W=0;
A=0;
S=0;
D=1;
J=0;
end
8'b00111011://J
begin
W=0;
A=0;
S=0;
D=0;
J=1;
end
endcase

always@(posedge keyclk or posedge rst)//keyboard                                                  ※posedge 改成negedge
        if(rst==0)
            count2<=4'd0;
        else
            case(count2)
                4'd0:begin count2<=count2+4'd1;keydata2[0]<=data; end
                4'd1:begin count2<=count2+4'd1;keydata2[1]<=data; end
                4'd2:begin count2<=count2+4'd1;keydata2[2]<=data; end                 
                4'd3:begin count2<=count2+4'd1;keydata2[3]<=data; end                 
                4'd4:begin count2<=count2+4'd1;keydata2[4]<=data; end                 
                4'd5:begin count2<=count2+4'd1;keydata2[5]<=data; end                
                4'd6:begin count2<=count2+4'd1;keydata2[6]<=data; end                 
                4'd7:begin count2<=count2+4'd1;keydata2[7]<=data; end                 
                4'd8:begin count2<=count2+4'd1;keydata2[8]<=data; end
                4'd9:begin count2<=count2+4'd1;keydata2[9]<=data; end                       
                4'd10:begin count2<=4'd0;keydata2[10]<=data; end 
                default:count2<=4'd0;
            endcase


/*
assign logo_area2 = ((v_cnt >= 83) & (v_cnt
<= 83 + logo_height2 - 1) & (h_cnt >= 243) 
& (h_cnt <= 243 + logo_length2 - 1)) ? 1'b1 :
1'b0;
*/
always @(posedge pclk or posedge rst)
begin: logo_display
if (rst) begin
rom_addr <= 14'd0;
rom_addr2 <= 14'd0;
vga_data <= 12'd0;
end
else begin
if (valid == 1'b1) begin // send data
if (logo_area == 1'b1) begin
rom_addr <= rom_addr +14'd1;
vga_data <= rom_dout;
end
else if(logo_area2 == 1'b1)
begin
rom_addr2 <= rom_addr2 +14'd1;
vga_data <= rom_dout2;
end
else begin
rom_addr <= rom_addr;
rom_addr2 <= rom_addr2;
vga_data <= 12'd0;
if(((((78<=v_cnt) && (v_cnt<= 83)) || ((158 <=v_cnt) && (v_cnt<= 163)) || ((238 <=v_cnt) && (v_cnt<= 243)) || ((318 <=v_cnt) && (v_cnt<= 323)) || ((398 <=v_cnt) && (v_cnt<= 403))) && (158 <=h_cnt) && (483 >=h_cnt)) ||(( ((158 <=h_cnt) && (h_cnt<= 163)) || ((238 <=h_cnt) && (h_cnt<= 243)) || ((318 <=h_cnt)&& (h_cnt<= 323))|| ((398 <=h_cnt) && (h_cnt<= 403)) || ((478 <=h_cnt) && (h_cnt<= 483))) && ((78 <=v_cnt) && (v_cnt<= 403))) )
vga_data <= 12'b111111111111;
else if(((323<=v_cnt) && (v_cnt<= 398)) && ((163 <=h_cnt) && (h_cnt<= 238)) || ((243<=v_cnt) && (v_cnt<= 318)) && ((403 <=h_cnt) && (h_cnt<= 478)))
vga_data <= 12'b1111;
else
vga_data <= 12'd0;
end
end

else begin
vga_data <= 12'h0;
if (v_cnt == 0)
begin
rom_addr <= 14'd0;
rom_addr2 <= 14'd0;
end
else
begin
rom_addr <= rom_addr;
rom_addr2 <= rom_addr2;
end
end
end
end
assign {vga_r,vga_g,vga_b} = vga_data;


endmodule


/*
module final(clk, rst, hsync, vsync, vga_r,vga_g, vga_b);
input clk;
input rst;
output hsync, vsync;
output [3:0] vga_r, vga_b, vga_g;
wire pclk;
wire valid;
wire [9:0] h_cnt, v_cnt;
reg [11:0] vga_data;
reg [11:0] vga_data2;
wire [11:0] rom_dout;
reg [11:0] rom_addr; // 2^14=16384
wire [11:0] rom_dout2;
reg [11:0] rom_addr2;
wire logo_area;
wire logo_area2;
reg [9:0] logo_x, logo_y, next_logo_x,
next_logo_y;

parameter logo_length = 65;
parameter  logo_height = 55;

parameter logo_length2 = 48;
parameter  logo_height2 = 70;

dcm_25M  (
// Clock in ports
.clk_in1(clk), // input clk_in1
// Clock out ports
.clk_out1(pclk), // output clk_out1
// Status and control signals
.reset(rst));
ROM1 (
.clka(pclk), // input wire clka
.addra(rom_addr), // input
.douta(rom_dout)); // output
// module on p14.
ROM2 (
.clka(pclk), // input wire clka
.addra(rom_addr2), // input
.douta(rom_dout2)); // output
// module on p14.

SyncGeneration u2 (
.pclk(pclk),
.reset(rst),
.hSync(hsync),
.vSync(vsync),
.dataValid(valid),
.hDataCnt(h_cnt),
.vDataCnt(v_cnt) );

assign logo_area = ((v_cnt >= 83) & (v_cnt
<= 83 + logo_height - 1) & (h_cnt >= 163) 
& (h_cnt <= 163 + logo_length - 1)) ? 1'b1 :
1'b0;

assign logo_area2 = ((v_cnt >= 83) & (v_cnt
<= 83 + logo_height2 - 1) & (h_cnt >= 243) 
& (h_cnt <= 243 + logo_length2 - 1)) ? 1'b1 :
1'b0;

always @(posedge pclk or posedge rst)
begin: logo_display
if (rst) begin
rom_addr <= 14'd0;
rom_addr2 <= 14'd0;
vga_data <= 12'd0;
end
else begin
if (valid == 1'b1) begin // send data
if (logo_area == 1'b1) begin
rom_addr <= rom_addr +14'd1;
vga_data <= rom_dout;
end
else if(logo_area2 == 1'b1)
begin
rom_addr2 <= rom_addr2 +14'd1;
vga_data <= rom_dout2;
end
else begin
rom_addr <= rom_addr;
rom_addr2 <= rom_addr2;
vga_data <= 12'd0;
if(((((78<=v_cnt) && (v_cnt<= 83)) || ((158 <=v_cnt) && (v_cnt<= 163)) || ((238 <=v_cnt) && (v_cnt<= 243)) || ((318 <=v_cnt) && (v_cnt<= 323)) || ((398 <=v_cnt) && (v_cnt<= 403))) && (158 <=h_cnt) && (483 >=h_cnt)) ||(( ((158 <=h_cnt) && (h_cnt<= 163)) || ((238 <=h_cnt) && (h_cnt<= 243)) || ((318 <=h_cnt)&& (h_cnt<= 323))|| ((398 <=h_cnt) && (h_cnt<= 403)) || ((478 <=h_cnt) && (h_cnt<= 483))) && ((78 <=v_cnt) && (v_cnt<= 403))) )
vga_data <= 12'b111111111111;
else
vga_data <= 12'd0;
end
end

else begin
vga_data <= 12'h000;
if (v_cnt == 0)
begin
rom_addr <= 14'd0;
rom_addr2 <= 14'd0;
end
else
begin
rom_addr <= rom_addr;
rom_addr2 <= rom_addr2;
end
end
end
end
assign {vga_r,vga_g,vga_b} = vga_data;


endmodule

*/