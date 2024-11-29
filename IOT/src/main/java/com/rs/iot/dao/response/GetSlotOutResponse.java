package com.rs.iot.dao.response;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;


@Builder
@AllArgsConstructor
@NoArgsConstructor
@Data
public class GetSlotOutResponse {
    private int check;
    private String car_code;
    private Date checkIn;
    private Date checkOut;
    private String message;

}
