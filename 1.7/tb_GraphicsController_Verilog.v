`timescale 1ps / 1ps

module tb_GraphicsController_Verilog();

	reg unsigned [15:0] AddressIn;								// CPU 32 bit address bus
	reg unsigned [15:0] DataInFromCPU; 						// 16 bit data bus from CPU

    reg Clk, Reset_L;
    reg AS_L, UDS_L, LDS_L, RW;

    // VGA display driver signals (the circuit actually displaying the contents of the frame buffer)

    reg GraphicsCS_L;	 											// CS from main computer address decoder
    reg VSync_L;														// Vertical sync from VGA controller
    reg unsigned [15:0] SRam_DataIn;							// 16 bit data bus in from Sran
    
    // Sram output signals
    
    wire unsigned [9:0] VScrollValue;  					// scroll value for terminal emulation (allows screen scrolling up/down)
    wire unsigned [9:0] HScrollValue;   				// scroll value for terminal emulation (allows screen scrolling left/right)

    // Data bus back to CPU	
    wire unsigned [15:0] DataOutToCPU;					// 16 bit data bus to CPU

    // Memory output signals
    // Memory holds the graphics image that we see and draw - we have to dri these signals to create the image as part of a state machine
    // Memory is 16 wide, split into 2 x 8 bit halves
    // each location is thus 2 bytes and holds two pixels from our image

    wire unsigned [17:0] Sram_AddressOut;				// graphics controller address out 256k locations = 18 address lines
    wire unsigned [15:0] Sram_DataOut;					// graphics controller Data out
    
    wire Sram_UDS_Out_L; 									// Upper Data Strobe : Drive to '0' if graphics wants to read/write from/to lower byte in memory
    wire Sram_LDS_Out_L; 									// Lower Data Strobe : Drive to '0' if graphics wants to read/write from/to upper byte in memory
    wire Sram_RW_Out;											// Read/Write : Drive to '0' if graphics wants to write or '1' if graphics wants to read											
    
    wire unsigned [5:0] ColourPalletteAddr;			// an address connected to programmable colour pallette (64 colours)
    wire unsigned [23:0] ColourPalletteData;			// 24 bit 00RRGGBB value to write to the colour pallette
    wire ColourPallette_WE_H;								// signal to actually write to colour pallette (data and address must be valid at this time)

    // here are some state numbers associated with some functionality already present in the graphics controller, e.g.
	// writing a pixel, reading a pixel, programming a colour pallette
	//
	// you will be adding new states so make sure you have unique values for each state (no duplicate values)
	// e.g. DrawHLine does not do anything yet - you have add the code to that state to draw a line
	
	parameter Idle	= 8'h00;										// main waiting State
	parameter ProcessCommand = 8'h01;						// State is figure out command
	parameter DrawHLine = 8'h02;			 	 				// State for drawing a Horizontal line
	parameter DrawVline = 8'h03;			 	 				// State for drawing a Vertical line
	parameter DrawLine = 8'h04;				 	 			// State for drawing any line
	parameter DrawPixel = 8'h05;							 	// State for drawing a pixel
	parameter ReadPixel = 8'h06;							 	// State for reading a pixel
	parameter ReadPixel1 = 8'h07;							 	// State for reading a pixel
	parameter ReadPixel2 = 8'h08;							 	// State for reading a pixel
	parameter PalletteReProgram = 8'h09;					// State for programming a pallette colour
	parameter DrawLine1 = 8'h0a;
	parameter DrawLine2 = 8'h0b;
	parameter DrawLine3 = 8'h0c;
	parameter DrawLine4 = 8'h0d;
	parameter DrawLine5 = 8'h0e;
	parameter DrawLine6 = 8'h0f;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Commands values that can be written to command register by CPU to get graphics controller to draw a shape
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	parameter Hline = 16'h0001;							 	// command is draw Horizontal line
	parameter Vline = 16'h0002;								// command is draw Vertical line
	parameter ALine = 16'h0003;								// command is draw any line
	parameter PutPixel = 16'h000a;							// command to draw a pixel
	parameter GetPixel = 16'h000b;							// command to read a pixel
	parameter ProgramPallette = 16'h0010;					// command is program one of the 256 pallettes with a new RGB value
	
    GraphicsController_Verilog dut(.*);

    initial begin
        Clk = 1'b0;
        forever begin
            #5;
            Clk = ~Clk;
        end
    end

    initial begin
        Reset_L = 1'b1;
        #2;
        Reset_L = 1'b0;
        #20;
        Reset_L = 1'b1;

        AS_L = 0;
        RW = 0;
        GraphicsCS_L = 0;
        AddressIn[15:8] = 8'h00;
        UDS_L = 0;
        LDS_L = 0;

        AddressIn[7:1] = 7'b0000_001;
        DataInFromCPU = 100;
        AS_L = 0;
        #20;
        AS_L = 1;
        #20;

        AddressIn[7:1] = 7'b0000_010;
        DataInFromCPU = 100;
        AS_L = 0;
        #20;
        AS_L = 1;
        #20;

        AddressIn[7:1] = 7'b0000_011;
        DataInFromCPU = 150;
        AS_L = 0;
        #20;
        AS_L = 1;
        #20;

        AddressIn[7:1] = 7'b0000_100;
        DataInFromCPU = 150;
        AS_L = 0;
        #20;
        AS_L = 1;
        #20;

        AddressIn[7:1] = 7'b0000_111;
        DataInFromCPU = 2; // RED
        AS_L = 0;
        #20;
        AS_L = 1;
        #20;

        AddressIn[7:1] = 7'b0000_000;
        DataInFromCPU = ALine;
        AS_L = 0;
        #20;
        AS_L = 1;
        #200;

        $stop;
    end

endmodule