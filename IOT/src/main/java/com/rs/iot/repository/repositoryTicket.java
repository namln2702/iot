package com.rs.iot.repository;

import com.rs.iot.entity.Bill;
import com.rs.iot.entity.Ticket;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface repositoryTicket extends JpaRepository<Ticket, Integer> {

    @Query("select TICKET from Ticket TICKET where TICKET.cardCode = :cardCode")
    Ticket findByCardCode(@Param("cardCode")String card_code);

}
