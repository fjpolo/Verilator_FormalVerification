`ifdef	FORMAL
// Change direction of assumes
`define	ASSERT	assert
`ifdef	APB_SLAVE
`define	ASSUME	assume
`else
`define	ASSUME	assert
`endif

	////////////////////////////////////////////////////
	//
	// f_past_valid register
	//
	////////////////////////////////////////////////////
	reg	f_past_valid;
	initial	f_past_valid = 0;
	always @(posedge i_clk)
		f_past_valid <= 1'b1;

	////////////////////////////////////////////////////
	//
	// Reset
	//
	////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	//
	// BMC
	//
	////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	//
	// Contract
	//
	////////////////////////////////////////////////////   

	//
	// 1. Basic APB Protocol Properties
	// These properties ensure the master and slave adhere to the fundamental APB protocol rules.
	//
	
	// a. Signal Stability During Transfer
	// 	- Property: During a transfer (PSELx is high), the address (PADDR) and control signals 
	//	(PWRITE, PENABLE) must remain stable.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
		if (PSELx) begin
			`ASSUME(PADDR == $past(PADDR));
			`ASSUME(PWRITE == $past(PWRITE));
			`ASSUME(PENABLE == $past(PENABLE));
		end
	end
	
	// b. PENABLE Timing
	// 	-	Property: PENABLE must only be high in the second cycle of a transfer.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
			if ((PSELx)&&(!$past(PENABLE)))
				`ASSUME(PENABLE);
	end

	// c. Transfer Completion
	// 	- Property: After PENABLE is high, the transfer completes, and PSELx and PENABLE must deassert in the next cycle.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
		if (($past(PSELx))&&($past(PENABLE))&&($past(PREADY)))
		`ASSUME((!PSELx)&&(!PENABLE));
	end
	
	//
	// 2. Read/Write Transaction Properties
	// These properties ensure the master and slave handle read and write transactions correctly.
	//
	
	// a. Write Transaction
	// 	- Property: During a write transaction (PWRITE is high), the master must drive PWDATA when PENABLE is high.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
			if (($past(PSELx))&&(PWRITE)&&(!$past(PENABLE))&&(PREADY)) begin
				case(reg_file_addr)
				0: assert(reg_file_0 == $past(PWDATA));
				1: assert(reg_file_1 == $past(PWDATA));
				2: assert(reg_file_2 == $past(PWDATA));
				3: assert(reg_file_3 == $past(PWDATA));
				4: assert(reg_file_4 == $past(PWDATA));
				5: assert(reg_file_5 == $past(PWDATA));
				6: assert(reg_file_6 == $past(PWDATA));
				7: assert(reg_file_7 == $past(PWDATA));
				default: ;
				endcase
			end
	end
	
	// b. Read Transaction
	// 	- Property: During a read transaction (PWRITE is low), the slave must drive PRDATA with the correct data when PENABLE is high.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
		if (($past(PSELx))&&(!PWRITE)&&(!$past(PENABLE))&&(PREADY)) begin
			case(reg_file_addr)
				0: assert(PRDATA == $past(reg_file_0));
				1: assert(PRDATA == $past(reg_file_1));
				2: assert(PRDATA == $past(reg_file_2));
				3: assert(PRDATA == $past(reg_file_3));
				4: assert(PRDATA == $past(reg_file_4));
				5: assert(PRDATA == $past(reg_file_5));
				6: assert(PRDATA == $past(reg_file_6));
				7: assert(PRDATA == $past(reg_file_7));
				default: ;
				endcase
		end
	end

	//
	// 3. Error Handling Properties
	// These properties ensure the master and slave handle error conditions correctly.
	//

	// a. Invalid Address
	// 	- Property: If the address (PADDR) is invalid, the slave should not respond or should signal an error.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
		if (($past(PSELx))&&(PENABLE)&&(!$past(address_is_valid))&&($past(state) == ACCESS))
		assert ((PREADY)&&(PSLVERR));
	end

	//
	// 4. Timing and Performance Properties
	// These properties ensure the master and slave meet timing requirements.
	//

	// // a. PREADY Assertion
	// // 	- Property: The slave must assert PREADY within a specified number of cycles after PSELx is asserted.
	// always @(posedge PCLK) begin
	// if (PSELx) begin
	// 	assert (##[1:MAX_LATENCY] PREADY);
	// end
	// end

	// // b. Back-to-Back Transfers
	// // 	- Property: The master and slave should handle back-to-back transfers without violating the protocol.
	// always @(posedge PCLK) begin
	// if (PSELx && PENABLE) begin
	// 	assert (##1 PSELx && !PENABLE ##1 PSELx && PENABLE);
	// end
	// end

	//
	// 5. Reset Behavior
	// These properties ensure the master and slave behave correctly during and after reset.
	//

	// a. Reset State
	// 	- Property: All outputs should be in a known state during reset.
	always @(posedge i_clk) begin
		if (!$past(i_reset_n))
		assert ((PREADY == 0)&&(PSLVERR == 0)&&(PRDATA == 'h0));
	end
	
	initial assert(reg_file_0 == 'h0);
	initial assert(reg_file_1 == 'h0);
	initial assert(reg_file_2 == 'h0);
	initial assert(reg_file_3 == 'h0);
	initial assert(reg_file_4 == 'h0);
	initial assert(reg_file_5 == 'h0);
	initial assert(reg_file_6 == 'h0);
	initial assert(reg_file_7 == 'h0);
	always @(posedge i_clk) begin
		if (($past(f_past_valid))&&(f_past_valid)&&(!$past(i_reset_n))&&(i_reset_n)) begin
			assert(reg_file_0 == 'h0);
			assert(reg_file_1 == 'h0);
			assert(reg_file_2 == 'h0);
			assert(reg_file_3 == 'h0);
			assert(reg_file_4 == 'h0);
			assert(reg_file_5 == 'h0);
			assert(reg_file_6 == 'h0);
			assert(reg_file_7 == 'h0);
		end
	end

	////////////////////////////////////////////////////
	//
	// Induction
	//
	////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////
	//
	// Cover
	//
	////////////////////////////////////////////////////     

	// Read/Write Transactions
	always @(posedge i_clk) begin
		cover (PSELx && PWRITE && PENABLE); // Write transaction
		cover (PSELx && !PWRITE && PENABLE); // Read transaction
	end

	// Error Conditions
	always @(posedge i_clk)
		cover (PSLVERR); // Slave error


`endif // FORMAL

