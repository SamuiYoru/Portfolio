executable file
	cadb0068	

Introduction
	要減少verilog檔案中assign和select的次數以優化原先的verilog檔案

Compile
	因為有利用到C++11裡面的指令所以原始的cpp要利用C++11的編譯器來編譯
	g++ -std=c++0x cadb0068.cpp  cadb0068

Use
	將要轉換的original.v和.exe放在同一個資料夾裡面
	./cadb0068 原始檔案名稱.v 新輸出的檔名.v 
	(ex:./cadb0068 original.v optimized.v)

checker
	1.	/bin/tcsh
	2.	/project/cad/cad50/synopsys/CIC/vcs.cshrc
	3.	tcsh
	4.	vcs -sverilog 原始檔案名稱.v -o 輸出執行檔的名稱
		(ex:vcs -sverilog optimized.v -o optimized)
	5.	./輸出執行檔的名稱
		(ex:./optimized)
	6.	diff simorig.txt result.txt
		因為原始的original.v裡面的tb限制了輸出的結果命名會是result.txt，所以是拿result.txt和大會提供的testbench中的simorig.txt做比較

 
    
    