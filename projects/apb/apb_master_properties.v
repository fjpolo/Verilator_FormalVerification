`ifdef	FORMAL
// Change direction of assumes
`define	ASSERT	assert
`ifdef	APB_MASTER
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

    // Property: All outputs should be in a known state after reset
    always @(posedge i_clk) begin
        if (!$past(i_reset_n))
            assert ((PADDR == 0)&&(PWDATA == 0)&&(PWRITE == 0)&&(PSELx == 0)&&(PENABLE == 0));
    end

    // Property: After reset, the master and slave should be ready to accept new transactions
    always @(posedge i_clk) begin
        if ($rose(i_reset_n))
          assert (!PSELx && !PENABLE);
    end

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
    //
    // These properties ensure the master and slave adhere to the fundamental APB protocol rules.
    //

    // a. Signal Stability During Transfer
    //  -  Property: During a transfer (PSELx is high), the address (PADDR) and control signals 
    //    (PWRITE, PENABLE) must remain stable.
    always @(posedge i_clk) begin
        if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n)&&($past(state == ACCESS)))
            if (PSELx) begin
                assert (PADDR   == $past(PADDR));
                assert (PSELx   == $past(PSELx));
                assert (PWRITE  == $past(PWRITE));
                assert (PENABLE == $past(PENABLE));
            end
    end

    // b. PENABLE Timing
    //  - Property: PENABLE must only be high in the second cycle of a transfer.
    always @(posedge i_clk) begin
        if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
            if ((PSELx)&&(!$past(PENABLE))&&($past(state == ACCESS)))
                assert (PENABLE);
    end

    // c. Transfer Completion
    //  - Property: After PENABLE is high, the transfer completes, and PSELx and 
    //  PENABLE must deassert in the next cycle.
    always @(posedge i_clk) begin
        if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
            if (($past(PSELx))&&($past(PENABLE))&&($past(PREADY))&&($past(state) == ACCESS))
                assert ((!PSELx)&&!(PENABLE));
    end

    //
    // 2. Read/Write Transaction Properties
    // These properties ensure the master and slave handle read and write transactions correctly.
    //

    // a. Write Transaction
    //  - Property: During a write transaction (PWRITE is high), 
    //  the master must drive PWDATA when PENABLE is high.
    always @(posedge i_clk) begin
        if ((PSELx)&&(PWRITE)&&(PENABLE))
            if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
            assert(PWDATA == $past(PWDATA));
    end   

    // b. Read Transaction
    //  - Property: During a read transaction (PWRITE is low), 
    //  the slave must drive PRDATA with the correct data when 
    //  PENABLE is high.
    always @(posedge i_clk) begin
        if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n)) 
        if (($past(PSELx))&&(!$past(PWRITE))&&($past(PENABLE))&&($past(PREADY))&&($past(state) == ACCESS))
        assert (o_rdata == $past(PRDATA));
    end
    
    //
    // 3. Error Handling Properties
    // These properties ensure the master and slave handle error conditions correctly.
    //

    //
    // 4. Timing and Performance Properties
    // These properties ensure the master and slave meet timing requirements.
    //

    // ToDo: Add functionality and FV
    // // a. PREADY Assertion
    // //  - Property: The slave must assert PREADY within a specified number of 
    // //  cycles after PSELx is asserted.
    // always @(posedge PCLK) begin
    //     if (PSELx)
    //       assert (##[1:MAX_LATENCY] PREADY);
    // end
    
    // ToDo: Add functionality and FV
    // // b. Back-to-Back Transfers
    // //  - Property: The master and slave should handle back-to-back transfers without 
    // //  violating the protocol.
    // always @(posedge PCLK) begin
    //     if ((PSELx)&&(PENABLE))
    //       assert (##1 (PSELx)&&(!PENABLE) ##1 (PSELx)&&(PENABLE));
    // end


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
        cover ((PSELx)&&(PWRITE)&&(PENABLE));   // Write transaction
        cover ((PSELx)&&(!PWRITE)&&(PENABLE));  // Read transaction
    end
            
`endif

