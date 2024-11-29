package com.rs.iot.service;

import com.rs.iot.dao.response.CheckInResponse;
import com.rs.iot.entity.UserSystem;
import org.springframework.http.ResponseEntity;

import java.util.List;

public interface BillService {
    public CheckInResponse  checkInputBill(String card_code);
}
