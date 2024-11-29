package com.rs.iot.dao.response;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Builder
@Data
@AllArgsConstructor
@NoArgsConstructor

public class TempSlotResponse {

    private float temp;
    private float sumSlot;
    private float slot1;
    private float slot2;
    private float slot3;
    private float slot4;


}
