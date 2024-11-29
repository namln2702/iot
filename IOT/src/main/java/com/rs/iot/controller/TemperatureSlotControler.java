package com.rs.iot.controller;

import com.rs.iot.dao.response.TempSlotResponse;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@RestController
@CrossOrigin
@RequestMapping("/tempSlot")
public class TemperatureSlotControler {

    private float temp = 0;
    private float sumSlot = 0;
    private float slot1 =0;
    private float slot2 = 0;
    private float slot3 = 0;
    private float slot4 = 0;



    @PostMapping
    ResponseEntity<?> receive(@RequestBody Map<String, Float> receiveTempSlot){
        temp = receiveTempSlot.get("temp");
        sumSlot = receiveTempSlot.get("tongViTri");
        slot1 = receiveTempSlot.get("giatri1");
        slot2 = receiveTempSlot.get("giatri2");
        slot3 = receiveTempSlot.get("giatri3");
        slot4 = receiveTempSlot.get("giatri4");




        return ResponseEntity.ok().body("Nhan roi nhe");

    }

    @GetMapping
    ResponseEntity<?> send(){
        return ResponseEntity.ok().body(TempSlotResponse.builder()
                        .sumSlot(sumSlot)
                        .slot1(slot1)
                        .slot2(slot2)
                        .slot3(slot3)
                        .slot4(slot4)
                        .temp(temp)
                .build()
        );
    }




}
