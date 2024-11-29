package com.rs.iot.service.Impl;

import com.rs.iot.dao.request.LoginRequest;
import com.rs.iot.dao.response.CheckInResponse;
import com.rs.iot.dao.response.CreateUserResponse;
import com.rs.iot.dao.response.LoginResponse;
import com.rs.iot.entity.UserSystem;
import com.rs.iot.repository.repositoryUser;
import com.rs.iot.service.TicketService;
import com.rs.iot.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.List;

@Service

public class UserServiceImpl implements UserService {

    @Autowired
    repositoryUser repositoryUser ;
    BCryptPasswordEncoder encoder = new BCryptPasswordEncoder(10);

    @Override
    public CreateUserResponse createUser(UserSystem userSystem) {
        UserSystem userSystemCheck = repositoryUser.findByUserName(userSystem.getUserName());

        if(userSystemCheck == null){

            UserSystem userSystemSave = UserSystem.builder()
                    .userName(userSystem.getUserName())
                    .passWord(encoder.encode(userSystem.getPassWord()))
                    .name(userSystem.getName())
                    .phone(userSystem.getPhone())
                    .address(userSystem.getAddress())
                    .build();

            repositoryUser.save(userSystemSave);
            return CreateUserResponse.builder()
                    .check(1)
                    .message("Tao thanh cong")
                    .build();
        }
        return CreateUserResponse.builder()
                .check(0)
                .message("Tao that bai")
                .build();
    }

    @Override
    public LoginResponse loginUser(LoginRequest loginRequest) {
        UserSystem userSystem = repositoryUser.findByUserName(loginRequest.getUserName());

        if(userSystem == null){
            return LoginResponse.builder()
                    .check(0)
                    .message("Tai khoan khong ton tai")
                    .build();
        }

        boolean check = encoder.matches(loginRequest.getPassWord(), userSystem.getPassWord());

        if(!check){
            return LoginResponse.builder()
                    .check(0)
                    .message("Mat khau khong dung")
                    .build();
        }

        return LoginResponse.builder()
                .check(1)
                .message("Dang nhap thanh cong")
                .build();
    }
}
