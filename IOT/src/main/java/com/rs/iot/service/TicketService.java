package com.rs.iot.service;

import com.rs.iot.dao.response.GetSlotInResponse;
import com.rs.iot.dao.response.CheckInResponse;
import com.rs.iot.dao.response.CheckOutResponse;

public interface TicketService {
    public CheckInResponse checkIn(String card_code);

    public CheckOutResponse checkOut(String card_code);
    public GetSlotInResponse getSlotInRequest();
}
