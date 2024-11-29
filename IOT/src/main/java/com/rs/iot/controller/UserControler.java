package com.rs.iot.controller;

import com.rs.iot.dao.request.LoginRequest;
import com.rs.iot.dao.response.CreateUserResponse;
import com.rs.iot.dao.response.LoginResponse;
import com.rs.iot.entity.UserSystem;
import com.rs.iot.service.Impl.UserServiceImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin
@RequestMapping("/user")
public class UserControler {

    @Autowired
    private UserServiceImpl userService;


    @PostMapping("/create")
    public ResponseEntity<?> create(@RequestBody UserSystem userSystem){

        CreateUserResponse createUserResponse = userService.createUser(userSystem);
        return ResponseEntity.ok().body(createUserResponse);
    }

    @PostMapping("/login")
    public ResponseEntity<?> login(@RequestBody LoginRequest loginRequest){
        LoginResponse loginResponse = userService.loginUser(loginRequest);

        return ResponseEntity.ok().body(loginResponse);
    }


}
