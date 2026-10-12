
# **GAME DEVELOPMENT DOCUMENTATION**  
**Project Name:** gamesdl2  

---

## **I. DEVELOPMENT TIMELINE**  
Quá trình phát triển game được thực hiện theo các mốc thời gian sau:  

- **23/02:**  
  - Tìm hiểu về SDL2 và quy trình phát triển game.  
  - Cài đặt và cấu hình SDL2.  

- **24/02:**  
  - Lên ý tưởng game.  
  - Xây dựng cơ bản cấu trúc game.  
  - Viết file header.  

- **27/02:**  
  - Triển khai cơ chế di chuyển nhân vật.  
  - Tìm kiếm và thiết kế đồ họa cho game.  

- **02/03:**  
  - Phát triển menu game.  

- **07/03:**  
  - Thêm cơ chế theo dõi người chơi (player tracking).  

- **12/03:**  
  - Triển khai cơ chế "quái đột biến".  

- **17/03:**  
  - Thêm cơ chế wave (đợt quái).  

- **30/03:**  
  - Triển khai cơ chế boss.  

- **13/04:**  
  - Thêm tính năng dừng game và quay về menu.  
  - Bổ sung hệ thống năng lượng và đạn đặc biệt.  
  - Thêm 2 boss mới và cơ chế đạn của boss.  

- **16/04:**  
  - Chỉnh sửa hitbox.  
  - Cân bằng lại cơ chế máu, đạn và điểm rơi của kẻ địch.  
  - Thêm thanh máu cho người chơi.  

- **23/04:**  
  - Hoàn thiện phần kết thúc game (game over).  
  - Tối ưu code để tránh bug và nâng cao hiệu suất.  

- **24/04:**  
  - Thêm tính năng replay sau khi game over.  

---

## **II. GAME INTRODUCTION**  

### **Concept & Gameplay**  
Game lấy cảm hứng từ thể loại "bắn gà" cổ điển, với các yếu tố:  
- **Di chuyển & né đạn** – Người chơi điều khiển nhân vật để tránh đạn và tiêu diệt kẻ địch.  
- **Hệ thống wave ngẫu nhiên** – Mỗi lần chơi là một trải nghiệm khác nhau do cơ chế spawn quái được thiết kế ngẫu nhiên.  

### **Controls**  
- **Di chuyển:** Phím mũi tên (↑ ↓ ← →).  
- **Bắn đạn:** Phím **SPACE**.  
- **Sử dụng đạn đặc biệt:** Phím **1**.  
- **Restart / Quay về menu:** Phím **P**.  
 **video demo và giới thiệu ngắn về game **("https://drive.google.com/file/d/1kJi6incLzUISuAULorneqVIAJIvq4hFD/view?usp=sharing")
---


