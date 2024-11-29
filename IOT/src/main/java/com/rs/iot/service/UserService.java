package com.rs.iot.service;

import com.rs.iot.dao.request.LoginRequest;
import com.rs.iot.dao.response.CheckInResponse;
import com.rs.iot.dao.response.CreateUserResponse;
import com.rs.iot.dao.response.LoginResponse;
import com.rs.iot.entity.UserSystem;

import java.util.List;

public interface UserService {
    public CreateUserResponse createUser(UserSystem userSystem);

    public LoginResponse loginUser(LoginRequest loginRequest);
}
