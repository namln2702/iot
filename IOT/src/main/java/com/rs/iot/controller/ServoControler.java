package com.rs.iot.controller;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

@RestController
@CrossOrigin
@RequestMapping("/controlServo")
public class ServoControler {

    private String ipIn = "192.168.117.134";
    private String ipOut = "192.168.117.125";

    @GetMapping("/openServoIn")
    ResponseEntity<?> openServoIn(){

        RestTemplate restTemplate = new RestTemplate();
        String url = "http://"+ipIn+"/OpenServoIn"; // Địa chỉ server bạn muốn gọi

        // Gửi request GET đến server khác
        ResponseEntity<String> response = restTemplate.getForEntity(url, String.class);

        // Trả về phản hồi từ server khác
        return ResponseEntity.status(response.getStatusCode()).body(response.getBody());
    }
    @GetMapping("/closeServoIn")
    ResponseEntity<?> closeServoIn(){
        RestTemplate restTemplate = new RestTemplate();
        String url = "http://"+ipIn+"/CloseServoIn"; // Địa chỉ server bạn muốn gọi

        // Gửi request GET đến server khác
        ResponseEntity<String> response = restTemplate.getForEntity(url, String.class);

        // Trả về phản hồi từ server khác
        return ResponseEntity.status(response.getStatusCode()).body(response.getBody());
    }
    @GetMapping("/openServoOut")
    ResponseEntity<?> openServoOut(){

        RestTemplate restTemplate = new RestTemplate();
        String url = "http://"+ipOut+"/OpenServoOut"; // Địa chỉ server bạn muốn gọi

        // Gửi request GET đến server khác
        ResponseEntity<String> response = restTemplate.getForEntity(url, String.class);

        // Trả về phản hồi từ server khác
        return ResponseEntity.status(response.getStatusCode()).body(response.getBody());
    }
    @GetMapping("/closeServoOut")
    ResponseEntity<?> closeServoOut(){
        RestTemplate restTemplate = new RestTemplate();
        String url = "http://"+ipOut+"/CloseServoOut"; // Địa chỉ server bạn muốn gọi

        // Gửi request GET đến server khác
        ResponseEntity<String> response = restTemplate.getForEntity(url, String.class);

        // Trả về phản hồi từ server khác
        return ResponseEntity.status(response.getStatusCode()).body(response.getBody());
    }


}
