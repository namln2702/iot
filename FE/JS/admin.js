const entryData = [];
const exitData = [];
let slotOut = {
  check: 1,
  carCode: "",
  checkIn: "",
  checkOut: "",
};

let slotIn = {
  check: 1,
  carCode: "",
  checkIn: "",
};
let count = 0;
let temp = 0;
let sumSlot = 0;
let slot1 = 0;
let slot2 = 0;
let slot3 = 0;
let slot4 = 0;

const buttonOpenServoIn = document.getElementById("openGateButtonIn");
const buttonCloseServoIn = document.getElementById("closeGateButtonIn");
const buttonOpenServoOut = document.getElementById("openGateButtonOut");
const buttonCloseServoOut = document.getElementById("closeGateButtonOut");

buttonCloseServoIn.addEventListener("click", () => {
  fetch("http://localhost:8080/controlServo/closeServoIn").then((response) => {
    if (!response.ok) {
      throw new Error("Loi servo");
    }
    console.log("close servo");
  });
});
buttonOpenServoIn.addEventListener("click", () => {
  fetch("http://localhost:8080/controlServo/openServoIn").then((response) => {
    if (!response.ok) {
      throw new Error("Loi servo");
    }
    console.log("open servo");
  });
});
buttonCloseServoOut.addEventListener("click", () => {
  fetch("http://localhost:8080/controlServo/closeServoOut").then((response) => {
    if (!response.ok) {
      throw new Error("Loi servo");
    }
    console.log("close servo");
  });
});
buttonOpenServoOut.addEventListener("click", () => {
  fetch("http://localhost:8080/controlServo/openServoOut").then((response) => {
    if (!response.ok) {
      throw new Error("Loi servo");
    }
    console.log("open servo");
  });
});

// Giả lập việc lấy dữ liệu từ backend
function fetchData() {
  //API nhiet do va trang thai bai do xe
  fetch("http://localhost:8080/tempSlot")
    .then((response) => {
      if (!response.ok) {
        throw new Error("Loi mang");
      }

      return response.json();
    })
    .then((data) => {
      temp = data.temp;
      sumSlot = data.sumSlot;
      slot1 = data.slot1;
      slot2 = data.slot2;
      slot3 = data.slot3;
      slot4 = data.slot4;
      if (temp > 70) {
        alert("Cảnh báo nhiệt độ cao");
      }
    });
  // Giả lập dữ liệu
  const temperature = temp; // Thay đổi nhiệt độ
  const availableSlots = sumSlot; // Thay đổi số slot còn trống
  const slots = [
    slot1,
    slot2,
    slot3, // Vị trí 3 trống
    slot4, // Vị trí 4 trống
  ];

  // Cập nhật nội dung
  document.getElementById("temperature").textContent = temperature.toFixed(2);
  document.getElementById("available-slots").textContent = availableSlots;
  for (let i = 0; i < slots.length; i++) {
    document.getElementById(`slot-${i + 1}`).textContent = slots[i];
  }

  // Cập nhật bảng xe vào và xe ra
  getIn();
  getOut();
  updateEntryTable();
  updateExitTable();
}

function getIn() {
  fetch("http://localhost:8080/inOut/getSlotIn")
    .then((response) => {
      if (!response.ok) {
        throw new Error("Loi getIn");
      }
      return response.json();
    })
    .then((data) => {
      if (data.checkIn != slotIn.checkIn) {
        slotIn.check = 0;
        slotIn.carCode = data.car_code;
        slotIn.checkIn = data.checkIn;
        console.log(slotIn);
      }
    });
}

function getOut() {
  fetch("http://localhost:8080/inOut/getSlotOut")
    .then((response) => {
      if (!response.ok) {
        throw new Error("Loi getOut");
      }
      return response.json();
    })
    .then((data) => {
      if (data.checkOut != slotOut.checkOut) {
        slotOut.check = 0;
        slotOut.carCode = data.car_code;
        slotOut.checkIn = data.checkIn;
        slotOut.checkOut = data.checkOut;
      }
    });
}

function updateEntryTable() {
  const entryTableBody = document.getElementById("entry-table-body");
  // // entryTableBody.innerHTML = ""; // Xóa nội dung cũ

  // if (entryData.length === 0) {
  //   entryTableBody.innerHTML = "<tr><td colspan='2'>Chưa có xe vào</td></tr>";
  // } else {
  //   entryData.forEach((entry) => {
  //     const row = `<tr>
  //                       <td>${entry.licensePlate}</td>
  //                       <td>${entry.timeIn}</td>
  //                   </tr>`;
  //     entryTableBody.innerHTML += row;
  //   });
  // }

  if (slotIn.check == 0) {
    const row = `<tr>
                    <td>${slotIn.carCode}</td>
                    <td>${updateDate(slotIn.checkIn)}</td>
                </tr>`;
    slotIn.check = 1;
    entryTableBody.innerHTML += row;
  }
}

function updateExitTable() {
  const exitTableBody = document.getElementById("exit-table-body");

  if (slotOut.check == 0) {
    slotOut.check = 1;
    const row = `<tr>
                        <td>${slotOut.carCode}</td>
                        <td>${updateDate(slotOut.checkIn)}</td>
                        <td>${updateDate(slotOut.checkOut)}</td>
                    </tr>`;
    exitTableBody.innerHTML += row;
  }
}

function updateDate(date) {
  // Lấy ngày và giờ theo định dạng mong muốn
  const newDate = new Date(date);
  const options = {
    year: "numeric",
    month: "2-digit",
    day: "2-digit",
    hour: "2-digit",
    minute: "2-digit",
    hour12: false,
  };
  let formattedDate = newDate.toLocaleString("vi-VN", options);
  console.log(formattedDate);
  return formattedDate;
}

window.onload = fetchData;
setInterval(fetchData, 2000);

// // Giả lập thêm xe vào
// function addVehicleEntry(licensePlate, timeIn) {
//   entryData.push({ licensePlate, timeIn });
//   fetchData(); // Cập nhật dữ liệu
// }

// // Giả lập thêm xe ra
// function addVehicleExit(licensePlate, timeIn, timeOut) {
//   exitData.push({ licensePlate, timeIn, timeOut });
//   fetchData(); // Cập nhật dữ liệu
// }

// Lấy dữ liệu khi tải trang
// window.onload = fetchData;

// // Cập nhật dữ liệu khi nhấn nút
// document.getElementById("refresh-button").onclick = () => {
//   // Giả lập thêm xe vào và ra
//   addVehicleEntry("29A-12345", "10:00 AM");
//   addVehicleExit("29A-12345", "10:00 AM", "11:00 AM");
// };
