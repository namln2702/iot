package com.rs.iot.dao.response;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class GetSlotInResponse {

    private int check;
    private String message;
    private String car_code;
    private Date checkIn;
}
