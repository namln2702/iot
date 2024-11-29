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
public class CheckOutResponse {
    private int check ;
    private Date checkIn;
    private Date checkOut;
    private String car_code;
    private String message;
}
