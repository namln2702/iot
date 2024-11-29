package com.rs.iot.repository;

import com.rs.iot.entity.Bill;
import com.rs.iot.entity.Ticket;
import com.rs.iot.entity.UserSystem;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface repositoryBill extends JpaRepository<Bill, Integer> {

    @Query("select Bill from Bill Bill where Bill.status = 0 and Bill.ticket = :ticket")
    Bill findByIdTicket(@Param("ticket") Ticket ticket);
}
