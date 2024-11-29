package com.rs.iot.repository;

import com.rs.iot.entity.UserSystem;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface repositoryUser extends JpaRepository<UserSystem, Integer> {

    @Query("select UserSystem  from UserSystem UserSystem where UserSystem.userName = :userName")

    UserSystem findByUserName(@Param("userName") String userName);

}
