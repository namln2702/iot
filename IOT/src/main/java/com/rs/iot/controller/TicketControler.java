package com.rs.iot.controller;

import com.rs.iot.dao.response.GetSlotInResponse;
import com.rs.iot.dao.response.CheckInResponse;
import com.rs.iot.dao.response.CheckOutResponse;
import com.rs.iot.dao.response.GetSlotOutResponse;
import com.rs.iot.service.TicketService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.Map;

@RestController
@CrossOrigin
@RequestMapping("/inOut")
public class TicketControler {


    @Autowired
    private TicketService ticketService;

    private GetSlotOutResponse getSlotOutResponse ;

    private GetSlotInResponse getSlotInResponse ;

    @PostMapping("/in")
    ResponseEntity<?> checkIn(@RequestBody Map<String, String> requestBody){
        System.out.println(1111);
        String card_code = requestBody.get("card_code");
        System.out.println(card_code);

        CheckInResponse checkIn = ticketService.checkIn(card_code);

        if(checkIn.getCheck() == 1){
            getSlotInResponse = GetSlotInResponse.builder()
                    .check(1)
                    .checkIn(checkIn.getTimeIn())
                    .car_code(checkIn.getCar_code())
                    .build();
        }

        return ResponseEntity.ok().body(checkIn);

    }

    @PostMapping("/out")
    ResponseEntity<?> checkOut(@RequestBody Map<String, String> requestBody){
        String card_code = requestBody.get("card_code");
        CheckOutResponse checkOut = ticketService.checkOut(card_code);

        if(checkOut.getCheck() == 1){
            getSlotOutResponse = GetSlotOutResponse.builder()
                    .check(1)
                    .car_code(checkOut.getCar_code())
                    .checkIn(checkOut.getCheckIn())
                    .checkOut(checkOut.getCheckOut())
                    .build();
        }

        return ResponseEntity.ok().body(checkOut);

    }

    @GetMapping("/getSlotIn")
    ResponseEntity<?> getIn(){
        return ResponseEntity.ok().body(getSlotInResponse);
    }

    @GetMapping("/getSlotOut")
    ResponseEntity<?> getOut(){
        return ResponseEntity.ok().body(getSlotOutResponse);
    }

}
