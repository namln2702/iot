let buttonSubmit = document.getElementById("submit");
console.log(buttonSubmit);

buttonSubmit.addEventListener("click", (e) => {
  let userName = document.getElementById("userName").value;
  let passWord = document.getElementById("passWord").value;

  const data = {
    userName: userName,
    passWord: passWord,
  };

  const options = {
    method: "POST",
    headers: {
      "Content-Type": "application/json", // Set content type to JSON
    },
    body: JSON.stringify(data), // Convert JSON data to a string and set it as the request body
  };

  fetch("http://localhost:8080/user/login", options)
    .then((response) => {
      console.log(response);
      return response.json();
    })
    .then((dataRes) => {
      if (dataRes.check == 1) {
        window.location.href = "admin.html";
      } else {
        alert(dataRes.message);
      }
    })
    .catch((error) => {
      console.error("loi dang nhap: ", error);
    });
});
