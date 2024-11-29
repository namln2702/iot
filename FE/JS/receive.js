document
  .getElementById("openGateButtonIn")
  .addEventListener("click", function () {
    // Gửi yêu cầu đến server để mở cửa
    fetch("http://192.168.2.2/open-gate", {
      // Thay đổi URL nếu cần
      method: "POST",
    })
      .then((response) => {
        if (response.ok) {
          document.getElementById("message").innerText = "Cửa đã được mở!";
          document.getElementById("message").classList.add("text-success");
        } else {
          document.getElementById("message").innerText = "Có lỗi xảy ra!";
          document.getElementById("message").classList.add("text-danger");
        }
      })
      .catch((error) => {
        document.getElementById("message").innerText = "Có lỗi xảy ra!";
        document.getElementById("message").classList.add("text-danger");
      });
  });
