package com.rs.iot.service.Impl;

import com.rs.iot.dao.response.GetSlotInResponse;
import com.rs.iot.dao.response.CheckInResponse;
import com.rs.iot.dao.response.CheckOutResponse;
import com.rs.iot.entity.Bill;
import com.rs.iot.entity.Ticket;
import com.rs.iot.repository.repositoryBill;
import com.rs.iot.repository.repositoryTicket;
import com.rs.iot.service.TicketService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Date;


@Service
public class TicketServiceImpl implements TicketService {

    @Autowired
    repositoryTicket repositoryTicket;

    @Autowired
    repositoryBill repositoryBill;
    @Override
    public CheckInResponse checkIn(String card_code) {
        Ticket ticket = repositoryTicket.findByCardCode(card_code);
        System.out.println(card_code);
        if(ticket != null){
            Bill bill = repositoryBill.findByIdTicket(ticket);
            if(bill == null) {
                Bill billSave = Bill.builder()
                        .checkIn(new Date())
                        .status(0)
                        .ticket(ticket)
                        .build();

                repositoryBill.save(billSave);

                System.out.println("hello");
                return CheckInResponse.builder()
                        .check(1)
                        .message("Khong hop le")
                        .timeIn(new Date())
                        .car_code(ticket.getCarCode())
                        .build();
            }
        }

        return CheckInResponse.builder()
                .check(0)
                .message("Khong hop le")
                .build();
    }

    @Override
    public CheckOutResponse checkOut(String card_code) {
        Ticket ticket = repositoryTicket.findByCardCode(card_code);
        if(ticket != null){
            Bill bill = repositoryBill.findByIdTicket(ticket);
            if(bill != null){
            Bill billNew = Bill.builder()
                        .id(bill.getId())
                         .checkIn(bill.getCheckIn())
                        .checkOut(new Date())
                        .status(1)
                        .ticket(ticket)
                        .build();

                repositoryBill.save(billNew);

                return CheckOutResponse.builder()
                        .check(1)
                        .car_code(ticket.getCarCode())
                        .checkIn(bill.getCheckIn())
                        .checkOut(bill.getCheckOut())
                        .build();
            }

            return CheckOutResponse.builder()
                    .check(0)
                    .message("Khong hop le")
                    .build();

        }
        return CheckOutResponse.builder()
                .check(0)
                .message("Khong hop le")
                .build();
    }

    @Override
    public GetSlotInResponse getSlotInRequest() {
        return null;
    }
}
